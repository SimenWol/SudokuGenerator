#pragma once
#include "solver.h"
#include <iostream>

enum class Difficulty
{
	Easy,
	Medium,
	Hard,
	Invalid
};

Difficulty ClassifyDifficulty(const SolveStats& stats)
{
	if (stats.usedBacktracking) { return Difficulty::Invalid; }

	switch (stats.HardestUsed())
	{
		case StrategyType::NakedSingle:
		case StrategyType::HiddenSingle: return Difficulty::Easy;
		case StrategyType::Pointing:
		case StrategyType::Claiming: 
		case StrategyType::NakedPair: return Difficulty::Medium;
		case StrategyType::HiddenPair:
		case StrategyType::NakedTriple: return Difficulty::Hard;
		default: return Difficulty::Invalid;
	}
}

void PrintDifficulty(Difficulty difficulty)
{
	switch (difficulty)
	{
		case Difficulty::Easy: std::cout << "Difficulty: Easy\n\n"; break;
		case Difficulty::Medium: std::cout << "Difficulty: Medium\n\n"; break;
		case Difficulty::Hard: std::cout << "Difficulty: Hard\n\n"; break;
		case Difficulty::Invalid: std::cout << "Difficulty: Invalid\n\n"; break;
	}
}