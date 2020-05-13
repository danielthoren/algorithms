
all: test_main

test_main : test_main.o test_collision.o test_polygon.o test_rectangle.o test_vec2d.o
	g++ -std=c++17 -g -Wall -Wextra test_main.o test_vec2d.o test_collision.o test_polygon.o test_rectangle.o

test_main.o : test_main.cpp
	g++ -std=c++17 -g -Wall -Wextra test_main.cpp -c

test_collision.o : test_collision.cpp
	g++ -std=c++17 -g -Wall -Wextra test_collision.cpp -c

test_polygon.o : test_polygon.cpp 
	g++ -std=c++17 -g -Wall -Wextra test_polygon.cpp -c

test_rectangle.o : test_rectangle.cpp
	g++ -std=c++17 -g -Wall -Wextra test_rectangle.cpp -c

test_vec2d.o : test_vec2d.cpp
	g++ -std=c++17 -g -Wall -Wextra test_vec2d.cpp -c

clean:
	rm *.o
	rm ./a.out

pclean:
	rm ./a.out
