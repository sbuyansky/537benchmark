#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

const int ERROR_RETURN = -1;
const int FILESIZE = 134217728;
const int SECONDS_TO_MICROSECONDS = 1000000;
const int STRING_SIZE = 80;

void writeFile(int size);

int main(){
	writeFile(2);
	writeFile(16);
	writeFile(128);
	writeFile(1024);
	writeFile(8192);
	writeFile(65536);
	return 0;
}


void writeFile(int size){
	int i, filedesc, numWrites;
	long int time_elapsed;
	struct timeval begin_time, end_time;
	char buff[size], writeName[STRING_SIZE], fwriteName[STRING_SIZE];

	FILE * pFile;

	/*prepare file names*/

	sprintf(writeName,"/tmp/write_%d",size);
	sprintf(fwriteName,"/tmp/fwrite_%d",size);

	/*write*/

	printf("///////////////////// write %d //////////////////////\n", size);

	/*open file for writing*/

	filedesc = open(writeName, O_RDWR | O_CREAT | O_TRUNC, 0777);

	if(filedesc < 0){
		fprintf(stderr, "write: cannot open file to write to\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(ERROR_RETURN);
	}
	
	/*calculate the number of writes to be done*/

	numWrites = FILESIZE/size;
	printf("numWrites: %d\n", numWrites);

	/*get starting time*/

	if(gettimeofday(&begin_time, NULL) == -1){
		fprintf(stderr, "Could not get time of day.\n");
		exit(ERROR_RETURN);
	}

	/*perform writes*/

	for(i = 0; i < numWrites; i++){
		write(filedesc, buff, size);
	}

	/*get end time*/

	if(gettimeofday(&end_time, NULL) == -1){
		fprintf(stderr, "Could not get time of day.\n");
		exit(ERROR_RETURN);
	}

	/*close file */

	if(close(filedesc) == -1){
		fprintf(stderr, "File could not be closed\n");
		exit(ERROR_RETURN);
	}

	/*calculate time elapsed in microseconds */

	time_elapsed = (SECONDS_TO_MICROSECONDS * (end_time.tv_sec-begin_time.tv_sec)) + (end_time.tv_usec - begin_time.tv_usec);

	/*print out statistics */

	printf("write: Time elapsed:%ld\n", time_elapsed);


	/*fwrite*/ 

	printf("///////////////////// fwrite %d //////////////////////\n", size);
	
	/*open file*/

	pFile = fopen(fwriteName, "w+");

	if(pFile == NULL){
		fprintf(stderr, "fwrite: Cannot open file to write to\n");
		exit(ERROR_RETURN);
	}
	
	printf("numWrites: %d\n", numWrites);

	/*get starting time */

	if(gettimeofday(&begin_time, NULL) == -1){
		fprintf(stderr, "Could not get time of day.\n");
		exit(ERROR_RETURN);
	}

	/*perform writes */

	for(i = 0; i < numWrites; i++){
		fwrite(buff, sizeof(char), size, pFile);
	}

	/*get end time*/

	if(gettimeofday(&end_time, NULL) == -1){
		fprintf(stderr, "Could not get time of day.\n");
		exit(ERROR_RETURN);
	}

	/*close file */

	if(fclose(pFile) != 0){
		fprintf(stderr, "File could not be closed\n");
		exit(ERROR_RETURN);
	}

	/*calculate time elapsed in microseconds */

	time_elapsed = (SECONDS_TO_MICROSECONDS * (end_time.tv_sec-begin_time.tv_sec)) + (end_time.tv_usec - begin_time.tv_usec);

	/*print out statistics*/

	printf("fwrite: Time elapsed:%ld\n", time_elapsed);
}
