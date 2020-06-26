
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
		${BUILD_DIR}/test_vec2d.o \
		${BUILD_DIR}/test_line_segment.o \
		${BUILD_DIR}/test_polygon.o \
		${BUILD_DIR}/test_aabb.o \
		${BUILD_DIR}/test_circle.o \
		${BUILD_DIR}/test_intersect.o \
		${BUILD_DIR}/test_rectangle.o

	${CC} ${FLAGS} \
	${CATCH_DIR}/test_main.o \
	${BUILD_DIR}/test_vec2d.o \
	${BUILD_DIR}/test_line_segment.o \
	${BUILD_DIR}/test_polygon.o \
	${BUILD_DIR}/test_aabb.o \
	${BUILD_DIR}/test_circle.o \
	${BUILD_DIR}/test_intersect.o \
	${BUILD_DIR}/test_rectangle.o

${CATCH_DIR}/test_main.o : test_main.cpp
	${CC} ${FLAGS} -c test_main.cpp -o ${CATCH_DIR}/test_main.o

${BUILD_DIR}/test_intersect.o : test_intersect.cpp
	${CC} ${FLAGS} -c test_intersect.cpp -o ${BUILD_DIR}/test_intersect.o

${BUILD_DIR}/test_rectangle.o : test_rectangle.cpp
	${CC} ${FLAGS} -c test_rectangle.cpp -o ${BUILD_DIR}/test_rectangle.o

${BUILD_DIR}/test_aabb.o : test_aabb.cpp
	${CC} ${FLAGS} -c test_aabb.cpp -o ${BUILD_DIR}/test_aabb.o

${BUILD_DIR}/test_circle.o : test_circle.cpp
	${CC} ${FLAGS} -c test_circle.cpp -o ${BUILD_DIR}/test_circle.o

${BUILD_DIR}/test_polygon.o : test_polygon.cpp
	${CC} ${FLAGS} -c test_polygon.cpp -o ${BUILD_DIR}/test_polygon.o

${BUILD_DIR}/test_line_segment.o : test_line_segment.cpp
	${CC} ${FLAGS} -c test_line_segment.cpp -o ${BUILD_DIR}/test_line_segment.o

${BUILD_DIR}/test_vec2d.o : test_vec2d.cpp
	${CC} ${FLAGS} -c test_vec2d.cpp -o ${BUILD_DIR}/test_vec2d.o

clean:
	rm ${BUILD_DIR}/*.o

cleanall:
	rm -r ${BUILD_DIR}
