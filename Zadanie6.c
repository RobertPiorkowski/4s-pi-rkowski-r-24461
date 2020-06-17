#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main(void)
{
    pid_t pid;
    pid_t ch_pid;
    int stat;
    int ret;

    pid = fork();
    if(pid == -1)
    {
        fprintf(stderr, "Error\n");
        return 1;
    }
    if(pid == 0)
    {
        sleep(10);
        printf("Child Pid: %d\n", (int) getpid());
        printf("Fork returned: %d\n", (int) pid);
        // _exit(1);
        abort();
    }
    if(pid > 0)
        {
            printf("Parent Pid: %d\n", (int) getpid());
            printf("Fork returned: %d\n", (int) pid);
            ch_pid = wait(&stat);
            printf("Pid %d ended. Exit status: %d\n", (int) ch_pid, WEXITSTATUS(stat));
            if(WIFEXITED(stat))
            {
                printf("Normal execution\n");
            }
            if(WIFSIGNALED(stat))
            {
                printf("Program signaled\n");
            }
        }
    printf("Before exec\n");
    ret = execlp("ls", "ls", "-a", NULL);
    if (ret == -1)
    {
        fprintf(stderr, "error\n");
        return 1;
    }
    printf ("Finished\n");
    return 0;
       
    
}
