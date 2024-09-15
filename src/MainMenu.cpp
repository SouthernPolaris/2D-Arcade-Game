/* Implementation file for the main menu class*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Display.h"
#include "MainMenu.h"

// Constructor
MainMenu::MainMenu(int windowWidth, int windowHeight, sf::RenderWindow &window) :
    Display(windowWidth, windowHeight, window)
{
    selectedCount = 0;
    optionNum = 0;

    // Loads font
    if(!mainFont.loadFromFile("assets/arial.ttf")) {
        std::cout << "Font loading error" << std::endl;
    }

    // Sets the string text
    mainMenuText[0].setString("Start");
    mainMenuText[1].setString("Exit");

    // Other initialisers for the text
    for (int i = 0; i < MAX_OBJECTS; i++) {
        mainMenuText[i].setFont(mainFont);
    
        if (i == optionNum) {
            mainMenuText[i].setFillColor(sf::Color::Red);
            mainMenuText[i].setOutlineColor(sf::Color::White);
            mainMenuText[i].setOutlineThickness(2);
        } else {
            mainMenuText[i].setFillColor(sf::Color::Black);
            mainMenuText[i].setOutlineColor(sf::Color::White);
            mainMenuText[i].setOutlineThickness(2);
        }

        // Resest text origin to its centre by obtaining local bounds and taking their halves

        mainMenuText[i].setOrigin((mainMenuText[i].getLocalBounds().width) / 2.f, (mainMenuText[i].getLocalBounds().height) / 2.f);

        mainMenuText[i].setPosition(windowWidth / 2, (i+1) * windowHeight / (MAX_OBJECTS + 1));
    }

    // High score text
    std::string displayHighScore = "High Score: " + highScore;

    highScoreText.setString(displayHighScore);
    highScoreText.setFont(mainFont);
    highScoreText.setPosition(10,10);
    highScoreText.setFillColor(sf::Color::White);


}

void MainMenu::drawMenu(sf::RenderWindow &window) {
    // Draws the main menu
    
    if(!background_texture.loadFromFile("assets/SpaceBackground.png")) {

    }
    sf::Sprite background(background_texture);

    // double scale = window.getSize().x / 1000;
    // background.setScale(scale, scale);
    window.draw(background);
    
    
    for (int i = 0; i < MAX_OBJECTS; i++) {
        window.draw(mainMenuText[i]);
    }
    
    window.draw(highScoreText);
}

// Moves up through the menu
void MainMenu::upSelect() {
    if (optionNum - 1 >= 0) {
        mainMenuText[optionNum].setFillColor(sf::Color::Black);
        optionNum--;
        mainMenuText[optionNum].setFillColor(sf::Color::Red);
    }
}

// Moves down through the menu
void MainMenu::downSelect() {
    if (optionNum + 1 < MAX_OBJECTS) {
        mainMenuText[optionNum].setFillColor(sf::Color::Black);
        optionNum++;
        mainMenuText[optionNum].setFillColor(sf::Color::Red);
    }
}

int MainMenu::selected() {
    return optionNum;
}

MainMenu::~MainMenu() {
    
}