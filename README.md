# Load-Runner

Based on the classic Lode Runner game written in C++.
The code uses class inheritance, polymorphism and the SFML library.

# Game Rules

A game where a player needs to collect coins to pass the next level and there are enemies that try to kill him some are smart hooks that come towards the player, some move randomly and some only move right to left
The game has ladders and poles that a player can walk up and down
In the game the player also can't end gifts The gifts add score/time/life/enemy
The player can make a dig in the floor where he can drop and stick for a limited time as well
The player starts with 3 disqualifications for each coin the player collects he gets 2 times the number of the stage he is in points and when he finishes a stage he gets a bonus of 50 points
Description of gifts:
Enemy - adds another to the game
Life - adds one life to the player
Scoring - adds 20 points to the player
Time - adds 10 seconds to the game

the game supports 4 stages, each stage is in a separate file, each file is named Level with the number of the stage and a txt extension

Known bugs:
The smart enemy is somewhat limited in its ability and burdens the plan, therefore I limited the number of smart enemies to 2 in each stage
