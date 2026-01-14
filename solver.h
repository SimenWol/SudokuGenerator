#pragma once
#include <memory>
#include <vector>

#include "solve_strategies.h"

class SudokuBoard;

/**
* Class used to solve sudokus using human-like solving strategies with a backtracking solver as fallback.
*/
class SudokuSolver
{
public:
	SudokuSolver() { PopulateStrategies(); };
	SudokuSolver(std::shared_ptr<SudokuBoard> brd) { SetBoard(brd); PopulateStrategies(); };

	/** Solve the provided sudoku board. */
	bool Solve();
	
	/** Updates the board used by the solver to the provided one. */
	void SetBoard(std::shared_ptr<SudokuBoard> newBoard) { board = newBoard; }

private:
	/** Solve the sudoku with human-like solving techniques only. */
	bool SolveLogical();
	/** Solve the sudoku with backtracking. */
	bool SolveBacktracking();

	/** Populate the strategies vector with human-like solving techniques. TODO: settings to enable / disable certain types of techniques.*/
	void PopulateStrategies();

private:
	std::shared_ptr<SudokuBoard> board = nullptr;

	std::vector<std::unique_ptr<SolveStrategy>> strategies;
};