#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <map>
#include <string>
#include <sstream>
#include <set>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Menu.h"

enum GameState
{
    MENU,
    GAME_PLAY,
    GAME_PAUSE,
    GAME_OVER,
};

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
    sf::Text gameOverTextHint;
    sf::Clock clock;
    bool isVisible;

    //World
    sf::Sprite worldBackground;
    sf::Texture worldBackgroundTexture;

    //System
    unsigned points;

    //PlayerGui
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;

    //Explosion
    std::vector<std::shared_ptr<Explosion>> explosions;
    float explosionTime;
    float explosionTimeMax;

    //Menu
    Menu* menu;

    GameState gameState;

    //private functions 
    void initWindow();
    void initTextures();
    void initPlayer();
    void initEnemies();
    void initExplosion();
    void initGui();
    void initWorld();
    void initSystem();
    void initMenu();

public:
    Game();
    virtual ~Game();

    //functions
    void run();
    void update();
    void render();
    void updatePollEvents();
    void setGameState(GameState newState);
    void updateEnemies();
    void updateWorld();
    void updateCollision();
    void updateInit();
    void updateBullets();
    void updateCombat();
    void updateExplosion();
    void updateGui();
    void updateMenu();
    void renderGui();
    void renderWorld();
    void resetGame();
    void updateGameOver();
    void updateGamePlay();
};