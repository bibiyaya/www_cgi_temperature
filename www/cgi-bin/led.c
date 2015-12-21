#include"led.h"

void led_fun(int *led_config)
{
	unsigned int led_num = 0;
	int led_fd = open("/dev/TX2440-led", O_RDWR);	// open LED Device

	for (led_num = 0; led_num < 4; led_num++)
	{
		ioctl(led_fd, led_config[led_num], led_num);
	}
	
	close(led_fd);
}
