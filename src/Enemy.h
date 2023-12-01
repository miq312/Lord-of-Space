#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Enemy
{
private:
	sf::CircleShape shape;
	sf::Texture texture;

	unsigned pointCount;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initVaraibles();
	void initShape();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	void update();;
	void render(sf::RenderTarget* target);
	sf::Vector2f getPosition() const;
};

