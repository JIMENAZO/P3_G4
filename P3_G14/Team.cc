#include "Team.hh"



Team::Team(Map & map, int player) :
	myMap(map)
{
	t = player;
	if (player == 1) {
		for (int i = 0; i < MAXENTIOSTEAM; i++) {
			myTeam.push_back({ static_cast<char>(65+i),myMap.positionOfElement(static_cast<char>(65+i)), 0, 10, '.' });
		}
	}
	if (player == 2) {
		for (int i = 0; i < MAXENTIOSTEAM; i++) {
			myTeam.push_back({ static_cast<char>(49 + i),myMap.positionOfElement(static_cast<char>(49 + i)), 0, 10, '.' });
		}
	}

	currentEntio = 0;
}


Team::~Team()
{
	myTeam.clear();
}

int Team::getTeamNumber()
{
	return t;
}

Entio Team::getEntio(int i)
{
	return myTeam[i];
}

size_t Team::getTeamSize()
{
	return myTeam.size();
}

void Team::eraseEntio(int ent)
{
	if (ent < myTeam.size()) {
		myMap.modifyMap(myTeam[ent].position, myTeam[ent].elementAtPosition);
		myTeam.erase(myTeam.begin() + ent);
	}
}

bool Team::moveEntio(enti::InputKey key)
{
	switch (key) {
	case enti::InputKey::W:
		if (myMap.get_MapElement(myTeam[currentEntio].position.first - 1, myTeam[currentEntio].position.second) == '.'
			|| myMap.get_MapElement(myTeam[currentEntio].position.first - 1, myTeam[currentEntio].position.second) == ':') {

			lastMoves.push(std::pair<int, int>(myTeam[currentEntio].position.first, myTeam[currentEntio].position.second));
			myMap.modify_EntioPosition(std::pair<int, int>(myTeam[currentEntio].position.first - 1, myTeam[currentEntio].position.second), myTeam[currentEntio]);
			myTeam[currentEntio].fatiga++;
			return true;
		}
		break;
	case enti::InputKey::S:
		if (myMap.get_MapElement(myTeam[currentEntio].position.first + 1, myTeam[currentEntio].position.second) == '.'
			|| myMap.get_MapElement(myTeam[currentEntio].position.first + 1, myTeam[currentEntio].position.second) == ':') {

			lastMoves.push(std::pair<int, int>(myTeam[currentEntio].position.first, myTeam[currentEntio].position.second));
			myMap.modify_EntioPosition(std::pair<int, int>(myTeam[currentEntio].position.first + 1, myTeam[currentEntio].position.second), myTeam[currentEntio]);
			myTeam[currentEntio].fatiga++;
			return true;
		}
		break;
	case enti::InputKey::A:
		if (myMap.get_MapElement(myTeam[currentEntio].position.first, myTeam[currentEntio].position.second - 1) == '.'
			|| myMap.get_MapElement(myTeam[currentEntio].position.first, myTeam[currentEntio].position.second - 1) == ':') {

			lastMoves.push(std::pair<int, int>(myTeam[currentEntio].position.first, myTeam[currentEntio].position.second));
			myMap.modify_EntioPosition(std::pair<int, int>(myTeam[currentEntio].position.first, myTeam[currentEntio].position.second - 1), myTeam[currentEntio]);
			myTeam[currentEntio].fatiga++;
			return true;
		}
		break;
	case enti::InputKey::D:
		if (myMap.get_MapElement(myTeam[currentEntio].position.first, myTeam[currentEntio].position.second + 1) == '.'
			|| myMap.get_MapElement(myTeam[currentEntio].position.first, myTeam[currentEntio].position.second + 1) == ':') {

			lastMoves.push(std::pair<int, int>(myTeam[currentEntio].position.first, myTeam[currentEntio].position.second));
			myMap.modify_EntioPosition(std::pair<int, int>(myTeam[currentEntio].position.first, myTeam[currentEntio].position.second + 1), myTeam[currentEntio]);
			myTeam[currentEntio].fatiga++;
			return true;
		}
		break;
	default:
		std::cout << "WELL, THERE SHOULDN'T BE A DEFAULT, BUT WE PUT IT JUST IN CASE SOMETHING WENT WRONG" << std::endl;
	}
	return false;
}

