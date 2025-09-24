#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdint.h>
#include "adxl345/mavlink.h"           // Путь к MAVLink заголовкам
#include "adxl345/mavlink_msg_ins_accel.h"

#define UART_DEVICE "/dev/ttyUSB0"
#define BAUDRATE B115200

int main() {
    int fd = open(UART_DEVICE, O_RDONLY | O_NOCTTY);
    if (fd < 0) { perror("open"); return 1; }

    struct termios tty;
    tcgetattr(fd, &tty);
    cfsetspeed(&tty, BAUDRATE);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    tcsetattr(fd, TCSANOW, &tty);

    mavlink_message_t msg;
    mavlink_status_t status;
    unsigned char buf[256];

    while(1) {
        int n = read(fd, buf, sizeof(buf));
        for(int i = 0; i < n; i++) {
            if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status)) {
                if (msg.msgid == MAVLINK_MSG_ID_INS_ACCEL) {
                    mavlink_ins_accel_t accel;
                    mavlink_msg_ins_accel_decode(&msg, &accel);
                    // Преобразуем uint64_t в читаемый формат
                    printf("Time: %llu µs, X: %.3f, Y: %.3f, Z: %.3f\n",
                        (unsigned long long)accel.time_usec,
                        accel.x, accel.y, accel.z);
                }
            }
        }
    }

    close(fd);
    return 0;
}