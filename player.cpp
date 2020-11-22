#include "player.h"
#include <string>

int InputSize(int ship1, int ship2, int ship3, int ship4) {
	bool error = 0;
	int shipSize = 0;
	do {	
		error = 0;
		
		cout << "Введите размер корабля: 1-,2-,3- или 4-палубный (ожидается ввод числа от 1 до 4) ";
		cin >> shipSize;
		if (shipSize > 4 || shipSize < 1) {
			cout << "Внимательно прочитайте правила: такой размер задавать нельзя!" << endl;
			error = 1;
		}
		else {
			switch (shipSize) {
			case 1:
				if (ship1 >= 4) {
					cout << "Количество однопалубных кораблей выше, заданных правилом." << endl;
					error = 1;
				}
				else {
					return shipSize;
				}
			case 2:
				if (ship2 >= 3) {
					cout << "Количество двухпалубных кораблей выше, заданных правилом." << endl;
					error = 1;
				}
				else {
					return shipSize;
				}
			case 3:
				if (ship3 >= 2) {
					cout << "Количество трехпалубных кораблей выше, заданных правилом." << endl;
					error = 1;
				}
				else {
					return shipSize;
				}
			default:
				if (ship4 >= 1) {
					cout << "Количество четырехпалубных кораблей выше, заданных правилом." << endl;
					error = 1;
				}
				else {
					return shipSize;
				}
			}
		} 
		
	}while (error);
}

int InputOrientation(int size) {
	bool error = 0;
	do {
		error = 0;
		char orient;
		if (size == 1) {
			return 1;
		}
		else {
			cout << "Введите ориентацию корабля: v - вертикальная, h - горизонтальная ";
			cin >> orient;
			if (orient == 'h') {
				return 1;
			}
			else if (orient == 'v') {
				return 2;
			}
			else {
				cout << "Внимательно прочитайте правила: такой ориентации не существует!" << endl;
				error = 1;
			}
		}
	} while (error);
	cout << endl;
}


void Player::InputShips() {
	//заполнить поле игрока
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			ships[i][j] = 0;
		}
	}
	cout << "Введите данные о своих кораблях, соблюдая правила." << endl;
	
	int size = 0, x, y;
	int orientation;
	int ship1 = 0, ship2 = 0, ship3 = 0, ship4 = 0;
	bool error = 0;

	for (int i = 0; i < 10; ++i) {
		cout << endl;
		cout << "Введите данные " << i << "-го корабля." << endl;
		cout << "Вы ввели: "  << endl;
		cout << "    четырехпалубных - " << ship4 << endl;
		cout << "    трехпалубных - " << ship3 << endl;
		cout << "    двухпалубных - " << ship2 << endl;
		cout << "    однопалубных - " << ship1 << endl;
		
		size = InputSize(ship1, ship2, ship3, ship4);
		if (size == 1) {
			ship1++;
		}
		else if (size == 2) {
			ship2++;
		}
		else if (size == 3) {
			ship3++;
		}else{
			ship4++;
		}
		orientation = InputOrientation(size);
		bool errorColumn;
		cout << "Введите координаты корабля." << endl;
		cout << "Для многопалубных кораблей берутся координаты верхней левой клетки из занятых кораблем." << endl;
		cout << "Сначала вводится буква, обозначающая столбец, потом вводится число, обозначающее ряд." << endl;
		cout << "Номер столбца задается латинской буквой нижнего регистра." << endl<<endl;
		do {
			errorColumn = 0;
			do {
				cout << "Введите номер столбца: ";
				char column;
				cin >> column;
				if (column < 'a' || column >= 'k') {
					cout << "Внимательно прочитайте правила: такой координаты не существует!" << endl;
					errorColumn = 1;
				}
				else {
					if (column == 'a') {
						x = 0;
					}
					else if (column == 'b') {
						x = 1;
					}
					else if (column == 'c') {
						x = 2;
					}
					else if (column == 'd') {
						x = 3;
					}
					else if (column == 'e') {
						x = 4;
					}
					else if (column == 'f') {
						x = 5;
					}
					else if (column == 'g') {
						x = 6;
					}
					else if (column == 'h') {
						x = 7;
					}
					else if (column == 'i') {
						x = 8;
					}else{x = 9;
					}
				}
			} while (errorColumn);

			bool errorY;
			do {
				errorY = 0;
				cout << "Введите номер строки: ";
				cin >> y;
				if (y < 1 || y > 10) {
					cout << "Внимательно прочитайте правила: такой координаты не существует!" << endl;
					errorY = 1;
				}
				else {
					y = y - 1;
				}
			} while (errorY);
			//проверка размещения
			bool flag;
			int s = 0;
				if (orientation == 1) {
					for (int j = 0; j < size; ++j) {
						if (y!=0) { s = s + ships[x + j][y - 1]; }
						if (y!=9) { s = s + ships[x + j][y + 1]; }
					}
					if (x != 0) {
						if (y != 0) { s = s + ships[x - 1][y - 1]; }
						if (y != 9) { s = s + ships[x - 1][y + 1]; }
						s = s + ships[x - 1][y];
						}
					if (x+size-1 != 9) { 
						if (y != 0) {s = s + ships[x + size][y - 1]; }
						if (y != 9) {s = s + ships[x + size][y + 1]; }
						s = s + ships[x + size][y]; 
						}
					}
					else {
					for (int j = 0; j < size; ++j) {
						if (x != 0) { s = s + ships[x - 1][y+j]; }
						if (x != 9) { s = s + ships[x + 1][y+j]; }
						}
					if (y != 0) {
						if (x != 0) { s = s + ships[x - 1][y - 1]; }
						if (x != 9) { s = s + ships[x + 1][y - 1]; }
						s = s + ships[x][y-1];
						}
					if (y+size-1 != 9) {
						if (x != 0) { s = s + ships[x -1][y + size]; }
						if (x != 9) { s = s + ships[x + 1][y + size]; }
						s = s + ships[x ][y + size];
						}
					}
				if (s > 0) {
					flag = 1;
					cout << "Проверьте размещение, ваши корабли соприкасаются." << endl << "Все введенные значения обнуляются."<<endl;
					for (int i = 0; i < 10; ++i) {
						for (int j = 0; j < 10; ++j) {
							ships[i][j] = 0;
						}
					}
						ship1 = 0;
						ship2 = 0;
						ship3 = 0;
						ship4 = 0;
						error = 1;
				}
				else {
					error=0;
				}
		} while (error);
		//заполнение поля с кораблями
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

