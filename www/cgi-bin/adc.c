#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "adc.h"

int adc_fun(int ch)
{
	int fd;
	int ret;
	int data;	
	
	fd = open("/dev/TX2440-adc", 0);  //打开设备
	if (fd < 0)
	{
		perror("open device adc");
		exit(1);
	}
	
	ret = ioctl(fd, ch, 0);   //选择通道
	if(ret<0)
        perror("ioctl set adc channel error");
		
	ret = read(fd,&data,4);	
	if(ret<0)
	  printf("error\n");
	  
	return data;
	close(fd);

}
