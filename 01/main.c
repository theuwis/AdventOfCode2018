#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parse_data(void){
	char * data_read = NULL;
	size_t len; ssize_t read;
	int32_t result = 0;
	FILE *fp;

	// open the file
	if(!(fp = fopen("data", "r"))){
		fprintf(stderr, "Error opening file\n");
		return EXIT_FAILURE;
	}

	// convert the text on each line to int
	while((read = getline(&data_read, &len, fp)) != -1){
		result += atoi(data_read);
	}

	fclose(fp);
	return result;
}

int main(void){
	printf("answer=%d\n", parse_data());
	
	return EXIT_SUCCESS;
}