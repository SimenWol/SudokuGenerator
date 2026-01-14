#pragma once
// Helpful resource: https://hodoku.sourceforge.net/en/techniques.php

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

/** Solving technique where it finds candidates of the same digit that are confined to a row or column within a block,
* eliminating that digit in the same row/column outside of that block.
*/
class PointingPairTripleStrategy : public SolveStrategy
{
public:
	bool Apply(SudokuBoard& board) override { return BoxToRow(board) || BoxToColumn(board); }
private:
	bool BoxToRow(SudokuBoard& board);
	bool BoxToColumn(SudokuBoard& board);
};

/** Solving technique where it finds candidates of the same digit that are confined to a block within a row/column,
* eliminating that digit in the same block outside of that row/column.
*/
class ClaimingPairTripleStrategy : public SolveStrategy
{
public:
	bool Apply(SudokuBoard& board) override { return ClaimFromRows(board) || ClaimFromColumns(board); }
private:
	bool ClaimFromRows(SudokuBoard& board);
	bool ClaimFromColumns(SudokuBoard& board);
};