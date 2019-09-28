#include "minesweeper.h"

#include <SFML/Graphics.hpp>

int main()
{
	srand(time(NULL));

	unsigned int xRead, yRead, nBombs;
	std::cout << "Size in x direction?" << std::endl;
	std::cin >> xRead;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore('\n', 1000);
		std::cout << "Failed. Size in x direction?" << std::endl;
		std::cin >> xRead;
	}

	std::cout << "Size in y direction?" << std::endl;
	std::cin >> yRead;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore('\n', 1000);
		std::cout << "Failed. Size in y direction?" << std::endl;
		std::cin >> yRead;
	}

	std::cout << "Size: " << xRead << "x" << yRead << std::endl;
	std::cout << "Number of fields: " << (xRead * yRead) << std::endl;

	std::cout << "Number of Bombs?" << std::endl;
	std::cin >> nBombs;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore('\n', 1000);
		std::cout << "Number of Bombs?" << std::endl;
		std::cin >> nBombs;
	}

	minesweeper game = minesweeper(xRead, yRead, nBombs);

	sf::RenderWindow window(sf::VideoMode(game.getPixelsX(), game.getPixelsY()), "Minesweeper!");
	sf::Texture t;
	t.loadFromFile("images/tiles.jpg");
	sf::Sprite s(t);

	while (window.isOpen())
	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		int x = pos.x / 32;
		int y = pos.y / 32;

		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();

			if (e.type == sf::Event::MouseButtonPressed) {
				if (e.key.code == sf::Mouse::Left) game.ChooseField(x, y);
				else if (e.key.code == sf::Mouse::Right) game.FlagField(x, y);
			}
		}

		window.clear(sf::Color::White);

		game.display(s, window);

		window.display();
	}

	return 0;
}