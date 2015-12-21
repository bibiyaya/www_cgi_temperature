#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *str_len=NULL;
	int len=0;
	char buf[100]="";	
	char user[20]="";
	char passwd[20]="";
	
	printf("%s\r\n\r\n","Content-Type:text/html");
	printf("<html>\n<head>\n<title>CGI3:登录结果</title></head><br>\n");
	str_len = getenv("CONTENT_LENGTH");	
	if( (str_len==NULL)  || (sscanf(str_len, "%d", &len)!=1) || (len>80) )
		printf("sorry!error!");
	fgets(buf, len+1, stdin);	
	sscanf(buf, "name=%[^&]&password=%s", user,passwd);
	if( (strncmp(user,"root",4)==0) && (strncmp(passwd, "111111", 6)==0) )
	{
		printf("<script language=\"JavaScript\">self.location='main.cgi';</script>");
	}
		
	else
		printf("<h1>Sorry! 用户名或密码错误！");	
	return 0;
}