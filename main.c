#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

const int ERROR_RETURN = -1;
const int FILESIZE = 134217728;

int main(){
	

}


void writeFile(int size){
	printf("Size: %d\n", size);
	
	int filedesc = open("test.txt", OWRONLY | O_APPEND);
	if(filedesc < 0){
		fprintf(stderr, "Cannot open file to write to\n");
		exit(ERROR_RETURN);
	}
	
	char buff[FILESIZE];

	while(write(filedesc, buff, size) > 0){
		
	}
	printf("Successfully wrote to file\n");
}
