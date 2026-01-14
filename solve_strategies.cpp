#include "solve_strategies.h"
#include "board.h"
#include <iostream>

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
				for (int num = 0; num < 9; num++)
				{
					if (cell.candidates.test(num))
					{
						board.PlaceNumber(row, col, num + 1);
						std::cout << "Naked Single: " << (num + 1) << " from (" << row << "," << col << "\n";
						return true;
					}
				}
			}
		}
	}

	// No naked single found
	return false;
}

bool HiddenSingleStrategy::CheckRows(SudokuBoard& board)
{
	const auto& grid = board.GetBoard();

	for (int row = 0; row < board.boardSize; row++)
	{
		for (int num = 1; num <= 9; num++)
		{
			int foundCol = -1;

			for (int col = 0; col < board.boardSize; col++)
			{
				const Cell& cell = grid[row][col];

				if (cell.value == 0 && cell.candidates.test(num - 1))
				{
					if (foundCol != -1)
					{
						foundCol = -1;
						break;
					}
					foundCol = col;
				}
			}

			if (foundCol != -1)
			{
				board.PlaceNumber(row, foundCol, num);
				std::cout << "Hidden Single: " << num << " from (" << row << "," << foundCol << "\n";
				return true;
			}
		}
	}

	// No hidden single found
	return false;
}

bool HiddenSingleStrategy::CheckColumns(SudokuBoard& board)
{
	const auto& grid = board.GetBoard();

	for (int col = 0; col < board.boardSize; col++)
	{
		for (int num = 1; num <= 9; num++)
		{
			int foundRow = -1;

			for (int row = 0; row < board.boardSize; row++)
			{
				const Cell& cell = grid[row][col];

				if (cell.value == 0 && cell.candidates.test(num - 1))
				{
					if (foundRow != -1)
					{
						foundRow = -1;
						break;
					}
					foundRow = row;
				}
			}

			if (foundRow != -1)
			{
				std::cout << "Hidden Single: " << num << " from (" << foundRow << "," << col << "\n";
				board.PlaceNumber(foundRow, col, num);
				return true;
			}
		}
	}

	// No hidden single found
	return false;
}

bool HiddenSingleStrategy::CheckBoxes(SudokuBoard& board)
{
	const auto& grid = board.GetBoard();

	for (int br = 0; br < 3; br++)
	{
		for (int bc = 0; bc < 3; bc++)
		{
			for (int num = 1; num <= 9; num++)
			{
				int foundRow = -1;
				int foundCol = -1;

				for (int row = 0; row < 3; row++)
				{
					for (int col = 0; col < 3; col++)
					{
						int rr = br * 3 + row;
						int cc = bc * 3 + col;

						const Cell& cell = grid[rr][cc];

						if (cell.value == 0 && cell.candidates.test(num - 1))
						{
							if (foundRow != -1)
							{
								foundRow = -1;
								goto next_number; // break out of nested for loop
							}

							foundRow = rr;
							foundCol = cc;
						}
					}
				}

				if (foundRow != -1)
				{
					std::cout << "Hidden Single: " << num << " from (" << foundRow << "," << foundCol << "\n";
					board.PlaceNumber(foundRow, foundCol, num);
					return true;
				}

			next_number:;
			}
		}
	}

	// No hidden single found
	return false;
}

bool PointingPairTripleStrategy::BoxToRow(SudokuBoard& board)
{
	auto& grid = board.GetBoard();
	bool changed = false;

	for (int br = 0; br < 3; br++)
	{
		for (int bc = 0; bc < 3; bc++)
		{
			for (int num = 1; num <= 9; num++)
			{
				int targetRow = -1;

				for (int row = 0; row < 3; row++)
				{
					for (int col = 0; col < 3; col++)
					{
						int rr = br * 3 + row;
						int cc = bc * 3 + col;

						const Cell& cell = grid[rr][cc];

						if (cell.value == 0 && cell.candidates.test(num - 1))
						{
							if (targetRow == -1) { targetRow = rr; }
							else if (targetRow != rr) { goto next_number; }
						}
					}
				}

				if (targetRow != -1)
				{
					for (int col = 0; col < board.boardSize; col++)
					{
						const Cell& cell = grid[targetRow][col];

						if (col / 3 != bc && cell.value == 0 && cell.candidates.test(num - 1))
						{
							std::cout << "Locked candidate eliminated: " << num << " from (" << targetRow << "," << col << "\n";
							board.RemoveCandidate(targetRow, col, num);
							changed = true;
						}
					}
				}

			next_number:;
			}
		}
	}

	return changed;
}

bool PointingPairTripleStrategy::BoxToColumn(SudokuBoard& board)
{
	auto& grid = board.GetBoard();
	bool changed = false;

	for (int bc = 0; bc < 3; bc++)
	{
		for (int br = 0; br < 3; br++)
		{
			for (int num = 1; num <= 9; num++)
			{
				int targetCol = -1;

				for (int col = 0; col < 3; col++)
				{
					for (int row = 0; row < 3; row++)
					{
						int rr = br * 3 + row;
						int cc = bc * 3 + col;

						const Cell& cell = grid[rr][cc];

						if (cell.value == 0 && cell.candidates.test(num - 1))
						{
							if (targetCol == -1) { targetCol = cc; }
							else if (targetCol != cc) { goto next_number; }
						}
					}
				}

				if (targetCol != -1)
				{
					for (int row = 0; row < board.boardSize; row++)
					{
						const Cell& cell = grid[row][targetCol];

						if (row / 3 != br && cell.value == 0 && cell.candidates.test(num - 1))
						{
							std::cout << "Locked candidate eliminated: " << num << " from (" << row << "," << targetCol << "\n";
							board.RemoveCandidate(row, targetCol, num);
							changed = true;
						}
					}
				}

			next_number:;
			}
		}
	}

	return changed;
}
