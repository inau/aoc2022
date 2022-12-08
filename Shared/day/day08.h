#pragma once
#include <string>
#include "dayShared.h"
#include "../io/dataInstance.h"

namespace AoC22 { namespace Days {

	class Day08 : public Day
	{
	protected:
		// Inherited via Day
		virtual std::shared_ptr<DayResult> _runFirst(std::ifstream& data) override;
		virtual std::shared_ptr<DayResult> _runSecond(std::ifstream& data) override;

		virtual const unsigned int GetDay() const override;
	public:
		Day08(IO::InputDataReader& reader) : Day(reader) {};
	};

	class TreeGrid
	{
	public:
		class View
		{
		protected:
			const bool rowMajor;
		public:
			const uint8_t* begin;
			const uint8_t* end;

			View(uint8_t* b, uint8_t* e, bool rm) 
				: begin(b), end(e)
				, rowMajor(rm)
			{}
		};
	protected:
		unsigned _ColsSz;
		unsigned _RowsSz;
		std::vector<uint8_t> _forest_row_major;
		std::vector<uint8_t> _forest_col_major;
	
		void AddRow(std::vector<uint8_t> row);
		void Transpose();
		const unsigned GetIndex(unsigned col, unsigned row) const;
	public:
		unsigned Rows() const;
		unsigned Cols() const;

		const uint8_t& Get(unsigned col, unsigned row) const;

		static TreeGrid Builder(std::ifstream& data);
	};


}}
