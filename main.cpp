#include "stdio.h"
#include <iostream>

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

    if (solver.SolveBoard())
    {
        std::cout << "Solution for the given board:\n\n";
        board->PrintBoard();
    }
    else
    {
        std::cout << "No solution exists for the given board" << std::endl;
    }

    getchar();

    return 0;
}