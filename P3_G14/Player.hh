#pragma once
#include "libraries.hh"

class Player
{
public:
	Player(Map &myMatrix);
	~Player();

	void keepCalm();
	void attackEntio(enti::InputKey direction);
	void moveEntio();
	void undoAction();
	void redoAction();
	void changeEntio();
	void endTurn();
	bool terrainCheck(int originX, int originY, int destinyX, int destinyY, enti::InputKey direction);

	enum class Weapon { sword, bow, unarmed };

	struct Entio
	{
		int currentActions;
		int totalTurns;
		int fatigue;
		int hitPoints;
		int arrows;
		int positionX;
		int positionY;
		Weapon myWeapon;
		std::string myName;
		bool isAlive;

		Entio(int i, bool flag)
		{
			if (flag)
			{
				std::string studentArmy[] = { "Carla", "Bea", "Guille", "Alessandro", "Ferran", "Dani" }; //Mi array de strings que sólo existe en el scope del constructor de Entio
				myName = studentArmy[i];
			}			
			else 
			{
				std::string teacherArmy[] = { "Tona", "Radev", "Carles", "Oscar", "Rita", "Albert" };
				myName = teacherArmy[i];
			}

			currentActions = 0;
			totalTurns = 0;
			fatigue = 0;
			hitPoints = 10;
			arrows = 10;
			myWeapon = Weapon::unarmed;
		}
	};

	friend bool operator < (const Entio &A, const Entio &B); //He sobrecargado el operador para que se considere que el Entio con menor fatiga sea el mayor

private:

	enum class playerState { keepCalm, attackEntio, moveEntio, undoAction, redoAction, changeEntio, endTurn, notMyTurn };

	Map &Matrix;

	size_t myArmySize;

	enti::InputKey lastKeyPressed;

	std::priority_queue <Entio> myArmy;

	playerState state;

	bool myTurn;

	int remainingActions;
};

