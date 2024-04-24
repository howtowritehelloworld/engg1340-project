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
-   [Program Requirements](#program-feature)
    -   [1. Generation of random game elements](#1-generation-of-random-game-elements)
    -   [2. Data structures for storing game status](#2-data-structures-for-storing-game-status)
    -   [3. Dynamic Memory Management](#3-dynamic-memory-management)
    -   [4. File input/output (e.g., for loading/saving game status)](#4-file-inputoutput-eg-for-loadingsaving-game-status)
    -   [5. Program codes in multiple files](#5-program-codes-in-multiple-files)
    -   [6. Proper Indentation and naming styles](#6-external-libraries)
    -   [7. In-code documentation](#7-in-code-documentation)
-   [Graphical Demonstration](#Graphics)
-   [How to run the game](#how-to-run-the-game)

 ## Group members

1. Andy
2. Jason
3. Owen
4. Cyric
5. Donald

## Introduction
(name of game) is a tower defence simulator where the primary objective is to waves of incoming enemies from approaching the end of the map. The player must strategically place defensive towers, along predetermined paths or routes which enemies follow. These towers have unique abilities which make them suitable for different situations. With a limited amount of resources (money and health), players must carefully evaluate their positions and come up with the best defensive plan to stop the waves of incoming enemies.

## Controls
Upon the start of the game, players can select the map they want to play on.
After loading the map, players can press "start wave", "build" or "quit" at the action menu.

"start wave" will immediately begin to walk along the path and attempt to reach the end.
Please note that you will not be able to place down towers once the wave has started, so you should make sure you have sufficient defensive towers before starting each wave.

"build" will first allow the player to select a tile with a white cursor.

If the tile is empty, the player will be prompted to select a tower to place from the tower menu. If there is sufficient money, the tower will be placed at the location.

If the tile is a path, the player will return to the action menu.

If the tile is a tower, the player can choose to upgrade or sell the tower, allowing for higher damage output.

"quit" will return the user to the main menu.

## Gameplay

### 1. Gameflow
Each time a wave is passed, the player will be rewarded with money to further enhance their defence.

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
Cost: 20 -> 40 -> 60 -> 80 -> ... (level * 20)

Damage: 3 -> 6 -> 9 -> 12 -> ... (level * 3)

Attack speed: 1 (fast)

Range: 1

Notes: Single target, Can attack both ground and air enemies, Unable to detect Camo enemies.

#### Sniper
Cost: 50 -> 100 -> 150 -> 200 -> ... (level * 50)

Damage: 6 -> 12 -> 18 -> 24 -> ... (level * 6)

Attack speed: 3 (slow)

Range: 2

Notes: Single target, Can attack both ground and air enemies, Can detect Camo enemies.

#### Cannon

Cost: 40 -> 80 -> 120 -> 160 -> ... (level * 30)

Damage: 2 -> 4 -> 6 -> 8 -> ... (level * 4)

Attack speed: 3 (slow)

Range: 1

Notes: Multiple targets, Can only attack ground enemies, Unable to detect Camo enemies.

### 3. Enemies

#### Knight

#### Dragon

#### Vampire

#### Ghost

## Generation of random game elements
