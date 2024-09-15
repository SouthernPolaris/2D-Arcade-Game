# 2D Arcade Game

This is a 2D top-down arcade game. It is a combination of popular arcade games "Space Invaders" and "Asteroids". It involves the combat gameplay of Space Invaders while including the movement of Asteroids. It is an endless gamemode where there is no goal besides beating a previous high score and achieving a score as high as possible.

The player can move with 360 degree freedom, achieved through Euler integration and trigonometric calculations. The enemies have auto-targetting capabalities to lock onto the user given that they are a set distance away for fairness

The game also features some RPG elements where the player can level up by defeating more enemies. All players and enemies possess some "Vitality", "Strength", and "Luck". Every time the player levels up, one of the 3 is randomly levelled up to make the player stronger. Likewise, the enemies stats also scale on the player's level for fairness.

Vitality: Controls Health
Strength: Controls Damage Dealt
Luck: Slightly Randomises Damage Taken and Dealt, shifting the probability distribution to be more favourable to the entity in question at higher luck levels for the entity.

The levelling system is not linear but logarithmic to promote extended playtime.

## Images
Main Menu:
![alt text](https://github.com/SouthernPolaris/2D-Arcade-Game/blob/main/GameplayImages/2D_Arcade_Game.png?raw=true)

Gameplay:
![alt text](https://github.com/SouthernPolaris/2D-Arcade-Game/blob/main/GameplayImages/2D_Arcade_Gameplay.png?raw=true)

Defeated Screen:
![alt text](https://github.com/SouthernPolaris/2D-Arcade-Game/blob/main/GameplayImages/2D_Arcade_Defeated.png?raw=true)

## How to Run
Dependencies: SFML Graphics Library
To compile:

```
mkdir build
cd build
cmake ..
make
```

To run:
```
./game
```

The program will not run without SFML, which needs to be separately installed.

#### Unit Testing
The unit testing files present are for testing purposes only
To compile -> make unittest
To run -> ./UNIT_TEST

The unit test is successful when there is no output in the terminal. If the file outputs something in the terminal, there is an error present

## Controls
The mouse is involved in positioning the player's direction, which always faces the cursor. The mouse buttons play no role in the game
W Key - Move Up
A - Move Left
S - Move Down
D - Move Right
Esc - Go to Previous Menu (Or Exit Program if in Main Menu)
Enter(Main Menu Only) - Select Option

## Notes
This was originally made in September/October 2023, with only sprites being added recently for presentability.

## External Art Resources

Background:
https://deep-fold.itch.io/space-background-generator

Player:
https://foozlecc.itch.io/void-main-ship

Enemies:
https://foozlecc.itch.io/void-fleet-pack-1

Healing:
https://www.spriteland.com/sprites/medical-kit-sprites

These images are all royalty free as stated on their respective websites
