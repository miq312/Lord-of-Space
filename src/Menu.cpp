#include "Menu.h"
#include "GameConfig.h"
float windowSizeX = Config::Game::windowSizeX;
float windowSizeY = Config::Game::windowSizeY;

void Menu::initMenu()
{

	if (!font.loadFromFile("../../Fonts/calibri.ttf"))
		std::cout << "FAIL::GAME::INITGUI::Failed load font" << std::endl;

	// Play
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::White);
	menu[0].setString("Play");
	menu[0].setCharacterSize(80);
	//menu[0].setPosition(windowSizeX / 2 - menu[0].getLocalBounds().width / 2, windowSizeY / 2 - menu[0].getLocalBounds().height / 2 - 100);
	menu[0].setPosition(100, 50);
	// Ranking
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Ranking");
	menu[1].setCharacterSize(80);
	menu[1].setPosition(100, 150);
	// About
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("About");
	menu[2].setCharacterSize(80);
	//menu[1].setPosition(windowSizeX / 2 - menu[1].getLocalBounds().width / 2, windowSizeY / 2 - menu[1].getLocalBounds().height / 2);
	menu[2].setPosition(100, 250);
	// Exit
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setCharacterSize(80);
	//menu[2].setPosition(windowSizeX / 2 - menu[2].getLocalBounds().width / 2, windowSizeY / 2 - menu[2].getLocalBounds().height / 2 + 100);
	menu[3].setPosition(100, 350);

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

void Menu::render(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);

	for (int i = 0; i < 4; i++)
	{
		window.draw(menu[i]);
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

		menu[menuSelected].setFillColor(sf::Color(50,50,50));
	}
}

void Menu::moveDown()
{
	if (menuSelected + 1 < 4)
	{
		menu[menuSelected].setFillColor(sf::Color::White);
		menuSelected++;

		menu[menuSelected].setFillColor(sf::Color(50, 50, 50));
	}
	else if (menuSelected + 1 == 4)
	{
		menu[menuSelected].setFillColor(sf::Color::White);
		menuSelected = 0;

		menu[menuSelected].setFillColor(sf::Color(50, 50, 50));
	}
}


int Menu::menuPressed()
{
	return menuSelected + 1;
}

void Menu::renderRanking(sf::RenderWindow& window, std::vector<unsigned>& playerScores)
{
	sf::Text rankingText;
	rankingText.setFont(this->font);
	rankingText.setCharacterSize(24);
	rankingText.setFillColor(sf::Color::White);
	rankingText.setPosition(50.f, 200.f);

	std::stringstream ss;
	ss << "===== RANKING =====\n";
	for (size_t i = 0; i < playerScores.size(); i++)
	{
		ss << i + 1 << ". " << playerScores[i] << " points\n";
	}
	ss << "===================";

	rankingText.setString(ss.str());

	window.draw(rankingText);
}

