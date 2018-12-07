#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

#define NR_OF_IDS   1365
#define FABRIC_SIZE 2000
uint16_t fabric[FABRIC_SIZE][FABRIC_SIZE];

struct claim {
	uint16_t id;
	uint16_t left;
	uint16_t top;
	uint16_t width;
	uint16_t height;
};
struct claim claims[NR_OF_IDS];


static bool check_claim(struct claim claim_to_check){
	for(int i = claim_to_check.left; i < (claim_to_check.left + claim_to_check.width); i++){
		for(int j = claim_to_check.top; j < (claim_to_check.top + claim_to_check.height); j++){
			if(fabric[i][j] > 1) return false;
		}
	}

	printf("answer=%d\n", claim_to_check.id);
	return true;
}

static void find_answer(void){
	for(int i = 0; i < NR_OF_IDS; i++){
		if(check_claim(claims[i])){
			return;
		}
	}
}

static void place_fabric(uint16_t left, uint16_t top, uint16_t width, uint16_t height){
	for(int i = left; i < left + width; i++){
		for(int j = top; j < top + height; j++){
			fabric[i][j]++;
		}
	}
}

static void parse_line(char * line, struct claim * temp_claim){
	char * substr;
	uint16_t id, left, top, width, height;

	line += 1;
	id = atoi(line);

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

	temp_claim->id     = id;
	temp_claim->left   = left;
	temp_claim->top    = top;
	temp_claim->width  = width;
	temp_claim->height = height;
}

static void parse_data(void){
	char * data_read = NULL;
	size_t len; ssize_t read;
	uint16_t curr_line = 0;
	FILE *fp;

	if(!(fp = fopen("data", "r"))){
		fprintf(stderr, "Error opening file\n");
		exit(EXIT_FAILURE);
	}

	while((read = getline(&data_read, &len, fp)) != -1){
		data_read[strcspn(data_read, "\r\n")] = '\0';
		parse_line(data_read, &claims[curr_line]);
		curr_line++;
	}

	find_answer();

	free(data_read);
	fclose(fp);
}

int main(void){
	parse_data();
	
	return EXIT_SUCCESS;
}