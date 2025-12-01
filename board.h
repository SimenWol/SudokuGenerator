#pragma once
#include <array>

class SudokuBoard
{
public:
	SudokuBoard();

	void SetBoard(std::array<std::array<int, 9>, 9>& newBoard) { board = newBoard; }
	void PrintBoard() const;
	const int GetValue(const int& row, const int& col) const;
	void SetValue(const int& row, const int& col, int newValue);
	//isValid()
	//findEmptyCell()
	//solve()
private:
	std::array<std::array<int, 9>, 9> board; // TODO: create system for 'locked' cells
};