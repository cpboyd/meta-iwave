/** gpio_api.c
 *
 *  @Author : J.P.Raja (iWave Systems Technologies Pvt Ltd)
 *
 *  This file contains api's for buzzer.
 *
 *  Copyright (c) 2010-2012 iWave System Technologies Pvt Ltd.
 *
 *  All rights reserved. Copying, compilation, modification, distribution
 *  or any other use whatsoever of this material is strictly prohibited
 *  except in accordance with a Software License Agreement with
 *  iWave Systems Technologies Pvt Ltd.
 **/
#include <stdio.h>
#include <fcntl.h>

#define PIN_STATUS	22

enum {
        PIN1=0,
        PIN2,
        PIN3,
        PIN4,
};

int gpio_init()
{
	int fd;
	fd = open("/dev/dip_sw", O_RDWR, 0);
	if(fd < 0)
	{
		printf("cannot open device\r\n");
		return -1;
	}
	return fd;
}

int main ()
{
	int dev_fd,status;
	char usr_opt;

	dev_fd = gpio_init();	
	if (dev_fd < 0)
		return -1;

	do
	{
		printf("\r\n ***************************");
		printf("\r\n      DIP Switch Test       ");
		printf("\r\n ***************************");
		printf("\n\r A  Read DIP Switch1 status	");
		printf("\n\r B  Read DIP Switch2 status	");
		printf("\n\r C  Read DIP Switch3 status	");
		printf("\n\r D  Read DIP Switch4 status	");
		printf("\n\r X  Exit			");
		printf("\n\r Select your option:	");

		usr_opt = getchar();
		getchar();

		switch(usr_opt)
		{
			case 'A':
			case 'a':
				status=ioctl (dev_fd, PIN_STATUS, PIN1);
                                if(status == 0)
                                printf("Status of switch 1 is in OFF/LOW \r\n");
                                else
                                printf("Status of switch 1 is in ON/HIGH \r\n");
                                break;

			case 'B':
			case 'b':
				status=ioctl (dev_fd, PIN_STATUS, PIN2);
                                if(status == 0)
                                printf("Status of switch 2 is in OFF/LOW \r\n");
                                else
                                printf("Status of switch 2 is in ON/HIGH \r\n");
                                break;

			case 'C':
			case 'c':
				status=ioctl (dev_fd, PIN_STATUS, PIN3);
                                if(status == 0)
                                printf("Status of switch 3 is in OFF/LOW \r\n");
                                else
                                printf("Status of switch 3 is in ON/HIGH \r\n");
				break;

			case 'D':
			case 'd':
				status=ioctl (dev_fd, PIN_STATUS, PIN4);
                                if(status == 0)
                                printf("Status of switch 4 is in OFF/LOW \r\n");
                                else
                                printf("Status of switch 4 is in ON/HIGH \r\n");
				break;

			case 'X':
			case 'x':
				printf ("\nApplication Terminated by the User \r\n");
				//  DeInitialize the LED GPIO
				gpio_deinit(dev_fd);
				break;

			default:
				printf("Enter the correct option \r\n");
				return -1;
		}

	}
	while(usr_opt !='X' && usr_opt !='x');

	return 0;
}	

int gpio_deinit(int dev_fd)
{
        close(dev_fd);
}
