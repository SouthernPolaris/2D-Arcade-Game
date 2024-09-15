#ifndef HEALINGITEMS_H
#define HEALINGITEMS_H

/* Header file for HealingItems class which controsl health items which the player can use to heal */

#include <SFML/Graphics.hpp>
#include <chrono>

class HealingItems {
    private:
        // Variables
        int xPosition;
        int yPosition;
        sf::Sprite healthSprite;
        sf::Texture healthTexture;
        float size;
    public:
        // Member functions
        HealingItems(int windowWidth, int windowHeight);

        void drawHealing(sf::RenderWindow &window);

        bool playerInteracts(float playerX, float playerY);

        ~HealingItems();
};

#endif