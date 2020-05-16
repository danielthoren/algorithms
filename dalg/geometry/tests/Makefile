
CATCH_DIR=./build/catch
BUILD_DIR=./build

CC=g++
FLAGS=-std=c++17 -g -Wall -Wextra

all: dir test_main

dir:
	mkdir -p ${BUILD_DIR}
	mkdir -p ${CATCH_DIR}

test_main : test_main.o test_collision.o test_polygon.o test_rectangle.o test_vec2d.o
	${CC} ${FLAGS} \
	${BUILD_DIR}/test_main.o \
	${BUILD_DIR}/test_vec2d.o \
	${BUILD_DIR}/test_collision.o \
	${BUILD_DIR}/test_polygon.o \
	${BUILD_DIR}/test_rectangle.o

test_main.o: test_main.cpp
	${CC} ${FLAGS} test_main.cpp -c -o ${BUILD_DIR}/test_main.o

test_collision.o : test_collision.cpp
	${CC} ${FLAGS} test_collision.cpp -c -o ${BUILD_DIR}/test_collision.o

test_polygon.o : test_polygon.cpp
	${CC} ${FLAGS} test_polygon.cpp -c -o ${BUILD_DIR}/test_polygon.o

test_rectangle.o : test_rectangle.cpp
	${CC} ${FLAGS} test_rectangle.cpp -c -o ${BUILD_DIR}/test_rectangle.o

test_vec2d.o : test_vec2d.cpp
	${CC} ${FLAGS} test_vec2d.cpp -c -o ${BUILD_DIR}/test_vec2d.o

clean:
	rm ./build/*.o

cleanall:
	rm -r ./build
