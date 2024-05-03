#ifndef UCSSOLVER
#define UCSSOLVER

#include "SudokuSolver.hpp"
#include <vector>
#include <queue>


class UCSSolver : public SudokuSolver
{
protected:

    struct State
    {
        SudokuBoard board;
        int sum;
        State(SudokuBoard board, int sum) : board(board), sum(sum){}
        State(SudokuBoard board) : board(board){ sum = 0;}
        bool operator<(const State &other) const{
            return sum < other.sum;
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
            
            this->iterations++;
            auto [row, col] = r_c;
            int sum = current.sum;
            
            for (int value = 1; value <= BOARDSIZE; value++)
            {
                if (((sum + value) <= SUMMAX) && current.board.check(row, col, value))
                {
                    SudokuBoard sb = current.board;
                    sb.insert(row, col, value);
                    pq.push(State(sb, (sum + value)));
                }
            }
        }
        return false;
    }

public:
    UCSSolver(SudokuBoard &board) : SudokuSolver(board) {}
    UCSSolver() : SudokuSolver() {}
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