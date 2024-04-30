main: main.cpp game.o path.o map.o enemy.o tower.o save.o
	g++ $^ -o game -lncurses

tower.o: src/tower.cpp src/tower.h src/enemy.h src/map.h src/path.h
	g++ -c $<

enemy.o: src/enemy.cpp src/enemy.h
	g++ -c $<

map.o: src/map.cpp src/map.h src/path.h src/enemy.h src/tower.h
	g++ -c $<

path.o: src/path.cpp src/path.h src/map.h
	g++ -c $<

game.o: src/game.cpp src/game.h src/map.h src/enemy.h src/tower.h src/path.h src/save.h
	g++ -c $< -lncurses

save.o: src/save.cpp src/save.h src/map.h src/enemy.h src/tower.h src/path.h
	g++ -c $<

clean:
	rm -f *.o game save.txt

.PHONY: clean