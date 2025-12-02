#pragma once
#include <array>

class SudokuBoard
{
public:
	SudokuBoard();

	void PrintBoard() const;

	// Getters //
	const std::array<std::array<int, 9>, 9>& GetBoard() const { return board; }
	const int GetValue(const int& row, const int& col) const;
	
	// Setters //
	void SetBoard(std::array<std::array<int, 9>, 9>& newBoard) { board = newBoard; }
	void SetValue(const int& row, const int& col, int newValue);
private:
	std::array<std::array<int, 9>, 9> board; // TODO: create system for 'locked' cells
};