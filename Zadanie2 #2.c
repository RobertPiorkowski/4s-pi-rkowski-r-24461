#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[]){

    int fd_in, num, repeats = 1;
    char buf[60];


    if(argc != 2){
        fprintf(stderr, "Write file name to open\n");
        return 1;

    }
    fd_in = open(argv[1], O_RDONLY);
    for(; repeats < 11; repeats++){
        read(fd_in, &buf, 2);
        lseek(fd_in, 4, SEEK_CUR);
        num = atoi(buf) * 3;
        printf("%d\n", num);
    }
    return 0;


}