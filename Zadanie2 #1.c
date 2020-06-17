#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>


int randoRange(int low, int up)
{

	int number;
	number = (rand() % (up - low +1) + low);
	return number;

}

int main(int argc, char *argv[])
{
    const int low = 10, up = 99;
    int fd, repeats = 0, number[10];
    char buf[40];
    if(argc != 2){
        char filename[20];
        fprintf(stdout,"Enter the file name ");
        fscanf(stdin, "%s", filename);
        printf("File name:  %s\n", filename);
        fd = open(filename, O_CREAT | O_RDWR, 0644);
        for(;repeats < 10; repeats++){
            number[repeats] = randoRange(low, up);
            snprintf(buf, 40, "%d", number[repeats]);
            write(fd,buf,4);
            write(fd, "\n", 2);
        }
        
        close(fd);
    }
    if(argc == 2){
        fd = open(argv[1], O_CREAT | O_RDWR, 0644);
        for(;repeats < 10; repeats++){
            number[repeats] = randoRange(low, up);
            printf("%d\n", number[repeats]);
            snprintf(buf, 40, "%d", number[repeats]);
            write(fd,buf,4);
            write(fd, "\n", 2);
        }
    close(fd);
    }
}