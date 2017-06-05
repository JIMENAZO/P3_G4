#include "libraries.hh"


void GameLoop(Team &t, Atacks atacks, Map & map) {
	int turn = 0;
	while (turn < +10) {
		enti::InputKey key = enti::systemPause();
		if (key == enti::InputKey::W || key == enti::InputKey::A || key == enti::InputKey::S || key == enti::InputKey::D) {
			if (t.moveEntio(key)) {
				turn++;
			}
		}

		else if (key == enti::InputKey::z || key == enti::InputKey::Z) {
			t.undoMove();
			turn--;
		}
		else if (key == enti::InputKey::x || key == enti::InputKey::X){
			t.redoMove();
			turn++;
		}
		else if (key == enti::InputKey::SPACEBAR) {
			std::pair<char, int> aux = t.atack();
			if (aux.second == 10)
				atacks.atk(aux.first, aux.second, t.getTeamNumber());
			else {
				aux = atacks.arrowAtack(t.getTeamNumber());
				atacks.atk(aux.first, aux.second, t.getTeamNumber());
			}
			while (enti::getInputKey() == enti::InputKey::NONE);
			turn++;
		}

		else if (key == enti::InputKey::ENTER) {
			t.changeEntio();
			turn++;
		}
		map.printMap();
		enti::cout << enti::Color::WHITE << "TURN: " <<  turn << enti::endl;
		enti::cout << enti::cend;
	}
	t.changeEntio();

	map.printMap();
	enti::cout << enti::Color::WHITE << "TO CHANGE TURN PLAYER PRESS ENTER" << enti::endl;
	enti::cout << enti::cend;

	while (enti::getInputKey() != enti::InputKey::ENTER);

	map.printMap();
	enti::cout << enti::cend;
}

int main()
{
	Map map;
	Team team1(map, 1);
	Team team2(map, 2);
	Atacks atack(team1, team2, map);

	enti::cout << enti::Color::YELLOW << "CLASH OF ENTIOS" << enti::endl;
	enti::cout << enti::endl;
	enti::cout << enti::Color::WHITE << "- Each player has 6 entios." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Use WASD to move each entio." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Use Z to undo a movement." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Each entio has two weapons: 1 sword and 1 bow." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Press SPACEBAR to use a weapon." << enti::endl;
	enti::cout << enti::Color::WHITE << "- The sword can instantly kill an enemy if it is placed in a cell next door." << enti::endl;
	enti::cout << enti::Color::WHITE << "- The bow can damage an enemy within a maximum distance of 10 cells." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Each character has only 10 arrows." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Each turn the less fatigued entio will play first." << enti::endl;
	enti::cout << enti::Color::WHITE << "- To play with the next entio press ENTER." << enti::endl;
	enti::cout << enti::Color::WHITE << "- Each player can do 10 of these actions per turn." << enti::endl;
	enti::cout << enti::endl;
	enti::cout << enti::Color::LIGHTMAGENTA << "Press any key to begin the game!" << enti::endl;
	enti::cout << enti::cend;
	while (enti::getInputKey() == enti::InputKey::NONE);

	map.printMap();
	enti::cout << enti::cend;
	while (true)
	{
		GameLoop(team1, atack, map);
		GameLoop(team2, atack, map);
	}
	team1.PrintTeam();
	//team2.PrintTeam();
	//std::cout << static_cast<int>('1') << std::endl;
	return 0;
}







/*
Juego estilo Dwarf Fortress / Clash Royal / Warhammer de 2 jugadores.
OBJETIVO: acabar con todos los jugadores del enemigo

REGLAS:
-El mapa es una matriz de 36x74 chars (0 ≤ x < 74, 0 ≤ y < 36)
-Cada char puede ser un tipo de terreno: montanya(X), agua(O), bosque(:), tierra(.)
-Cada jugador tiene 6 entios(con 10 puntos de vida) i cada entio tiene un caracter especial (A,B,C,D,E,F)J1/(1,2,3,4,5,6)J2
-Cada jugador puede hacer 10 acciones en un turno (mover un entio aliado, atacar a un entio enemigo, controlar a otro entio(si, gasta un punto)
-En cada turno el entio menos fatigado juega primero (fatiga = turnos jugados + jugadas de ese turno)

-Los entios aliados se mueven con WASD, i el jugador puede deshacer un movimiento pulsando la tecla Z i opcionalmente rehacer-lo pulsando X
-Cuando el jugador canvia de entio se eliminan todos los movimientos guardados

-para atacar a un enemigo, se deve pulsar "SPACE" e indicar el arma y la posicion a la que atacar (arriba, abajo, izquierda o derecha)
-Cada entio posee 2 armas (ESPADA, arco + 10 FLECHAS) la espada mata instantaniamente a un enemigo que este alrededor (tiene 10 de daño)
y las flechas tienen un alcance de minimo 3 i maximo 10 casillas (segun la distancia tienen menos daño distancia 3 = daño 8
distancia 10= daño 1)
-Si un entio se queda sin flechas, solo puede usar la espada.
-Las flechas atraviesan todo tipo de terreno excepto la montanya.
-Para cambiar de entio se pulsa la tecla "Enter", lo cual procesa la fatiga del entio actual i salta al siguiente entio menos fatigado

al consumir las 10 acciones del turno debe pulsarse enter para dar paso al siguiente jugador

*/