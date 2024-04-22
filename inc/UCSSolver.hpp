#ifndef BFSSOLVER
#define BFSSOLVER

#include "SudokuSolver.hpp"

class BFSSolver : public SudokuSolver{
    protected:
        bool solve_sudoku(SudokuBoard &board){
            std::pair<int, int> r_c = board.get_next();
            
            if(r_c == FULL)
                return true;

            int row = r_c.first, col = r_c.second;

            for (int elem = 1; elem <= BOARDSIZE; elem++){
                if(board.check(row, col, elem)){

                    board.insert(row, col, elem);

                    if(solve_sudoku(board))
                        return true;

                    board.insert(row, col, NULL_ELEM);
                }
            }

            return false;
        }

    public:

    BFSSolver(SudokuBoard &board): SudokuSolver(board){}
    
    void solve() override{
        bool res = solve_sudoku(this->board);
        if(res)
            print_board();
        else
            fail();
    }

};

#endif