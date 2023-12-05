#include "Enemy.h"

void Enemy::initVaraibles()
{
	this->pointCount = rand() % 8 + 3;
	this->type = 0;
	this->speed = static_cast<float>(this->pointCount/3);
	this->hp = this->hpMax;
	this->hpMax = static_cast<int>(this->pointCount);
	this->damage = this->pointCount;
	this->points = this->pointCount;
}


void Enemy::initShape()
{
	if (!this->texture.loadFromFile("../../Images/asteroid.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file" << std::endl;
	}
	this->shape.setRadius(this->pointCount * 7);
	this->shape.setPointCount(this->pointCount);
	this->shape.setTexture(&texture);
	//this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVaraibles();
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}


void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

sf::Vector2f Enemy::getPosition() const
{
	return this->shape.getPosition();
}

