#include "minesweeper.h"

int minesweeper::_adjacencyX[8] = { 1, 0 , -1, 1, -1, 1, 0 ,-1 };
int minesweeper::_adjacencyY[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
int minesweeper::_PixelsPerSquare = 32;



void minesweeper::createField()
{
	field = new char* [_sizeX];
	for (int i = 0; i < _sizeX; ++i)
		field[i] = new char[_sizeY];
	for (int i = 0; i < _sizeX; i++)
		for (int j = 0; j < _sizeY; j++)
			field[i][j] = 31;
}

void minesweeper::initializeField()
{
	// Add bombs randomly to the field
	int n = _sizeX * _sizeY;
	int pos = 0;
	int iterator = -1;
	for (int i = 0; i < _numberBombs; i++) {
		pos = rand() % n + 1;
		iterator = -1;
		while (pos > 0) {
			++iterator;
			if (field[iterator / _sizeY][iterator % _sizeY] != 29) pos--;
		}
		field[iterator / _sizeY][iterator % _sizeY] = 29;
		n--;
	}

	// Add numbers
	for (int i = 0; i < _sizeX; i++)
		for (int j = 0; j < _sizeY; j++)
			if (field[i][j] != 29) field[i][j] = getAdjacentBombs(i,j) + 20;
}

char minesweeper::getAdjacentBombs(int positionX, int positionY)
{
	char result = 0;
	int CandidateX, CandidateY;
	for (int i = 0; i < 8; i++) {
		CandidateX = positionX + _adjacencyX[i];
		CandidateY = positionY + _adjacencyY[i];
		if (CandidateX >= 0 && CandidateX < _sizeX && CandidateY >= 0 && CandidateY < _sizeY) {
			if (field[CandidateX][CandidateY] == 29 || field[CandidateX][CandidateY] == 19 || field[CandidateX][CandidateY] == 9) {
				result++;
			}
		}
	}
	return result;
}

bool minesweeper::RevealFields(int positionX, int positionY)
{
	char auxiliary = field[positionX][positionY];
	bool result = 0;

	if (field[positionX][positionY] >= 20 && field[positionX][positionY] < 30) {
		field[positionX][positionY] -= 20;
	}
	else if (field[positionX][positionY] >= 10 && field[positionX][positionY] < 20) {
		field[positionX][positionY] -= 10;
	}
	else {
		return result;
	}

	// reveal more if auxiliary is 0 with recursive call
	if (field[positionX][positionY] == 0) {
		int CandidateX, CandidateY;
		for (int i = 0; i < 8; i++) {
			CandidateX = positionX + _adjacencyX[i];
			CandidateY = positionY + _adjacencyY[i];
			if (CandidateX >= 0 && CandidateX < _sizeX && CandidateY >= 0 && CandidateY < _sizeY) {
				result = result || RevealFields(CandidateX, CandidateY);
			}
		}
	}
	else if (field[positionX][positionY] == 9) {
		result = 1;
	}

	return result;
}

void minesweeper::RevealEverything()
{
	for(int i = 0; i<_sizeX; i++)
		for (int j = 0; j < _sizeY; j++) {
			if (field[i][j] >= 20 && field[i][j] < 30) {
				field[i][j] -= 20;
			}
			else if (field[i][j] >= 10 && field[i][j] < 20) {
				field[i][j] -= 10;
			}
		}
}

minesweeper::minesweeper(int sizeX, int sizeY, int numberBombs):
	_sizeX(sizeX),_sizeY(sizeY)
{
	// check that number of bombs is lower than total number of fields
	if (numberBombs < sizeX * sizeY) _numberBombs = numberBombs;
	else _numberBombs = sizeX * sizeY -1;

	createField();

	initializeField();
}

minesweeper::~minesweeper()
{
	for (int i = 0; i < _sizeX; ++i)
		delete[] field[i];
	delete[] field;
}

void minesweeper::displayFieldInConsole()
{
	std::cout << std::endl;
	for (int i = 0; i < _sizeX; i++)
	{
		for (int j = 0; j < _sizeY; j++)
		{
			std::cout << " " << static_cast<int>(field[i][j]) << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void minesweeper::FlagField(int positionX, int positionY)
{
	if (field[positionX][positionY] >= 20 && field[positionX][positionY] < 30) {
		field[positionX][positionY] -= 10;
	}
	else if (field[positionX][positionY] >= 10 && field[positionX][positionY] < 20) {
		field[positionX][positionY] += 10;
	}
}

void minesweeper::ChooseField(int positionX, int positionY)
{
	if (RevealFields(positionX, positionY) == 1) RevealEverything();
}

void minesweeper::display(sf::Sprite s, sf::RenderWindow& window)
{
	for (int i = 0; i < _sizeX; i++)
		for (int j = 0; j < _sizeY; j++)
		{
			if (field[i][j] < 10) {
				s.setTextureRect(sf::IntRect((field[i][j]) * _PixelsPerSquare, 0, _PixelsPerSquare, _PixelsPerSquare));
			}
			else if (field[i][j] < 20 && field[i][j] >= 10) {
				s.setTextureRect(sf::IntRect(11 * _PixelsPerSquare, 0, _PixelsPerSquare, _PixelsPerSquare));
			}
			else if (field[i][j] < 30 && field[i][j] >= 20) {
				s.setTextureRect(sf::IntRect(10 * _PixelsPerSquare, 0, _PixelsPerSquare, _PixelsPerSquare));
			}
			s.setPosition(i * _PixelsPerSquare, j * _PixelsPerSquare);
			window.draw(s);
		}
}

int minesweeper::getPixelsX()
{
	return _sizeX * _PixelsPerSquare;
}

int minesweeper::getPixelsY()
{
	return _sizeY * _PixelsPerSquare;
}
