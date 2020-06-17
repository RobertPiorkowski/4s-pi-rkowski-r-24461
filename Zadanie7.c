#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<time.h>


static void sig_usr(int);
FILE *new;

int main(int argc, char *argv[]){
    pid_t pid = getpid();
    if((new = fopen("pid.txt", "w")) == NULL){
        fprintf(stderr, "Error\n");
        return 1;
    }
    fprintf(new, "Pid = %d\n", pid);
    if(signal(SIGUSR1, sig_usr) == SIG_ERR)
    {
        printf("Signal error\n");
        return 1;
    }
    if(signal(SIGUSR2, sig_usr) == SIG_ERR)
    {
        printf("Signal error\n");
    }
    while(1)
    {
        pause();
    }
    


}
static void sig_usr(int signo)
{
    if(signo == SIGUSR1)
    {
        pid_t ppid = getppid();
        fprintf(new, "PPID = %d\n", ppid);
        fclose(new);
        exit(0);
    }

    else if(signo == SIGUSR2)
    {
        new = freopen("pid.txt", "w", new);
        fclose(new);
        exit(0);
    }
    else
    {

        printf("Signal error\n");
    }

}