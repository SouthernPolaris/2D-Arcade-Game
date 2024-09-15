#ifndef MAINMENU_H
#define MAINMENU_H

/* Header file for the main menu class, which controls the main menu,
    including the navigation of that menu */

#define MAX_OBJECTS 2

#include <SFML/Graphics.hpp>
#include "Display.h"

class MainMenu: public Display {
    protected:
        // Variables
        int optionNum;
        sf::Text mainMenuText[MAX_OBJECTS];
        sf::Text highScoreText;
    public:

        // Member functions
        MainMenu(int windowWidth, int windowHeight, sf::RenderWindow &window);

        void drawMenu(sf::RenderWindow &window);

        void upSelect();
        void downSelect();

        int selected();

        ~MainMenu();
};

#endif