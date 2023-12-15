#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Menu
{
private:
	int menuSelected;
	sf::Text menu[4];
	sf::Font font;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	void initMenu();

public:
	Menu(float width, float height);
	virtual ~Menu();

	void render(sf::RenderWindow* window);
	void initBackground();
	void moveUp();
	void moveDown();
	int menuPressed();
};

