#ifndef ASTARSOLVER
#define ASTARSOLVER

#include "SudokuSolver.hpp"
#include <vector>
#include <map>
#include <queue>

class AStarSolver : public SudokuSolver
{
protected:
    struct Next{
        int i, j, options;
        Next(int i, int j, int options): i(i), j(j), options(options){}
        bool operator<(const Next &other) const{
            return std::tie(options, i, j) > std::tie(other.options, other.i, other.j);
        }
    };
    struct State
    {
        SudokuBoard board;
        int filled_cells;
        std::priority_queue<Next, std::vector<Next>> next_cell;
        State(SudokuBoard board, int filled_cells) : board(board), filled_cells(filled_cells){
            for (int i = 0; i < BOARDSIZE; i++){
                for (int j = 0; j < BOARDSIZE; j++){
                    if(board.get(i, j) == 0){
                        int count = 0;
                        for (int value = 1; value <= BOARDSIZE; value++){
                            if(board.check(i,j,value)) count++;
                        }
                        next_cell.push(Next(i, j, count));
                    }
                }
            }
        }
        State(SudokuBoard board) : State(board, 0) {}
        bool operator<(const State &other) const{
            if(filled_cells != other.filled_cells)
                return filled_cells < other.filled_cells;
            if(this->next_cell.empty())
                return false;
            if(other.next_cell.empty())
                return true;
            return this->next_cell.size() < other.next_cell.size();
        }
    };
    bool solve_sudoku(SudokuBoard &board)
    {
        std::priority_queue<State, std::vector<State>> pq;
        pq.push(State(board));
        while (!pq.empty())
        {
            State current = pq.top();
            pq.pop();
            auto r_c = current.board.get_next();
            if (r_c == FULL)
            {
                board = current.board;
                return true;
            }
            if(current.next_cell.empty())
                continue;
            
            auto [row, col, qntd] = current.next_cell.top();
            current.next_cell.pop();
            if(qntd == 0)
                continue;;
            this->iterations++;
            
            int filled_cells= current.filled_cells;
            for (int value = 1; value <= BOARDSIZE; value++)
            {
                if (current.board.check(row, col, value))
                {
                    SudokuBoard sb = current.board;
                    sb.insert(row, col, value);
                    pq.push(State(sb, filled_cells + 1));
                }
            }
        }
        return false;
    }

public:
    AStarSolver(SudokuBoard &board) : SudokuSolver(board) {}
    AStarSolver() : SudokuSolver() {}
    void solve() override
    {
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