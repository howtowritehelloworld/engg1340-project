gametest: gametest.cpp map.cpp enemy.cpp path.cpp tower.cpp
	g++ test.cpp path.cpp map.cpp enemy.cpp tower.cpp -o gametest -lncurses
