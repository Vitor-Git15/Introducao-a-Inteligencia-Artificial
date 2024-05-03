#ifndef IDSSOLVER
#define IDSSOLVER

#include "SudokuSolver.hpp"
#include <stack>
#include <map>
class IDSSolver : public SudokuSolver
{
protected:
    std::map<std::pair<int, int>, int> depth;

    void set_depth(){
        int pos = 1;
        for (int i = 0; i < BOARDSIZE; i++){
            for (int j = 0; j < BOARDSIZE; j++){
                if(this->board.get(i, j) == 0){
                    depth.insert({{i,j}, pos});
                    pos++;
                }
            }
        }
    }

    int calc_depth(int ci, int cj){
        auto it = depth.find({ci, cj});
        if(it == depth.end())
            return (MAXELEMENTS + 1);
        return it->second;
    }

    bool solve_sudoku(SudokuBoard &board, int lim)
    {
        std::stack<SudokuBoard> states;
        std::pair<int, int> r_c = board.get_next();

        if (r_c == FULL)
            return true;
        states.push(board);

        while (!states.empty()){
            SudokuBoard current = states.top();
            states.pop();
            r_c = current.get_next();
            if (r_c == FULL){
                board = current;
                return true;
            }
            int row = r_c.first, col = r_c.second;
            if(calc_depth(row, col) > lim)
                return false;

            this->iterations++;
            

            for (int i = 1; i <= BOARDSIZE; i++){
                if (current.check(row, col, i)){
                    SudokuBoard sb = current;
                    sb.insert(row, col, i);
                    states.push(sb);
                }
            }
        }
        return false;
    }

public:
    IDSSolver(SudokuBoard &board) : SudokuSolver(board) {}
    IDSSolver() : SudokuSolver() {}
    void solve() override{
        auto inicio = std::chrono::high_resolution_clock::now();
        int lim = 0;
        set_depth();
        while (lim <= MAXELEMENTS){
            bool res = solve_sudoku(this->board, lim);
            if (res){
                auto resultado = std::chrono::high_resolution_clock::now() - inicio;
                long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(resultado).count();
                print_board();
                std::cout << lim << " " << iterations << " " << milliseconds << std::endl;
                return;
            }
            lim++;
        }
        fail();
    }
};

#endif