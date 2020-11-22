#include "player.h"
#include <string>
#include <ctime>

void Player::InitShips() {
	int shipSize[10] = { 4,3,3,2,2,2,1,1,1,1};
	int orientation = 1;
	int x = 0, y = 0;
	srand(static_cast<int>(time(NULL)));

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			ships[i][j] = 0;
		}
	}

	for (int i = 0; i < 10; ++i) {
		int size;
		size = shipSize[i];
		bool flag=0;
		do {
		orientation= (rand() % 2);
		x = rand() % 10; 
		y = rand() % 10;
		
			int s = 0;
			if (orientation == 1) {
				for (int j = 0; j < size; ++j) {
					if (y != 0) { s = s + ships[x + j][y - 1]; }
					if (y != 9) { s = s + ships[x + j][y + 1]; }
				}
				if (x != 0) {
					if (y != 0) { s = s + ships[x - 1][y - 1]; }
					if (y != 9) { s = s + ships[x - 1][y + 1]; }
					s = s + ships[x - 1][y];
				}
				if (x + size - 1 != 9) {
					if (y != 0) { s = s + ships[x + size][y - 1]; }
					if (y != 9) { s = s + ships[x + size][y + 1]; }
					s = s + ships[x + size][y];
				}
			}
			else {
				for (int j = 0; j < size; ++j) {
					if (x != 0) { s = s + ships[x - 1][y + j]; }
					if (x != 9) { s = s + ships[x + 1][y + j]; }
				}
				if (y != 0) {
					if (x != 0) { s = s + ships[x - 1][y - 1]; }
					if (x != 9) { s = s + ships[x + 1][y - 1]; }
					s = s + ships[x][y - 1];
				}
				if (y + size - 1 != 9) {
					if (x != 0) { s = s + ships[x - 1][y + size]; }
					if (x != 9) { s = s + ships[x + 1][y + size]; }
					s = s + ships[x][y + size];
				}
			}
			if (s > 0) {
				flag = 1;
			}
			else { flag = 0; }
		} while (flag);
		if (orientation == 1) {
			for (int j = x; j < x + size; ++j) {
				ships[j][y] = 1;
			}
		}
		else {
			for (int j = y; j < y + size; ++j) {
				ships[x][j] = 1;
			}
		}
	}

}