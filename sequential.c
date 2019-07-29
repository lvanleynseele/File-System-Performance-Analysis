#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	unsigned int buffer;
	FILE *file = fopen(argv[1], "r"); //opens the file in argv[1] for reading
	if(file == NULL){
		printf("File not found\n");
		return;
	}
	while(!feof(file)){ //while not at the end of file
		fread(&buffer, 1, 1, file); //reads data from file into buffer
	}
    fclose(file); //close the file
	return 0;
} 
