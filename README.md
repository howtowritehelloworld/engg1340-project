# Kingdom of Eldoria (Tower Defense Game) ENGG1340 Project

## Table of contents

-   [Group members](#group-members)
-   [Introduction](#introduction)
-   [Gameplay](#gameplay)
    -   [1. Features](#features)
    -   [2. Gameflow](#gameflow)
    -   [3. Controls](#controls)
    -   [4. Towers](#towers)
    -   [5. Enemies](#enemies)
-   [Installation](#installation)
-   [Project Requirements](#project-requirements)
    -   [1. Generation of random game elements](#random)
    -   [2. Data structures for storing game status](#data-structures)
    -   [3. Dynamic Memory Management](#dynamic-memory)
    -   [4. File input/output (e.g., for loading/saving game status)](#file-inputoutput)
    -   [5. Program codes in multiple files](#multiple-files)
    -   [6. Proper Indentation and naming styles](#external-libraries)
    -   [7. In-code documentation](#documentation)

 ## Group members <a name="group-members"></a>

There is a known problem where some commits doesn't count towards the person's contribution statistics. Hence the contribution percentages and numbers are inaccurate. To avoid being labelled as a "free rider", all the functions and features each of us has worked on will be written down here.

| Group Member | uid | Work done |
|---------|---------|---------|
| Zheng Andy | 3036222642 | stuff |
| Jason Ip Tsz Shun | 3036226222 | stuff |
| Owen Wen Sze Hoi | 3036226583 | stuff |
| Cyric (full name) | uid | stuff |
| Donald Leung Kit Yiu | 3036226557 | stuff |

## Introduction <a name="introduction"></a>

Kingdom of Eldoria is a tower defence simulator where the primary objective is to waves of incoming enemies from approaching the end of the map. The player must strategically place defensive towers, along predetermined paths or routes which enemies follow. These towers have unique abilities which make them suitable for different situations. With a limited amount of resources (money and health), players must carefully evaluate their positions and come up with the best defensive plan to stop the waves of incoming enemies.

We recommend playing the tutorial of the game before playing the main game. The tutorial is located at the help button on the main screen. A short story will also be included.


## Gameplay <a name="gameplay"></a>

### 1. Features <a name = "features"></a> 

Our game includes: 
- Colorful GUI
- Easy to use controls
- A wide variety of maps, even custom maps can be made
- Diverse towers and enemies
- Saving and loading

### 2. Gameflow <a name="gameflow"></a>

Each time an enemy is killed, the player will be rewarded with money to further enhance their defence.

If the player runs out of health, a game over screen will pop up and they will have to play again.

Upon reaching the last wave, the player will be rewarded with a win screen.

To start playing, choose New Game or Help to play the main game or tutorial level respectively. Again we recommend you try out the tutorial level first. It's short and can help you grasp the core gameplay mechanics and controls quickly.

If you have played the game before, click load game to get back your progress.

Upon entering, you will be prompted to place towers or start the wave.

Once you complete a wave, money will be granted to you based on the wave number. Moreover killing enemies also grant you a specific amount of money based on enemy type and their level.

Upon completing wave 15, you have won the required stages of the game and can continue by pressing the infinite waves option.

### 3. Controls <a name="controls"></a>

Upon the start of the game, players can select the map they want to play on with arrow keys. Players can even choose to play on a random map by choosing the map with a question mark on it.

After loading the map, players can press "start wave", "build" or "quit" at the action menu.

"start wave" will immediately spawn enemies that walk along the path and attempt to reach the end. 1 Health will be reduced per enemy that reaches the end.

Please note that you will not be able to place down towers once the wave has started, so you should make sure you have sufficient defensive towers before starting each wave.

"build" will first allow the player to select a tile with a white cursor, controlled with arrow keys

If the tile is empty, the player will be prompted to select a tower to place from the tower menu. If there is sufficient money, the tower will be placed at the location.

If the tile is a path, the player will return to the action menu.

If the tile is a tower, the player can choose to upgrade or sell the tower, allowing for higher damage output.

"quit" will return the user to the main menu.

### 4. Towers <a name="towers"></a>

There are a total of 4 types of towers in the game (Mage, Archer, Sniper, Cannon). Each of these towers have different stats that make them useful in different situations.

You can place, sell and upgrade towers in between waves.

There is no limit on the level of the towers you can upgrade to.

#### Mage

<i>The Mages, masters of arcane arts, unleash devastating spells, engulfing the enemy in flames. Their power is unmatched, and their knowledge of the mystical arts is a force to be reckoned with.</i>

Cost: 40 -> 80 -> 120 -> 160 -> ... (level * 40)

Damage: 2 -> 4 -> 6 -> 8 -> ... (level * 2)

Attack speed: 1 (fast)

Range: 1

Notes: Multiple targets, Can attack both ground and air enemies, Can detect Camo enemies.

#### Archer

<i>Archers, agile and swift, move with grace and dexterity across the battlefield. Their bows are extensions of their very beings, and their arrows find their mark with unerring accuracy.</i>

Cost: 20 -> 40 -> 60 -> 80 -> ... (level * 20)

Damage: 3 -> 6 -> 9 -> 12 -> ... (level * 3)

Attack speed: 1 (fast)

Range: 1

Notes: Single target, Can attack both ground and air enemies, Unable to detect Camo enemies.

#### Sniper

<i>Snipers, sharp-eyed and patient, take their positions atop towers and vantage points, armed with long-range rifles. Their steady aim and  precision shots can pick off enemies from afar, eliminating key targets before they can breach the kingdom's defenses.</i>

Cost: 50 -> 100 -> 150 -> 200 -> ... (level * 50)

Damage: 6 -> 12 -> 18 -> 24 -> ... (level * 6)

Attack speed: 3 (slow)

Range: 2

Notes: Single target, Can attack both ground and air enemies, Can detect Camo enemies.

#### Cannon

<i>Cannoneers, masters of explosive firepower, wield massive cannons capable of unleashing devastation upon the enemy. Their booming blasts send shockwaves through the ranks, tearing apart adversaries and creating chaos amidst the horde.</i>

Cost: 40 -> 80 -> 120 -> 160 -> ... (level * 30)

Damage: 2 -> 4 -> 6 -> 8 -> ... (level * 4)

Attack speed: 3 (slow)

Range: 1

Notes: Multiple targets, Can only attack ground enemies, Unable to detect Camo enemies.

### 5. Enemies <a name="enemies"></a>

Like towers, there are also 4 types of enemies (Knight, Dragon, Ghost and Vampire).

They each have unqiue types and health so the player need to be careful with their choice of towers. For example if you place all cannons then you cannot hit air enemies.

Flying enemies (Air) will be marked with wings on the side. (Example: ^D^)

Camoflauged enemies (Camo) will be of color green.

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

## Installation <a name="installation"></a>

Run make && ./test into the terminal after downloading all the files and putting them into the same directory.

Make sure your terminal is large enough so that the whole game can be presented.

Also our game uses ncurses's color feature so there's a very slim chance that colors cannot be shown on you terminal due to your terminal is incapable of showing colors. However from our testing with vscode the color works fine.

## Project requirements <a name="project-requirements"></a>

### Generation of random game elements <a name="random"></a>

The game provides an option for the player to choose the map randomly.

The game features an "Infinite Mode" option, where players can engage in an endless gameplay experience. In this mode, random enemies are dynamically generated based on the wave number, ensuring that the difficulty scales as the player progresses through the waves.

### Data structures for storing game status <a name="data-structures"></a>

The game creates numerous structures for tiles on maps and enemies.

The game implements a 2D vector to store the map elements, 

### Dynamic Memory Management <a name="dyanmic-memory"></a>

The game heaveily uses vectors and linked lists.

### File input/output (e.g., for loading/saving game status) <a name="file-inputoutput"></a>

The game saves the maps as text files and then reads and prints them out accordingly.

Additionally, the game automatically saves the game every time you pass a wave inside a text file, so if you ever accidentally quit or want to continue playing another time, you can maintain all your progress.

### Program codes in multiple files <a name="multiple-files"></a>

In total, the program includes X C++ files, X header files, X txt files and one Makefile.

### Proper Indentation and naming styles <a name="external-libraries"></a>

Each control structures provide an indentati on and all the variables have meaningful names.

### In-code documentation <a name="documentation"></a>

Easy-to-understand documentation is included in the code.
