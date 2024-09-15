/* The main file which runs the game */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Stats.h"
#include "Display.h"
#include "MainMenu.h"
#include "Gameplay.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include <string>
#include <vector>
#include <ctime>

void handleEvents(sf::RenderWindow &window, MainMenu &myMenu, Gameplay &myMode);
void updateGame(sf::RenderWindow &window, Gameplay &myMode);
void draw(sf::RenderWindow &window, MainMenu &myMenu, Gameplay &myMode);

int main() {
    const int windowWidth = 1000;
    const int windowHeight = 1000;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game");
    window.setFramerateLimit(60);

    int screenWidth = sf::VideoMode::getDesktopMode().width;
    int screenHeight = sf::VideoMode::getDesktopMode().height;
    window.setPosition({(screenWidth / 2) - (windowWidth / 2), (screenHeight / 2) - (windowHeight / 2)});

    MainMenu myMenu(windowWidth, windowHeight, window);
    Gameplay myMode(windowWidth, windowHeight, window);

    while (window.isOpen()) {
        handleEvents(window, myMenu, myMode);

        window.clear();

        draw(window, myMenu, myMode);

        window.display();
    }
    return 0;
}

void handleEvents(sf::RenderWindow &window, MainMenu &myMenu, Gameplay &myMode) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::W:
                    case sf::Keyboard::Up:
                        myMenu.upSelect();
                        break;
                    case sf::Keyboard::S:
                    case sf::Keyboard::Down:
                        myMenu.downSelect();
                        break;
                    case sf::Keyboard::Enter:
                        myMenu.setSelectedCount(1);
                        if (myMenu.selected() == 0) {
                            std::cout << "Start button was selected" << std::endl;
                        } else {
                            std::cout << "Exit was pressed" << std::endl;
                            window.close();
                        }
                        break;
                    case sf::Keyboard::Escape:
                        if (myMenu.getSelectedCount() == 0) {
                            std::cout << "Escape pressed: Exiting the game." << std::endl;
                            window.close(); // Exit the program
                        } else {
                            std::cout << "Escape pressed: Returning to main menu" << std::endl;
                            myMode.setScore(0);
                            myMenu.setSelectedCount(0); // Return to main menu
                        }
                        break;
                    case sf::Keyboard::D:
                    case sf::Keyboard::A:
                        break;
                    default:
                        myMode.invalidKey(window);
                        break;
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                {
                    sf::View view = window.getDefaultView();
                    view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                    window.setView(view);
                }
                break;
            default:
                break;
        }
    }
}

void updateGame(sf::RenderWindow &window, Gameplay &myMode, sf::Event &event) {
    static int timeNow = time(0);
    int deltaTime = time(0) - timeNow;
    timeNow = time(0);

    myMode.drawMenu(window);
    myMode.getPlayer()->shoot(window, event);

    if (deltaTime >= 1) {
        myMode.addEnemy();
    }

    myMode.getPlayer()->move(window);
    myMode.enemyDefeated(window);
}

void draw(sf::RenderWindow &window, MainMenu &myMenu, Gameplay &myMode) {
    if (myMenu.getSelectedCount() == 0) {
        myMenu.drawMenu(window);
    } else {
        sf::Event event;
        updateGame(window, myMode, event);
    }
}
