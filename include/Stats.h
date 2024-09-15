#ifndef STATS_H
#define STATS_H

/* This header file contains all the stats for the entities in the game 
    such as the player and enemies*/

class Stats {
    protected:
        // Baseline stats that all players and enemies have
        int level;
        int baseHealth;
        int vitality;
        int strength;
        int luck;
    public:
        // Constructors
        Stats(int vitality, int strength, int luck);
        Stats();

        /* Getters and Setters
            Level and BaseHealth do not have setters
            as they are already dependent on the other 3 */

        int getLevel();
        void setLevel(int level);

        int getBaseHealth();

        int getVitality();
        void setVitality(int vitality);

        int getStrength();
        void setStrength(int strength);

        int getLuck();
        void setLuck(int luck);

        /* Pure virtual function to make the class abstract
            Spend points refers to getting points every level up
            which can be invested into one of the 3 stats with setters */

        virtual bool spendPoints() = 0;


        // Virtual destructor
        virtual ~Stats();
};

#endif