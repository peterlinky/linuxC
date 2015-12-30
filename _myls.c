#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<grp.h>
#include<pwd.h>

#define P_MaxName 125
int display(char* name);

void display_attribute(struct stat buf, char *name);
int display_dir(char *PathName);

int main(int argc, char *argv[]){
	
	char PathName[P_MaxName];
	int l;
	//
	if(argc == 1){
		strcpy(PathName, ".");
	//	PathName[1] = '\0';
	}else{
		l = strlen(argv[1]);
		strcpy(PathName, argv[1]);
	//	PathName[l] = '\0';

	}


	display_dir(PathName);
	return 0;
}

int display_dir(char *PathName){

	DIR *dir;
	struct dirent *ptr;
	char filename[256][P_MaxName+1];
	int count = 0;
	int i;
	int len = strlen(PathName);

	if((dir = opendir(PathName)) == NULL){
		perror("opendir");
		exit(-1);

	}

	while((ptr = readdir(dir)) != NULL){
		if((strcmp(ptr->d_name, ".") !=0)&&(strcmp( ptr->d_name,"..")!=0)){ 
		strcpy(filename[count], PathName);
		strcat(filename[count], "/");
		strcat(filename[count], ptr->d_name);
		filename[count][len+strlen(ptr->d_name)+1] = '\0';
		count++;	
		}
	}

	for( i = 0; i<count; i++){
		display(filename[i]);
	}

	closedir(dir);
	return 0;
}


int display(char *name){

	struct stat buf;
	
	if(lstat(name,&buf)==-1){
		perror("lstat");
		exit(-1);
	}

	display_attribute(buf, name);
	printf("\t%s\n" ,name);
	return 0;
}


/*获取文件属性并打印*/
void display_attribute(struct stat buf, char *name)
{
    char buf_time[32];
    struct passwd *psd;     //从该结构体中获取文件所有者的用户名
    struct group *grp;      //从该结构体中获取文件所有者所在组名

    /*获取并打印文件类型*/
    if(S_ISLNK(buf.st_mode))
    {
        printf("l");
    }
    else if(S_ISREG(buf.st_mode))
    {
        printf("-");
    }
    else if(S_ISDIR(buf.st_mode))
    {
        printf("d");
    }
    else if(S_ISCHR(buf.st_mode))
    {
        printf("c");
    }
    else if(S_ISBLK(buf.st_mode))

	{
        printf("b");
    }
    else if(S_ISFIFO(buf.st_mode))

	{
        printf("f");
    }
    else if(S_ISSOCK(buf.st_mode))
    {
        printf("s");

	}


    /*获取并打印文件所有者的权限*/
    if(buf.st_mode & S_IRUSR)

	{
        printf("r");
    }else{
		printf("-");
	}
    if(buf.st_mode & S_IWUSR)

	{
        printf("w");
    }else{
		printf("-");
	}
    if(buf.st_mode & S_IXUSR)
    {
        printf("x");

	}else
    {
        printf("-");

	}


    /*获取并打印与文件所有者同组的用户对文件的权限*/
    if(buf.st_mode & S_IRGRP)
    {
        printf("r");
    }else{
		printf("-");
	}
    if(buf.st_mode & S_IWGRP)
    {
        printf("w");
    }else{
		printf("-");
	}
    if(buf.st_mode & S_IXGRP)
    {
        printf("x");
    }else{
		printf("-");
	}


    /*获取并打印其他用户对该文件的权限*/
    if(buf.st_mode & S_IROTH)
    {
        printf("r");
    }else{
		printf("-");
	}
    if(buf.st_mode & S_IWOTH)
    {
        printf("w");
    }else{
		printf("-");
	}
    if(buf.st_mode & S_IXOTH)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }


    printf("    ");

    /*根据uid与gid获取文件所有者的用户名与组名*/
    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);
    printf("%4d", buf.st_nlink);        //打印文件连接数
    printf("%-8s", psd->pw_name);
    printf("%-8s", grp->gr_name);

    printf("%6d", buf.st_size);         //打印文件大小
    strcpy(buf_time, ctime(&buf.st_mtime));
    buf_time[strlen(buf_time) - 1] = '\0';      //去掉换行符
    printf("  %s", buf_time);                   //打印文件时间信息

}
