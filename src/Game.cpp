#include "Game.h"
#include "Utilities.h"

Game::Game()
{
    this->initWindow();
    this->initMenu();
    this->initTextures();
    this->initPlayer();
    this->initEnemies();
    this->initWorld();
    this->initGui();
    this->initSystem();
    this->initExplosion();

    this->gameState = MENU;
}

Game::~Game()
{
    delete this->window;
    delete this->player;

    for (auto& i : this->textures)
    {
        delete i.second;
    }

    for (auto* i : this->bullets)
    {
        delete i;
    }
    for (auto* i : this->enemies)
    {
        delete i;
    }

    this->explosions.clear();
}

//functions
void Game::run()
{
    while (this->window->isOpen())
    {
        this->updatePollEvents();
        if (this->player->getHp() > 0)
            this->update();

        this->render();
    }
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1200, 850), "Lords of space", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
    this->textures["BULLET"] = new sf::Texture();
    if (!this->textures["BULLET"]->loadFromFile("../../Images/bullet.png"))
        std::cout << "ERROR::GAME::INITTEXTURE::Could not load texture file" << std::endl;
}

void Game::initPlayer()
{
    this->player = new Player();
}

void Game::initEnemies()
{
    this->spawnTimerMax = Util::Game::spawnTMax;
    this->spawnTimer = this->spawnTimerMax;
}

void Game::initExplosion()
{
    this->explosionTimeMax = Util::Game::explosiontimemax;
    this->explosionTime = Util::Game::explosiontime;
}

void Game::initGui()
{
    if (!this->font.loadFromFile("../../Fonts/calibri.ttf"))
        std::cout << "FAIL::GAME::INITGUI::Failed load font" << std::endl;

    this->pointText.setPosition(1000, 10);
    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(30);
    this->pointText.setFillColor(sf::Color::White);
    this->pointText.setString("test");

    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(80);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("GAME OVER");
    this->gameOverText.setPosition(
        this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
        this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

    this->gameOverTextHint.setFont(this->font);
    this->gameOverTextHint.setCharacterSize(30);
    this->gameOverTextHint.setFillColor(sf::Color(128, 128, 128));
    this->gameOverTextHint.setString("Press space to go to the menu");
    this->gameOverTextHint.setPosition(
        this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
        this->window->getSize().y - 100);

    this->pauseText.setFont(this->font);
    this->pauseText.setCharacterSize(30);
    this->pauseText.setFillColor(sf::Color::White);
    this->pauseText.setString("PAUSE");
    this->pauseText.setOrigin(this->pauseText.getGlobalBounds().width / 2.f, this->pauseText.getGlobalBounds().height / 2.f);
    this->pauseText.setPosition(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);


    //Init PlayerGui
    this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

    std::cout << "about" << std::endl;
    this->aboutText.setPosition(10, 10);
    this->aboutText.setFont(this->font);
    this->aboutText.setCharacterSize(30);
    this->aboutText.setFillColor(sf::Color::Blue);
    this->aboutText.setString("Welcome to Lords of Space!\n\n"
        "Lords of Space is an exciting space-themed shooter game where you, as the player,\n"
        "take control of a powerful spaceship to defend against waves of enemy invaders.\n\n"
        "Controls:\n"
        " - Use 'W', 'A', 'S', 'D' to move your spaceship.\n"
        " - Press the left mouse button to shoot bullets and eliminate enemies.\n"
        " - Avoid colliding with enemies to maintain your spaceship's health.\n"
        " - Collect points by destroying enemies and aim for the highest score!\n\n"
        "Future Improvements:\n"
        " - Expand gameplay with even more challenging enemy waves and unique adversaries.\n"
        " - Enhance visual experience with cutting-edge graphics and mesmerizing visual effects.\n"
        " - Introduce new gameplay elements, such as power-ups and special abilities for your spaceship.\n"
        " - Implement a leaderboard system to allow players to compete for high scores globally.\n"
        " - Unlock achievements and rewards to become the ultimate Lord of Space!\n\n"
        "Press 'Space' to return to the main menu and embark on your evolving space adventure!"

    );


}

void Game::initWorld()
{
    if (!this->worldBackgroundTexture.loadFromFile("../../Images/world.png"))
        std::cout << "FAIL::GAME::INITWORLD::Failed load texture file" << std::endl;
    this->worldBackground.setTexture(this->worldBackgroundTexture);
    this->worldBackground.setScale(0.5, 0.5);  //poprawic
}

void Game::initSystem()
{
    this->points = 0;
}

void Game::initMenu()
{
    this->menu = new Menu(this->window->getSize().x, this->window->getSize().y);
}

void Game::updatePollEvents()
{
    sf::Event e;
    while (this->window->pollEvent(e))
    {
        if (e.Event::type == sf::Event::Closed)
            this->window->close();
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
            this->window->close();
    }
}

void Game::setGameState(GameState newState)
{
    this->gameState = newState;
}

void Game::updateInit()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        this->player->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        this->player->move(0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        this->player->move(0.f, 1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        this->player->move(1.f, 0.f);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAtack())// or if (... && !isShooting)
    {
        this->bullets.push_back(
            new Bullet(
                this->textures["BULLET"],
                this->player->getPos().x + this->player->getBounds().width / 2.f,
                this->player->getPos().y,
                0.f,
                -1.f,
                5.f
            )
        );
        isShooting = true;
    }

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        isShooting = false;
    }
}

