#ifndef UCSSOLVER
#define UCSSOLVER

#include "SudokuSolver.hpp"
#include <vector>
#include <tuple>
#include <algorithm>

// No algoritmo em questão o custo é dado como a quantidade de valores possíveis
// para determinado quadrante, iniciamos com os que possuem menor quantidade
// caminhando para aquele de maior, o desempate é feito pela linha e coluna.
// OBS: calculamos o valor apenas uma vez a fim de evitar custos maiores a cada iteração
class UCSSolver : public SudokuSolver{
    protected:
        int iterations = 0;
        std::vector<std::tuple<int, int, int>> cost;
        static bool compare_cost(const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b) {
            if(std::get<2>(a) != std::get<2>(b))
                return std::get<2>(a) < std::get<2>(b);
            if(std::get<0>(a) != std::get<0>(b))
                return std::get<0>(a) < std::get<0>(b);
            return std::get<1>(a) < std::get<1>(b);
        }
        void possibilities(int ci, int cj, int inc){
            for(auto &c: cost){
                if((std::get<0>(c) == ci || std::get<1>(c) == cj) && (std::get<0>(c) != ci || std::get<1>(c) != cj))
                    std::get<2>(c) += inc;
            }
            std::sort(cost.begin(), cost.end(), compare_cost);
        }
        void set_cost_table(){
            for (int i = 0; i < BOARDSIZE; i++){
                for (int j = 0; j < BOARDSIZE; j++){
                    if(board.get(i, j) == 0){
                        int count = 0;

                        for (int val = 1; val <= BOARDSIZE; val++){
                            if(board.check(i, j, val))
                                count++;
                        }

                        cost.push_back(std::make_tuple(i, j, count));
                    }
                }
            }
            std::sort(cost.begin(), cost.end(), compare_cost);
        }
        bool solve_sudoku(SudokuBoard &board){
            if(cost.empty()){
                std::pair<int, int> r_c = board.get_next();
            
                if(r_c == FULL)
                    return true;
                return false;
            }
            iterations++;
            std::tuple<int, int, int> next = cost[0];

            int row = std::get<0>(next), col = std::get<1>(next), val = std::get<2>(next);
            std::cout << row << " " << col << " " << val << std::endl;
            cost.erase(cost.begin());
            possibilities(row, col, -1);
            for (int elem = 1; elem <= BOARDSIZE; elem++){
                if(board.check(row, col, elem)){

                    board.insert(row, col, elem);
                    if(solve_sudoku(board))
                        return true;
                    board.insert(row, col, NULL_ELEM);
                }
            }
            possibilities(row, col, 1);
            cost.insert(cost.begin(), std::make_tuple(row, col, val));
            return false;
        }

    public:

    UCSSolver(SudokuBoard &board): SudokuSolver(board){}
    
    void solve() override{
        set_cost_table();
        std::cout << cost.size() << std::endl;
        bool res = solve_sudoku(this->board);
        if(res){
            print_board();
            std::cout << iterations << std::endl;
        }
            
        else
            fail();
    }

};

#endif