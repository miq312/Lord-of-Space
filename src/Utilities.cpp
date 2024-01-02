#include "Utilities.h"

namespace Util
{
    namespace Game
    {
        float spawnTMax{ 50.f };
        float explosiontimemax{ 150.f };
        float explosiontime{ 0.f };
        float windowSizeX{ 1200 };
        float windowSizeY{ 850 };
        std::string abouttext {"Welcome to Lords of Space!\n\n"
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
        "Press 'Space' to return to the main menu and embark on your evolving space adventure!\n\n"
        "Lords of Space was created by Michal Lazarz, a passionate game developer,\n"
            "Follow me on https://github.com/miq312 for updates and more exciting projects.\n"};
    }

    namespace Player
    {
        float movespeed{ 3.5f };
        float attackcoolcownmax{ 10.f };
        int hpmax{ 100 };
        float scaleX{ 0.1f };
        float scaleY{ 0.1f };
        float startPositionX{ 500.f };
        float startPositionY{ 500.f };
    }

    namespace Enemy
    {
        int getRandomPointCount() { return rand() % 8 + 3; }
        float radiusconv{ 7.f };
        float speedconv{ 3.f };
    }

    namespace Bullet
    {
        float scaleX{ 0.5f };
        float scaleY{ 0.5f };
    }

    namespace Explosion
    {
        float scaleX{ 0.5f };
        float scaleY{ 0.5f };
    }

    namespace Menu
    {
        
    }
}