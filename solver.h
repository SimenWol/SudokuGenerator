#pragma once
#include <memory>

class SudokuBoard;

class SudokuSolver
{
public:
	SudokuSolver() {};
	SudokuSolver(std::shared_ptr<SudokuBoard> brd) { SetBoard(brd); };

	bool SolveBoard();
	
	// Setters //
	void SetBoard(std::shared_ptr<SudokuBoard> newBoard) { board = newBoard; }
private:
	bool IsValid(const int& row, const int& col, const int& num);
	bool FindEmptyCell(int& row, int& col);
private:
	std::shared_ptr<SudokuBoard> board = nullptr;

	// TODO: solver settings (e.g. enable / disable certain types of solving algorithms)
};