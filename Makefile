gametest: test.cpp map.cpp enemy.cpp path.cpp tower.cpp chooseMap.cpp
	g++ test.cpp path.cpp map.cpp enemy.cpp tower.cpp chooseMap.cpp save.cpp -o test -lncurses