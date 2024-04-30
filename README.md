# Kingdom of Eldoria (Tower Defense Game) ENGG1340 Project

## Table of contents
-   [Quick Start](#quickstart)
-   [Group members](#group-members)
-   [Introduction](#introduction)
-   [Gameplay](#gameplay)
    -   [1. Features](#features)
    -   [2. Gameflow](#gameflow)
    -   [3. Controls](#controls)
    -   [4. Towers](#towers)
    -   [5. Enemies](#enemies)
-   [Project Requirements](#project-requirements)
    -   [1. Generation of random game elements](#random)
    -   [2. Data structures for storing game status](#data-structures)
    -   [3. Dynamic Memory Management](#dynamic-memory)
    -   [4. File input/output (e.g., for loading/saving game status)](#file-inputoutput)
    -   [5. Program codes in multiple files](#multiple-files)
-   [External Libraries](#external-libraries)


## Quick Start <a name="quickstart"></a>

Download the zip file and unzip it.

In the terminal,
Type `make` to create the executable.
Type `./game` to play the game.

Use arrows keys <kbd>←</kbd><kbd>↑</kbd><kbd>→</kbd><kbd>↓</kbd> to navigate the menu, and ENTER to select.

We recommend opening the terminal in full size for the best gameplay experience

 ## Group members <a name="group-members"></a>

Some commits don't count towards the person's contribution statistics. Hence the contribution percentages and numbers are inaccurate. To avoid being labeled as a "free rider", all the functions and features we have worked on will be written down here.

| Group Member | uid | Work done |
|---------|---------|---------|
| [Zheng Andy (Andy)](https://github.com/howtowritehelloworld) | 3036222642 | Pathfinding, wave display, gameplay mechanics, testing, debugging, documentation, formatting |
| [Ip Tsz Shun (Jason)](https://github.com/rtween1) | 3036226222 | GUI, damage calculation, tutorial mode |
| [Wen Sze Hoi (Owen)](https://github.com/WenSzeHoi) | 3036226583 | Towers, Enemies, Infinite waves generation, Balancing, Chest feature |
| [Wong Chun Sun (Cyric)](https://github.com/suncyric) | 3036222965 | Map design, save and load game, game title, video demo |
| [Leung Kit Yiu (Donald)](https://github.com/Dsl0503) | 3036226557 | GUI, tutorial mode, map display, readme file|

## Introduction <a name="introduction"></a>

The Kingdom of Eldoria is a tower defense simulator with the primary objective of defending waves of enemies. The player must strategically place defensive towers, along predetermined paths or routes that enemies follow. These towers have unique abilities which make them suitable for different situations. With limited resources (money and health), players must carefully evaluate their positions and come up with the best defensive plan to stop the waves of incoming enemies.

We recommend playing the tutorial of the game before playing the main game. The tutorial is located at the help button on the main screen. A short story will also be included.


## Gameplay <a name="gameplay"></a>

### 1. Features <a name = "features"></a> 

Our game includes: 
- Colorful GUI
- [Text Art](https://www.asciiart.eu/text-to-ascii-art)
- Simple controls
- A wide variety of maps, even custom maps can be made
- Diverse towers and enemies
- Auto-saving and loading

### 2. Gameflow <a name="gameflow"></a>

Each time a wave is completed, the player will be rewarded with $ 8*(wave_number+1) to further enhance their defence.

If the player runs out of health, a game over screen will pop up and they will have to play again.

Upon reaching the last wave, the player will be rewarded with a win screen.

To start playing, choose New Game or Help to play the main game or tutorial level respectively. Again we recommend you try out the tutorial level first. It's short and can help you grasp the core gameplay mechanics and controls quickly.

If you have played the game before, click load game to get back your progress.

Upon entering, you will be prompted to place towers or start the wave.

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

Attack speed: 2 (medium)

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

Cost: 30 -> 60 -> 90 -> 120 -> ... (level * 30)

Damage: 5 -> 10 -> 15 -> 20 -> ... (level * 5)

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

Type: Ground

#### Dragon

Health: 12 per level

Type: Air

#### Ghost

Health: 9 per level

Type: Ground, Camo

#### Vampire

Health: 9 per level

Type: Air, Camo

## Project requirements <a name="project-requirements"></a>

### Generation of random game elements <a name="random"></a>

The game provides an option for the player to choose the map randomly.

The game features an "Infinite Mode" option. In this mode, random enemies are randomly generated based on the wave number, ensuring that the difficulty scales as the player progresses through the waves.

Every 3 waves are completed, a player will be rewarded with a chest that they can choose from 3 chests. Each chest will contain a random amount of money based on the wave number.

### Data structures for storing game status <a name="data-structures"></a>

The game uses different data structures to store the game.

Vector to store the pointers of all towers.

Linked list to store the path and the pointers to the enemies.

A Text file is used for saving and loading the game.

### Dynamic Memory Management <a name="dynamic-memory"></a>

Enemies and towers are all created and stored as pointers.

When a tower is sold or when an enemy is defeated,

the pointer will be deleted to free up memory.

### File input/output (e.g., for loading/saving game status) <a name="file-inputoutput"></a>

The game saves the current progress in a text file. This includes

- Map number
- Health
- Money
- Wave number
- Tower information (Name, level, coordinates)

When loading a game, the data from the text file will be read and the game status will be updated.

Additionally, the game automatically saves the game after editing and after each wave. The player does not need to actively save their game.

### Program codes in multiple files <a name="multiple-files"></a>

The source code is split into different components and stored inside `src` folder. 

A Makefile is created to compile all the code components.

## External Libraries <a name="external-libraries"></a>
`Ncurses` is used for the graphical user interface in this project.


