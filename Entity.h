#ifndef ENTITY_H
#define ENTITY_H

/* Header file for class Entity. Contains all things common to an entity such as name, current health and movement
    Inherits from Stats as all entities have stats */

#include <string>
#include "Stats.h"
#include <SFML/Graphics.hpp>
#include <chrono>



using namespace std;

typedef chrono::steady_clock clockCount;

class Entity: public Stats {
    protected:
        // Things associated with entities which don't fit in Stats category
        string name;
        int currentHealth;

        sf::Sprite sprite;

        int size;        

        float deltaTime;


        // Screen size for positioning entities according to the screen
        int windowWidth;
        int windowHeight;

    public:
        
        // Entity position and velocity
        pair<float, float> displacement;
        pair<float, float> velocity;

        // Constructors
        Entity(string name, int vitality, int strength, int luck);
        Entity(string name, int vitality, int strength, int luck, sf::RenderWindow &window);
        Entity(int vitality, int strength, int luck);
        Entity();

        // Virtual function controlling movement
        virtual void move(sf::RenderWindow &window, float displacementX, float displacementY);

        // Getters and setters
        string getName();
        void setName(string name);

        int getCurrentHealth();
        void setCurrentHealth(int currentHealth);

        int getSize();
        void setSize(int size);

        sf::Sprite* getSprite();

        // Entity takes a certain amount of damage, reducing health by that much
        virtual void takeDamage(int dealtDamage);

        // Another pure virtual function which will be implemented properly 
        // in the next layer of inherited classes
        virtual bool aliveStatus(float ballX, float ballY, int size, Entity* entity) = 0;

        // Destructor
        virtual ~Entity();
};

#endif