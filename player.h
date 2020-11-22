#pragma once
#include <iostream>
using namespace std;

class Player
{
public:
	bool defeat_flag = 0; //victory
	int hits[10][10]; //выстрелы
	int ships[10][10]; //корабли

	void InputShips(); //заполнение вручную
	void InitShips(); //заполнение автоматически
	void PrintShips(); //вывод текущего состояния игрока
	void InitHits(); //заполнение массива выстрелов
};