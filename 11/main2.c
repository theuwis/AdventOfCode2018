#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

#define GRID_SN 7347
int32_t power_grid[300][300];

struct identifier {
	uint16_t x;
	uint16_t y;
	uint16_t size;
	int32_t power;
} identifier;

void find_square(uint16_t size){
	for(int y = 0; y < 300 - size; y++){
		for(int x = 0; x < 300 - size; x++){
			int32_t result = 0;
			for(int j = y; j < y + size; j++){
				for(int i = x; i < x + size; i++){
					result += power_grid[i][j];
				}
			}
			
			if(result > identifier.power){
				identifier.x = x + 1;
				identifier.y = y + 1;
				identifier.size = size;
				identifier.power = result;
			}
		}
	}
}

int main(void){
	for(int x = 0; x < 300; x++){
		for(int y = 0; y < 300; y++){
			int32_t power = ((((x + 1) + 10) * (y + 1)) + GRID_SN) * ((x + 1) + 10);

			if((power < 100) & (power > -100)){
				power = 0;
			}
			else{
				int32_t temp_power = (int32_t) floor((abs(power)/100) % 10);

				(power < 0) ? (power = -temp_power) : (power = temp_power);
			}

			power_grid[x][y] = (power - 5);
		}
	}

	identifier.power = 0;
	for(int size = 0; size < 300; size++){
		find_square(size);
	}
	
	printf("%d,%d,%d (power=%d)\n", identifier.x, identifier.y, identifier.size, identifier.power);

	return EXIT_SUCCESS;
}