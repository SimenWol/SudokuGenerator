#pragma once
#include "unit_helpers.h"

// Helpful resource: https://hodoku.sourceforge.net/en/techniques.php

class SudokuBoard;

enum class StrategyType
{
	NakedSingle,
	HiddenSingle,
	Pointing,
	Claiming,
	NakedPair,
	HiddenPair,
	NakedTriple
};

class SolveStrategy
{
public:
	virtual ~SolveStrategy() = default;
	virtual bool Apply(SudokuBoard& board) = 0;
	virtual StrategyType GetType() const = 0;
};

/** Solving technique where it finds any cell with only one possible candidate left. */
class NakedSingleStrategy : public SolveStrategy
{
public:
	bool Apply(SudokuBoard& board) override;
	StrategyType GetType() const override { return StrategyType::NakedSingle; }
};

/** Solving technique where it finds a candidate digit in a row/column or box in only one cell. */
class HiddenSingleStrategy : public SolveStrategy
{
public:
	bool Apply(SudokuBoard& board) override { return HiddenSingleInUnit(board, UnitType::Row) || HiddenSingleInUnit(board, UnitType::Column) || HiddenSingleInUnit(board, UnitType::Box); }
	StrategyType GetType() const override { return StrategyType::HiddenSingle; }

private:
	bool HiddenSingleInUnit(SudokuBoard& board, UnitType type);
};

/** Solving technique where it finds candidates of the same digit that are confined to a row or column within a block,
* eliminating that digit in the same row/column outside of that block.
*/
class PointingPairTripleStrategy : public SolveStrategy
{
public:
	bool Apply(SudokuBoard& board) override { return BoxToRow(board) || BoxToColumn(board); }
	StrategyType GetType() const override { return StrategyType::Pointing; }

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
	StrategyType GetType() const override { return StrategyType::Claiming; }

private:
	bool ClaimFromRows(SudokuBoard& board);
	bool ClaimFromColumns(SudokuBoard& board);
};

/** Solving technique where it finds two cells in a block/row/column only contain 2 candidates of the same kind,
* eliminating those digits in other cells of the same block/row/column.
*/
class NakedPairStrategy : public SolveStrategy
{
public:
	bool Apply(SudokuBoard& board) override;
	StrategyType GetType() const override { return StrategyType::NakedPair; }
};

/** Solving technique where it finds two cells in a block/row/column contain 2 candidates of the same kind,
* where no other cell in the same block/row/column contains those candidates,
* eliminating those digits in other cells of the same block/row/column.
*/
class HiddenPairStrategy : public SolveStrategy
{
public:
	bool Apply(SudokuBoard& board) override;
	StrategyType GetType() const override { return StrategyType::HiddenPair; }

};

/** Solving technique where it finds three cells in a block/row/column that only contains 3 candidates of the same kind,
* eliminating those digits in other cells of the same block/row/column.
*/
class NakedTripleStrategy : public SolveStrategy
{
public:
	bool Apply(SudokuBoard& board) override;
	StrategyType GetType() const override { return StrategyType::NakedTriple; }
};