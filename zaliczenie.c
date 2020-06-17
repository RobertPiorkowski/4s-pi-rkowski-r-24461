#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>


int main(int argc, char *argv[])
{ 
pid_t main_pid;
pid_t s_pid;
int cat;
struct stat file_stat;
int stat;

if (argc <= 1){
	perror("Write more arguments!\n");
	return 1;
}

main_pid = fork();

if(main_pid == -1){
	perror("Error\n");
	return 2;
}

if(main_pid == 0){
	FILE *file;
	int i; 
	
	cat = mkdir("zaliczenie", 0755);
	if(cat == -1){
		perror("Can not create catalog\n");
		return 3;	
	}
	file=fopen("zaliczenie/lista.txt","w");
	if (file == NULL){
		perror("Error\n");
		return 4;
  }
	for(i=1; i<argc; i++){
		
		if(lstat(argv[i], &file_stat ) == -1){
			fprintf(file, "File %s: doesn't exist\n", argv[i]);
			continue;
		}
		else if(S_ISREG(file_stat.st_mode)){
			fprintf(file,"File %s have size: %d\n", argv[i], (int)file_stat.st_size );
			continue;
		}
		else{
			fprintf(file,"File %s: is not regular\n", argv[i]);
			continue;
		}
	}

	if( (fclose(file))== EOF ){
		fprintf(stderr, "Error\n");
	}

}

else if(main_pid > 0){
	printf("PID parent: %d\n", (int)getpid());
	s_pid = wait(&stat);
	printf("PID kid: %d\n", (int)s_pid);
	if(WIFEXITED(stat))
        {
            printf("Finished\n");
        }
		
		if(WIFSIGNALED(stat))
        {
            printf("In program was signal\n");
        }
  
		
}


return 0;
}

