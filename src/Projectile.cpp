/* Implementation file for projectiles */

#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include <cmath>
#include <iostream>


// Constructor
Projectile::Projectile(float size, float positionX, float positionY, float velocityX, float velocityY, float playerAngle) {
    
    // Positions projectile respective to player
    playerAngle = playerAngle - (3.14 / 2);
    
    float offsetX = 20 * cos(playerAngle);
    float offsetY = 20 * sin(playerAngle);

    this->playerAngle = playerAngle;

    position = {positionX + offsetX, positionY + offsetY};
    velocity = {2 * (velocityX * cos(playerAngle)), 2 * (velocityY * sin(playerAngle))};
    radius = size;

    // Creates sprite
    sf::Sprite myProjectile;
    projectile = myProjectile;

    projectile.setPosition(position.first, position.second);
    projectile.setRotation((3.14 / 2 + playerAngle) * 180.0 / 3.14);

}

// Draws projectile and moves it
void Projectile::drawProjectile(sf::RenderWindow &window) {
    projectile.move(velocity.first, velocity.second);
    window.draw(projectile);
}

// Gets radius
int Projectile::getRadius() {
    return radius;
}

void Projectile::setProjectileTexture(sf::Texture& texture) {
    projectile.setTexture(texture);
}

// Destructor
Projectile::~Projectile() {
    
}