# engg1340-project

## Table of contents

-   [Group members](#group-members)
-   [Introduction](#introduction)
-   [Controls](#controls)
-   [Gameplay](#gameplay)
    -   [1. Gameflow](#1-gameflow)
    -   [2. Towers](#2-towers)
    -   [3. Enemies](#3-towers)
-   [How to play](#how-to-play)
-   [Project Requirements](#program-requirements)
    -   [1. Generation of random game elements](#1-generation-of-random-game-elements)
    -   [2. Data structures for storing game status](#2-data-structures-for-storing-game-status)
    -   [3. Dynamic Memory Management](#3-dynamic-memory-management)
    -   [4. File input/output (e.g., for loading/saving game status)](#4-file-inputoutput-eg-for-loadingsaving-game-status)
    -   [5. Program codes in multiple files](#5-program-codes-in-multiple-files)
    -   [6. Proper Indentation and naming styles](#6-external-libraries)
    -   [7. In-code documentation](#7-in-code-documentation)

 ## Group members

1. Andy (full name) (uid)
2. Jason Ip Tsz Shun 3036226222
3. Owen (full name) (uid)
4. Cyric (full name) (uid)
5. Donald Leung Kit Yiu 3036226557

## Introduction

Kingdom of Eldoria is a tower defence simulator where the primary objective is to waves of incoming enemies from approaching the end of the map. The player must strategically place defensive towers, along predetermined paths or routes which enemies follow. These towers have unique abilities which make them suitable for different situations. With a limited amount of resources (money and health), players must carefully evaluate their positions and come up with the best defensive plan to stop the waves of incoming enemies.

## Controls

Upon the start of the game, players can select the map they want to play on with arrow keys. Players can even choose to play on a random map by choosing the map with a question mark on it.

After loading the map, players can press "start wave", "build" or "quit" at the action menu.

"start wave" will immediately spawn enemies that walk along the path and attempt to reach the end. 1 Health will be reduced per enemy that reaches to the end.

Please note that you will not be able to place down towers once the wave has started, so you should make sure you have sufficient defensive towers before starting each wave.

"build" will first allow the player to select a tile with a white cursor, controlled with arrow keys

If the tile is empty, the player will be prompted to select a tower to place from the tower menu. If there is sufficient money, the tower will be placed at the location.

If the tile is a path, the player will return to the action menu.

If the tile is a tower, the player can choose to upgrade or sell the tower, allowing for higher damage output.

"quit" will return the user to the main menu.

## Gameplay

### 1. Gameflow

Each time an enemy is killed, the player will be rewarded with money to further enhance their defence.

If the player runs out of health, a game over screen will pop up and they will have to play again.

Upon reaching the last wave, the player will be rewarded with a win screen.

### 2. Towers

#### Mage

<i>In the realm of Eldoria, the Mage emerges from the Order of Arcanum, gifted with mastery over all sorts of elements. Trained in defensive magic, the Mage casts devastating spells to protect the realm from evilness. The Mage's reputation as a formidable defender grows, inspiring hope and safeguarding Eldoria from chaos.</i>

Cost: 40 -> 80 -> 120 -> 160 -> ... (level * 40)

Damage: 2 -> 4 -> 6 -> 8 -> ... (level * 2)

Attack speed: 1 (fast)

Range: 1

Notes: Multiple targets, Can attack both ground and air enemies, Can detect Camo enemies.

#### Archer

<i>In the enchanted realm of Eldoria, a skilled archer from the Woodland Brotherhood defends the land with her unparalleled marksmanship. Guided by nature's forces, her arrows strike true, imbued with elemental power. The archer's unwavering dedication ensures the realm's harmony remains preserved.</i>

Cost: 20 -> 40 -> 60 -> 80 -> ... (level * 20)

Damage: 3 -> 6 -> 9 -> 12 -> ... (level * 3)

Attack speed: 1 (fast)

Range: 1

Notes: Single target, Can attack both ground and air enemies, Unable to detect Camo enemies.

#### Sniper

<i>The legendary sniper from Eldoria's Silent Vanguard, strikes fear with lethal precision. Known as the Phantom Sniper, he safely eliminates his targets from a long distance, safeguarding Eldoria's peace from the shadows.</i>

Cost: 50 -> 100 -> 150 -> 200 -> ... (level * 50)

Damage: 6 -> 12 -> 18 -> 24 -> ... (level * 6)

Attack speed: 3 (slow)

Range: 2

Notes: Single target, Can attack both ground and air enemies, Can detect Camo enemies.

#### Cannon

<i>Built by the best engineer in Eldoria, the cannon is capable of shooting the most powerful bomb at enemies and creating catastrophic explosions. Destined to protect its homeland, the cannon tries its best to obey its commander.</i>

Cost: 40 -> 80 -> 120 -> 160 -> ... (level * 30)

Damage: 2 -> 4 -> 6 -> 8 -> ... (level * 4)

Attack speed: 3 (slow)

Range: 1

Notes: Multiple targets, Can only attack ground enemies, Unable to detect Camo enemies.

### 3. Enemies

#### Knight

Health: 9 per level

Money given after defeat: 4 per level

Type: Ground

#### Dragon

Health: 12 per level

Money given after defeat: 4 per level

Type: Air

#### Ghost

Health: 9 per level

Money given after defeat: 3 per level

Type: Ground, Camo

#### Vampire

Health: 9 per level

Money given after defeat: 4 per level

Type: Air, Camo

## How to play
Run make && ./test into the terminal after downloading all the files and putting them into the same directory.

## Project requirements

### Generation of random game elements
The game provides an option for the player to choose the map randomly

### Data structures for storing game status
The game creates numerous structures for tiles on maps and enemies.
The game implements a 2D vector to store the map elements, 

### Dynamic Memory Management
The game uses vectors and linked lists.

### File input/output (e.g., for loading/saving game status)
The game saves the maps as text files and then reads and prints them out accordingly.

### Program codes in multiple files
In total, the program includes X C++ files, X header files, X txt files and one Makefile.

### Proper Indentation and naming styles
Each control structures provide an indentation and all the variables have meaningful names.

### In-code documentation
Easy-to-understand documentation is included in the code.
