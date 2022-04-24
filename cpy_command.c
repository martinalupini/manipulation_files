//in input --> nome file dove vado a copiare altro file
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>

#define fflush(stdin)  while(getc(stdin)!='\n')
#define BUFF_SIZE 1024

#ifdef DEBUG
#define print(s, ...)  printf("%s\n", s, ##__VA_ARGS__)
#else
#define print(s, ...)
#endif

int main(int argc, char **argv){
	struct dirent *dirp;
	DIR *dp;
	char *sn, buff[BUFF_SIZE];
	int sd, dd, act_read, written;

	if(argc < 2){
		printf("Usage: ./cpy name_new_file.\n");
		exit(EXIT_FAILURE);
	}

	//opening and printing of the content of current directory
	dp = opendir(".");
	while( (dirp= readdir(dp)) != NULL ){	
		printf("%s\n", dirp->d_name);
		//fflush(stdout);    perchè dava problemi?
	}
	closedir(dp);
	
	//inserting the name of source file
	printf("Insert the name of a file you want to copy: ");
	scanf("%ms", &sn);
	fflush(stdin);
	puts("");
	
	//opening of files
	dd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0660);
	sd = open(sn, O_RDONLY);
	if( dd == -1 || sd ==-1){
		printf("Error on the opening of files.\n");
		exit(EXIT_FAILURE);
	}

	//cpy operation
	do{
		act_read = read(sd, buff, BUFF_SIZE);
		if( act_read ==-1){
			printf("Error on reading the file.\n");
			exit(EXIT_FAILURE);
		}

		written = write(dd, buff, act_read);
		if(written < act_read || written ==-1){
			printf("Error on writing the new file.\n");
			exit(EXIT_FAILURE);
		}

	}while( written > 0);

	close(sd);
	close(dd);

	return 0;
}

