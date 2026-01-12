#pragma once
#include <memory>
#include <vector>

class SudokuBoard;

class SolveStrategy
{
public:
	virtual bool Apply(SudokuBoard& board) = 0;
};

class SudokuSolver
{
public:
	SudokuSolver() {};
	SudokuSolver(std::shared_ptr<SudokuBoard> brd) { SetBoard(brd); };

	bool Solve();

	// Old backtracking solve - also needs updating later but low prio as eventually i dont want to use this anymore
	bool SolveBoard();
	
	// Setters //
	void SetBoard(std::shared_ptr<SudokuBoard> newBoard) { board = newBoard; }
private:
	bool IsValid(const int& row, const int& col, const int& num); // to be removed
	bool FindEmptyCell(int& row, int& col);
private:
	std::shared_ptr<SudokuBoard> board = nullptr;

	std::vector<std::unique_ptr<SolveStrategy>> strategies;

	// TODO: solver settings (e.g. enable / disable certain types of solving algorithms)
};