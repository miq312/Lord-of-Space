#include "Bullet.h"
#include "Utilities.h"

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float move_speed)
{
	this->shape.setTexture(*texture);
	this->shape.setPosition(pos_x, pos_y);
	this->shape.setScale(Util::Bullet::scaleX, Util::Bullet::scaleY);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movespeed = move_speed;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullet::update()
{
	this->shape.move(this->movespeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}


