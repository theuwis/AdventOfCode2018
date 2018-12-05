#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

static bool check_freq(int32_t freq_array[], int32_t freq, int16_t nr_of_freq){
	for(int i = 0; i < nr_of_freq; i++){
		if(freq_array[i] == freq){
			return true;
		}
	}
	return false;
}

static int32_t parse_data(void){
	char * data_read = NULL;
	size_t len; ssize_t read;
	int32_t result = 0, result_array[1000000];
	uint32_t curr_freq = 0;
	FILE *fp;

	if(!(fp = fopen("data", "r"))){
		fprintf(stderr, "Error opening file\n");
		return EXIT_FAILURE;
	}

	while(!check_freq(&result_array[0], result, curr_freq - 1)){
		if((read = getline(&data_read, &len, fp)) == -1){
			rewind(fp);
			read = getline(&data_read, &len, fp);
		}
		
		result += atoi(data_read);
		result_array[curr_freq] = result;

		curr_freq++;
	}

	fclose(fp);
	return result_array[curr_freq - 1];
}

int main(void){
	printf("answer=%d\n", parse_data());
	
	return EXIT_SUCCESS;
}