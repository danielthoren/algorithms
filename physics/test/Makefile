
SHELL = /bin/sh

CATCH_DIR=./build/catch
BUILD_DIR=./build

CC=g++
FLAGS=-std=c++17 -g -Wall -Wextra

all: dir test_main.o
	./a.out

dir:
	mkdir -p ${BUILD_DIR}
	mkdir -p ${CATCH_DIR}

test_main.o :   ${CATCH_DIR}/test_main.o \
		${BUILD_DIR}/test_collision.o

	${CC} ${FLAGS} \
	${CATCH_DIR}/test_main.o \
	${BUILD_DIR}/test_collision.o

${CATCH_DIR}/test_main.o : test_main.cpp
	echo "test_main"
	${CC} ${FLAGS} -c test_main.cpp -o ${CATCH_DIR}/test_main.o

${BUILD_DIR}/test_collision.o : test_collision.cpp
	${CC} ${FLAGS} -c test_collision.cpp -o ${BUILD_DIR}/test_collision.o

clean:
	rm ${BUILD_DIR}/*.o

cleanall:
	rm -r ${BUILD_DIR}
