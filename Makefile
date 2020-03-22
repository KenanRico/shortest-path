#Compiler
CC := gcc

#IO FILES
SRCDIR := src
SRC := $(SRCDIR)/*.c $(SRCDIR)/algo/*.c
TARGET := dijkstra.exe

#Flags
FLAGS := -std=c11 -Wall

#INCLUDE PATHS
INCL_PATHS := -ID:\Coding\libs\SDL2_VC\include

#LIB_PATHS
LIB_PATHS := -LD:\Coding\libs\SDL2_VC\lib\x64 -LD:\Coding\libs\SDL2_VC\Extensions\SDL2_image-2.0.1\lib\x64 -LD:\Coding\libs\SDL2_VC\Extensions\SDL2_ttf-2.0.15\lib\x64

#LINKER FLAGS
LINKER_FLAGS := -lSDL2main -lSDL2 -lSDL2test -lSDL2_image -lSDL2_ttf

#Make
dmake:
	$(CC) $(SRC) -o $(TARGET) $(FLAGS) $(INCL_PATHS) $(LIB_PATHS) $(LINKER_FLAGS) 
