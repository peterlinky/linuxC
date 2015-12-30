#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

//显示错误信息
void seerror(const char *error_string, int line)
{
	perror(error_string);
}

void fun(char *buf, int *argcount, char arglist[100][256]);	/* 对输入命令进行解析 */
void do_cmd(int argcount, char arglist[100][256]);			/* 执行命令 */


//对输入命令进行解析
void fun(char *buf, int *argcount, char a[100][256])
{
	int i, j;
	int d;

	j = 0;
	d = 0;
	for (i = 0; *(buf + i) != '\0'; i++) {
		if (*(buf + i) != ' ') {
			a[d][j] = *(buf + i);
			j++;
			a[d][j] = '\0';
		} else {
			d++;
			j = 0;
		}
	}
	*argcount = d + 1;

}

//执行命令
void do_cmd(int argcount, char arglist[100][256])
{
	int flag = 0;
	int status;
	int i;
	int fd;
	char *arg[argcount + 1];
	char *argnext[argcount + 1];
	char *file;
	pid_t pid;
	//取出命令
	for (i = 0; i < argcount; i++)

	{
		arg[i] = (char *) arglist[i];
	}
	arg[argcount] = NULL;
	pid = fork();


	if(pid == 0){	
		if (execvp(arg[0], arg) == 0)

		{
			printf("%s: command not found\n", arg[0]);
		exit(0);
		}
	}

	if (waitpid(pid, &status, 0) == -1)
		printf("wait for child process error\n");
}

int main(void)
{
	char *buf;		//记录输入的命令
	int argcount;		//记录参数个数
	char arglist[100][256];	//解析出来的参数
	int i;			//循环变量

	while(1)
	{
		printf("myshell: ");
		buf = malloc(1024);
		gets(buf);
		if ((strcmp("quit", buf) == 0))

		{
			free(buf);
			exit(0);
		}
		argcount = 0;
		for (i = 0; i < 100; i++)

		{
			arglist[i][0] = '\0';
		}


		fun(buf, &argcount, arglist);

		do_cmd(argcount, arglist);
		free(buf);

	}

	exit(1);
}
