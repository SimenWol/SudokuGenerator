#include <stdio.h>
#include <iostream>
#include <chrono>

#include "board.h"
#include "solver.h"

int main()
{
    SudokuBoard brd;
    std::shared_ptr<SudokuBoard> board = std::make_shared<SudokuBoard>(brd);

    std::cout << "Initial board:\n\n";

    board->PrintBoard();
    std::cout << "\n\n\n";

    getchar();

    SudokuSolver solver;
    solver.SetBoard(board);

    auto start = std::chrono::high_resolution_clock::now();

    if (solver.Solve(/*false*/))
    {
        auto stop = std::chrono::high_resolution_clock::now();
        
        std::cout << "\nSolution for the given board:\n\n";
        board->PrintBoard();

        std::cout << "\nSolve time (microseconds): " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;
    }
    else
    {
        std::cout << "\nNo solution exists for the given board" << std::endl;

        std::cout << "\nSolver got this far:\n\n";
        board->PrintBoard();
    }

    getchar();

    return 0;
}