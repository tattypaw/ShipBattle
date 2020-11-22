#include "player.h"

void Player::InitHits() {
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			hits[i][j] = 0;
		}
	}
}