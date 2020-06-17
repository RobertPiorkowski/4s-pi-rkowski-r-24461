#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]){
    FILE *directory, *reg;
    DIR *etc, *sys;
    struct dirent *dir;
    struct stat sta;
    char path[256];


    mkdir("results", (S_IRUSR | S_IWUSR | S_IXUSR));
    if((directory = fopen("results/etc_dir.out", "w")) == NULL){
        fprintf(stderr, "Creating file error\n");
        return 1;
    }
    if((reg = fopen("results/sysconfig.out", "w")) == NULL){
        fprintf(stderr, "Creating file error\n");
        return 1;
    }
    etc = opendir("/etc");
    if(etc != NULL){
        while((dir = readdir(etc)) != NULL){
            if(dir->d_type == DT_DIR){
                fprintf(directory, "%s\n", dir->d_name);
            }
        }
        closedir(etc);
    }
    sys = opendir("/etc/sysconfig/");
    if(sys != NULL){
        while((dir = readdir(sys)) != NULL){
            if(dir->d_type == DT_REG){
                memset(path,'\0',256);
                strcat(path,"/etc/sysconfig/");
                strcat(path, dir->d_name);
                if(lstat(path, &sta) == -1){
                    fprintf(stderr, "Open file %s error\n", dir->d_name);
                    return 2;
                }
                if(sta.st_mode & S_IROTH)
                    continue;
                if(sta.st_mode & S_IWOTH)
                    continue;
                if(sta.st_mode & S_IXOTH)
                    continue;
                fprintf(reg, "%s\n", dir->d_name);
                }
            }
        closedir(sys);
        }
    fclose(directory);
    fclose(reg);
    return 0;
}