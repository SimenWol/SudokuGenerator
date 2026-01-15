#pragma once
#include "unit_helpers.h"
#include "difficulty_classifier.h"

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

	void DigPuzzle(SudokuBoard& board, int minClues, Difficulty targetDifficulty);

	bool HasUniqueSolution(const SudokuBoard& puzzle);

private:
	bool SolveBacktrackingCount(SudokuBoard& board, int& solutionCount, SolveMode mode);
	bool IsAcceptablePuzzle(const SudokuBoard& puzzle, Difficulty target);
};