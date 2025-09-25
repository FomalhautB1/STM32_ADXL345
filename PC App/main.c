#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdint.h>
#include "src/adxl345/mavlink.h"
#include "src/adxl345/mavlink_msg_ins_accel.h"

#define UART_DEVICE "/dev/ttyUSB0"
#define BAUDRATE B115200
#define READ_BUF_SIZE 256
#define PRINT_BUF_SIZE 4096  // Буфер для вывода

int main() {
    // Открываем UART неблокирующим для быстрого чтения
    int fd = open(UART_DEVICE, O_RDONLY | O_NOCTTY | O_NONBLOCK);
    if (fd < 0) { perror("open"); return 1; }

    // Настройка UART
    struct termios tty;
    if(tcgetattr(fd, &tty) != 0) { perror("tcgetattr"); return 1; }
    cfsetspeed(&tty, BAUDRATE);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_oflag &= ~OPOST;
    tcsetattr(fd, TCSANOW, &tty);

    mavlink_message_t msg;
    mavlink_status_t status;
    unsigned char buf[READ_BUF_SIZE];
    char print_buf[PRINT_BUF_SIZE];
    int print_pos = 0;

    while(1) {
        int n = read(fd, buf, sizeof(buf));
        if (n > 0) {
            for (int i = 0; i < n; i++) {
                if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status)) {
                    if (msg.msgid == MAVLINK_MSG_ID_INS_ACCEL) {
                        mavlink_ins_accel_t accel;
                        mavlink_msg_ins_accel_decode(&msg, &accel);

                        // Формируем строку в буфер
                        print_pos += snprintf(print_buf + print_pos, PRINT_BUF_SIZE - print_pos,
                            "Time: %llu µs, X: %.3f, Y: %.3f, Z: %.3f\n",
                            (unsigned long long)accel.time_usec,
                            accel.x, accel.y, accel.z);

                        // Если буфер почти заполнен, выводим и сбрасываем
                        if (print_pos > PRINT_BUF_SIZE - 128) {
                            fwrite(print_buf, 1, print_pos, stdout);
                            print_pos = 0;
                        }
                    }
                }
            }
        }
        else if (n == -1) {
            // Нет данных сейчас, можно чуть подождать
            usleep(1000);  // 1 мс, чтобы не загружать CPU на 100%
        }

        // Периодически сбрасываем буфер, если есть данные
        if (print_pos > 0) {
            fwrite(print_buf, 1, print_pos, stdout);
            print_pos = 0;
        }
    }

    close(fd);
    return 0;
}