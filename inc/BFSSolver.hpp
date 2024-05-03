#ifndef BFSSOLVER
#define BFSSOLVER

#include "SudokuSolver.hpp"
#include <queue>

class BFSSolver : public SudokuSolver{
    protected:
        
        bool solve_sudoku(SudokuBoard &board){
            std::queue<SudokuBoard> states;
            std::pair<int, int> r_c = board.get_next();
            
            if(r_c == FULL)
                return true;
            states.push(board);

            while(!states.empty()){
                
                SudokuBoard current = states.front();
                states.pop();
                
                r_c = current.get_next();
                if(r_c == FULL){
                    board = current;
                    return true;
                }
                this->iterations++;
                int row = r_c.first, col = r_c.second;

                for(int i = 1; i <= BOARDSIZE; i++){
                    if(current.check(row, col, i)){
                        SudokuBoard sb = current;
                        sb.insert(row, col, i);
                        states.push(sb);
                    }
                }
            }
            return false;
        }

    public:

    BFSSolver(SudokuBoard &board): SudokuSolver(board){}
    BFSSolver(): SudokuSolver(){}
    void solve() override{
        auto inicio = std::chrono::high_resolution_clock::now();
        bool res = solve_sudoku(this->board);
        auto resultado = std::chrono::high_resolution_clock::now() - inicio;
        if (res)
        {
            long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(resultado).count();
            print_board();
            std::cout << iterations << " " << milliseconds << std::endl;
        }

        else
            fail();
    }

};

#endif