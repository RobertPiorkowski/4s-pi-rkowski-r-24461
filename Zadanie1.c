#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {

int fd_input, fd_output;
ssize_t size;
char file[255] = "";
char buff[1];
int i;

if (argc != 2) {
	perror("No arguments");
	return 1;
}

fd_input = open(argv[1], O_RDONLY);
    
    if (fd_input == -1) {
        
        perror("Input error");
        return 2;
    }
    
strcpy(file, argv[1]);
strcat(file, ".red"); 
 
fd_output = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd_output == -1) {  
        perror("Output error");
        return 2;
    }
    
i= 0;

while (read(fd_input, &buff, 1) == 1) {
	
	if( (i % 3) == 0) {

		size = write(fd_output, &buff, 1);
		
		if (size == -1){
			perror("Save error");
			continue;
		}
	}
	i++;
}
    close (fd_output);
    close (fd_input);
    return 0;
	
}