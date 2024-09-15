/* Implementation file for class Entity */

#include <string>
#include "Stats.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

using namespace std;

typedef chrono::steady_clock clockCount;

// Constructors

Entity::Entity(string name, int vitality, int strength, int luck) : 
    Stats(vitality, strength, luck) 
{
    size = 10;
    this->name = name;
    this->currentHealth = baseHealth;
}

Entity::Entity(string name, int vitality, int strength, int luck, sf::RenderWindow &window) :
    Entity(name, vitality, strength, luck)
{
    this->windowWidth = window.getSize().x;
    this->windowHeight = window.getSize().y;
}


Entity::Entity(int vitality, int strength, int luck) : 
    Entity("null", vitality, strength, luck)
{

}

Entity::Entity() : Entity("null", 1, 1, 1)
{

}

void Entity::move(sf::RenderWindow &window, float displacementX, float displacementY) {

    // Moves entity
    float velocityX = 3;
    float velocityY = 3;

    sprite.move(velocityX, velocityY);

}

// Getters and Setters

string Entity::getName() {
    return name;
}

void Entity::setName(string name) {
    this->name = name;
}

int Entity::getCurrentHealth() {
    return currentHealth;
}

void Entity::setCurrentHealth(int currentHealth) {
    this->currentHealth = currentHealth;
}

int Entity::getSize() {
    return size;
}

void Entity::setSize(int size) {
    this->size = size;
    // sprite.setRadius(size);
}

void Entity::takeDamage(int dealtDamage) {
        currentHealth -= dealtDamage;
}


sf::Sprite* Entity::getSprite() {
    return &sprite;
}

// Destructor
Entity::~Entity() {

}