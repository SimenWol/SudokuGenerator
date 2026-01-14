#include <stdio.h>
#include <iostream>
#include <chrono>

#include "board.h"
#include "solver.h"
#include "board_generator.h"

int main()
{
    BoardGenerator generator;

    auto board = std::make_shared<SudokuBoard>(generator.GenerateSolvedBoard());

    std::cout << "Generated board:\n\n";
    board->PrintBoard();

    generator.DigPuzzle(*board, 25);

    std::cout << "\n\nGenerated puzzle:\n\n";
    board->PrintBoard();
    std::cout << "\n\n";

    getchar();

    SudokuSolver solver(board);

    auto start = std::chrono::high_resolution_clock::now();

    if (solver.Solve(/*false*/))
    {
        auto stop = std::chrono::high_resolution_clock::now();
        
        std::cout << "\nSolution:\n\n";
        board->PrintBoard();

        std::cout << "\nSolve time (microseconds): " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;
    }
    else
    {
        std::cout << "\nNo solution exists!" << std::endl;

        std::cout << "\nSolver got this far:\n\n";
        board->PrintBoard();
    }

    getchar();

    return 0;
}