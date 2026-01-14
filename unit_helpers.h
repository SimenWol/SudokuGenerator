#pragma once
#include <utility>
#include <vector>

using CellPos = std::pair<int, int>;

/** Unit types available in a sudoku. */
enum class UnitType
{
	Row,
	Column,
	Box
};

/** Helper function for iterating cells in a unit. */
static std::vector<CellPos> GetUnit(UnitType type, int index)
{
	std::vector<CellPos> cells;

	switch (type)
	{
		case UnitType::Row:
		{
			for (int c = 0; c < 9; c++) { cells.emplace_back(index, c); }

			break;
		}
		case UnitType::Column:
		{
			for (int r = 0; r < 9; r++) { cells.emplace_back(r, index); }

			break;
		}
		case UnitType::Box:
		{
			int br = (index / 3) * 3;
			int bc = (index % 3) * 3;
			for (int r = 0; r < 3; r++)
				for (int c = 0; c < 3; c++)
					cells.emplace_back(br + r, bc + c);

			break;
		}
	}

	return cells;
}

/** Helper function that returns the box index from the provided cell.
* 
* Index convention is as follows:
* 0 1 2
* 3 4 5
* 6 7 8
*/
static inline int BoxIndex(int row, int col) { return (row / 3) * 3 + (col / 3); }