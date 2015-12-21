#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
#include "led.h"
#include "adc.h"
#include"ds18b20.h"

void config(int *led_config,int led_num);

int main()
{
	int led_num=0;
	int adc_data = 0;
	float tmp_temp;
	unsigned short tmp_data;
	int led_config[8]={0,0,0,0};
	FILE *fp_html;
	char buf[512]="";
	char *len;
	printf("%s\r\n\r\n","Content-Type:text/html");	
	len = getenv("CONTENT_LENGTH");
	if(len != NULL)	
	{ 
		unsigned int content_len = 0;
		char *data;
		content_len = atoi(len);
		data = malloc(content_len + 1);
		read(0, data, content_len);	
		sscanf(data,"led%d",&led_num);
		free(data);
	}
	else 
	{
		led_num=0;
	}
	config(led_config,led_num);
	
	led_fun(led_config);	
	if( (fp_html=fopen("main_html","r")) == NULL)
	{
		exit(1);
	}
	while(fgets(buf,512,fp_html))
	{
		if(strncmp(buf,"$FLAG1$",7)==0)
		{
			tmp_data = ds18b20_fun();
			tmp_temp = tmp_data * 0.0625;
			tmp_data = tmp_temp * 10 + 0.5;
			if (tmp_data < 1000)
				printf("&nbsp;&nbsp;%2d.%d ¡æ\n", tmp_data/10, tmp_data%10);
			else
				printf("&nbsp;&nbsp;85.0 ¡æ\n");
		}
		else if(strncmp(buf,"$FLAG2$",7)==0)
		{
			adc_data = adc_fun(0);
			printf("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%2d %\n", (adc_data/11));
		}
		else if(strncmp(buf,"$FLAG3$",7)==0)
		{
			adc_data = adc_fun(1);
			printf("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%2d %\n", (adc_data/11));
		}
		
		else if(strncmp(buf,"$FLAG4$",7)==0)
		{			
			int i=0;
			for(i=0; i < 4; i++)
			{
				if(led_config[i]==0)
				{
					printf("<img src=\"../image/off.png\" width=30 height=30 hspace=45 >");
				}
				else 
				{
					printf("<img src=\"../image/on.png\" width=30 height=30 hspace=45 >");
				}
			}
		}

		else 
			printf("%s",buf);	
	}
	return 0;				
}

void config(int *led_config,int led_num)
{
	FILE *fp;
	if((fp=fopen("config.ini","r+"))==NULL)
	{
		printf("<p>fopen Error!<a href=\"/cgi-bin/main.cgi\">Return/a>");
		exit(1);
	}
	fscanf(fp,"led1=%d,led2=%d,led3=%d,led4=%d",led_config,led_config+1,led_config+2,led_config+3);
	
	if(led_num > 0)
	{
		if(led_config[led_num-1]==1)
		{
			led_config[led_num-1] = 0;
		}	
		else 
		{
			led_config[led_num-1] = 1;
		}
		fseek(fp,7*(led_num-1)+5,SEEK_SET);
		fprintf(fp,"%d",led_config[led_num-1]);
	}
	fclose(fp);
}
