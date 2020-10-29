###This make file was intended for use with nmake

#compiler
CC = cl

#executable name
EXE = dijkstra

#include directory
SRC_DIR = .
OBJ_DIR = obj
#INCLUDE_DIR = .

#source files
SRC = $(SRC_DIR)/*.cpp

#flags
CFLAGS = /W4 /nologo /EHsc

.PHONY: all

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) $? /Fo: $(OBJ_DIR)/ /Fe: $@.exe


clean:
	del $(OBJ_DIR)\*.obj $(EXE).exe