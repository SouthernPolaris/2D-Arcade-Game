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

int main() {

    int timeNow = time(0);

    int windowWidth = 1000;
    int windowHeight = 1000;

    int menuCount = 0;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game");

    // Framerate limit
    window.setFramerateLimit(60);

    sf::View view = window.getDefaultView();


    MainMenu myMenu(windowWidth, windowHeight, window);
    Gameplay myMode(windowWidth, windowHeight, window);

    int screenWidth = sf::VideoMode::getDesktopMode().width;
    int screenHeight = sf::VideoMode::getDesktopMode().height;

    int windowXPosition = (screenWidth / 2) - (windowWidth / 2);
    int windowYPosition = (screenHeight / 2) - (windowHeight / 2);

    sf::Vector2i windowNewPos = {windowXPosition, windowYPosition};

    window.setPosition(windowNewPos);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            switch (event.type) {
                case sf::Event::KeyReleased :
                    
                    // Key Press Detection
                    switch (event.key.code) {
                        case sf::Keyboard::W:
                            myMenu.upSelect();
                            break;
                        case sf::Keyboard::Up:
                            myMenu.upSelect();
                            break;
                        case sf::Keyboard::S:
                            myMenu.downSelect();
                            break;

                        case sf::Keyboard::Down:
                            myMenu.downSelect();
                            break;     
                        case sf::Keyboard::Enter:
                            myMenu.setSelectedCount(1);
                            if (myMenu.selected() == 0) {
                                std::cout << "Start button was selected" << std::endl;
                            } else if (myMenu.selected() == 1) {
                                std::cout << "Exit was pressed" << std::endl;
                                event.type = sf::Event::Closed;
                            }
                            break;
                        case sf::Keyboard::Escape:
                            std::cout << "Escape pressed" << std::endl;
                            menuCount = myMenu.getSelectedCount();
                            
                            if (menuCount == 0) {
                                event.type = sf::Event::Closed;
                            } else {
                                myMode.setScore(0);
                            }
                            
                            myMenu.setSelectedCount(menuCount - 1);
                            break;

                        case sf::Keyboard::D:
                            break;
                        case sf::Keyboard::A:
                            break;
                        default:
                            myMode.invalidKey(window);
                            break;                          
                    }

                default:
                    break;
            }

            // Closes window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                view.setSize({
                    static_cast<float>(event.size.width),
                    static_cast<float>(event.size.height)
                });
                window.setView(view);
            }


            // Clearing window
            window.clear();


            // Drawing window
            if (myMenu.getSelectedCount() == 0) {
                myMenu.drawMenu(window);
            } else if (myMenu.getSelectedCount() == 1) {

                int timeOld = timeNow;

                timeNow = time(0);

                int deltaTime = timeNow - timeOld;

                myMode.drawMenu(window);
                
                myMode.getPlayer()->shoot(window, event);
                
                if(deltaTime >= 1) {
                    myMode.addEnemy();
                }

                myMode.getPlayer()->move(window);
                myMode.enemyDefeated(window);
            } else {
                event.type = sf::Event::Closed;
            }


            // Displaying window
            window.display();


        }
    }
    return 0;
}