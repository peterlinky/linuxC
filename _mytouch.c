/*实现touch命令*/


#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<utime.h>


int touchFile(char *filename);


int main(int argc, char *argv[])
{
	if(argc < 2){
		printf("touch <filename>\n");
		exit(1);
	}else{
		touchFile(argv[1]);
	}
	return 0;
}

int touchFile(char *filename)
{
	struct utimbuf buf;
	int fd;

	if(fd = open(filename, O_RDWR|O_CREAT, 110) == -1){
		if(utime(filename,NULL) == -1){
			perror("utime");
			exit(1);
		}
	}
	close(fd);
	return 0;
}
