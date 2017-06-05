#include "Map.hh"

Map::Map()
{
	std::ifstream myMapFile("default.cfg"); //Creo mi archivo file de tipo ifstream en el que cargo el contenido del documento default.cfg (el campo de juego)
	std::string currentLine;

	if (myMapFile.is_open())
	{
	int counter = 0;

	while (getline(myMapFile, currentLine))
	{
		for (int i = 0; i < currentLine.size(); i++)
		{
			map[counter][i] = currentLine[i]; //linea.at(i);
		}
		counter++;
	}
  	myMapFile.close();
	}
	else enti::cout << enti::Color::WHITE << "No se encuentra el archivo que intenta abrir" << enti::endl;
}


Map::~Map()
{
	delete[] map;
}

void Map::printMap()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column - 1; j++)
		{
			switch (map[i][j])
			{																	//Aplicamos color a cada caracter leído según cual sea
			case 'X': enti::cout << enti::Color::BROWN << map[i][j] << " ";		
				break;
			case 'O': enti::cout << enti::Color::LIGHTCYAN << map[i][j] << " ";
				break;
			case '.': enti::cout << enti::Color::YELLOW << map[i][j] << " ";
				break;
			case ':': enti::cout << enti::Color::GREEN << map[i][j] << " ";
				break;
			default:
				enti::cout << enti::Color::LIGHTMAGENTA << map[i][j] << " ";
				break;
			}
		}
		enti::cout << enti::endl;
	}
}

char Map::get_MapElement(int x, int y)
{
	char aux = map[x][y];
	return aux;
}

void Map::modify_EntioPosition(std::pair<int, int> newPosition, Entio &entio)
{
	map[entio.position.first][entio.position.second] = entio.elementAtPosition;
	entio.elementAtPosition = map[newPosition.first][newPosition.second];
	map[newPosition.first][newPosition.second] = entio.character;
	entio.position.first = newPosition.first;
	entio.position.second = newPosition.second;
	/*system("cls");
	printMap();*/
}

void Map::modifyMap(std::pair<int, int> position, char a)
{
	map[position.first][position.second] = a;
}



std::pair<int, int> Map::positionOfElement(char element)
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if(map[i][j] == element)
				return std::pair<int, int>(i, j);
		}
	}
	enti::cout << enti::Color::WHITE << "ENTIO NOT FOUND" << enti::endl;
	return std::pair<int, int>(0, 0);
}
