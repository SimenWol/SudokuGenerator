#pragma once

class SudokuBoard;

class SolveStrategy
{
public:
	virtual bool Apply(SudokuBoard& board) = 0;
};

/** Solving technique where it finds any cell with only one possible candidate left. */
class NakedSingleStrategy : public SolveStrategy
{
public:
	bool Apply(SudokuBoard& board) override;
};

/** Solving technique where it finds a candidate digit in a row/column or box in only one cell. */
class HiddenSingleStrategy : public SolveStrategy
{
public:
	bool Apply(SudokuBoard& board) override { return CheckRows(board) || CheckColumns(board) || CheckBoxes(board); }
private:
	bool CheckRows(SudokuBoard& board);
	bool CheckColumns(SudokuBoard& board);
	bool CheckBoxes(SudokuBoard& board);
};

// Pointing pair/triple - WIP
class PointingPairTripleStrategy : public SolveStrategy
{
public:
	bool Apply(SudokuBoard& board) override { return BoxToRow(board) || BoxToColumn(board); }
private:
	bool BoxToRow(SudokuBoard& board);
	bool BoxToColumn(SudokuBoard& board);
};

// TBA claiming pair/triple