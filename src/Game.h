#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <map>
#include <string>
#include <sstream>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Explosion.h"


class Game
{
private:
    //Window
    sf::RenderWindow* window;

    //Reasurces
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;
    bool isShooting = false;

    //Player
    Player* player;

    //Enemies
    float spawnTimer;
    float spawnTimerMax;
    std::vector<Enemy*> enemies;

    //GUI
    sf::Font font;
    sf::Text pointText;

    sf::Text gameOverText;

    //World
    sf::Sprite worldBackground;
    sf::Texture worldBackgroundTexture;

    //System
    unsigned points;

    //PlayerGui
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;

    //Explosion
    std::vector<Explosion*> explosions;
    float explosionTime;
    float explosionTimeMax;

    //private functions 
    void initWindow();
    void initTextures();
    void initPlayer();
    void initEnemies();
    void initExplosion();
    void initGui();
    void initWorld();
    void initSystem();

public:
    Game();
    virtual ~Game();

    //functions
    void run();
    void update();
    void render();
    void updatePollEvents();
    void updateEnemies();
    void updateWorld();
    void updateCollision();
    void updateInit();
    void updateBullets();
    void updateCombat();
    void updateExplosion();
    void updateGui();
    void renderGui();
    void renderWorld();
};