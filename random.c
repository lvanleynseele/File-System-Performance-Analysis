#include <stdio.h>
#include <stdlib.h>
/*sequentialRead will read generated files using a random pattern(reading bytes from random locations).*/

int main(int argc, char*argv[]) {
	if(argc<2) {
        printf("invalid fileName \n");
        return 1;
	}
	
	
	
	FILE *file = fopen(argv[1], "r");
    if(file == NULL){
        printf("File not found\n");
        return;
    }
	fseek(file, 0L, SEEK_END); //set position indicator with no offset from eof
	long long file_ptr;ftell(file);
	rewind(file); //go to beginning of file
    
    long long rand_char;
    int i=0;
	for(i=0; i<file_ptr; i++){
		rand_char = rand(); //choose a random byte
		fseek(file, file_ptr*rand_char/RAND_MAX, SEEK_SET);  //find that byte in file
	}
	fclose(file); //close the file
    return 0;
}

