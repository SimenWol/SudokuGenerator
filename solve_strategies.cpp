#include "solve_strategies.h"
#include "board.h"

bool NakedSingleStrategy::Apply(SudokuBoard& board)
{
	auto& grid = board.GetBoard();

	for (int row = 0; row < board.boardSize; row++)
	{
		for (int col = 0; col < board.boardSize; col++)
		{
			// Check if cell has only one candidate -> if yes placenumber, else continue
			const Cell& cell = grid[row][col];

			if (cell.value == 0 && cell.candidates.count() == 1)
			{
				for (int n = 0; n < 9; n++)
				{
					if (cell.candidates.test(n))
					{
						board.PlaceNumber(row, col, n + 1);
						return true;
					}
				}
			}
		}
	}

	// No naked single found
	return false;
}