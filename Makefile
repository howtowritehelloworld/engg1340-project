gametest: test.cpp map.cpp enemy.cpp path.cpp tower.cpp 
	g++ test.cpp path.cpp map.cpp enemy.cpp tower.cpp save.cpp -o test -lncurses
