#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Explosion
{
private:

    sf::Sprite shape;
    sf::Texture texture;

    void initShape();

public:
    Explosion(float pos_x, float pos_y);
    virtual ~Explosion();

    void update();;
    void render(sf::RenderTarget* target);
    sf::Vector2f getPosition() const;
};

