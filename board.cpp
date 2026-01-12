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
			std::cout << board[row][col].value << " ";
		}
		std::cout << "\n";
	}
}

void SudokuBoard::RecomputeAllCandidates()
{
    // Reset all empty cells
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board[i][j].candidates.set();

    // Go through all filled cells and "apply the move"
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            UpdateCandidatesAfterMove(i, j);
}

void SudokuBoard::UpdateCandidatesAfterMove(int row, int col)
{
    const int value = board[row][col].value;
    if (value == 0) return;

    int index = value - 1;

    // Set filled space to empty as move has been validated
    board[row][col].candidates.reset();

    // Row / column
    for (int i = 0; i < 9; i++)
    {
        board[row][i].candidates.reset(index);
        board[i][col].candidates.reset(index);
    }

    // Subgrid
    int sr = row - row % 3;
    int sc = col - col % 3;

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[sr + r][sc + c].candidates.reset(index);
}

bool SudokuBoard::PlaceNumber(int row, int col, int num)
{
    assert(num >= 0 && num < 10);
    assert(row >= 0 && row < 9);
    assert(col >= 0 && col < 9);

    if (board[row][col].locked) { return false; }
    if (!IsValidMove(row, col, num)) { return false; }

    board[row][col].value = num;
    board[row][col].candidates.reset();
    board[row][col].candidates.set(num - 1);

    UpdateCandidatesAfterMove(row, col);

    return true;
}

const int SudokuBoard::GetValue(const int& row, const int& col) const
{
    assert(row >= 0 && row < 9);
    assert(col >= 0 && col < 9);

    return board[row][col].value;
}

void SudokuBoard::SetBoard(std::array<std::array<int, 9>, 9>& newBoard)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board[i][j].value = newBoard[i][j];
            board[i][j].locked = (newBoard[i][j] != 0);
            board[i][j].candidates.set();

            if (board[i][j].locked)
            {
                board[i][j].candidates.reset();
            }
        }
    }

    RecomputeAllCandidates();
}

bool SudokuBoard::SetValue(const int& row, const int& col, int newValue)
{
    assert(row >= 0 && row < 9);
    assert(col >= 0 && col < 9);
    assert(newValue >= 0 && newValue < 10);

    if (board[row][col].locked) { return false; }

    board[row][col].value = newValue;
    return true;
}