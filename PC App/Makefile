
TARGET = pc_app

SRCS = main.c

CC = gcc
CFLAGS = -O3 -Wall -Wextra -march=native
LDFLAGS = 

INCLUDES = -I src/adxl345

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean