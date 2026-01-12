#include "board.h"

#include <iostream>
#include <cassert>

SudokuBoard::SudokuBoard()
{
    // Temporary template board - TODO: easier way to define a new locked board
    std::array<std::array<Cell, 9>, 9> templ;
    
    templ[0][0].value = 5;
    templ[0][1].value = 3;
    templ[0][4].value = 7;

    templ[1][0].value = 6;
    templ[1][3].value = 1;
    templ[1][4].value = 9;
    templ[1][5].value = 5;
    
    templ[2][1].value = 9;
    templ[2][2].value = 8;
    templ[2][7].value = 6;
    
    templ[3][0].value = 8;
    templ[3][4].value = 6;
    templ[3][8].value = 3;
    
    templ[4][0].value = 4;
    templ[4][3].value = 8;
    templ[4][5].value = 3;
    templ[4][8].value = 1;

    templ[5][0].value = 7;
    templ[5][4].value = 2;
    templ[5][8].value = 6;
    
    templ[6][1].value = 6;
    templ[6][6].value = 2;
    templ[6][7].value = 8;
    
    templ[7][3].value = 4;
    templ[7][4].value = 1;
    templ[7][5].value = 9;
    templ[7][8].value = 5;
    
    templ[8][4].value = 8;
    templ[8][7].value = 7;
    templ[8][8].value = 9;

    //    {5,3,0, 0,7,0, 0,0,0}
    //    {6,0,0, 1,9,5, 0,0,0}
    //    {0,9,8, 0,0,0, 0,6,0}

    //    {8,0,0, 0,6,0, 0,0,3}
    //    {4,0,0, 8,0,3, 0,0,1}
    //    {7,0,0, 0,2,0, 0,0,6}

    //    {0,6,0, 0,0,0, 2,8,0}
    //    {0,0,0, 4,1,9, 0,0,5}
    //    {0,0,0, 0,8,0, 0,7,9}

    SetBoard(templ);
};

void SudokuBoard::PrintBoard() const
{
	for (int row = 0; row < board.size(); row++)
	{
		for (int col = 0; col < board.size(); col++)
		{
			std::cout << board[row][col].value << " ";
		}
		std::cout << "\n";
	}
}

const int SudokuBoard::GetValue(const int& row, const int& col) const
{
    assert(row >= 0 && row < 9);
    assert(col >= 0 && col < 9);

    return board[row][col].value;
}

void SudokuBoard::SetValue(const int& row, const int& col, int newValue)
{
    assert(row >= 0 && row < 9);
    assert(col >= 0 && col < 9);

    board[row][col].value = newValue;
}