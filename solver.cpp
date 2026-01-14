#include "solver.h"
#include "board.h"
#include <iostream>

bool SudokuSolver::Solve()
{
	if (SolveLogical())
	{
		if (board->IsSolved()) { return true; }

		std::cout << "\n\nLogical solve failed, using backtracking fallback now.\n\n";

		return SolveBacktracking();
	}

	return false;
}

bool SudokuSolver::SolveLogical()
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

		if (!progress) { break; }
	}

	return true;
}

bool SudokuSolver::SolveBacktracking()
{
	if (!SolveLogical()) { return false; }
	if (board->IsSolved()) { return true; }

	// Find cell with fewest candidates
	int bestRow = -1, bestCol = -1;
	size_t bestCount = 10;

	const auto& grid = board->GetBoard();
	for (int r = 0; r < 9; r++)
	for (int c = 0; c < 9; c++)
	{
		const Cell& cell = grid[r][c];
		if (cell.value == 0)
		{
			size_t count = cell.candidates.count();
			if (count < bestCount)
			{
				bestCount = count;
				bestRow = r;
				bestCol = c;
			}
		}
	}

	if (bestRow == -1) { return false; }

	auto savedBoard = *board;

	for (int num = 1; num <= 9; num++)
	{
		if (grid[bestRow][bestCol].candidates.test(num - 1))
		{
			*board = savedBoard;

			if (board->PlaceNumber(bestRow, bestCol, num))
			{
				if (SolveBacktracking()) { return true; }
			}
		}
	}

	*board = savedBoard;
	return false;
}

void SudokuSolver::PopulateStrategies()
{
	strategies.push_back(std::make_unique<NakedSingleStrategy>());
	strategies.push_back(std::make_unique<HiddenSingleStrategy>());
	strategies.push_back(std::make_unique<PointingPairTripleStrategy>());
	strategies.push_back(std::make_unique<ClaimingPairTripleStrategy>());
	strategies.push_back(std::make_unique<NakedPairStrategy>());
	strategies.push_back(std::make_unique<HiddenPairStrategy>());
	strategies.push_back(std::make_unique<NakedTripleStrategy>());
}