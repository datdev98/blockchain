# Compiler options
CC=g++
CFLAGS=-c -Wall -Iincl
LDFLAGS=
EXECUTABLE_NAME=Blockchain.exe

# Folders
SRC=src
BIN=bin
OBJ=obj

# Files
SOURCE_FILES= $(wildcard $(SRC)/*.cpp) main.cpp
EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(BIN)/%)
OBJECT_FILES     = $(SOURCE_FILES:%.cpp=$(OBJ)/%.o)

build: $(EXECUTABLE_FILES)

clean:
	rm -r -f $(BIN)

.PHONY: build clean

$(EXECUTABLE_FILES): $(OBJECT_FILES)
	@mkdir -p $(BIN)
	@$(CC) $(LDFLAGS) -o $@ $^
	@echo "Build successful!"

$(OBJECT_FILES): $(OBJ)/%.o: %.cpp
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ $<