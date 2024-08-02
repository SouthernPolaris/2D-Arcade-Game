#ifndef PROJECTILE_H
#define PROJECTILE_H

/* Header file for projectile class, which the player shoots on the screen */

#include <SFML/Graphics.hpp>

using namespace std;

class Projectile {
    protected:
        // Variables
        sf::Sprite projectile;
        sf::Texture projectileTexture;
        int radius;
        float playerAngle;
    public:

        // Public variables
        pair<float, float> position;
        pair<float, float> velocity;

        // Member functions
        Projectile(float size, float positionX, float positionY, float velocityX, float velocityY, float playerAngle);

        void drawProjectile(sf::RenderWindow &window);

        int getRadius();

        void setProjectileTexture(sf::Texture& texture);

        ~Projectile();

};

#endif