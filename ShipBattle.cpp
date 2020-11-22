// ShipBattle.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "player.h"
#include <ctime>

using namespace std;

int InputX() {
	bool errorColumn;
	int x;
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
				x = int(column) - 97;
				errorColumn = 0;
			}
		} while (errorColumn);
		return x;
	};
int InputY() {
	bool errorY;
	int y;
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
			errorY = 0;
		}
	} while (errorY);
	return y;
};

int main()
{
	setlocale(LC_ALL, "Russian");

	Player player;
	Player computer;
	int x, y, countPlayer = 0, countComputer = 0;
	bool KeyPressed = false;
	
	//Правила игры и заполнение данных
	cout << "Игровое поле представляет собой квадрат 10 на 10 клеток." << endl;
	cout << "\t";
	for (int i = 0; i < 10; ++i) {
		cout << char(i + 97) << ' ';
	}
	cout << endl;
	for (int j = 0; j < 10; ++j) {
		cout << j + 1 << "\t";
		for (int i = 0; i < 10; ++i) {
			cout << "0" << ' ';
		}
		cout << endl;
	}
	cout << "На поле игрока пустые клетки обозначаются нулями, клетки в которых расположены корабли единицами." << endl;
	cout << "Рядом с полем игрока показывается пустое поле (заполнено нулями), на котором будут отмечаться ходы игрока и их результат." << endl;
	cout << "При попадании в корабль клетка обозначается двойкой. При промахе клетка обозначается тройкой." << endl;

	cout << "Флот каждого игрока состоит из 10 кораблей:" << endl;
	cout << "- 4 однопалубных" << endl;
	cout << "- 3 двухпалубных" << endl;
	cout << "- 2 трехпалубных" << endl;
	cout << "- 1 четырехпалубный" << endl;
	cout << "Все суда сторонами или углами не могут касаться друг друга." << endl;
	cout << "Все суда ориентированы по вертикали или горизонтали." << endl;
	cout << "---------------------------------------------------------------------------" << endl << endl;

	int choice = 0;
	do {
		cout << "Выберите способ заполнения игрового поля: 1 - вручную; 2 - автоматически. Ваш выбор: "; cin >> choice;
		if (choice == 1) {
			player.InputShips();
		}
		else if (choice == 2) { player.InitShips(); }
		else { cout << "Не понял Ваш выбор. Введите 1 (заполнение вручную) или 2 (автоматическое заполнение)." << endl; }
	} while (choice != 1 && choice != 2);
	player.InitHits();
	computer.InitShips();
	computer.InitHits();
	do {
		bool result = 0;
		do {
			system("cls");
			cout << "Счет: Игрок - " << countPlayer << "\t\tКомпьютер - " << countComputer << endl;
			cout << "---------------------------------------------------------------------------------" << endl;
			cout << "\tВаше поле" << "\t\t\t\t" << "Ваши выстрелы" << endl;
			player.PrintShips();
			cout << "Ваш ход." << endl;

			x = InputX();
			y = InputY();

			if (player.hits[x][y] != 0) {
				cout << "Вы уже стреляли по этому месту." << endl;
				result = 0;
			}
			else if (computer.ships[x][y] == 1) {
				cout << "Попали!" << endl;
				result = 1;
				computer.ships[x][y] = 2;
				player.hits[x][y] = 2;
			}
			else {
				cout << "Промах!" << endl;
				result = 0;
				player.hits[x][y] = 3;
			}
			if (result == 1) {
				bool kill = 0;
				int south = 0;
				int nord = 0;
				int west = 0;
				int east = 0;
				int s = 0;
				if (y != 0) { nord = computer.ships[x][y - 1]; }
				if (y != 9) { south = computer.ships[x][y + 1]; }
				if (x != 0) { west = computer.ships[x - 1][y]; }
				if (x != 9) { east = computer.ships[x + 1][y]; }
				s = south + west + nord + east;
				switch (s) {
				case 0: {
					kill = 1;
					break; }
				default:
				{if (nord == 2 || south == 2) {
					int yTop = y;
					do {
						if (computer.ships[x][yTop] > 0) {
							yTop = yTop - 1;
						}
					} while (yTop > 0 && computer.ships[x][yTop] > 0);
					int size = 0;
					int number = 0;
					do {
						if (computer.ships[x][yTop] != 0) {
							size++;
						}
						if (computer.ships[x][yTop] == 2) {
							number++;
						}
						yTop = yTop + 1;
					} while (computer.ships[x][yTop] != 0 && yTop < 10);
					if (number == size) { kill = 1; }
				}
				else if (west == 2 || east == 2) {
					int xLeft = x;
					do {
						if (computer.ships[xLeft][y] > 0) {
							xLeft = xLeft - 1;
						}
					} while (xLeft > 0 && computer.ships[xLeft][y] > 0);
					int size = 0;
					int number = 0;
					do {
						if (computer.ships[xLeft][y] != 0) {
							size++;
						}
						if (computer.ships[xLeft][y] == 2) {
							number++;
						}
						xLeft = xLeft + 1;
					} while (computer.ships[xLeft][y] != 0 && xLeft < 10);
					if (number == size) { kill = 1; }
				}
				break;
				}
				}
				if (kill) {
					cout << "Корабль потоплен!" << endl;
					countPlayer++;
				}
			}
			cout << "Для продолжения работы программы нажмите любую клавишу...";
			system("pause");
			
		} while (result && countPlayer < 10);
		if (countPlayer == 10) { break; }
		do {
			system("cls");
			cout << "Счет: Игрок - " << countPlayer << "\t\tКомпьютер - " << countComputer << endl;
			cout << "---------------------------------------------------------------------------------" << endl;
			cout << "\tВаше поле" << "\t\t\t\t" << "Ваши выстрелы" << endl;
			player.PrintShips();
			cout << "Ход компьютера." << endl;
			do {
				x = rand() % 10;
				y = rand() % 10;
			} while (computer.hits[x][y] != 0);
			cout << "Column = " << char(x + 97) << "\tRow = " << y + 1 << endl;
				if (player.ships[x][y] == 1) {
				cout << "В Вас попали!" << endl;
				result = 1;
				player.ships[x][y] = 2;
				computer.hits[x][y] = 2;
			}
			else {
				cout << "Компьютер промахнулся!" << endl;
				result = 0;
				computer.hits[x][y] = 3;
			}
			if (result == 1) {
				bool kill = 0;
				int south = 0;
				int nord = 0;
				int west = 0;
				int east = 0;
				int s = 0;
				if (y != 0) { nord = player.ships[x][y - 1]; }
				if (y != 9) { south = player.ships[x][y + 1]; }
				if (x != 0) { west = player.ships[x - 1][y]; }
				if (x != 9) { east = player.ships[x + 1][y]; }
				s = south + west + nord + east;
				switch (s) {
				case 0: {
					kill = 1;
					break; }
				default:
				{if (nord == 2 || south == 2) {
					int yTop = y;
					do {
						if (player.ships[x][yTop] > 0) {
							yTop = yTop - 1;
						}
					} while (yTop > 0 && player.ships[x][yTop] > 0);
					int size = 0;
					int number = 0;
					do {
						if (player.ships[x][yTop] != 0) {
							size++;
						}
						if (player.ships[x][yTop] == 2) {
							number++;
						}
						yTop = yTop + 1;
					} while (player.ships[x][yTop] != 0 && yTop < 10);
					if (number == size) { kill = 1; }
				}
				else if (west == 2 || east == 2) {
					int xLeft = x;
					do {
						if (player.ships[xLeft][y] > 0) {
							xLeft = xLeft - 1;
						}
					} while (xLeft > 0 && player.ships[xLeft][y] > 0);
					int size = 0;
					int number = 0;
					do {
						if (player.ships[xLeft][y] != 0) {
							size++;
						}
						if (player.ships[xLeft][y] == 2) {
							number++;
						}
						xLeft = xLeft + 1;
					} while (player.ships[xLeft][y] != 0 && xLeft < 10);
					if (number == size) { kill = 1; }
				}
				break;
				}
				}
				if (kill) {
					cout << "Корабль потоплен!" << endl;
					countComputer++;
				}
			}
			cout << "Для продолжения работы программы нажмите любую клавишу...";
			system("pause");
		} while (result && countComputer < 10);
	}while (countPlayer!=10&&countComputer!=10);
	system("cls");
	cout << "Счет: Игрок - " << countPlayer << "\t\tКомпьютер - " << countComputer << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "\tВаше поле" << "\t\t\t\t" << "Ваши выстрелы" << endl;
	player.PrintShips();
	if (countPlayer == 10) {cout << "ПОЗДРАВЛЯЕМ!!!!  ВЫ ВЫИГРАЛИ!!!" <<endl;}
	else { cout << "ВЫ ПРОИГРАЛИ!!!" << endl; }
	cout << "Для продолжения работы программы нажмите любую клавишу...";
	system("pause");
}