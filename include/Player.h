#ifndef PLAYER_H
#define PLAYER_H

/* Header file of class that controls player. Can move the player around and summon projectiles*/

#include <string>
#include "Entity.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Projectile.h"

class Player: public Entity {
    private:
        // Variables
        float playerAngle;
        clockCount::time_point playerImmunity;
        clockCount::time_point projectileTime;
        float deltaProjectile;
        int defeated;
        sf::Texture playerTexture;
        sf::Texture projectileTexture;
    public:
        
        // Public variable
        std::vector<Projectile> projectiles;

        // Member functions

        Player(std::string name, int vitality, int strength, int luck);
        Player();

        bool aliveStatus(float ballX, float ballY, int radius, Entity* entity) override;

        void takeDamage(int dealtDamage);
        
        void move(sf::RenderWindow &window);
        void shoot(sf::RenderWindow &window, sf::Event &event);
        
        bool levelUp(int defetaed);
        bool spendPoints();

        // sf::CircleShape* getCharSprite();

        ~Player();
};

#endif