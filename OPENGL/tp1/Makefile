CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -lglu32 -lopengl32 -lfreeglut
LDXX_FLAGS = -lGL  -lGLEW -lglut -lpthread

SRC_FILES=src/matrix4.cpp src/main.cpp src/vector3.cc src/fructum.cpp src/program/program.cpp
OBJ_FILES=src/matrix4.o src/main.o src/vector3.o src/fructum.o src/program/program.o

all: ${OBJ_FILES}
	${CXX} -o out ${CXX_FLAGS} ${LDXX_FLAGS} ${OBJ_FILES}
