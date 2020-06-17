#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>


int main(int argc, const char * argv[])
{
    int catalog, openFlags, etc_dir, sysconfig;
    FILE *mf;
    FILE *mf1;
    DIR *d1;
    struct dirent *dir;
    DIR *d2;
    struct dirent *dir2;
    
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;

    printf("\n\nCreate a catalog: results\n");
    catalog = mkdir("results", (S_IRUSR | S_IWUSR | S_IXUSR | S_IXGRP | S_IXOTH));
    
    mf = fopen ("results/etc_dir.out", "w");
    if (mf == NULL)
    {
        perror("create");
        return 1;
    }
    
    mf1 = fopen ("results/sysconfig.out", "w");
    if (mf1 == NULL)
    {
        perror("create");
        return 1;
    }    
    
    d1 = opendir("/etc");
    if(d1 != NULL)
    {
        while((catalog = readdir(d1)) != NULL)
        {
            if(catalog->d_type == DT_DIR) {
                //printf("\t%s\n", dir2->d_name);
                fprintf(mf, "\t%s\n", catalog->d_name);
                
            }
        }
        closedir(d1);
    }
    else
    {
        printf("Open dir error\n");
    }
    
    d2 = opendir("/etc/sysconfig/");
    if(d2 != NULL)
    {
        while((dir2 = readdir(d2)) != NULL)
        {
            if(dir2->d_type == DT_DIR) {
                //printf("\t%s\n", dir2->d_name);
                fprintf(mf1, "\t%s\n", dir2->d_name);
            }
        }
        closedir(d2);
    }
    else
    {
        printf("Open dir /etc/sysconfig error\n");
    }
    
    fclose(mf);
    fclose(mf1);

    return 0;;
}

