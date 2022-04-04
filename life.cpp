#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <chrono>
#include <thread>

#define ON 1
#define OFF 0

const int x_N = 40;
const int y_N = 25;

int getRandBool() {
    // return the pseudo-random value
      // functions: rand()
    return (rand()% (2));
}

void random_grid(int gameboard[y_N][x_N]) {
	for(int i = 0;i < y_N;i++) {
		for(int j = 0;j < x_N;j++) {
			gameboard[i][j] = getRandBool();
		}
	}
}

void blank_grid(int gameboard[y_N][x_N]) {
	for(int i = 0;i < y_N;i++) {
		for(int j = 0;j < x_N;j++) {
			gameboard[i][j] = 0;
		}
	}
}

int neighbors(int gameboard[y_N][x_N], int rowind, int colind) {
	int num_neighbors = 0;

	if(colind > 0) {
		num_neighbors += gameboard[rowind][(colind-1)%x_N];
	}
	if(rowind > 0) {
		num_neighbors += gameboard[(rowind-1)%y_N][colind];
	}
	if(colind < x_N) {
		num_neighbors += gameboard[rowind][(colind+1)%x_N];
	}
	if(rowind < y_N) {
		num_neighbors += gameboard[(rowind+1)%y_N][colind];
	}
	if(rowind > 0 && colind > 0) {
		num_neighbors += gameboard[(rowind-1)%y_N][(colind-1)%x_N];
	}
	if(rowind < y_N && colind < x_N) {
		num_neighbors += gameboard[(rowind+1)%y_N][(colind+1)%x_N];
	}
	if(rowind > 0 && colind < x_N) {
		num_neighbors += gameboard[(rowind-1)%y_N][(colind+1)%x_N];
	}
	if(rowind < y_N && colind > 0) {
		num_neighbors += gameboard[(rowind+1)%y_N][(colind-1)%x_N];
	}

	return num_neighbors;
}

void update(int gameboard[y_N][x_N]) {
	int cloneboard[y_N][x_N];

	for(int i = 0;i < y_N;i++) {
		for(int j = 0;j <x_N;j++) {
			cloneboard[i][j] = gameboard[i][j];
		}
	}
	// loop through arrays
	for(int i = 0;i < y_N;i++) {
		for(int j = 0;j <x_N;j++) {
			// check game rules
			 // if populated
			if(gameboard[i][j] == ON) {
				// underpopulation
				if(neighbors(gameboard, i, j) < 2) {
					cloneboard[i][j] = 0;
				}
				// overpopulation
				if(neighbors(gameboard, i, j) > 3) {
					cloneboard[i][j] = 0;
				}

			} else { // otherwise not populated
				if(neighbors(gameboard, i, j) == 3) {
					cloneboard[i][j] = 1;
				}
			}	
		}
	}
	for(int i = 0;i < y_N;i++) {
		for(int j = 0;j <x_N;j++) {
			gameboard[i][j] = cloneboard[i][j];
		}
	}
}

void display_game(int gameboard[y_N][x_N]) {
	for(int i = 0;i < y_N;i++) {
		for(int j = 0;j < x_N;j++) {
			if(gameboard[i][j] == 1) {
				printf(" \x1B[92m%d\033[0m", gameboard[i][j]);
			}
			else {
				printf(" \x1B[34m%d\033[0m", gameboard[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n================================================\n");
}

void draw_corona(int gameboard[y_N][x_N], int row, int col) {
	gameboard[row][col+6] = 1;
	gameboard[row+1][col+5] = 1;
	gameboard[row+2][col+5] = 1;
	gameboard[row+1][col+7] = 1;
	gameboard[row+2][col+7] = 1;
	gameboard[row+3][col+6] = 1;
	gameboard[row+4][col+4] = 1;
	gameboard[row+4][col+8] = 1;
	gameboard[row+5][col+1] = 1;
	gameboard[row+5][col+2] = 1;
	gameboard[row+6][col] = 1;
	gameboard[row+6][col+3] = 1;
	gameboard[row+7][col+1] = 1;
	gameboard[row+7][col+2] = 1;
	gameboard[row+8][col+4] = 1;
	gameboard[row+9][col+6] = 1;
	gameboard[row+10][col+5] = 1;
	gameboard[row+11][col+5] = 1;
	gameboard[row+12][col+6] = 1;
	gameboard[row+10][col+7] = 1;
	gameboard[row+11][col+7] = 1;
	gameboard[row+8][col+8] = 1;
	gameboard[row+6][col+9] = 1;
	gameboard[row+5][col+10] = 1;
	gameboard[row+5][col+11] = 1;
	gameboard[row+6][col+12] = 1;
	gameboard[row+7][col+10] = 1;
	gameboard[row+7][col+11] = 1;
}

void draw_glider(int gameboard[y_N][x_N], int row, int col) {
	gameboard[row][col+1] = 1;
	gameboard[row+1][col+2] = 1;
	gameboard[row+2][col] = 1;
	gameboard[row+2][col+1] = 1;
	gameboard[row+2][col+2] = 1;
}

int main(int argc, char *argv[]) {
	using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
	using namespace std;

	// create board
	int gameboard[y_N][x_N];
	// set random seed
	srand(time(NULL));
	// fill board
	string rand_choice = "--random";

	if(argc == 2) {
		string rand_inp = string(argv[1]);
		if(rand_inp.compare(rand_choice)==0) {
			random_grid(gameboard);
		}
	} else if(argc < 2) {
		// clear board
		blank_grid(gameboard);
		
		// standard gliders
		draw_glider(gameboard, rand()%y_N, rand()%x_N);
		draw_glider(gameboard, rand()%y_N, rand()%x_N);
		draw_glider(gameboard, rand()%y_N, rand()%x_N);

		// Corona entity
		draw_corona(gameboard, 9, 9);
	}

	// test board for ending game later
	int testboard[y_N][x_N];
	blank_grid(testboard);

	// enter game loop
	bool gameloop = true;
	// iteration counter
	int iterations = 0;

	while(gameloop) {
		display_game(gameboard);
		update(gameboard);
		iterations += 1;
		sleep_until(system_clock::now() + nanoseconds(100000000));
		int change_tester = 0;
	
		// loop to determine if board changed	
		for(int i = 0;i < y_N;i++) {
			for(int j = 0;j < x_N;j++) {
				if(testboard[i][j]==gameboard[i][j]) {
					change_tester += 1;
				}
			}
		}
		if(change_tester == (y_N*x_N)) {
			printf("Lasted for %d generations", iterations);
			gameloop = false;
		}

		// loop to set testboard
		for(int i = 0;i < y_N;i++) {
			for(int j = 0;j < x_N;j++) {
				testboard[i][j] = gameboard[i][j];
			}
		}
	}

	return 0;
}
