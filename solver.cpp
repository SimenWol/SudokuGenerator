#include "solver.h"
#include "board.h"
#include <iostream>

void SudokuSolver::PopulateStrategies()
{
	strategies.push_back(std::make_unique<NakedSingleStrategy>());
	strategies.push_back(std::make_unique<HiddenSingleStrategy>());
	strategies.push_back(std::make_unique<PointingPairTripleStrategy>());
}

bool SudokuSolver::Solve()
{
	while (true)
	{
		bool progress = false;
		
		for (auto& strategy : strategies)
		{
			if (strategy->Apply(*board))
			{
				if (board->HasContradiction()) { std::cout << "Contradiction detected!\n\n"; return false; }
				progress = true;
				break;
			}
		}

		if (!progress)
			break;
	}

	//return board->IsSolved() || BackTrackingSolve();
	return board->IsSolved();
}

bool SudokuSolver::SolveBoard()
{
	int row, col;

	// All cells occupied -> solved
	if (!FindEmptyCell(row, col))
	{
		return true;
	}

	// Solve through backtracking (bruteforce solution)
	for (int num = 1; num <= 9; num++)
	{
		if (IsValid(row, col, num))
		{
			board->SetValue(row, col, num);

			if (SolveBoard())
			{
				return true;
			}

			// Backtrack
			board->SetValue(row, col, 0);
		}
	}

	return false;
}

bool SudokuSolver::IsValid(const int& row, const int& col, const int& num)
{
	auto currBoard = board->GetBoard();

	// Check row & column
	for (int x = 0; x < currBoard.size(); x++)
	{
		if (currBoard[row][x].value == num || currBoard[x][col].value == num)
		{
			return false;
		}
	}

	// Check 3x3 subgrid
	int startRow = row - row % 3;
	int startCol = col - col % 3;

	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (currBoard[startRow + r][startCol + c].value == num)
			{
				return false;
			}
		}
	}

	return true;
}

bool SudokuSolver::FindEmptyCell(int& row, int& col)
{
	auto& currBoard = board->GetBoard();
	const size_t boardSize = currBoard.size();

	for (row = 0; row < boardSize; row++)
	{
		for (col = 0; col < boardSize; col++)
		{
			if (currBoard[row][col].value == 0)
			{
				return true;
			}
		}
	}

	return false;
}