int Team::lookForEntio(char aux)
{
	bool found = false;
	int i = 0;
	while (!found && i < myTeam.size()) {
		if (aux == myTeam[i].character)
			return i;
		i++;
	}
	return 20;
}

void Team::changeEntio()
{
	int aux = 0;
	for (int i = 1; i < myTeam.size(); i++) {
		if (myTeam[i].fatiga < myTeam[aux].fatiga)
			aux = i;
	}
	currentEntio = aux;
	setLastMoveTo0();
}

void Team::undoMove()
{
	if (lastMoves.size() != 0) {
		myMap.modify_EntioPosition(std::pair<int, int>(lastMoves.top().first, lastMoves.top().second), myTeam[currentEntio]);
		myTeam[currentEntio].fatiga--;
		reMoves.push(std::pair<int, int>(lastMoves.top().first, lastMoves.top().second));
		lastMoves.pop();
	}
}

void Team::redoMove()
{
	if (reMoves.size() != 0) {
		myMap.modify_EntioPosition(std::pair<int, int>(reMoves.top().first, reMoves.top().second), myTeam[currentEntio]);
		myTeam[currentEntio].fatiga--;
		lastMoves.push(std::pair<int, int>(reMoves.top().first, reMoves.top().second));
		reMoves.pop();
	}
}

void Team::setLastMoveTo0()
{
	while (lastMoves.size() != 0)
	{
		lastMoves.pop();
	}
}

std::pair<char, int> Team::atack()
{
	myMap.printMap();
	enti::cout << enti::Color::WHITE  << "YOU'VE CHOOSED TO ATACK, SELECT THE WEAPON:" << enti::endl;
	enti::cout << enti::Color::WHITE  << "1-Sword" << enti::endl;
	enti::cout << enti::Color::WHITE  << "2-Arrow" << enti::endl;
	enti::cout << enti::Color::WHITE  << "OTHER-Leave atack menu" << enti::endl;
	enti::cout << enti::cend;


	
	enti::InputKey option = enti::systemPause();
	if (option == enti::InputKey::NUM1) {
		//swordAtack
		enti::InputKey direction = atackAt();
		switch (direction) {
		case enti::InputKey::W:
			return std::pair<char, int>(myMap.get_MapElement(myTeam[currentEntio].position.first - 1, myTeam[currentEntio].position.second), 10);
			break;
		case enti::InputKey::A:
			return std::pair<char, int>(myMap.get_MapElement(myTeam[currentEntio].position.first, myTeam[currentEntio].position.second - 1), 10);
			break;
		case enti::InputKey::S:
			return std::pair<char, int>(myMap.get_MapElement(myTeam[currentEntio].position.first + 1, myTeam[currentEntio].position.second), 10);
			break;
		case enti::InputKey::D:
			return std::pair<char, int>(myMap.get_MapElement(myTeam[currentEntio].position.first, myTeam[currentEntio].position.second + 1), 10);
			break;
		}
	}

	else if (option == enti::InputKey::NUM2) {
		//ArrowAtack();
		return std::pair<char, int>({ '1', 0 });
	}
	else
		return std::pair<char,int>({ '0', 10 });
}

enti::InputKey Team::atackAt()
{
	myMap.printMap();
	enti::cout << enti::Color::WHITE  << "USE WASD TO CHOOSE THE ATACK DIRECTION" << enti::endl;
	enti::cout << enti::cend;

	return enti::systemPause();
}

void Team::entioTakeDamge(int dmg, int entio) {
	myTeam[entio].life -= dmg;
}

void Team::PrintTeam()
{
	for (int i = 0; i < myTeam.size(); i++) {
		std::cout << myTeam[i].character << myTeam[i].position.first << myTeam[i].position.second << myTeam[i].fatiga << myTeam[i].elementAtPosition << std::endl;
	}
}

Entio Team::get_CurrentEntio()
{
	return myTeam[currentEntio];
}
