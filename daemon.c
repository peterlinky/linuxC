#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/param.h>
#include<sys/stat.h>
#include<time.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<syslog.h>
int init_daemon(void);


int main(void){
	time_t now;
	int fd;
	char *s = "hello\n";

	//创建守护进程
	init_daemon();

	//守护进程间隔向文件写入数据
	while(1){
		if((fd = open("/home/linky/Coding/linuxc/test.log", O_RDWR|O_CREAT|O_APPEND, 0744)) == -1){
			perror("open");
			exit(-1);
		}
		if((write(fd, s, strlen(s))) == -1){
			perror("write");
			exit(-1);
		}
		sleep(3);
		close(fd);
	}

}

int init_daemon(void){
	int pid;
	int i;

	pid = fork();
	//使子进程在后台进行
	if(pid > 0){
		exit(0);
	}else if(pid < 0){
		exit(-1);
	}
	//让进程成为无终端的会话组长
	setsid();

	pid = fork();
	//使进程不在成为会话组长
	if(pid > 0){
		exit(0);
	}else if(pid < 0){
		exit(-1);
	}

	//关闭从父进程继承的文件描述符
	for(i = 0; i < NOFILE; i++){
		close(i);
	}
	//修改根目录
	chdir("/");
	//权限修饰位
	umask(0);

	return 0;
}
