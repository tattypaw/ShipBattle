#include "player.h"

void Player::PrintShips() {
	cout << "\t";
	for (int i = 0; i < 10; ++i) {
		cout << char(i+97) << ' ';
	}
	cout << "\t\t\t";
	for (int i = 0; i < 10; ++i) {
		cout << char(i + 97) << ' ';
	}
cout << endl;
	for (int j = 0; j < 10; ++j) {
cout << j+1<<'\t';
		for (int i = 0; i < 10; ++i) {
			cout << ships[i][j] << ' ';
		}
		cout << "\t\t";
		cout << j + 1 << '\t';
		for (int i = 0; i < 10; ++i) {
			cout << hits[i][j] << ' ';
		}
		cout << endl;
	}
}