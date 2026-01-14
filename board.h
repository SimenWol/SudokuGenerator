#pragma once
#include <array>
#include <bitset>

/**
* Struct containing all cell data of a sudoku board.
*/
struct Cell
{
	int value = 0; // 0 = empty
	bool locked = false;
	std::bitset<9> candidates;

	Cell()
	{
		candidates.set();
	}
};

/**
* Class handling all operations that can be applied to a sudoku board.
* Also holds all the data related to the sudoku board, such as original values and candidate sets.
*/
class SudokuBoard
{
public:
	SudokuBoard();

	/** Outputs the entire sudoku board to the console. */
	void PrintBoard() const;

	/** Checks whether the entire board is solved without any mistakes and returns the answer. */
	bool IsSolved();
	/** Checks whether the board has any empty cells without any possible candidates left. */
	bool HasContradiction();

	/** Places specified number in the provided cell. Returns false if move is invalid or illegal. */
	bool PlaceNumber(int row, int col, int num);
	/** Removes specified candidate from provided cell. Returns false if the candidate couldn't be removed or was already removed. */
	bool RemoveCandidate(int row, int col, int num);

	/** Returns the contents of the current sudoku board. */
	const std::array<std::array<Cell, 9>, 9>& GetBoard() const { return board; }
	
	/** Sets the board contents to the provided input. */
	void SetBoard(std::array<std::array<Cell, 9>, 9>& newBoard) { board = newBoard; }
	/** Sets the board contents to the provided input. */
	void SetBoard(std::array<std::array<int, 9>, 9>& newBoard);

private:
	/** Checks whether the provided move is valid. Returns false if move is illegal. */
	bool IsValidMove(int row, int col, int num) const { return board[row][col].value == 0 && board[row][col].candidates.test(num - 1); };

	/** Recomputes the entire board's candidates based on its current state. NOTE: this overrides any removed candidates from solving strategies. */
	void RecomputeAllCandidates();
	/** Removes all candidates from all affected cells based on the provided input location. */
	void UpdateCandidatesAfterMove(int row, int col);

public:
	static constexpr int boardSize = 9;

private:
	std::array<std::array<Cell, 9>, 9> board;
};