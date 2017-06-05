#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "Map.hh"
#include "Entio.hh"
#include "Input.inl.hh"

class Team
{
public:
	Team(Map & map, int player);
	~Team();

	int getTeamNumber();
	Entio getEntio(int i);
	size_t getTeamSize();
	void eraseEntio(int ent);
	bool moveEntio(enti::InputKey key);
	int lookForEntio(char aux);
	void changeEntio();
	void undoMove();
	void redoMove();
	std::pair<char, int>atack();
	enti::InputKey atackAt();
	void entioTakeDamge(int dmg, int entio);
	void PrintTeam(); // control function
	Entio get_CurrentEntio();

private:
	void setLastMoveTo0();

	std::vector<Entio> myTeam;
	std::stack<std::pair<int, int>> lastMoves;
	std::stack<std::pair<int, int>> reMoves;
	int currentEntio;
	const int MAXENTIOSTEAM = 6;
	Map & myMap;
	int t;
};
