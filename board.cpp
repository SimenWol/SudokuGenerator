#include "board.h"

#include <iostream>
#include <cassert>

SudokuBoard::SudokuBoard()
{
    // Temporary template board
    //std::array<std::array<int, boardSize>, boardSize> templ = { {
    //    {5,3,0, 0,7,0, 0,0,0},
    //    {6,0,0, 1,9,5, 0,0,0},
    //    {0,9,8, 0,0,0, 0,6,0},

    //    {8,0,0, 0,6,0, 0,0,3},
    //    {4,0,0, 8,0,3, 0,0,1},
    //    {7,0,0, 0,2,0, 0,0,6},

    //    {0,6,0, 0,0,0, 2,8,0},
    //    {0,0,0, 4,1,9, 0,0,5},
    //    {0,0,0, 0,8,0, 0,7,9}
    //} };

    //// Solvable by just applying hidden/naked singles
    //std::array<std::array<int, boardSize>, boardSize> templ = { {
    //    {0,0,0, 2,6,0, 7,0,1},
    //    {6,8,0, 0,7,0, 0,9,0},
    //    {1,9,0, 0,0,4, 5,0,0},

    //    {8,2,0, 1,0,0, 0,4,0},
    //    {0,0,4, 6,0,2, 9,0,0},
    //    {0,5,0, 0,0,3, 0,2,8},

    //    {0,0,9, 3,0,0, 0,7,4},
    //    {0,4,0, 0,5,0, 0,3,6},
    //    {7,0,3, 0,1,8, 0,0,0}
    //} };

    // Check pointing pair/triple
    std::array<std::array<int, boardSize>, boardSize> templ = { {
        {0,0,0, 0,0,0, 2,0,0},
        {0,8,0, 0,0,7, 0,9,0},
        {6,0,2, 0,0,0, 5,0,0},

        {0,7,0, 0,6,0, 0,0,0},
        {0,0,0, 9,0,1, 0,0,0},
        {0,0,0, 0,2,0, 0,4,0},

        {0,0,5, 0,0,0, 6,0,3},
        {0,9,0, 4,0,0, 0,7,0},
        {0,0,6, 0,0,0, 0,0,0}
    } };

    // Check naked triple
    //std::array<std::array<int, boardSize>, boardSize> templ = { {
    //    {0,0,0, 2,6,0, 7,0,1},
    //    {6,8,0, 0,7,0, 0,9,0},
    //    {1,9,0, 0,0,4, 5,0,0},
    //
    //    {8,2,0, 1,0,0, 0,4,0},
    //    {0,0,4, 6,0,2, 9,0,0},
    //    {0,5,0, 0,0,3, 0,2,8},
    //
    //    {0,0,9, 3,0,0, 0,7,4},
    //    {0,4,0, 0,5,0, 0,3,6},
    //    {7,0,3, 0,1,8, 0,0,0}
    //} };


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

bool SudokuBoard::IsSolved()
{
    for (const auto& row : board)
        for (const auto& cell : row)
            if (cell.value == 0)
                return false;

    return true;
}

bool SudokuBoard::HasContradiction()
{
    for (const auto& row : board)
        for (const auto& cell : row)
            if (cell.value == 0 && cell.candidates.none())
                return true;

    return false;
}

bool SudokuBoard::PlaceNumber(int row, int col, int num)
{
    assert(num >= 0 && num < 10);
    assert(row >= 0 && row < boardSize);
    assert(col >= 0 && col < boardSize);

    if (board[row][col].locked) { return false; }
    if (!IsValidMove(row, col, num)) { return false; }

    board[row][col].value = num;
    board[row][col].candidates.reset();
    board[row][col].candidates.set(num - 1);

    UpdateCandidatesAfterMove(row, col);
    return true;
}

bool SudokuBoard::RemoveCandidate(int row, int col, int num)
{
    if (board[row][col].value == 0 && board[row][col].candidates.test(num - 1))
    {
        board[row][col].candidates.reset(num - 1);
        return true;
    }

    // Candidate was already set to false
    return false;
}

void SudokuBoard::SetBoard(std::array<std::array<int, 9>, 9>& newBoard)
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j].value = newBoard[i][j];
            board[i][j].locked = (newBoard[i][j] != 0);
            board[i][j].candidates.set();

            if (board[i][j].locked)
            {
                board[i][j].candidates.reset();
                board[i][j].candidates.set(newBoard[i][j] - 1);
            }
        }
    }

    RecomputeAllCandidates();
}

void SudokuBoard::RecomputeAllCandidates()
{
    // Reset all empty cells
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (board[i][j].value == 0)
            {
                board[i][j].candidates.set();
            }
            else
            {
                board[i][j].candidates.reset();
                board[i][j].candidates.set(board[i][j].value - 1);
            }
        }
    }

    // Go through all filled cells and "apply the move"
    for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
            UpdateCandidatesAfterMove(i, j);
}

void SudokuBoard::UpdateCandidatesAfterMove(int row, int col)
{
    const int value = board[row][col].value;
    if (value == 0) return;

    int index = value - 1;

    // Set filled space to empty as move has been validated
    board[row][col].candidates.reset();
    board[row][col].candidates.set(index);

    // Row / column
    for (int i = 0; i < boardSize; i++)
    {
        if (board[row][i].value == 0) { board[row][i].candidates.reset(index); }
        if (board[i][col].value == 0) { board[i][col].candidates.reset(index); }
    }

    // Subgrid
    int sr = row - row % 3;
    int sc = col - col % 3;

    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (board[sr + r][sc + c].value == 0) { board[sr + r][sc + c].candidates.reset(index); }
        }
    }
}