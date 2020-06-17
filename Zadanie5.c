#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
    pid_t pid;
    FILE *mf;
    int i = 0;
    int array[91];
    int devide;
    
    pid = fork();
    if(pid == -1)
    {
        fprintf(stderr, "Error\n");
        return 1;
    }
    if(pid == 0)
    {
        
        mf = fopen("numbers", "w");
        if (mf == NULL)
        {
            perror("create");
            return 1;
        }
        for(i = 0; i < 91; i++)
        {
            array[i] = i+9;
        }
        for (i = 0; i < 91; i++)
        {
            devide = array[i] % 3;
            if (devide == 0) {
                fprintf(mf, "%d\n", array[i]);
            }
        }
    }
    else if (pid > 0)
    {
        int status;
        wait(&status);
        if ( WIFEXITED(status) ) {  
            printf("Child exited: %d\n", WEXITSTATUS(status) );
        }
        printf("Finished\n");
    }
}

