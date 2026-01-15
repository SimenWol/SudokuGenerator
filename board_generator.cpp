#include "board_generator.h"
#include "board.h"
#include <algorithm>
#include <vector>
#include <random>
#include <cassert>

static std::mt19937 rng(std::random_device{}());

SudokuBoard BoardGenerator::GenerateSolvedBoard()
{
	SudokuBoard board;
	board.RecomputeAllCandidates();

	int solutions = 0;
	SolveBacktrackingCount(board, solutions, SolveMode::FindOne);

	return board;
}

std::vector<CellPos> BoardGenerator::ShuffledCellList()
{
	std::vector<CellPos> cells;

	for (int r = 0; r < 9; r++)
		for (int c = 0; c < 9; c++)
			cells.emplace_back(r, c);

	std::shuffle(cells.begin(), cells.end(), rng);

	return cells;
}

void BoardGenerator::DigPuzzle(SudokuBoard& board, int minClues, Difficulty targetDifficulty)
{
	auto order = ShuffledCellList();

	for (const auto& cellPos : order)
	{
		int r = cellPos.first;
		int c = cellPos.second;
		int backup = board.GetBoard()[r][c].value;
		board.SetValue(r, c, 0);
		board.RecomputeAllCandidates();

		if (!HasUniqueSolution(board) || !IsAcceptablePuzzle(board, targetDifficulty) || board.CountClues() < minClues)
		{
			board.SetValue(r, c, backup);
			board.RecomputeAllCandidates();
		}
	}
}

bool BoardGenerator::HasUniqueSolution(const SudokuBoard& puzzle)
{
	SudokuBoard copy = puzzle;
	int solutions = 0;
	SolveBacktrackingCount(copy, solutions, SolveMode::CountUpToTwo);
	return solutions == 1;
}

bool BoardGenerator::SolveBacktrackingCount(SudokuBoard& board, int& solutionCount, SolveMode mode)
{
	// While yes this is a solver, this is deliberately seperated from the logical solver and its sole purpose is to generate unique sudoku boards.

	if (board.HasContradiction()) { return false; }

	if (board.IsSolved())
	{
		solutionCount++;
		//return solutionCount < 2 || mode == SolveMode::FindOne;
		return true;
	}

	int row = -1, col = -1;
	size_t bestCount = 10;

	const auto& grid = board.GetBoard();
	for (int r = 0; r < 9; r++)
	for (int c = 0; c < 9; c++)
	{
		if (grid[r][c].value == 0)
		{
			size_t count = grid[r][c].candidates.count();
			if (count < bestCount)
			{
				bestCount = count;
				row = r;
				col = c;
			}
		}
	}

	if (bestCount == 0) { return false; }

	std::vector<int> nums;
	for (int n = 1; n <= 9; n++)
	{
		if (grid[row][col].candidates.test(n - 1)) { nums.push_back(n); }
	}

	// Randomize
	std::shuffle(nums.begin(), nums.end(), rng);

	for (int num : nums)
	{
		SudokuBoard snapshot = board;
		board.PlaceNumber(row, col, num);

		if (SolveBacktrackingCount(board, solutionCount, mode))
		{
			if (mode == SolveMode::FindOne) { return true; }
		}

		board = snapshot;

		if (mode == SolveMode::CountUpToTwo && solutionCount >= 2) { return false; }
	}

	return false;
}

bool BoardGenerator::IsAcceptablePuzzle(const SudokuBoard& puzzle, Difficulty target)
{
	auto board = std::make_shared<SudokuBoard>(puzzle);
	SudokuSolver solver(board);

	if (!solver.Solve(false)) { return false; }

	DifficultyClassifier difficultyClassifier;
	Difficulty actual = difficultyClassifier.Classify(solver.GetStats());

	return actual <= target;
}