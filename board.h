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

	void PrintBoard() const;

	void RecomputeAllCandidates();
	void UpdateCandidatesAfterMove(int row, int col);
	bool IsValidMove(int row, int col, int num) const { return board[row][col].value == 0 && board[row][col].candidates.test(num - 1); };

	bool IsSolved();
	bool HasContradiction();

	bool PlaceNumber(int row, int col, int num);

	// Getters //
	const std::array<std::array<Cell, 9>, 9>& GetBoard() const { return board; }
	const int GetValue(const int& row, const int& col) const;
	
	// Setters //
	void SetBoard(std::array<std::array<Cell, 9>, 9>& newBoard) { board = newBoard; }
	void SetBoard(std::array<std::array<int, 9>, 9>& newBoard);

//private:
	/** Places the provided value into the given space. Returns false if cell is locked and the number cannot be placed. */
	bool SetValue(const int& row, const int& col, int newValue); // to be removed
private:
	std::array<std::array<Cell, 9>, 9> board;
};