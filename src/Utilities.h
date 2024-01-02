#pragma once
#include <cstdlib>
#include <string>

namespace Util
{
    namespace Game
    {
        extern float spawnTMax;
        extern float explosiontimemax;
        extern float explosiontime;
        extern float windowSizeX;
        extern float windowSizeY;
        extern std::string abouttext;
    }

    namespace Player
    {
        extern float movespeed;
        extern float attackcoolcownmax;
        extern int hpmax;
        extern float scaleX;
        extern float scaleY;
        extern float startPositionX;
        extern float startPositionY;
    }

    namespace Enemy
    {
        extern int getRandomPointCount();
        extern float radiusconv;
        extern float speedconv;
    }

    namespace Bullet
    {
        extern float scaleX;
        extern float scaleY;
    }

    namespace Explosion
    {
        extern float scaleX;
        extern float scaleY;
    }

    namespace Menu
    {
        
    }
}
