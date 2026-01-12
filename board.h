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

	// Getters //
	const std::array<std::array<Cell, 9>, 9>& GetBoard() const { return board; }
	const int GetValue(const int& row, const int& col) const;
	
	// Setters //
	void SetBoard(std::array<std::array<Cell, 9>, 9>& newBoard) { board = newBoard; }
	void SetBoard(std::array<std::array<int, 9>, 9>& newBoard);
	void SetValue(const int& row, const int& col, int newValue);
private:
	std::array<std::array<Cell, 9>, 9> board;
};