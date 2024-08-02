#include "Stats.h"

/* Implementation file for stats class */

// Constructor taking 3 parameters
Stats::Stats(int vitality, int strength, int luck) {
    this->vitality = vitality;
    this->strength = strength;
    this->luck = luck;

    level = vitality + strength + luck;

    baseHealth = vitality * 10;
}

// Default constructor
Stats::Stats(): Stats(1, 1, 1) {

}


// Getters and setters
int Stats::getLevel() {
    return level;
}

void Stats::setLevel(int level) {
    this->level = level;
}

int Stats::getBaseHealth() {
    return baseHealth;
}


int Stats::getVitality() {
    return vitality;
}

void Stats::setVitality(int vitality) {
    this->vitality = vitality;
    this->baseHealth = vitality*10;
}


int Stats::getStrength() {
    return strength;
}

void Stats::setStrength(int strength) {
    this->strength = strength;
}


int Stats::getLuck() {
    return luck;
}

void Stats::setLuck(int luck) {
    this->luck = luck;
}


// Destructor
Stats::~Stats() {

}