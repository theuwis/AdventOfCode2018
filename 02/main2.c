#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define NR_OF_IDS 250
#define ID_LEN    26

static void find_string(char ids[NR_OF_IDS][ID_LEN + 1]){
	uint32_t nr_of_diff_chars = 0;


	for(int i = 0; i < NR_OF_IDS - 1; i++){
		for(int j = i + 1; j < NR_OF_IDS - 2; j++){
			for(int k = 0; k < ID_LEN; k++){
				if(ids[i][k] != ids[j][k]) nr_of_diff_chars++;
			}
		
		if(nr_of_diff_chars == 1){
			uint8_t diff_found_flag = 0;

			for(int k = 0; k < ID_LEN; k++){
				if(ids[i][k] != ids[j][k]){
					diff_found_flag = 1;
				}
				if(diff_found_flag){
					ids[i][k] = ids[i][k + 1];
				}
			}

			printf("answer=%s\n", ids[i]);
			return;
		}

		nr_of_diff_chars = 0;
		}
	}
}

static void parse_data(void){
	char * data_read = NULL;
	size_t len; ssize_t read;
	FILE *fp;

	char strings[NR_OF_IDS][ID_LEN + 1];
	uint32_t curr_line = 0;

	// open the file
	if(!(fp = fopen("data", "r"))){
		fprintf(stderr, "Error opening file\n");
		exit(0);
	}

	// parse each ID
	while((read = getline(&data_read, &len, fp)) != -1){
		data_read[strcspn(data_read, "\r\n")] = '\0';

		strncpy(strings[curr_line], data_read, ID_LEN + 1);
		curr_line++;
	}

	fclose(fp);
	find_string(strings);
}

int main(void){
	parse_data();
	
	return EXIT_SUCCESS;
}