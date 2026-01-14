#include "solve_strategies.h"
#include "board.h"
#include <iostream>

bool NakedSingleStrategy::Apply(SudokuBoard& board)
{
	const auto& grid = board.GetBoard();

	for (int row = 0; row < board.boardSize; row++)
	{
		for (int col = 0; col < board.boardSize; col++)
		{
			// Check if cell has only one candidate -> if yes placenumber, else continue
			const Cell& cell = grid[row][col];

			if (cell.value == 0 && cell.candidates.count() == 1)
			{
				for (int num = 0; num < 9; num++)
				{
					if (cell.candidates.test(num))
					{
						if (board.PlaceNumber(row, col, num + 1))
						{
							std::cout << "Naked Single: " << (num + 1) << " from (" << (row + 1) << "," << (col + 1) << ")\n";
						
							return true;
						}
					}
				}
			}
		}
	}

	// No naked single found
	return false;
}

bool HiddenSingleStrategy::HiddenSingleInUnit(SudokuBoard& board, UnitType type)
{
	const auto& grid = board.GetBoard();

	for (int unit = 0; unit < 9; unit++)
	{
		auto cells = GetUnit(type, unit);
		for (int num = 1; num <= 9; num++)
		{
			CellPos found = { -1, -1 };

			for (const auto& cell : cells)
			{
				int r = cell.first;
				int c = cell.second;

				if (grid[r][c].value == 0 && grid[r][c].candidates.test(num - 1))
				{
					if (found.first != -1) { goto next_number; }

					found = { r, c };
				}
			}

			if (found.first != -1)
			{
				if (board.PlaceNumber(found.first, found.second, num))
				{
					std::cout << "Hidden Single: " << num << " from (" << (found.first + 1) << "," << (found.second + 1) << ")\n";
					return true;
				}
			}

		next_number:;
		}
	}

	// No hidden single found
	return false;
}

bool PointingPairTripleStrategy::BoxToRow(SudokuBoard& board)
{
	auto& grid = board.GetBoard();

	for (int br = 0; br < 3; br++)
	{
		for (int bc = 0; bc < 3; bc++)
		{
			for (int num = 1; num <= 9; num++)
			{
				int targetRow = -1;
				int count = 0;

				for (int row = 0; row < 3; row++)
				{
					for (int col = 0; col < 3; col++)
					{
						int rr = br * 3 + row;
						int cc = bc * 3 + col;

						const Cell& cell = grid[rr][cc];

						if (cell.value == 0 && cell.candidates.test(num - 1))
						{
							if (targetRow == -1) { targetRow = rr; }
							else if (targetRow != rr) { goto next_number; }

							count++;
						}
					}
				}

				if (count >= 2 && targetRow != -1)
				{
					for (int col = 0; col < board.boardSize; col++)
					{
						const Cell& cell = grid[targetRow][col];

						if (col / 3 != bc && cell.value == 0 && cell.candidates.test(num - 1))
						{
							if (board.RemoveCandidate(targetRow, col, num))
							{
								std::cout << "Pointing pair/triple: candidate eliminated: " << num << " from (" << (targetRow + 1) << "," << (col + 1) << ")\n";
							
								return true;
							}
						}
					}
				}

			next_number:;
			}
		}
	}

	// No pointing pair found
	return false;
}

bool PointingPairTripleStrategy::BoxToColumn(SudokuBoard& board)
{
	auto& grid = board.GetBoard();

	for (int bc = 0; bc < 3; bc++)
	{
		for (int br = 0; br < 3; br++)
		{
			for (int num = 1; num <= 9; num++)
			{
				int targetCol = -1;
				int count = 0;

				for (int col = 0; col < 3; col++)
				{
					for (int row = 0; row < 3; row++)
					{
						int rr = br * 3 + row;
						int cc = bc * 3 + col;

						const Cell& cell = grid[rr][cc];

						if (cell.value == 0 && cell.candidates.test(num - 1))
						{
							if (targetCol == -1) { targetCol = cc; }
							else if (targetCol != cc) { goto next_number; }

							count++;
						}
					}
				}

				if (count >= 2 && targetCol != -1)
				{
					for (int row = 0; row < board.boardSize; row++)
					{
						const Cell& cell = grid[row][targetCol];

						if (row / 3 != br && cell.value == 0 && cell.candidates.test(num - 1))
						{
							
							if (board.RemoveCandidate(row, targetCol, num))
							{
								std::cout << "Pointing pair/triple: candidate eliminated: " << num << " from (" << (row + 1) << "," << (targetCol + 1) << ")\n";
							
								return true;
							}
						}
					}
				}

			next_number:;
			}
		}
	}

	// No pointing pair found
	return false;
}

