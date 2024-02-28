#include "Enemy.h"
#include "GameConfig.h"

void Enemy::initVaraibles()
{
	this->pointCount = Config::Enemy::getRandomPointCount();
	this->speed = static_cast<float>(this->pointCount / Config::Enemy::speedconv);
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
	this->shape.setRadius(this->pointCount * Config::Enemy::radiusconv);
	this->shape.setPointCount(this->pointCount);
	this->shape.setTexture(&texture);
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

