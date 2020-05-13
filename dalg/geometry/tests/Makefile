
all: test_main

test_main : test_main.o test_collision.o test_polygon.o
	g++ -std=c++17 -g -Wall -Wextra test_main.o test_collision.o test_polygon.o

test_main.o : test_main.cpp
	g++ -std=c++17 -g -Wall -Wextra test_main.cpp -c

test_collision.o : test_collision.cpp
	g++ -std=c++17 -g -Wall -Wextra test_collision.cpp -c

test_polygon.o : test_polygon.cpp 
	g++ -std=c++17 -g -Wall -Wextra test_polygon.cpp -c

clean:
	rm *.o
	rm ./a.out

pclean:
	rm ./a.out
