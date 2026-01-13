#pragma once
#include <memory>
#include <vector>

#include "solve_strategies.h"

class SudokuBoard;

class SudokuSolver
{
public:
	SudokuSolver() { PopulateStrategies(); };
	SudokuSolver(std::shared_ptr<SudokuBoard> brd) { SetBoard(brd); PopulateStrategies(); };

	void PopulateStrategies();

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