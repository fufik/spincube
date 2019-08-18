#all :
#	g++ main.cpp bmp.cpp shader.cpp -std=c++14 -fpermissive -Wwrite-strings -lglfw -lGL -lGLEW -o test
CC	 := g++
CFLAGS := -fpermissive -Wwrite-strings -lglfw -lGL -lGLEW 
TARGET := application

SRC	 := src
OBJ	 := obj
BIN	 := bin

${OBJ} ${BIN}:
	mkdir -p $@

SOURCES  := $(wildcard ${SRC}/*.cpp)
OBJECTS  := $(patsubst ${SRC}/%.cpp, ${OBJ}/%.o, ${SOURCES})

all:	${OBJ} ${BIN} ${OBJECTS}
	${CC} ${CFLAGS} ${OBJ}/* -o ${BIN}/example 
	
	
${OBJ}/%.o: ${SRC}/%.cpp
	${CC} ${CFLAGS} -c $< -o $@


clean:
	rm -rf ${BIN}
	rm -rf ${OBJ}


.PHONY: clean all
