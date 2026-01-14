#pragma once
#include "unit_helpers.h"

class SudokuBoard;

enum class SolveMode
{
	FindOne,
	CountUpToTwo
};

class BoardGenerator
{
public:
	BoardGenerator() {}

	SudokuBoard GenerateSolvedBoard();

	std::vector<CellPos> ShuffledCellList();

	void DigPuzzle(SudokuBoard& board, int minClues);

	bool HasUniqueSolution(const SudokuBoard& puzzle);

private:
	bool SolveBacktrackingCount(SudokuBoard& board, int& solutionCount, SolveMode mode);
};