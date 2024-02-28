#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>


class Player
{
private:
	sf::Sprite sprite{};
	sf::Texture texture{};

	float moveSpeed{};
	float attackCoolDown{};
	float attackCoolDownMax{};

	int hp{};
	int hpMax{};

	void initSprite();
	void initTexture();
	void initVaraibles();

public:
	Player();
	virtual ~Player();

	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;
	const bool canAtack();

	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void updateAttack();
	void move(const float dirX, const float dirY);
	void update();
	void render(sf::RenderTarget& target);
	void setHp(const int hp);
	void loseHp(const int value);
	void reset();

};

