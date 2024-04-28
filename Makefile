main: main.cpp src/game.cpp src/path.cpp src/map.cpp src/enemy.cpp src/tower.cpp src/save.cpp
	g++ main.cpp src/game.cpp src/path.cpp src/map.cpp src/enemy.cpp src/tower.cpp src/save.cpp -o game -lncurses
