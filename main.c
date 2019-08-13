/*
 *  Created on: Aug 5, 2019
 *      Author: Cristian Fatu
 *      This project implements a basic UART communication over UART on Petalinux, unsing Uart Lite linux driver.
 *      The hardware platform implements an UART Lite IP core and the device tree (in pl.dtsi) sets the appropriate parameters.  After booting linux, the "/dev/ttyUL1" must be present.
 */

#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include "uart.h"

#define MAX_RECV_SIZE 235

int main()
{
	char data[MAX_RECV_SIZE];
	char data1[MAX_RECV_SIZE + 20];
	int received;
	int sent;
	int rc;


	struct UartDevice dev;

	dev.name = "/dev/ttyUL1";
	dev.rate = B9600;
	printf("UART Demo\n");
	rc = uartStart(&dev, 0);
	if (rc) {
		return rc;
	}
	sent = uartSend(&dev, "UART Demo\r\n", -1);
	printf("sent %d characters\r\n", sent);


	while (1) {
		received = uartReceive(&dev, data, MAX_RECV_SIZE);	// receive text over UART
		if(received > 0)
		{
			printf("received %d characters: %s\n", received, data);
			sprintf(data1, "Received : %s", data);
			sent = uartSend(&dev, data1, -1);	// send the received text over UART
			printf("loopback %d characters\r\n", sent);
		}
	}

	uartStop(&dev);

    return 0;
}