void Game::updateBullets()
{
    unsigned counter = 0;
    for (auto* bullet : this->bullets)
    {
        bullet->update();

        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {
            delete this->bullets.at(counter);
            this->bullets.erase(this->bullets.begin() + counter);
        }

        ++counter;
    }
}


void Game::updateEnemies()
{
    this->spawnTimer += 0.5f;
    if (this->spawnTimer >= this->spawnTimerMax)
    {
        this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 30.f, -100.f));
        this->spawnTimer = 0.f;
    }

    unsigned counter = 0;
    for (auto* enemy : this->enemies)
    {
        enemy->update();

        if (enemy->getBounds().top > this->window->getSize().y)
        {
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
        }

        else if (enemy->getBounds().intersects(this->player->getBounds()))
        {
            this->player->loseHp(this->enemies.at(counter)->getDamage());
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
        }
        ++counter;
    }
}

void Game::updateCombat()
{
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        bool enemy_deleted = false;
        for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
        {
            if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
            {
                //wspolrzedne ekspolzji
                this->explosions.push_back(std::make_shared<Explosion>(this->enemies[i]->getPosition().x, this->enemies[i]->getPosition().y));

                this->points += this->enemies[i]->getPoints();

                delete this->bullets[k];
                this->bullets.erase(this->bullets.begin() + k);

                delete this->enemies[i];
                this->enemies.erase(this->enemies.begin() + i);

                enemy_deleted = true;
            }
        }
    }
}

void Game::updateExplosion()
{
    this->explosionTime += 1.2f;

    if ((this->explosionTime >= this->explosionTimeMax) && !this->explosions.empty())
    {
        this->explosions.erase(this->explosions.begin());
        this->explosionTime = 0;
    }
}


void Game::updateCollision()
{
    //left screen collision
    if (this->player->getBounds().left < 0.f)
    {
        this->player->setPosition(0.f, this->player->getBounds().top);
    }

    //right screen collision
    else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
    {
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
    }

    //top screen collision
    if (this->player->getBounds().top < 0.f)
    {
        this->player->setPosition(this->player->getBounds().left, 0.f);
    }

    //bottom screen collision
    else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
    {
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
    }
}

void Game::updateWorld()
{
}

void Game::updateGui()
{
    std::stringstream ss;
    ss << "Points: " << this->points;

    this->pointText.setString(ss.str());


    //Update PlayerGui

    float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
    this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateMenu()
{
    static bool arrowKeyPressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !arrowKeyPressed) {
        this->menu->moveUp();
        arrowKeyPressed = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !arrowKeyPressed) {
        this->menu->moveDown();
        arrowKeyPressed = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        arrowKeyPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        switch (menu->menuPressed())
        {
        case 1:
            this->setGameState(GAME_PLAY);
            break;
        case 2:
            this->setGameState(MENU_ABOUT);
            break;
        case 3:
            this->window->close();
            break;
        }
    }
}


void Game::renderGui()
{
    this->window->draw(this->pointText);
    this->window->draw(this->playerHpBar);
    this->window->draw(this->playerHpBarBack);
}

void Game::renderWorld()
{
    this->window->draw(this->worldBackground);
}

void Game::resetGame()
{
    this->points = 0;
    this->player->reset();
    this->bullets.clear();
    this->enemies.clear();
    this->explosions.clear();
    this->setGameState(MENU);
}

void Game::updateGameOver()
{
    isVisible = static_cast<int>(clock.getElapsedTime().asSeconds()) % 2 == 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        this->setGameState(MENU);
    }
}

void Game::updateGamePlay()
{
    this->updateInit();
    this->player->update();
    this->updateCollision();
    this->updateBullets();
    this->updateEnemies();
    this->updateCombat();
    this->updateExplosion();
    this->updateGui();
    this->updateWorld();
    if (this->player->getHp() <= 0)
    {
        this->resetGame();
        this->setGameState(GAME_OVER);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        this->setGameState(GAME_PAUSE);
}

void Game::updateGamePause()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        this->setGameState(GAME_PLAY);
    }
}

void Game::updateAboutMenu()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        this->gameState = MENU;
    }
}

void Game::renderAboutMenu()
{
    this->window->draw(aboutText);
}

void Game::update()
{
    switch (gameState)
    {
    case MENU:
        this->updateMenu();
        break;
    case MENU_ABOUT:
        this->updateAboutMenu();
        break;

    case GAME_PLAY:
        this->updateGamePlay();
        break;

    case GAME_PAUSE:
        this->updateGamePause();
        break;

    case GAME_OVER:
        this->updateGameOver();
        break;
    }
}
void Game::render()
{
    this->window->clear();

    switch (this->gameState)
    {
    case MENU:
        this->menu->render(this->window);
        break;

    case MENU_ABOUT:
        this->renderAboutMenu();
        break;

    case GAME_PLAY:

        this->renderWorld();

        this->player->render(*this->window);

        for (auto* bullet : this->bullets)
        {
            bullet->render(this->window);
        }

        for (auto* enemy : this->enemies)
        {
            enemy->render(this->window);
        }

        this->renderGui();
        for (auto& explosion : this->explosions)
            explosion->render(this->window);
        break;

    case GAME_PAUSE:
        this->window->draw(this->pauseText);
        break;
    case GAME_OVER:

        this->window->draw(this->gameOverText);
        if (isVisible)
            this->window->draw(this->gameOverTextHint);
        break;
    }
    this->window->display();
}

