#include "Game.h"
//#include "Utilities.h"

Game::Game()
{
    this->initWindow();
    this->initTextures();
    this->initPlayer();
    this->initEnemies();
    this->initWorld();
    this->initGui();
    this->initSystem();
    this->initExplosion();
}

Game::~Game()
{
    delete this->window;
    delete this->player;

    for (auto &i : this->textures)
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
    for (auto* i : this->explosions)
    {
        delete i;
    }
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
    if(!this->textures["BULLET"]->loadFromFile("Images/bullet.png"))
        std::cout << "ERROR::GAME::INITTEXTURE::Could not load texture file" << std::endl;
}

void Game::initPlayer()
{
    this->player = new Player();
}

void Game::initEnemies()
{
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;
}

void Game::initExplosion()
{
    this->explosionTimeMax = 150.f;
    this->explosionTime = 0.f;
}

void Game::initGui()
{
    if (!this->font.loadFromFile("Fonts/calibri.ttf"))
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


    //Init PlayerGui
    this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
    if (!this->worldBackgroundTexture.loadFromFile("Images/world.png"))
        std::cout << "FAIL::GAME::INITWORLD::Failed load texture file" << std::endl;
    this->worldBackground.setTexture(this->worldBackgroundTexture);
    this->worldBackground.setScale(1.95, 1.55);  //poprawic
}

void Game::initSystem()
{
    this->points = 0;
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
                this->player->getPos().x + this->player->getBounds().width/2.f,
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
                this->explosions.push_back(new Explosion(this->enemies[i]->getPosition().x, this->enemies[i]->getPosition().y));

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
    this->explosionTime += 1.f;
    //if (this->explosions.size() >= 2)
    //{
    //   delete this->explosions[0];
    //    this->explosions.erase(this->explosions.begin());
    //}

    if ((this->explosionTime >= this->explosionTimeMax) && !this->explosions.empty())
    {
        delete this->explosions[0];
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
        this->player->setPosition(this->player->getBounds().left , this->window->getSize().y - this->player->getBounds().height);
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

void Game::update()
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
}

void Game::render()
{
    this->window->clear();
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
    for (auto* explosion : this->explosions)
        explosion->render(this->window);

    if (this->player->getHp() <= 0)
        this->window->draw(this->gameOverText);
    this->window->display();
}

