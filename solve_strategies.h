#pragma once

class SudokuBoard;

class SolveStrategy
{
public:
	virtual bool Apply(SudokuBoard& board) = 0;
};

class NakedSingleStrategy : public SolveStrategy
{
public:
	bool Apply(SudokuBoard& board) override;
};

//class HiddenSingleStrategy : public SolveStrategy
//{
//public:
//	bool Apply(SudokuBoard& board) override;
//};