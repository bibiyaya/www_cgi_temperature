#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "ds18b20.h"

unsigned short ds18b20_fun(void)
{
	int fd;
	int ret;
	float temp;
	unsigned short data;
	
	fd = open("/dev/TX2440-ds18b20", 0);
	if (fd < 0)
	{
		perror("open device ds18b20");
		exit(1);
	}

	ret = read(fd,&data,4);
	if(ret<0)
		printf("read ds18b20 error\n");

	return data;
	close(fd);	
}