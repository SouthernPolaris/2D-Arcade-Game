#ifndef DISPLAY_H
#define DISPLAY_H

/* Header file for display class. 
Involves the main features of displaying such as the window and display text */

#include <SFML/Graphics.hpp>
#include <string>

class Display {
    protected:
        // Variables
        int selectedCount;
        int windowWidth;
        int windowHeight;
        sf::RenderWindow *window;
        std::string highScore;
        sf::Font mainFont;

        sf::Texture background_texture;

    public:
        // Member functions
        Display(int windowWidth, int windowHeight, sf::RenderWindow &window);
        virtual void drawMenu(sf::RenderWindow &window) = 0;

        int getSelectedCount();
        void setSelectedCount(int count);

        int getWindowWidth();
        int getWindowHeight();

        ~Display();
};

#endif