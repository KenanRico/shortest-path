#Compiler
CC := gcc

#IO FILES
SRC := *.c
TARGET := dijkstra.exe

#Flags
FLAGS := -std=c11 -Wall

#INCLUDE PATHS
INCL_PATHS := -ID:\Coding\libs\SDL2_VC\include

#LIB_PATHS
LIB_PATHS := -LD:\Coding\libs\SDL2_VC\lib\x64

#LINKER FLAGS
LINKER_FLAGS := -lSDL2main -lSDL2 -lSDL2test

#Make
dmake:
	$(CC) $(SRC) -o $(TARGET) $(FLAGS) $(INCL_PATHS) $(LIB_PATHS) $(LINKER_FLAGS) 
