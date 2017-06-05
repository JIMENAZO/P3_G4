#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Entio.hh"
#include "Renderer.hh"

#define column 74
#define row 36

class Map
{
public:
	Map();
	~Map();

	void printMap();
	char get_MapElement(int x, int y);
	void modify_EntioPosition(std::pair<int, int> newPosition, Entio &entio);
	void modifyMap(std::pair<int, int> position, char a);
	std::pair <int, int> positionOfElement(char element);


private:
	char map[row][column];
};
