#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

const int ERROR_RETURN = -1;
const int FILESIZE = 134217728;
const int SECONDS_TO_MICROSECONDS = 1000000;
const char C = 'c';
const int STRING_SIZE = 80;

void writeFile(int size);

int main(){
	writeFile(2);
	writeFile(16);
	writeFile(128);
	writeFile(1026);
	writeFile(8192);
	writeFile(65536);
	return 0;
}


void writeFile(int size){
	int i, filedesc, numWrites;
	long int time_elapsed;
	struct timeval begin_time, end_time;
	char buff[size+1], writeName[STRING_SIZE], fwriteName[STRING_SIZE];

	FILE * pFile;

	sprintf(writeName,"write_%d",size);
	sprintf(fwriteName,"fwrite_%d",size);

	printf("Size: %d\n", size);

	/*write*/
	printf("///////////////////// write  //////////////////////\n");

	filedesc = open(writeName, O_RDWR | O_TRUNC | O_CREAT);

	if(filedesc < 0){
		fprintf(stderr, "Cannot open file to write to\n");
		exit(ERROR_RETURN);
	}
	
	for(i = 0; i < size; i++){
		buff[i] = C;
	}

	buff[size] = '\0';

	numWrites = FILESIZE/size;
	printf("numWrites: %d\n", numWrites);

	if(gettimeofday(&begin_time, NULL) == -1){
		fprintf(stderr, "Could not get time of day.\n");
		exit(ERROR_RETURN);
	}

	for(i = 0; i < numWrites; i++){
		write(filedesc, buff, size);
	}

	if(gettimeofday(&end_time, NULL) == -1){
		fprintf(stderr, "Could not get time of day.\n");
		exit(ERROR_RETURN);
	}

	if(close(filedesc) == -1){
		fprintf(stderr, "File could not be closed\n");
		exit(ERROR_RETURN);
	}

	time_elapsed = (SECONDS_TO_MICROSECONDS * (end_time.tv_sec-begin_time.tv_sec)) + (end_time.tv_usec - begin_time.tv_usec);

	printf("write: Time elapsed:%ld\n", time_elapsed);
	printf("write: Time per write:%f\n", (double) time_elapsed/ (double) numWrites);
	printf("write: Time per byte: %f\n\n", (double) time_elapsed/ (double) FILESIZE);


	/*fwrite*/ 

	printf("///////////////////// fwrite //////////////////////\n");

	pFile = fopen(fwriteName, "w+");

	if(pFile == NULL){
		fprintf(stderr, "fwrite: Cannot open file to write to\n");
		exit(ERROR_RETURN);
	}
	
	numWrites = FILESIZE/size;
	printf("numWrites: %d\n", numWrites);

	if(gettimeofday(&begin_time, NULL) == -1){
		fprintf(stderr, "Could not get time of day.\n");
		exit(ERROR_RETURN);
	}

	for(i = 0; i < numWrites; i++){
		fwrite(buff, sizeof(char), size, pFile);
	}

	if(gettimeofday(&end_time, NULL) == -1){
		fprintf(stderr, "Could not get time of day.\n");
		exit(ERROR_RETURN);
	}

	if(fclose(pFile) != 0){
		fprintf(stderr, "File could not be closed\n");
		exit(ERROR_RETURN);
	}

	time_elapsed = (SECONDS_TO_MICROSECONDS * (end_time.tv_sec-begin_time.tv_sec)) + (end_time.tv_usec - begin_time.tv_usec);

	printf("fwrite: Time elapsed:%ld\n", time_elapsed);
	printf("fwrite: Time per write:%f\n", (double) time_elapsed/ (double) numWrites);
	printf("fwrite: Time per byte: %f\n\n", (double) time_elapsed/ (double) FILESIZE);

}
