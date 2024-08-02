#ifndef UNITTESTING_H
#define UNITTESTING_H

// Header file for unit testing all classes and objects

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Display.h"
#include "MainMenu.h"
#include "Gameplay.h"
#include "Stats.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "HealingItems.h"

class UnitTesting {
    public:
        // All tests
        void runTests() {
            testDisplay();
            testMainMenu();
            testGameplay();
            testStats();
            testEntity();
            testEnemy();
            testPlayer();
            testProjectile();
            testHealingItems();
        }

    private:
        // Tests the display class
        void testDisplay() {
            sf::RenderWindow window;
            MainMenu testingMainMenu(100, 100, window);
        
            if(testingMainMenu.getWindowWidth() == 100 && testingMainMenu.getWindowHeight() != 100) {
                std::cout << "Test 1 failed\n";
            }
        };

        // Tests the main menu class
        void testMainMenu()  {
            sf::RenderWindow window;
            MainMenu testingMainMenu(50, 100, window);

            if (testingMainMenu.selected() != 0) {
                std::cout << "Test 2 failed\n";
            }

            testingMainMenu.downSelect();

            if (testingMainMenu.selected() != 1) {
                std::cout << "Test 2 failed\n";
            }

            testingMainMenu.upSelect();

            if (testingMainMenu.selected() != 0) {
                std::cout << "Test 2 failed\n";
            }

        }

        // Tests the Gameplay class
        void testGameplay() {
            sf::RenderWindow window;
            Gameplay testingGameplay(100, 100, window);

            bool test = testingGameplay.getPlayerAlive();

            if (test != true) {
                std::cout << "Test 3 failed\n";
            }

            testingGameplay.getPlayer()->takeDamage(100);

            test = testingGameplay.getPlayerAlive();

            if (test != true) {
                std::cout << "Test 3 failed\n";
            }
        }

        // Tests the stats class
        void testStats() {
            Enemy testingEnemy("enemy", 10, 10, 10, 0);
            if (testingEnemy.getBaseHealth() >= 100) {
                std::cout << "Test 4 failed\n";
            }

            testingEnemy.setVitality(100);

            if (testingEnemy.getBaseHealth() != 1000) {
                std::cout << "Test 4 failed\n";
            }
        }

        // Tests the entity class
        void testEntity() {
            Enemy testingEnemy("enemy", 10, 10, 10, 0);

            if (testingEnemy.getName() != "enemy") {
                std::cout << "Test 5 failed\n";
            }

            int tempHealth = testingEnemy.getCurrentHealth();

            testingEnemy.takeDamage(10);

            if(testingEnemy.getCurrentHealth() != (tempHealth - 10)) {
                std::cout << "Test 5 failed\n";
            }
        }

        // Tests the enemy class
        void testEnemy() {
            Enemy testingEnemy("enemy", 10, 10, 10, 0);
            Player testingPlayer("hero", 10, 10, 10);
            testingEnemy.takeDamage(100);

            if(testingEnemy.aliveStatus(100, 100, 10, &testingPlayer)) {
                std::cout << "Test 6 failed\n";
            }

        }

        // Tests the player class
        void testPlayer() {
            Player testingPlayer("Hero", 10, 10, 10);

            if (testingPlayer.getName() != "Hero") {
                std::cout << "Test 7 failed\n";
            }

            testingPlayer.takeDamage(1000);

            Enemy testingEnemy("enemy", 10, 10, 10, 0);

            if(testingPlayer.aliveStatus(100, 100, 10, &testingEnemy)) {
                std::cout << "Test 7 failed\n";
            }

            if (testingPlayer.projectiles.size() != 0) {
                std::cout << "Test 8 failed\n";
            }

        }

        // Tests the projectile class
        void testProjectile() {
            Projectile testingProjectile(10, 100, 100, 5, 5, 3.14);

            if(testingProjectile.getRadius() != 10) {
                std::cout << "Test 8 failed\n";
            }
        }

        // Tests the healing items class
        void testHealingItems() {
            HealingItems testingHealingItems(1, 1);

            if(!testingHealingItems.playerInteracts(0,0)) {
                std::cout << "Test 9 failed\n";
            }
        }

};

#endif