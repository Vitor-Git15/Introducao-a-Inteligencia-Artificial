#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa sudoku
# Autor		: Vitor Emanuel Ferreira Vital (vitorvital@dcc.ufmg.br)
# Histórico	: 2024 - abril - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CXX = g++
SRC = src
OBJ = obj
INC = inc
BIN = bin
OBJS = $(OBJ)/main.o
HDRS = $(INC)/SudokuBoard.hpp $(INC)/SudokuSolver.hpp $(INC)/BFSSolver.hpp $(INC)/IDSSolver.hpp
CFLAGS = -pg -std=c++11 -Wall -c -I$(INC)

EXE = $(BIN)/main

all: $(EXE)

$(BIN)/main: $(OBJS)
	$(CXX) -pg -o $@ $(OBJS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CXX) $(CFLAGS) -o $@ $(SRC)/main.cpp

clean:
	rm -f $(EXE) $(OBJS)