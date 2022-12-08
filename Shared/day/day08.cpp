#include "day08.h"
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <algorithm>

namespace AoC22 { namespace Days {

const unsigned int AoC22::Days::Day08::GetDay() const
{
	return 8u;
}

bool has_line_of_sight(const TreeGrid& grid, unsigned col, unsigned row)
{
	uint8_t west = 0u, east = 0u, north = 0u, south = 0u, treehouse = 0u;
	for (int c = 0u; c < grid.Cols(); c++)
	{
		const uint8_t& tree = grid.Get(c, row);
		if (c < col) west = west < tree ? tree : west;
		if (c > col) east = east < tree ? tree : east;
		else treehouse = tree;
	}
	for (int r = 0u; r < grid.Rows(); r++)
	{
		const uint8_t& tree = grid.Get(col, r);
		if (r < row) north = north < tree ? tree : north;
		if (r > row) south = south < tree ? tree : south;
		else treehouse = tree;
	}

	return (treehouse > north)
		|| (treehouse > east)
		|| (treehouse > south)
		|| (treehouse > west)
		;
}

unsigned int get_scenic_score(const TreeGrid& grid, unsigned col, unsigned row)
{
	uint8_t west = 0u, east = 0u, north = 0u, south = 0u, treehouse = 0u;
	treehouse = grid.Get(col, row);
	for (int c = col; c > 0; c--)
	{
		west++;
		const uint8_t& tree = grid.Get(c-1, row);
		if (tree >= treehouse) break;
	}
	for (int c = col; c < grid.Cols()-1; c++)
	{
		east++;
		const uint8_t& tree = grid.Get(c+1, row);
		if (tree >= treehouse) break;
	}

	for (int r = row; r > 0; r--)
	{
		north++;
		const uint8_t& tree = grid.Get(col, r-1);
		if (tree >= treehouse) break;
	}
	for (int r = row; r < grid.Rows()-1; r++)
	{
		south++;
		const uint8_t& tree = grid.Get(col, r+1);
		if (tree >= treehouse) break;
	}

	return (west*east*south*north);
}

std::shared_ptr<DayResult> AoC22::Days::Day08::_runFirst(std::ifstream& data)
{
	unsigned losCount = 0;

	TreeGrid grid = TreeGrid::Builder(data);

	// edges
	losCount = 2 * (grid.Cols() - 2) + 2 * grid.Rows();

	// process middle
	for (int c = 1; c < grid.Cols() - 1; ++c)
	{
		for (int r = 1; r < grid.Rows() - 1; ++r)
		{
			losCount += has_line_of_sight(grid, c, r);
		}
	}

	return std::make_shared<DayIntegerResult>(losCount);
}



std::shared_ptr<DayResult> AoC22::Days::Day08::_runSecond(std::ifstream& data)
{
	unsigned int bestScene = 0u;

	TreeGrid grid = TreeGrid::Builder(data);

	// process middle
	for (int c = 1; c < grid.Cols()-1; ++c)
	{
		for (int r = 1; r < grid.Rows()-1; ++r)
		{

			unsigned int score = get_scenic_score(grid, c, r);
			if (score > bestScene) bestScene = score;
		}
	}

	return std::make_shared<DayIntegerResult>(bestScene);
}

// grid

unsigned Days::TreeGrid::Rows() const { return _RowsSz; };
unsigned Days::TreeGrid::Cols() const { return _ColsSz; };

const uint8_t& TreeGrid::Get (unsigned col, unsigned row) const
{
	return _forest_row_major[GetIndex(col, row)];
}

void Days::TreeGrid::AddRow(std::vector<uint8_t> row)
{
	if (_ColsSz == 0) _ColsSz = row.size();

	if (row.size() != _ColsSz) throw std::exception("rows have different column widths");

	for (auto& r : row)
	{
		_forest_row_major.push_back(r);
	}
	_RowsSz++;

}

std::vector<uint8_t> transpose(const std::vector<uint8_t>& original, const unsigned columns, const unsigned rows)
{
	std::vector<uint8_t> transposed;
	transposed.resize(original.size());
	for (int x = 0; x < columns; x++)
		for (int y = 0; y < rows; y++)
		{
			unsigned src = x + (y * rows);
			unsigned tar = (x*columns) + y;

			transposed[tar] = original[src];
		}
	return transposed;
}
void Days::TreeGrid::Transpose()
{
//	_forest_col_major = transpose(_forest_row_major, _ColsSz, _RowsSz);
}

const unsigned TreeGrid::GetIndex(unsigned col, unsigned row) const
{
	unsigned idx = col + (row * _RowsSz);
	if (idx >= _forest_row_major.size()) throw std::exception("treegrid index was out of bounds");
	return idx;
}

TreeGrid Days::TreeGrid::Builder(std::ifstream& data)
{
	TreeGrid grid;

	std::stringstream sstr;
	uint8_t tree;
	std::vector<uint8_t> row;
	auto func = [&](const std::string& line)
	{
		if (row.size() == 0) { row.resize(line.size()); }

		if (line.size() != row.size()) throw std::exception("columns have different widths");

		sstr << line;

		unsigned idx = 0;
		while (sstr >> tree && idx < row.size())
		{
			row[idx++] = tree;
		}

		grid.AddRow(row);

		sstr.clear();
	};
	IterateData(data, func);
	
//	grid.Transpose();


	return grid;
}

}}