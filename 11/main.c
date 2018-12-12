#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

#define GRID_SN 7347
int32_t power_grid[300][300];

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

	int32_t answer = 0;
	int16_t x_coord, y_coord;
	for(int y = 0; y < 300 - 3; y++){
		for(int x = 0; x < 300 - 3; x++){
			int32_t result = power_grid[x][y]     + power_grid[x + 1][y]     + power_grid[x + 2][y] +
			                 power_grid[x][y + 1] + power_grid[x + 1][y + 1] + power_grid[x + 2][y + 1] +
			                 power_grid[x][y + 2] + power_grid[x + 1][y + 2] + power_grid[x + 2][y + 2];
			
			if(result > answer){
				x_coord = x + 1;
				y_coord = y + 1;
				answer = result;
			}
		}
	}

	printf("%d,%d (power=%d)\n", x_coord, y_coord, answer);

	return EXIT_SUCCESS;
}