bool ClaimingPairTripleStrategy::ClaimFromRows(SudokuBoard& board)
{
	const auto& grid = board.GetBoard();

	for (int row = 0; row < 9; row++)
	{
		for (int num = 1; num <= 9; num++)
		{
			int targetBox = -1;
			int count = 0;

			for (int col = 0; col < 9; col++)
			{
				const Cell& cell = grid[row][col];

				if (cell.value == 0 && cell.candidates.test(num - 1))
				{
					int box = BoxIndex(row, col);

					if (targetBox == -1) { targetBox = box; }
					else if (targetBox != box) { goto next_number; }

					count++;
				}
			}

			if (count >= 2 && targetBox != -1)
			{
				int br = (targetBox / 3) * 3;
				int bc = (targetBox % 3) * 3;

				for (int r = 0; r < 3; r++)
				{
					for (int c = 0; c < 3; c++)
					{
						int rr = br + r;
						int cc = bc + c;

						if (rr == row) continue;

						const Cell& cell = grid[rr][cc];
						if (cell.value == 0 && cell.candidates.test(num - 1))
						{
							if (board.RemoveCandidate(rr, cc, num))
							{
								std::cout << "Claiming pair/triple: candidate eliminated: " << num << " from (" << (row + 1) << "," << (cc + 1) << ")\n";
							
								return true;
							}
						}
					}
				}
			}

		next_number:;
		}
	}

	// No claiming pair found
	return false;
}

bool ClaimingPairTripleStrategy::ClaimFromColumns(SudokuBoard& board)
{
	const auto& grid = board.GetBoard();

	for (int col = 0; col < 9; col++)
	{
		for (int num = 1; num <= 9; num++)
		{
			int targetBox = -1;
			int count = 0;

			for (int row = 0; row < 9; row++)
			{
				const Cell& cell = grid[row][col];

				if (cell.value == 0 && cell.candidates.test(num - 1))
				{
					int box = BoxIndex(row, col);

					if (targetBox == -1) { targetBox = box; }
					else if (targetBox != box) { goto next_number; }

					count++;
				}
			}

			if (count >= 2 && targetBox != -1)
			{
				int br = (targetBox / 3) * 3;
				int bc = (targetBox % 3) * 3;

				for (int r = 0; r < 3; r++)
				{
					for (int c = 0; c < 3; c++)
					{
						int rr = br + r;
						int cc = bc + c;

						if (cc == col) continue;

						const Cell& cell = grid[rr][cc];
						if (cell.value == 0 && cell.candidates.test(num - 1))
						{
							if (board.RemoveCandidate(rr, cc, num))
							{
								std::cout << "Claiming pair/triple: candidate eliminated: " << num << " from (" << (rr + 1) << "," << (col + 1) << ")\n";
							
								return true;
							}
						}
					}
				}
			}

		next_number:;
		}
	}

	// No claiming pair found
	return false;
}

