#include "libraries.hh"

Player::Player(Map &myMatrix) : Matrix {myMatrix}
{
	state = playerState::notMyTurn;

	myArmySize = 6;

	myTurn = false;

	remainingActions = 0;

	for (int i = 0; i < myArmySize; i++)
	{

	}
}

Player::~Player()
{}


void Player::keepCalm()
{

	while(state != playerState::endTurn)
	{
		switch(state)
		{
		case playerState::attackEntio: attackEntio(lastKeyPressed);
			break;
		case playerState::changeEntio: changeEntio();
			break;
		case playerState::moveEntio: moveEntio();
			break;
		case playerState::undoAction: undoAction();
			break;
		case playerState::redoAction: redoAction();
			break;
		default:
			break;
		}
	}
}


void Player::attackEntio(enti::InputKey direction)
{

}

void Player::moveEntio()
{
}

void Player::undoAction()
{
}

void Player::redoAction()
{
}

void Player::changeEntio()
{
}

void Player::endTurn()
{
}

bool operator < (const Player::Entio & A, const Player::Entio & B)
{
	if (A.fatigue < B.fatigue)
		return B < A;
}

bool Player::terrainCheck(int originX, int originY, int destinyX, int destinyY, enti::InputKey direction)
{
	if (direction == enti::InputKey::w || direction == enti::InputKey::W)
	{
		for (int i = originX, j = originY; j > destinyY; j--)
		{
			if (Matrix.map[i][j] == Matrix.mountain) return false;
		}
	}
	else if (direction == enti::InputKey::s || direction == enti::InputKey::S)
	{
		for (int i = originX, j = originY; j < destinyY; j++)
		{
			if (Matrix.map[i][j] == Matrix.mountain) return false;
		}
	}
	else if (direction == enti::InputKey::a || direction == enti::InputKey::A)
	{
		for (int i = originX, j = originY; i > destinyX; i--)
		{
			if (Matrix.map[i][j] == Matrix.mountain) return false;
		}
	}
	else if (direction == enti::InputKey::d || direction == enti::InputKey::D)
	{
		for (int i = originX, j = originY; i < destinyX; i++)
		{
			if (Matrix.map[i][j] == Matrix.mountain) return false;
		}
	}
	else return true;
}
