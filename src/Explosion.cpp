#include "Explosion.h"
#include "Utilities.h"

void Explosion::initShape()
{
	if (!this->texture.loadFromFile("../../Images/explosion.png"))
	{
		std::cout << "ERROR::EXPLOSION::INITSHAPE::Could not load texture file" << std::endl;
	}

	this->shape.setTexture(texture);
	this->shape.setScale(Util::Explosion::scaleX, Util::Explosion::scaleY);
}

Explosion::Explosion(float pos_x, float pos_y)
{
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
}

Explosion::~Explosion()
{
}

void Explosion::update()
{
}

void Explosion::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

sf::Vector2f Explosion::getPosition() const
{
	return this->shape.getPosition();
}

