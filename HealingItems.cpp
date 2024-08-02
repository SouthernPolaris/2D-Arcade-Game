/* Implementation file for the HealingItems class */

#include <SFML/Graphics.hpp>
#include <chrono>
#include <cstdlib>
#include "HealingItems.h"
#include <iostream>

HealingItems::HealingItems(int windowWidth, int windowHeight) {

    // Summon healing at random positions

    srand(time(0));

    xPosition = rand() % windowWidth;
    yPosition = rand() % windowHeight;

    sf::Sprite tempSprite;
    healthSprite = tempSprite;

    if(!healthTexture.loadFromFile("health.png")) {

    }

    healthSprite.setTexture(healthTexture);

    // Set the sprite on the screen
    // size = 20;
    // healthSprite.setSize(sf::Vector2f(size, size));
    // healthSprite.setFillColor(sf::Color::Green);
    healthSprite.setScale(0.2, 0.2);
    healthSprite.setPosition(xPosition, yPosition);

}

// Draw healing sprite
void HealingItems::drawHealing(sf::RenderWindow &window) {
    window.draw(healthSprite);
}

// Test if player interacts
bool HealingItems::playerInteracts(float playerX, float playerY) {

    bool interact = healthSprite.getGlobalBounds().contains(playerX, playerY);
    return interact;
}

// Destructor
HealingItems::~HealingItems() {

}

