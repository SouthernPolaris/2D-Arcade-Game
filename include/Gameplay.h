#ifndef GAMEPLAY_H
#define GAMEPLAY_H

/* Header file of main gameplay class. Has player and multiple enemies. 
    Also has projectiles originating from player. Player can also control movement */

#include <SFML/Graphics.hpp>
#include "Display.h"
#include "Player.h"
#include "Entity.h"
#include "Enemy.h"
#include "Projectile.h"
#include "HealingItems.h"
#include <vector>
#include <map>
#include <string>
#include <chrono>

class Gameplay: public Display {
    private:
        // Variables
        Player mainChar;

        // Pointer to base class points to derived class
        std::vector<Entity*> enemies;
    
        std::vector<Enemy*> enemyVector;
        std::vector<HealingItems*> healthReplenish;
        std::chrono::steady_clock::time_point healingTime;
        float deltaHealingTime;

        bool playerAlive;
        int currentScore;
        sf::Text scoreText;
        std::string score;

        sf::Text healthText;
        std::string health;

        sf::Text levelUpText;
        std::string level;

        sf::Text defeatedText;

    public:
        // Member functions
        Gameplay(int windowWidth, int windowHeight, sf::RenderWindow &window);

        void drawMenu(sf::RenderWindow &window);

        void addEnemy();

        void enemyDefeated(sf::RenderWindow &window);

        void spawnHealing(sf::RenderWindow &window);

        void invalidKey(sf::RenderWindow &window);

        Player* getPlayer();

        bool getPlayerAlive();

        int getScore();
        void setScore(int score);

        void setPlayer(Player player);
        ~Gameplay();

};

#endif