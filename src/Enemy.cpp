/* Implementation file for enemy class */

#include <string>
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

Enemy::Enemy(std::string name, int vitality, int strength, int luck, bool isBoss) :
    Entity(name, ceil(vitality/10.0), strength, luck)
{
    this->isBoss = isBoss;

    if (isBoss == true) {
        baseHealth = baseHealth * 3;
        currentHealth = currentHealth * 3;
        strength = strength * 2;
        name = "Tough Guy";
    }

    counter = 0;

    sf::Sprite enemySprite;
    sprite = enemySprite;

    if(!regular.loadFromFile("assets/regularEnemy.png")) {

    }

    if(!boss.loadFromFile("assets/bossEnemy.png")) {

    }

    sprite.setTexture(regular);

    displacement = {100, 100};

    sprite.setPosition(displacement.first, displacement.second);



}

Enemy::Enemy() : Entity()
{
    this->isBoss = false;
}

void Enemy::setPosition(float x, float y) {

    displacement = {x, y};


    sprite.setPosition(displacement.first, displacement.second);
}

void Enemy::move(sf::RenderWindow &window, float displacementX, float displacementY) {

    // If the enemy is not too close to the player, go to their location
    if ((displacementX - displacement.first > 1/2 * windowWidth && displacementY - displacement.second > 1/2 * windowHeight) 
        || (counter == 0)) {
        float positionX = displacementX - displacement.first;
        float positionY = displacementY - displacement.second;
        playerAngle = atan2(positionY, positionX);
        counter++;
    }

    // The way they move is dependent on player location
    float velocityX = 10 * cos(playerAngle);
    float velocityY = 10 * sin(playerAngle);

    // Purple boss enemies move slower than regular red enemies
    if (isBoss == false) {
        sprite.move(velocityX, velocityY);
        displacement = {velocityX + displacement.first, velocityY + displacement.second};

        float rotationRadians = 3.14 / 2 + std::atan2(velocityY, velocityX);
        float rotationDegrees = rotationRadians * 180.0 / 3.14;
        sprite.setRotation(rotationDegrees);

    } else {
        sprite.move(velocityX / 2, velocityY / 2);
        displacement = {(velocityX / 2) + displacement.first, (velocityY / 2) + displacement.second};   

        float rotationRadians = 3.14 / 2 + std::atan2(velocityY / 2, velocityX / 2);
        float rotationDegrees = rotationRadians * 180.0 / 3.14;

        sprite.setRotation(rotationDegrees);
    }


}


bool Enemy::aliveStatus(float ballX, float ballY, int radius, Entity* entity) {

    bool alive = true;

    // If the distance between objects is smaller than their total radius, then they interact

    float distBetween_sqr = abs(((ballX - displacement.first) * (ballX - displacement.first)) + 
        ((ballY - displacement.second) * (ballY - displacement.second)));
    
    float radius_sqr = (radius + size) * (radius + size);

    

    // Randomise damage based on luck
    srand(time(0));

    if(distBetween_sqr < radius_sqr) {
        int damageToTake = entity->getStrength();
        
        int offsetDir = rand() % getLuck();

        if(offsetDir > (rand() % getLevel())) {
            damageToTake++;
        }

        
        takeDamage(damageToTake * 4);
    }

    // If health is less than 1, alive = false
    if (currentHealth <= 0) {
        alive = false;
    }


    return alive;
}

void Enemy::setBossTexture() {

    sprite.setTexture(boss);

}

bool Enemy::spendPoints() {
    return true;
}