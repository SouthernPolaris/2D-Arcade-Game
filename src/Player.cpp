/* Implementation file for player class */

#include <string>
#include "Entity.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <algorithm>
#include <cmath>
#include "Stats.h"

// Constructor
Player::Player(std::string name, int vitality, int strength, int luck) : 
    Entity(name, vitality, strength, luck)
{

    sf::Sprite playerIcon;

    sprite = playerIcon;

    // sprite.setOrigin((sprite.getLocalBounds().width) / 2, (sprite.getLocalBounds().height) / 2);

    // sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("assets/mainShip.png")) {

    }

    if(!projectileTexture.loadFromFile("assets/ShipProjectile.png")) {

    }

    sprite.setTexture(playerTexture);

    // sprite.setFillColor(sf::Color::Black);
    // sprite.setOutlineColor(sf::Color::White);
    // sprite.setOutlineThickness(3);
    sprite.setPosition(1000/2, 1000 - 1000/6);

    // mainCharSprite = sprite;

    projectileTime = clockCount::now();

    defeated = 0;

}

// Default constructor
Player::Player() : Player("Hero", 1, 1, 1) {

}

// Collision and alive status
bool Player::aliveStatus(float ballX, float ballY, int radius, Entity* entity) {
    bool alive = true;


    float distBetween_sqr = abs(((ballX - displacement.first) * (ballX - displacement.first)) + 
        ((ballY - displacement.second) * (ballY - displacement.second)));
    
    float radius_sqr = (radius + size) * (radius + size);


    // Randomise damage based on luck
    srand(time(0));

    if (distBetween_sqr < radius_sqr) {
        int damageToTake = entity->getStrength();
        
        int offsetDir = rand() % getLuck();

        if(offsetDir > (rand() % getLevel())) {
            damageToTake++;
        }

        takeDamage(damageToTake);
    }

    if (currentHealth <= 0) {
        alive = false;
    }

    return alive;
}

void Player::move(sf::RenderWindow &window) {
    
    // Moves based on keyboard movement with WASD keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        
        // Limits player from going over the borders
        if(sprite.getPosition().x >= 0) {
            sprite.move(-8, 0.f);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
       
        // Limits player from going over the borders
        if(sprite.getPosition().x <= window.getSize().x) {
            sprite.move(8, 0.f);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        
        // Limits player from going over the borders
        if (sprite.getPosition().y >= 0) {
            sprite.move(0.f, -8);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        
        // Limits player from going over the borders
        if(sprite.getPosition().y <= window.getSize().y) {
            sprite.move(0.f, 8);
        }
    }

    // Rotates sprite to always point to mouse cursor

    sf::Vector2i mousePos = {sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y};

    float rotationCoordsX = mousePos.x - sprite.getPosition().x;
    float rotationCoordsY = mousePos.y - sprite.getPosition().y;

    playerAngle = 3.14/2 + atan2(rotationCoordsY, rotationCoordsX);

    sprite.setRotation(playerAngle * 180 / 3.14);

    // Draws player and projectile

    window.draw(sprite);

    for(size_t i = 0; i < projectiles.size(); i++) {
        projectiles[i].drawProjectile(window);
    }

}

void Player::shoot(sf::RenderWindow &window, sf::Event &event) {
    
    // Set time before each projectile fires
    clockCount::time_point tempTime = clockCount::now();
    deltaProjectile = chrono::duration<float>(tempTime - projectileTime).count();


    // Determines where the projectile is summoned
    displacement.first = sprite.getPosition().x;
    displacement.second = sprite.getPosition().y;



    if (deltaProjectile > 0.1) {
        
        Projectile tempProjectile(10, displacement.first, displacement.second, 10, 10, playerAngle);
        tempProjectile.setProjectileTexture(projectileTexture);
        projectiles.push_back(tempProjectile);
        // projectiles.back().setProjectileTexture(projectileTexture);
        projectileTime = tempTime;
        deltaProjectile = 0;
    }

    // If there are too many on screen at once, erase the first one

    if(projectiles.size() > 10) {
        projectiles.erase(projectiles.begin());
    }


}

// Levels up character
bool Player::levelUp(int defeated) {
    
    int tempLevel = defeated % 5;

    if (tempLevel == 0 && this->defeated == defeated - 5) {
        setLevel(getLevel() + 1);
        this->defeated = defeated;

        srand(time(0));


        // Upgrades a random stat
        int StatUp = rand() % 3;

        if (StatUp == 0) {
            setVitality(getVitality() + 1);
            setCurrentHealth(getBaseHealth());
            std::cout << "Levelled up vitality\n";
        } else if (StatUp == 1) {
            setStrength(getStrength() + 1);
            std::cout << "Levelled up strength\n";
        } else if (StatUp == 2) {
            setLuck(getLuck() + 1);
            std::cout << "Levelled up luck\n";
        } else {
            std::cout << "Error levelling\n";
        }

        return true;
    }

    return false;
}

void Player::takeDamage(int dealtDamage) {
    
    // Timer to give player a second of immunity
    clockCount::time_point playerImmunityNow = clockCount::now();
    float lengthImmunity = chrono::duration<float>(playerImmunityNow - playerImmunity).count(); 

    // Dealing damage
    if (lengthImmunity > 1) {
        currentHealth -= dealtDamage;
        playerImmunity = clockCount::now();
    }
}

bool Player::spendPoints() {
    return true;
}

Player::~Player() {

}