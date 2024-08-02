/* Implementation of the main gameplay class */

#include <SFML/Graphics.hpp>
#include "Display.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include <vector>
#include <cmath>
#include "HealingItems.h"
#include "Gameplay.h"
#include <cstdlib>
#include <chrono>
#include <fstream>

// Constructor
Gameplay::Gameplay(int windowWidth, int windowHeight, sf::RenderWindow &window) :
    Display(windowWidth, windowHeight, window)
{

    // Randomises stats of enemies
    int vitality = (rand() % mainChar.getLevel() + 1) / 4;
    int strength = (rand() % mainChar.getLevel() + 1)/ 4;
    int luck = (rand() % mainChar.getLevel() + 1)/ 4;

    // Creates enemy based on random stats and stores them in vector
    Enemy* tempEnemy = new Enemy("Bad Guy", vitality, strength, luck, 0);
    
    // Stores pointers in vector of base class
    enemies.push_back(tempEnemy);
    enemyVector.push_back(tempEnemy);
    playerAlive = true;
    currentScore = 0;

    // Set the healing spawn timer
    healingTime = std::chrono::steady_clock::now();
    
    level = "3";

}

void Gameplay::drawMenu(sf::RenderWindow &window) {

    if(!background_texture.loadFromFile("SpaceBackground.png")) {

    }
    sf::Sprite background(background_texture);

    // double scale = window.getSize().x / 1000;
    // background.setScale(scale, scale);
    window.draw(background);

    // If the player is alive
    if (playerAlive) {



        // Score 
        score = to_string(currentScore);
        scoreText.setString("Score: " + score);

        // Font loading
        if(!mainFont.loadFromFile("arial.ttf")) {
                std::cout << "Font loading error" << std::endl;
        }

        // Text initialisation
        scoreText.setFont(mainFont);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10,10);
        scoreText.setCharacterSize(20);

        // Text Drawing
        window.draw(scoreText);
        
        // Health Text
        health = "Health: ";
        health.append(to_string(mainChar.getCurrentHealth()));
        healthText.setString(health);
        healthText.setFont(mainFont);
        healthText.setFillColor(sf::Color::White);
        healthText.setOrigin(healthText.getLocalBounds().width, 0);
        healthText.setPosition(windowWidth - 10, 10);
        healthText.setCharacterSize(20);

        // Draw health text
        window.draw(healthText);

        // Enemy movement
        for (size_t i = 0; i < enemies.size(); i++) {
            float displacementX = mainChar.displacement.first;
            float displacementY = mainChar.displacement.second;

            enemies[i]->move(window, displacementX, displacementY);
            window.draw(*(enemies[i]->getSprite()));
            playerAlive = mainChar.aliveStatus(enemies[i]->displacement.first, enemies[i]->displacement.second, enemies[i]->getSize(), enemies[i]);
        }

        // Player leveling
        bool increaseLevel = mainChar.levelUp(currentScore);

        if (increaseLevel) {
            level = to_string(mainChar.getLevel());
        }

        // Displays level
        
        levelUpText.setString("Level: " + level);
        levelUpText.setFont(mainFont);
        levelUpText.setFillColor(sf::Color::White);
        levelUpText.setOrigin(0, levelUpText.getLocalBounds().height);
        levelUpText.setPosition(10, windowHeight - 50);

        window.draw(levelUpText);




        // Health spawning
        spawnHealing(window);
    }
    
    // If the player dies
    if (playerAlive == false) {
        
        // Load font
        if(!mainFont.loadFromFile("arial.ttf")) {
            std::cout << "Font loading error" << std::endl;
        }

        // Initialise defeated text
        defeatedText.setString("You were defeated. ESC to exit");
        defeatedText.setFont(mainFont);
        defeatedText.setCharacterSize(48);
        defeatedText.setFillColor(sf::Color::Black);
        defeatedText.setOutlineColor(sf::Color::White);
        defeatedText.setOutlineThickness(3);
        defeatedText.setOrigin((defeatedText.getLocalBounds().width) / 2.f, (defeatedText.getLocalBounds().height) / 2.f);
        // Text follows player location
        defeatedText.setPosition(mainChar.displacement.first, mainChar.displacement.second - (1000 * 2/6));
        // Draw defeated text
        window.draw(defeatedText);
    
        // Write score to file if higher than previous high score
        if (currentScore > std::stoi(highScore)) {
            std::ofstream scoreFile;
            scoreFile.open ("High Score.txt");
            scoreFile << currentScore;
            scoreFile.close();
            highScore = score;
        }
    }

    return;
}

