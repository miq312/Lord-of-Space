#include "Menu.h"

void Menu::initMenu()
{
	if (!font.loadFromFile("../../Fonts/calibri.ttf"))
		std::cout << "FAIL::GAME::INITGUI::Failed load font" << std::endl;

	//Play
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::White);
	menu[0].setString("Play");
	menu[0].setCharacterSize(70);
	menu[0].setPosition(400, 200);

	//Ranking
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Ranking");
	menu[1].setCharacterSize(70);
	menu[1].setPosition(400, 300);

	//About
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("About");
	menu[2].setCharacterSize(70);
	menu[2].setPosition(400, 400);

	//Exit
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setCharacterSize(70);
	menu[3].setPosition(400, 500);

	menuSelected = -1;
}

Menu::Menu(float width, float height)
{
	this->initMenu();
}
Menu::~Menu()
{
}

void Menu::render(sf::RenderWindow* window)
{
	for (int i = 0; i < 4; i++)
	{
		window->draw(menu[i]);
	}
}

void Menu::moveUp()
{
	if (menuSelected - 1 >= 0)
	{
		menu[menuSelected].setFillColor(sf::Color::White);
		menuSelected--;

		menu[menuSelected].setFillColor(sf::Color::Blue);
	}
}

void Menu::moveDown()
{
	if (menuSelected + 1 < 4)
	{
		menu[menuSelected].setFillColor(sf::Color::White);
		menuSelected++;

		menu[menuSelected].setFillColor(sf::Color::Blue);
	}
	else if (menuSelected + 1 == 4)
	{
		menu[menuSelected].setFillColor(sf::Color::White);
		menuSelected = 0;

		menu[menuSelected].setFillColor(sf::Color::Blue);
	}
}


int Menu::menuPressed()
{
	return menuSelected + 1;
}

