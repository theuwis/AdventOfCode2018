#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define FABRIC_SIZE 2000
uint16_t fabric[FABRIC_SIZE][FABRIC_SIZE];

static uint32_t calc_nr_overlap(void){
	uint32_t answer = 0;

	for(int i = 0; i < FABRIC_SIZE; i++){
		for(int j = 0; j < FABRIC_SIZE; j++){
			if(fabric[i][j] > 1) answer++;
		}
	}

	return answer;
}

static void place_fabric(uint16_t left, uint16_t top, uint16_t width, uint16_t height){
	for(int i = left; i < left + width; i++){
		for(int j = top; j < top + height; j++){
			fabric[i][j]++;
		}
	}
}

static void parse_line(char * line){
	char * substr;
	uint16_t left, top, width, height;

	substr = strstr(line, "@ ");
	substr += 2;
	left = atoi(substr);
	substr = strstr(substr, ",");
	substr += 1;
	top = atoi(substr);
	substr = strstr(substr, " ");
	substr += 1;
	width = atoi(substr);
	substr = strstr(substr, "x");
	substr += 1;
	height = atoi(substr);

	place_fabric(left, top, width, height);
}

static void parse_data(void){
	char * data_read = NULL;
	size_t len; ssize_t read;
	FILE *fp;

	// open the file
	if(!(fp = fopen("data", "r"))){
		fprintf(stderr, "Error opening file\n");
		exit(EXIT_FAILURE);
	}

	// parse each ID
	while((read = getline(&data_read, &len, fp)) != -1){
		data_read[strcspn(data_read, "\r\n")] = '\0';
		parse_line(data_read);
	}

	free(data_read);
	fclose(fp);
}

int main(void){
	parse_data();
	printf("answer=%d\n", calc_nr_overlap());
	
	return EXIT_SUCCESS;
}