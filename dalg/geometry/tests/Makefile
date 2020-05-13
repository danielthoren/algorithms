
all: test_main

test_main : test_main.o test_collision.o
	g++ -std=c++17 -g -Wall -Wextra test_collision.o test_main.o

test_collision.o : test_collision.cpp
	g++ -std=c++17 -g -Wall -Wextra test_collision.cpp -c

test_main.o : test_main.cpp
	g++ -std=c++17 -g -Wall -Wextra test_main.cpp -c

clean:
	rm *.o
	rm ./a.out


