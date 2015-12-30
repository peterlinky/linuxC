/*实现rm 命令*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<dirent.h>
#include<string.h>


int my_rm(char *filename);
int get_Name(char *filename);

int main(int argc, char *argv[])
{
	if(argc < 2){
		printf("rm <filename>");
	}else{
		my_rm(argv[1]);
	}

	return 0;
}

int my_rm(char *filename)
{
	int flag = 0;
	//检测当前文件夹是否存在所要删除的文件
	flag = get_Name(filename);	

	if(flag){
		//如果文件存在则删除
		if(unlink(filename) == -1){
			perror("unlink");
			exit(1);
		}
	}else{
		printf("文件不存在，无法删除\n");
		exit(0);
	}
	return 0;	
}

int get_Name(char * filename)
{
	//获取当前目录下的文件名
	//若有要删除的文件返回1 否则返回0
	DIR *dir;
	struct dirent *ptr;
	int flag = 0;

	if((dir = opendir(".")) == NULL){
		perror("opendir");
		exit(1);
	}else{
		while((ptr = readdir(dir)) != NULL){
			if(strcmp(ptr->d_name, filename) == 0)
				flag = 1;
		}
	}

	return flag;
}	
