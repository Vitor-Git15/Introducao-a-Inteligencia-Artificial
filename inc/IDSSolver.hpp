#ifndef IDSSOLVER
#define IDSSOLVER

#include "SudokuSolver.hpp"

class IDSSolver : public SudokuSolver{
    protected:
        bool solve_sudoku(SudokuBoard &board, int lim){
            if(lim <= 0)
                return false;
            
            std::pair<int, int> r_c = board.get_next();
            
            if(r_c == FULL)
                return true;

            int row = r_c.first, col = r_c.second;

            for (int elem = 1; elem <= BOARDSIZE; elem++){
                if(board.check(row, col, elem)){

                    board.insert(row, col, elem);

                    if(solve_sudoku(board, lim - 1))
                        return true;

                    board.insert(row, col, NULL_ELEM);
                }
            }

            return false;
        }

    public:

    IDSSolver(SudokuBoard &board): SudokuSolver(board){}
    
    void solve() override{
        int lim = 1;
        while(lim <= MAXELEMENTS){
            bool res = solve_sudoku(this->board, lim);
            if(res){
                std::cout << lim << std::endl;
                print_board();
                return;
            }
            lim++;
        }
        fail();
    }

};

#endif