/* Implementation file for the Display class */

#include <SFML/Graphics.hpp>
#include "Display.h"
#include <string>
#include <fstream>
#include <iostream>

Display::Display(int windowWidth, int windowHeight, sf::RenderWindow &window) {
    // Variables
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->window = &window;
    selectedCount = 0;

    // Read a file for high score
    std::ifstream highScoreFile ("High Score.txt");
    std::string scoreString;

    if(highScoreFile.is_open()) {
        
        if(getline(highScoreFile, scoreString)) {
            highScore = scoreString;
        }
        
    }



}

// Getters and setters

int Display::getSelectedCount() {
    return selectedCount;
}

void Display::setSelectedCount(int count) {
    this->selectedCount = count;
}

int Display::getWindowWidth() {
    return windowWidth;
}

int Display::getWindowHeight() {
    return windowHeight;
}

Display::~Display() {
    
}