void Gameplay::enemyDefeated(sf::RenderWindow &window) {
    
    // Check if enemy vector is empty
    if(enemies.size() < 1) {
        return;
    }

    size_t idx = 0;

    // Iterates through enemies vector. Uses while loop as size changes inside loop itself
    while(idx < enemies.size()) {
        bool test = true;
        // Loops through each projectile
        for (size_t i = 0; i < mainChar.projectiles.size(); i++) {
            
            // Tests for collision
            test = enemyVector[idx]->aliveStatus(mainChar.projectiles[i].position.first, 
                mainChar.projectiles[i].position.second, mainChar.projectiles[i].getRadius(), &mainChar);
            if (test == false) {
                break;
            }
        }
        
        // If collides, delete that enemy from the vector after deallocating memory
        // Also increment score
        if (test == false) {
            enemies[idx]->getSprite()->setColor(sf::Color::Transparent);
            currentScore++;
            delete enemies[idx];
            enemies.erase(enemies.begin() + idx);
            enemyVector.erase(enemyVector.begin() + idx);
            idx--;
            break;
        }

        // If enemies go out of bounds, also delete enemies, but don't increment score
        if (enemies[idx]->displacement.first < 0 || enemies[idx]->displacement.second < 0 || 
                    enemies[idx]->displacement.first > windowWidth || enemies[idx]->displacement.second > windowHeight) 
        {
            delete enemies[idx];
            enemies.erase(enemies.begin() + idx);
            enemyVector.erase(enemyVector.begin() + idx);
            idx--;
        }

        idx++;
    }
}

// Randomly spawns enemy
void Gameplay::addEnemy() {

    srand(time(0));

    int level = mainChar.getLevel();

    // Gets randon stats for enemy
    int randStats = rand() % 2 + (level - 2);

    // Randomises if the enemy is a boss enemy
    int bossRand = rand() % 100;
    bool bossBool = false;

    if(bossRand >= 90) {
        bossBool = true;
    }

    // Creates an enemy pointer and stores them into a vector of entity pointers
    Enemy* tempEnemy = new Enemy("Bad Guy", randStats, randStats, randStats, bossBool);
    
    if (bossBool == true) {
        tempEnemy->setSize((tempEnemy->getSize()) * 2);
        
        // sf::Texture bossTexture;

        // if(!bossTexture.loadFromFile("bossEnemy.png")) {
        //     std::cout << "Boss Texture Failed to Load\n";
        // }
        
        tempEnemy->setBossTexture();
        // tempEnemy->getSprite()->setScale(2, 2);
    }

    int positionX = rand() % windowWidth;
    int positionY = rand() % (windowHeight/3);
    
    tempEnemy->setPosition(positionX, positionY);
    
    enemies.push_back(tempEnemy);
    enemyVector.push_back(tempEnemy);

    

}

void Gameplay::spawnHealing(sf::RenderWindow &window) {

    // Timer to spawn healing at set times
    std::chrono::steady_clock::time_point tempHealingTime = std::chrono::steady_clock::now();
    deltaHealingTime = std::chrono::duration<float>(tempHealingTime - healingTime).count();

    // Spawn healing items after certain time
    if(deltaHealingTime > 10) {
        HealingItems* healthItem = new HealingItems(windowWidth, windowHeight);
        healthReplenish.push_back(healthItem);
        healingTime = std::chrono::steady_clock::now();
    }

    // Set max limit for items on screen
    if (healthReplenish.size() > 5) {
        delete healthReplenish[0];
        healthReplenish.erase(healthReplenish.begin());
    }

    // Draw healing
    for(size_t i = 0; i < healthReplenish.size(); i++) {
        healthReplenish[i]->drawHealing(window);

        // Check if player interacts with any of them
        bool healthContact = healthReplenish[i]->playerInteracts(mainChar.displacement.first, mainChar.displacement.second);

        // Heal character
        if (healthContact == true && mainChar.getCurrentHealth() <= (mainChar.getBaseHealth() - (mainChar.getCurrentHealth()/5))) {
            mainChar.setCurrentHealth(mainChar.getCurrentHealth() + (mainChar.getCurrentHealth() / 5));

            delete healthReplenish[i];
            healthReplenish.erase(healthReplenish.begin() + i);

            i--;
        }

    }

}

void Gameplay::invalidKey(sf::RenderWindow &window) {
    std::cout << "Invalid Key" << std::endl;
}

// Getters and setters
bool Gameplay::getPlayerAlive() {
    return playerAlive;
}

Player* Gameplay::getPlayer() {
    return &mainChar;
}

void Gameplay::setPlayer(Player player) {
    this->mainChar = player;
}

int Gameplay::getScore() {
    return currentScore;
}

void Gameplay::setScore(int score) {
    currentScore = score;
}

// Destructor
Gameplay::~Gameplay() {
    // Delete all of the shallow copies in vectors
    for (size_t i = 0; i < enemies.size(); i++) {
        delete enemies[i];
    }

    for (size_t i = 0; i < healthReplenish.size(); i++) {
        delete healthReplenish[i];
    }
}