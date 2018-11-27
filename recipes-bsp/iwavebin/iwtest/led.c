/** gpio_api.c
 *
 *  @Author : J.P.Raja (iWave Systems Technologies Pvt Ltd)
 *
 *  This file contains api's for LED.
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
#define LED_OFF 20
#define LED_ON 21
enum {
	LED1,
	LED2,
	LED3,
	LED4,
};

int gpio_init()
{
	int fd;
	fd = open("/dev/led", O_RDWR, 0);
	if(fd < 0)
	{
		printf("cannot open device\r\n");
		return -1;
	}
	return fd;
}

void print_info (void)
{
	printf("\r\n");
	printf("\r\n *******************");
	printf("\n\r A  LED1		");
	printf("\n\r B  LED2		");
	printf("\n\r C  LED3		");
	printf("\n\r D  LED4		");
	printf("\n\r E  Back		");
	printf("\r\n *******************");
	printf("\n\r Select your option:");

}

int main ()
{
	int dev_fd, gpio_direction;
	char usr_opt;

	dev_fd = gpio_init();	
	if (dev_fd < 0)
		return -1;

	do
	{
		printf("\r\n");
		printf("\r\n *******************");
		printf("\r\n     LED Test       ");
		printf("\r\n *******************");
		printf("\n\r A  LED ON		");
		printf("\n\r B  LED OFF		");
		printf("\n\r X  Exit		");
		printf("\n\r Select your option:");

		usr_opt = getchar ();
		getchar ();

		switch(usr_opt)
		{
			case 'A':
			case 'a':
				{
				printf ("\nNOW !! The LED lights are ready to glow \r\n");
					do
					{
						print_info ();
						usr_opt = getchar ();
						getchar ();

						switch(usr_opt)
						{
							case 'A':
							case 'a':
								printf ("LED1 ON \r\n");
								ioctl (dev_fd, LED_ON, LED1);
								break;

							case 'B':
							case 'b':
								printf ("LED2 ON \r\n");
								ioctl (dev_fd, LED_ON, LED2);
								break;

							case 'C':
							case 'c':
								printf ("LED3 ON \r\n");
								ioctl (dev_fd, LED_ON, LED3);
								break;

							case 'D':
							case 'd':
								printf ("LED4 ON \r\n");
								ioctl (dev_fd, LED_ON, LED4);
								break;

							case 'E':
							case 'e':
								printf ("\nBack To The Main Function\r\n");
								break;

							default:
								printf("Enter the correct option \r\n");
								return -1;
						}
					}
					while (usr_opt != 'E' && usr_opt != 'e');
				}
				break;

			case 'B':
			case 'b':
				{
				printf ("\nNOW !! The LED lights are going to OFF \r\n");
					do
					{
						print_info ();
						usr_opt = getchar ();
						getchar ();

						switch(usr_opt)
						{
							case 'A':
							case 'a':
								printf ("LED1 OFF \r\n");
								ioctl (dev_fd, LED_OFF, LED1);
								break;

							case 'B':
							case 'b':
								printf ("LED2 OFF \r\n");
								ioctl (dev_fd, LED_OFF, LED2);
								break;

							case 'C':
							case 'c':
								printf ("LED3 OFF \r\n");
								ioctl (dev_fd, LED_OFF, LED3);
								break;

							case 'D':
							case 'd':
								printf ("LED4 OFF \r\n");
								ioctl (dev_fd, LED_OFF, LED4);
								break;

							case 'E':
							case 'e':
								printf ("\nBack To The Main Function\r\n");
								break;

							default:
								printf("Enter the correct option \r\n");
								return -1;
						}
					} while (usr_opt != 'E' && usr_opt != 'e');
				}
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
