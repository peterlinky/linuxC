#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<signal.h>

void readfile(int fd);
void writefile(int fd);

int main(int argc, char *argv[])
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
        exit(-1);

    pid_t pid;
    pid = fork();
	
	switch(pid){

		case -1:
			exit(-1);
		case 0:
			//关闭写入端
			close(pipefd[1]);
			//从管道中读取
			readfile(pipefd[0]);
			exit(0);
		default:
			//关闭读出端
			close(pipefd[0]);
			//向管道中写入内容
			writefile(pipefd[1]);
			exit(0);
	}
	return 0;
}

void readfile(int fd){
	char message[1024];
	//读取管道内容
	read(fd, message, 1024);
	int fd_2 = open("./test_1.txt", O_RDWR|O_APPEND);
	//写入到目标文件
	write(fd_2, message, strlen(message)+1);
}

void writefile(int fd){
	char message[1024];
	int fd_1 = open("test.txt", O_RDWR);
	//从原文件中读取内容
	read(fd_1, message, 1024);
	//写入管道
	write(fd, message, strlen(message)+1);
}	
