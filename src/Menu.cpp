#include "Menu.h"
#include "Utilities.h"

float windowSizeX = 1200.f;
float windowSizeY = 850.f;

void Menu::initMenu()
{

	if (!font.loadFromFile("../../Fonts/calibri.ttf"))
		std::cout << "FAIL::GAME::INITGUI::Failed load font" << std::endl;

	// Play
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::White);
	menu[0].setString("Play");
	menu[0].setCharacterSize(100);
	menu[0].setPosition(windowSizeX / 2 - menu[0].getLocalBounds().width / 2, windowSizeY / 2 - menu[0].getLocalBounds().height / 2 - 100);

	// About
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("About");
	menu[1].setCharacterSize(100);
	menu[1].setPosition(windowSizeX / 2 - menu[1].getLocalBounds().width / 2, windowSizeY / 2 - menu[1].getLocalBounds().height / 2);

	// Exit
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setCharacterSize(100);
	menu[2].setPosition(windowSizeX / 2 - menu[2].getLocalBounds().width / 2, windowSizeY / 2 - menu[2].getLocalBounds().height / 2 + 100);


	menuSelected = -1;
}

Menu::Menu(float width, float height)
{
	this->initMenu();
	this->initBackground();
}
Menu::~Menu()
{
}

void Menu::render(sf::RenderWindow* window)
{
	window->draw(backgroundSprite);

	for (int i = 0; i < 4; i++)
	{
		window->draw(menu[i]);
	}
}

void Menu::initBackground()
{
	if (!backgroundTexture.loadFromFile("../../Images/menu.png"))
	{
		std::cout << "FAIL::MENU::LOADBACKGROUNF::Failed to load background image" << std::endl;
	}

	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(windowSizeX / backgroundSprite.getLocalBounds().width, windowSizeY / backgroundSprite.getLocalBounds().height);

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

