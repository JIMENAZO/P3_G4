#pragma once
#include "Team.hh"
#include "Entio.hh"
#include "Map.hh"

class Atacks
{
public:
	Atacks(Team & t1, Team & t2, Map & m);
	~Atacks();
	
	void atk(char chrctr, int dmg, int t);
	void update(int t);
	std::pair<char, int> arrowAtack(int t);
private:
	Team & team1, & team2;
	Map & map;
};

Atacks::Atacks(Team & t1, Team & t2, Map & m) :
	team1(t1),
	team2(t2),
	map(m)
{
}

Atacks::~Atacks()
{
}

inline void Atacks::atk(char chrctr, int dmg, int t)
{
	int aux;
	if (t == 1) {
		aux = team2.lookForEntio(chrctr);
		if (aux != 20) {
			team2.entioTakeDamge(dmg, aux);
			map.printMap();
			enti::cout << enti::Color::WHITE << "Entio " << team1.getEntio(aux).character << " has atacked to " << team2.getEntio(aux).character 
				<< " producing " << dmg << " points of damage" << enti::endl;
			enti::cout << enti::cend;
		}
		else {
			map.printMap();
			enti::cout << enti::Color::WHITE << "YOU HAVE FAILED!" << enti::endl;
			enti::cout << enti::cend;
		}
	}
	else if (t == 2) {
		aux = team1.lookForEntio(chrctr);
		if (aux != 20) {
			team1.entioTakeDamge(dmg, aux);
			map.printMap();
			enti::cout << enti::Color::WHITE << "Entio " << team2.getEntio(aux).character << " has atacked to " << team1.getEntio(aux).character
				<< " producing " << dmg << " points of damage" << enti::endl;
			enti::cout << enti::cend;
		}
		else {
			map.printMap();
			enti::cout << enti::Color::WHITE << "YOU HAVE FAILED!" << enti::endl;
			enti::cout << enti::cend;
		}
	}
	update(t);
}

inline void Atacks::update(int t)
{
	if (t == 1) {
		for (int i = 0; i < team2.getTeamSize(); i++) {
			if (team2.getEntio(i).life < 1)
				team2.eraseEntio(i);
		}
	}
	if (t == 2) {
		for (int i = 0; i < team1.getTeamSize(); i++) {
			if (team1.getEntio(i).life < 1)
				team1.eraseEntio(i);
		}
	}
}

inline std::pair<char, int> Atacks::arrowAtack(int t)
{
	bool found = false;
	int i = 3;
	if (t == 1) {
		enti::InputKey direction = team1.atackAt();
		switch (direction) {
		case enti::InputKey::W:
			while (!found && i <= 10) {
				if (map.get_MapElement(team1.get_CurrentEntio().position.first - i, team1.get_CurrentEntio().position.second) >= '1'
					&& map.get_MapElement(team1.get_CurrentEntio().position.first - i, team1.get_CurrentEntio().position.second) <= '6') {
					
					return std::pair<char, int>({ map.get_MapElement(team1.get_CurrentEntio().position.first - i, team1.get_CurrentEntio().position.second) , 11 - i });
					i++;
				}
			}
			break;
		case enti::InputKey::A:
			while (!found && i <= 10) {
				if (map.get_MapElement(team1.get_CurrentEntio().position.first, team1.get_CurrentEntio().position.second - i) >= '1'
					&& map.get_MapElement(team1.get_CurrentEntio().position.first, team1.get_CurrentEntio().position.second - i) <= '6') {

					return std::pair<char, int>({ map.get_MapElement(team1.get_CurrentEntio().position.first, team1.get_CurrentEntio().position.second - i) , 11 - i });
				}
				i++;
			}
			break;
		case enti::InputKey::S:
			while (!found && i <= 10) {
				if (map.get_MapElement(team1.get_CurrentEntio().position.first + i, team1.get_CurrentEntio().position.second) >= '1'
					&& map.get_MapElement(team1.get_CurrentEntio().position.first + i, team1.get_CurrentEntio().position.second) <= '6') {

					return std::pair<char, int>({ map.get_MapElement(team1.get_CurrentEntio().position.first + i, team1.get_CurrentEntio().position.second) , 11 - i });
				}
				i++;
			}
			break;
		case enti::InputKey::D:
			while (!found && i <= 10) {
				if (map.get_MapElement(team1.get_CurrentEntio().position.first, team1.get_CurrentEntio().position.second + i) >= '1'
					&& map.get_MapElement(team1.get_CurrentEntio().position.first, team1.get_CurrentEntio().position.second + i) <= '6') {

					return std::pair<char, int>({ map.get_MapElement(team1.get_CurrentEntio().position.first, team1.get_CurrentEntio().position.second + i) , 11 - i });
				}
				i++;
			}
			break;
		}

	}
	if (t == 2) {
		enti::InputKey direction = team2.atackAt();
		switch (direction) {
		case enti::InputKey::W:
			while (!found && i <= 10) {
				if (map.get_MapElement(team2.get_CurrentEntio().position.first - i, team2.get_CurrentEntio().position.second) >= '1'
					&& map.get_MapElement(team2.get_CurrentEntio().position.first - i, team2.get_CurrentEntio().position.second) <= '6') {

					return std::pair<char, int>({ map.get_MapElement(team2.get_CurrentEntio().position.first - i, team2.get_CurrentEntio().position.second) , 11 - i });
				}
				i++;
			}
			break;
		case enti::InputKey::A:
			while (!found && i <= 10) {
				if (map.get_MapElement(team2.get_CurrentEntio().position.first, team2.get_CurrentEntio().position.second - i) >= '1'
					&& map.get_MapElement(team2.get_CurrentEntio().position.first, team2.get_CurrentEntio().position.second - i) <= '6') {

					return std::pair<char, int>({ map.get_MapElement(team2.get_CurrentEntio().position.first, team2.get_CurrentEntio().position.second - i) , 11 - i });
				}
				i++;
			}
			break;
		case enti::InputKey::S:
			while (!found && i <= 10) {
				if (map.get_MapElement(team2.get_CurrentEntio().position.first + i, team2.get_CurrentEntio().position.second) >= '1'
					&& map.get_MapElement(team2.get_CurrentEntio().position.first + i, team2.get_CurrentEntio().position.second) <= '6') {

					return std::pair<char, int>({ map.get_MapElement(team2.get_CurrentEntio().position.first + i, team2.get_CurrentEntio().position.second) , 11 - i });
				}
				i++;
			}
			break;
		case enti::InputKey::D:
			while (!found && i <= 10) {
				if (map.get_MapElement(team2.get_CurrentEntio().position.first, team2.get_CurrentEntio().position.second + i) >= '1'
					&& map.get_MapElement(team2.get_CurrentEntio().position.first, team2.get_CurrentEntio().position.second + i) <= '6') {

					return std::pair<char, int>({ map.get_MapElement(team2.get_CurrentEntio().position.first, team2.get_CurrentEntio().position.second + i) , 11 - i });
				}
				i++;
			}
			break;
		}

	}
	return std::pair<char, int>({});
}