bool NakedPairStrategy::Apply(SudokuBoard& board)
{
	const auto& grid = board.GetBoard();

	for (UnitType type : {UnitType::Row, UnitType::Column, UnitType::Box})
	{
		for (int unit = 0; unit < 9; unit++)
		{
			auto cells = GetUnit(type, unit);

			for (size_t i = 0; i < cells.size(); i++)
			{
				int r1 = cells[i].first;
				int c1 = cells[i].second;
				const Cell& cell1 = grid[r1][c1];

				if (cell1.value != 0 || cell1.candidates.count() != 2) { continue; }

				for (size_t j = i + 1; j < cells.size(); j++)
				{
					int r2 = cells[j].first;
					int c2 = cells[j].second;
					const Cell& cell2 = grid[r2][c2];

					if (cell2.value != 0) { continue; }

					if (cell1.candidates == cell2.candidates)
					{
						// Found naked pair
						for (const auto& cell : cells)
						{
							int r = cell.first;
							int c = cell.second;

							if ((r == r1 && c == c1) || (r == r2 && c == c2)) { continue; }

							for (int num = 1; num <= 9; num++)
							{
								if (cell1.candidates.test(num - 1))
								{
									if (board.RemoveCandidate(r, c, num))
									{
										std::cout << "Naked pair: candidate eliminated: " << num << " from (" << (r + 1) << "," << (c + 1) << ")\n";

										return true;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// No naked pair found
	return false;
}

bool HiddenPairStrategy::Apply(SudokuBoard& board)
{
	const auto& grid = board.GetBoard();

	for (UnitType type : {UnitType::Row, UnitType::Column, UnitType::Box})
	{
		for (int unit = 0; unit < 9; unit++)
		{
			auto cells = GetUnit(type, unit);

			for (int a = 1; a <= 8; a++)
			{
				for (int b = a + 1; b <= 9; b++)
				{
					std::vector<CellPos> aCells;
					std::vector<CellPos> bCells;

					for (const auto& cellPair : cells)
					{
						int r = cellPair.first;
						int c = cellPair.second;

						const Cell& cell = grid[r][c];
						if (cell.value != 0) continue;

						if (cell.candidates.test(a - 1))
							aCells.emplace_back(r, c);
						if (cell.candidates.test(b - 1))
							bCells.emplace_back(r, c);
					}

					if (aCells.size() == 2 &&
						bCells.size() == 2 &&
						aCells == bCells)
					{
						// Found hidden pair
						for (const auto& cellPair : aCells)
						{
							int r = cellPair.first;
							int c = cellPair.second;

							const Cell& cell = grid[r][c];

							for (int num = 1; num <= 9; num++)
							{
								if (cell.value == 0 && num != a && num != b && cell.candidates.test(num - 1))
								{
									if (board.RemoveCandidate(r, c, num))
									{
										std::cout << "Hidden pair: candidate eliminated: " << num << " from (" << (r + 1) << "," << (c + 1) << ")\n";

										return true;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// No hidden pair found
	return false;
}

bool NakedTripleStrategy::Apply(SudokuBoard& board)
{
	const auto& grid = board.GetBoard();

	for (UnitType type : {UnitType::Row, UnitType::Column, UnitType::Box})
	{
		for (int unit = 0; unit < 9; unit++)
		{
			auto cells = GetUnit(type, unit);

			// Collect candidate cells with 2 or 3 candidates
			std::vector<CellPos> candidates;
			for (const auto& cellPair : cells)
			{
				int r = cellPair.first;
				int c = cellPair.second;
				const Cell& cell = grid[r][c];

				if (cell.value == 0 && cell.candidates.count() >= 2 && cell.candidates.count() <= 3) { candidates.emplace_back(r, c); }
			}

			// Check all possible triples
			for (size_t i = 0; i < candidates.size(); i++)
			for (size_t j = i + 1; j < candidates.size(); j++)
			for (size_t k = j + 1; k < candidates.size(); k++)
			{
				int r1 = candidates[i].first;
				int c1 = candidates[i].second;

				int r2 = candidates[j].first;
				int c2 = candidates[j].second;

				int r3 = candidates[k].first;
				int c3 = candidates[k].second;

				std::bitset<9> unionSet =
					grid[r1][c1].candidates |
					grid[r2][c2].candidates |
					grid[r3][c3].candidates;

				if (unionSet.count() != 3) { continue; }

				// Eliminate frmo other cells in unit
				for (const auto& cellPair : cells)
				{
					int r = cellPair.first;
					int c = cellPair.second;

					if ((r == r1 && c == c1) ||
						(r == r2 && c == c2) ||
						(r == r3 && c == c3))
					{
						continue;
					}

					for (int num = 1; num <= 9; num++)
					{
						if (unionSet.test(num - 1))
						{
							if (board.RemoveCandidate(r, c, num))
							{
								std::cout << "Naked triple: candidate eliminated: " << num << " from (" << (r + 1) << "," << (c + 1) << ")\n";

								return true;
							}
						}
					}
				}
			}
		}
	}

	// No naked triple found
	return false;
}
