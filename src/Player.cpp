#include "Player.h"
#include "Utilities.h"

void Player::initSprite()
{
	this->sprite.setTexture(this->texture);

	this->sprite.scale(Util::Player::scaleX, Util::Player::scaleY);
}

void Player::initTexture()
{
	if (!this->texture.loadFromFile("../../Images/ship.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file" << std::endl;
	}
}

void Player::initVaraibles()
{
	this->moveSpeed = Util::Player::movespeed;
	this->attackCoolDownMax = Util::Player::attackcoolcownmax;
	this->attackCoolDown = this->attackCoolDownMax;

	this->hpMax = Util::Player::hpmax;
	this->hp = this->hpMax;
}

Player::Player()
{
	this->initVaraibles();

	this->initTexture();
	this->initSprite();
	this->setPosition(Util::Player::startPositionX, Util::Player::startPositionY);
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

const bool Player::canAtack()
{
	if (this->attackCoolDown >= this->attackCoolDownMax)
	{
		this->attackCoolDown = 0.f;
		return true;
	}

	return false;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::updateAttack()
{
	if (this->attackCoolDown < this->attackCoolDownMax)
		this->attackCoolDown += 0.5f;
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->moveSpeed * dirX, this->moveSpeed * dirY);
}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::reset()
{
	this->initVaraibles();
	this->setPosition(Util::Player::startPositionX, Util::Player::startPositionY);
}




