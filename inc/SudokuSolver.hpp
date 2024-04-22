#ifndef SOLVER
#define SOLVER

#include "SudokuBoard.hpp"

class SudokuSolver{
    protected:
        SudokuBoard board;
    public:
        SudokuSolver(SudokuBoard &board){this->board = board;}
        virtual void print_board(){ board.print_board(); }
        virtual void fail() {std::cerr << "Warning: Unable to solve the initially provided Sudoku board." << std::endl;}
        virtual void solve(){}
};

#endif