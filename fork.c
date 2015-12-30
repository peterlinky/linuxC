/*************************************************************************
    >文件名称: fork.c
    >程序功能:检验fork函数返回值
    >注意事项：
    >创建时间: 2014年12月10日 星期三 19时50分30秒
    >保持好奇，虚心接受
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#define FALSE 0
#define TRUE 1
#define OK 1
#define ERROR 0
#define MAXSIZE 100


int main(int argc, char *argv[])
{
	pid_t pid;	//pid_t为头文件<sys.types.h>中int的宏定义
	pid = fork();
	switch(pid)

	{
		case 0:

			while(1){
				int fd;
				char *s = "hello\n";

				if((fd = open("test.txt", O_RDWR|O_CREAT|O_APPEND, 0770)) ==-1){
				perror("open");
				exit(-1);
			}
				if(write(fd, s, strlen(s)) == -1){
					perror("write");
					exit(-1);
				}
				sleep(1);
			}
		case -1:
			printf("Process creation faild\n");
			break;
		default:
			while(1){
					int fd;
					char *buf;
					bzero(buf,1024);
					if((fd = open("test.txt", O_RDWR))==-1){
						perror("open");
						exit(-1);
					}
					if(read(fd, buf, 1024) == -1){
						perror("read");
						exit(-1);
					}
					printf("%s\n", buf);					
					sleep(3);

			}	

	}
}
