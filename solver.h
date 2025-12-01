#pragma once
#include <memory>

class SudokuBoard;

class SudokuSolver
{
public:
	SudokuSolver() {};
	void SetBoard(std::shared_ptr<SudokuBoard> newBoard) { board = newBoard; }

	bool SolveBoard();

private:
	bool IsValid(const int& row, const int& col, const int& num);
	bool FindEmptyCell(int& row, int& col);
private:
	std::shared_ptr<SudokuBoard> board = nullptr;

	// TODO: solver settings (e.g. enable / disable certain types of solving algorithms)
};