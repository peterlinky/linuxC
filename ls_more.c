#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<signal.h>

int main(int argc, char *argv[])
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
        exit(-1);

    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
	exit(-1);
    }

    if (pid == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO); //输出重定向
        close(pipefd[1]);
        close(pipefd[0]);
        execlp("ls", "ls", NULL);
        fprintf(stderr, "error execute ls\n");
        exit(-1);
    }

    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    close(pipefd[1]);
    execlp("more", "more",  NULL);
    fprintf(stderr, "error execute wc\n");
    exit(-1);

	    return 0;
}
