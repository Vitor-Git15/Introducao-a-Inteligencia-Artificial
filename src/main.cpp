#include <iostream>
#include <string>

#include "SudokuBoard.hpp"
#include "SudokuSolver.hpp"
#include "BFSSolver.hpp"
#include "IDSSolver.hpp"

#define MIN_ARGS 11

void use(){
    std::cout << "TP1 <option> <board 9x9>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "B - Breadth-first search" << std::endl;
    std::cout << "I - Iterative deepening search" << std::endl;
    std::cout << "U - Uniform-cost search" << std::endl;
    std::cout << "A - A* search" << std::endl;
    std::cout << "G - Greedy best-first search" << std::endl;
}

void parse_args(int argc, char **argv, SudokuBoard &ST){
    if(argc < MIN_ARGS){
        std::cerr << "Error: invalid arguments" << std::endl;
        use(); exit(1);
    }

    char* opt;
    opt = argv[1];

    switch (*opt){
    case 'B':
        break;
    case 'I':
        break;
    case 'U':
        break;
    case 'A':
        break;
    case 'G':
        break;
    default:
        std::cout << "Error: invalid algorithm option (" << *opt << ")" << std::endl;
        use(); exit(1);
    }
    char* board_line;
    for (int i = 2; i < argc; i++){
        board_line = argv[i];
        ST.insert_line((i - 2), std::string(board_line));
    }
}

int main(int argc, char **argv){

    SudokuBoard ST;
    parse_args(argc, argv, ST);

    BFSSolver bfs(ST);
    bfs.solve();

    return EXIT_SUCCESS;
}