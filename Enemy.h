#ifndef ENEMY_H
#define ENEMY_H

/* Header file for the class for Enemies. Can be a boss. Targets player location
    and moves towards them */

#include <string>
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Enemy: public Entity {
    private:
        bool isBoss;
        float playerAngle;
        int counter;
        sf::Texture regular;
        sf::Texture boss;
    public:
        Enemy(std::string name, int vitality, int strength, int luck, bool isBoss);
        Enemy();

        void move(sf::RenderWindow &window, float displacementX, float displcementY);

        // bool getIsBoss();
        // void setIsBoss(bool isBoss);

        bool aliveStatus(float ballX, float ballY, int radius, Entity* entity);

        void setPosition(float x, float y);
        void setBossTexture();

        bool spendPoints();
};

#endif