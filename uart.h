/*
 * uart.h
 *
 *  Created on: Aug 5, 2019
 *      Author: cristian
 */

#include <termios.h>
#include <unistd.h>

#ifndef SRC_UART_H_
#define SRC_UART_H_

#define UART_FAILURE -1
#define UART_SUCCESS 0

#define DEBUG

struct UartDevice {
	char* name;
	int rate;

	int fd;
	struct termios *tty;
};

int uartStart(struct UartDevice* dev, unsigned char canonic);
int uartSend(struct UartDevice* dev, char *data, int size);
int uartReceive(struct UartDevice* dev, char* data, int size_max);
int uartStop(struct UartDevice* dev);

#endif /* SRC_UART_H_ */
