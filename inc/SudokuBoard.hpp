#ifndef SUDOKU_BOARD
#define SUDOKU_BOARD

#include <iostream>
#include <string>

#define NULL_ELEM 0
#define WIN -1
#define SIZE_QUAD 3
#define BOARDSIZE 9
#define MAXELEMENTS 81
#define FULL std::make_pair(WIN, WIN)

class SudokuBoard{
    private:
        int size = BOARDSIZE;
        int board[BOARDSIZE][BOARDSIZE];

        // Verifica se o novo elemento inserido é válido na coluna inserida
        // true - se for válido
        // false - caso contrário
        bool check_row_and_col(int ci, int cj, int elem){
            for (int i = 0; i < BOARDSIZE; i++){
                if(((board[i][cj] == elem) && (i != ci)) ||
                   ((board[ci][i] == elem) && (i != cj)))
                    return false;
            }
            return true;
        }

        // Verifica se o novo elemento inserido é válido no quadrante inserido
        // true - se for válido
        // false - caso contrário
        bool check_quad(int ci, int cj, int elem){
            int startRow = (SIZE_QUAD * (ci / SIZE_QUAD));
            int startCol = (SIZE_QUAD * (cj / SIZE_QUAD));

            for (int i = startRow; i < startRow + SIZE_QUAD; i++){
                for (int j = startCol; j < startCol + SIZE_QUAD; j++){
                    if((board[i][j] == elem) && (ci != i || cj != j))
                        return false;
                }
            }
            return true;
        }

    public:
        SudokuBoard(){}

        int get(int i, int j){
            if(i >= BOARDSIZE || i < 0)
                return -1;
            if(j >= BOARDSIZE || j < 0)
                return -1;
            
            return this->board[i][j];
        }

        void insert(int ci, int cj, int elem){
            if(ci < 0 || ci >= BOARDSIZE)
                return;
            if(cj < 0 || cj >= BOARDSIZE)
                return;
            
            this->board[ci][cj] = elem;
        }

        void insert_line(int line, std::string elements){
            if(line < 0 || line >= BOARDSIZE)
                return;
            if(elements.size() != BOARDSIZE)
                return;

            for (int i = 0; i < BOARDSIZE; i++)
                insert(line, i, (elements[i] - '0'));
        }
        void print_board(){
            for (int i = 0; i < BOARDSIZE; i++){
                for (int j = 0; j < BOARDSIZE; j++){
                    std::cout << board[i][j] << " ";
                }
                std::cout << std::endl;
            }
            
        }

        // Verifica se o novo elemento inserido é válido na linha inserida
        // true - se for válido
        // false - caso contrário
        bool check(int ci, int cj, int elem){
            if(elem == NULL_ELEM)
                return true;
            
            if(!check_row_and_col(ci, cj, elem))
                return false;
            if(!check_quad(ci, cj, elem))
                return false;

            return true;
        }

        // Considero que sempre há a checagem para inserir um número e os valores iniciais
        // são corretos, portanto, apenas verificarei se há algum zero.
        // true - se a tabela está completa
        // false - caso contrário
        std::pair<int, int> get_next(){
            for (int i = 0; i < BOARDSIZE; i++){
                for (int j = 0; j < BOARDSIZE; j++){
                    if(board[i][j] == NULL_ELEM)
                        return std::make_pair(i, j);
                }
            }
            return FULL;
        }
};

#endif
