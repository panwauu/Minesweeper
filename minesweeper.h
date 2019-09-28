#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#pragma once
class minesweeper
{
private:
	static int _adjacencyX[8];
	static int _adjacencyY[8];
	static int _PixelsPerSquare;
	int _sizeX;
	int _sizeY;
	int _numberBombs;
	char** field;
	void createField();
	void initializeField();
	char getAdjacentBombs(int positionX, int positionY);
	bool RevealFields(int positionX, int positionY);
	void RevealEverything();


public:
	minesweeper(int sizeX, int sizeY, int numberBombs);
	~minesweeper();
	void displayFieldInConsole();
	void FlagField(int positionX, int positionY);
	void ChooseField(int positionX, int positionY);
	void display(sf::Sprite s, sf::RenderWindow& window);
	int getPixelsX();
	int getPixelsY();
};

