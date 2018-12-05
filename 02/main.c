#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

uint32_t nr_twice = 0, nr_thrice = 0;

static void check_id(char * id){
	uint8_t counts[26], id_len = strlen(id), twice_flag = 0, thrice_flag = 0;

	memset(counts, 0, 26);

	// count occurrences of each letter of the alphabet
	for(int i = 0; i < id_len; i++){
		counts[id[i] - 'a']++;
	}

	// check if letters appear two or three times (only count one letter!)
	for(int i = 0; i < 26; i++){
		if((counts[i] == 2) && (twice_flag == 0)){
			nr_twice++;
			twice_flag = 1;
		}

		if((counts[i] == 3) && (thrice_flag == 0)){
			nr_thrice++;
			thrice_flag = 1;
		}
	}
}

static uint32_t parse_data(void){
	char * data_read = NULL;
	size_t len; ssize_t read;
	int32_t result = 0;
	FILE *fp;

	// open the file
	if(!(fp = fopen("data", "r"))){
		fprintf(stderr, "Error opening file\n");
		return EXIT_FAILURE;
	}

	// parse each ID
	while((read = getline(&data_read, &len, fp)) != -1){
		data_read[strcspn(data_read, "\r\n")] = '\0';
		check_id(data_read);
	}

	fclose(fp);
	return result;
}

int main(void){
	parse_data();
	printf("answer=%d\n", nr_twice * nr_thrice);
	
	return EXIT_SUCCESS;
}