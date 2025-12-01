#include "board.h"

#include <iostream>
#include <cassert>

SudokuBoard::SudokuBoard()
{
    // Temporary template board
    std::array<std::array<int, 9>, 9> templ = { {
        {5,3,0, 0,7,0, 0,0,0},
        {6,0,0, 1,9,5, 0,0,0},
        {0,9,8, 0,0,0, 0,6,0},

        {8,0,0, 0,6,0, 0,0,3},
        {4,0,0, 8,0,3, 0,0,1},
        {7,0,0, 0,2,0, 0,0,6},

        {0,6,0, 0,0,0, 2,8,0},
        {0,0,0, 4,1,9, 0,0,5},
        {0,0,0, 0,8,0, 0,7,9}
    } };

    SetBoard(templ);
};

void SudokuBoard::PrintBoard() const
{
	for (int row = 0; row < board.size(); row++)
	{
		for (int col = 0; col < board.size(); col++)
		{
			std::cout << board[row][col] << " ";
		}
		std::cout << "\n";
	}
}

const int SudokuBoard::GetValue(const int& row, const int& col) const
{
    assert(row >= 0 && row < 9);
    assert(col >= 0 && col < 9);

    return board[row][col];
}

void SudokuBoard::SetValue(const int& row, const int& col, int newValue)
{
    assert(row >= 0 && row < 9);
    assert(col >= 0 && col < 9);

    board[row][col] = newValue;
}