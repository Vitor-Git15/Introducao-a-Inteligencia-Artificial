#ifndef GREEDYSOLVER
#define GREEDYSOLVER

#include "SudokuSolver.hpp"
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>

class GreedySolver : public SudokuSolver
{
protected:
    struct State
    {
        SudokuBoard board;
        int filled_cells;
        State(SudokuBoard board, int filled_cells) : board(board), filled_cells(filled_cells) {}
        State(SudokuBoard board) : State(board, 0) {}
        bool operator<(const State &other) const
        {
            return filled_cells < other.filled_cells;
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
            int filled_cells = current.filled_cells;
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
    GreedySolver(SudokuBoard &board) : SudokuSolver(board) {}
    GreedySolver() : SudokuSolver() {}
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