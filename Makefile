#Project

main: Stats.cpp HealingItems.cpp Projectile.cpp Entity.cpp Player.cpp Enemy.cpp Display.cpp MainMenu.cpp Gameplay.cpp main.cpp
	g++ -Wall Stats.cpp HealingItems.cpp Projectile.cpp Entity.cpp Player.cpp Enemy.cpp Display.cpp MainMenu.cpp Gameplay.cpp main.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system

unittest: Stats.cpp HealingItems.cpp Projectile.cpp Entity.cpp Player.cpp Enemy.cpp Display.cpp MainMenu.cpp Gameplay.cpp UnitTesting.cpp
	g++ -Wall Stats.cpp HealingItems.cpp Projectile.cpp Entity.cpp Player.cpp Enemy.cpp Display.cpp MainMenu.cpp Gameplay.cpp UnitTesting.cpp -o UNIT_TEST -lsfml-graphics -lsfml-window -lsfml-system