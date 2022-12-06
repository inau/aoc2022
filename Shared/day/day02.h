#pragma once
#include <string>
#include "dayShared.h"
#include "../io/dataInstance.h"

namespace AoC22 { namespace Days {

	class Day02 : public Day
	{
	protected:
		enum class Outcome
		{
			LOSS = 0,
			DRAW = 3,
			WIN = 6
		};
		enum class Token : unsigned
		{
			UND = 0,
			ROCK = 1,
			PAPER = 2,
			SCISOR = 3,
		};

		Token GetToken(char c)
		{
			Token t = Token::UND;
			switch (c)
			{
			case 'A': t = Token::ROCK; break;
			case 'B': t = Token::PAPER; break;
			case 'C': t = Token::SCISOR; break;

			case 'X': t = Token::ROCK; break;
			case 'Y': t = Token::PAPER; break;
			case 'Z': t = Token::SCISOR; break;
			}
			return t;
		}

		Outcome GetOutcome(char c)
		{
			Outcome t = Outcome::LOSS;
			switch (c)
			{
//			case 'X': t = Token::ROCK; break;
			case 'Y': t = Outcome::DRAW; break;
			case 'Z': t = Outcome::WIN; break;
			}
			return t;
		}

		Token GetTokenForOutcome(Token lhs, Outcome target)
		{
			Token rhs = lhs;
			
			switch (target)
			{
			case Outcome::WIN:
			{
				switch (lhs)
				{
				case Token::ROCK: rhs = Token::PAPER; break;
				case Token::PAPER: rhs = Token::SCISOR; break;
				case Token::SCISOR: rhs = Token::ROCK; break;
				}
			} break;
			case Outcome::LOSS:
			{
				switch (lhs)
				{
				case Token::ROCK: rhs = Token::SCISOR; break;
				case Token::PAPER: rhs = Token::ROCK; break;
				case Token::SCISOR: rhs = Token::PAPER; break;
				}
			} break;
			}

			return rhs;
		}

		Outcome GetOutcome(Token lhs, Token rhs)
		{
			Outcome score = Outcome::LOSS;

			switch (lhs)
			{
			case Token::ROCK:
			{
				switch (rhs)
				{
				case Token::ROCK: score = Outcome::DRAW; break;
				case Token::SCISOR: score = Outcome::WIN; break;
				}
			} break;
			case Token::SCISOR:
			{
				switch (rhs)
				{
				case Token::SCISOR: score = Outcome::DRAW; break;
				case Token::PAPER: score = Outcome::WIN; break;
				}
			} break;
			case Token::PAPER:
			{
				switch (rhs)
				{
				case Token::PAPER: score = Outcome::DRAW; break;
				case Token::ROCK: score = Outcome::WIN; break;
				}
			} break;
			}

			return score;
		}
	protected:
		// Inherited via Day
		virtual std::shared_ptr<DayResult> _runFirst(std::ifstream& data) override;
		virtual std::shared_ptr<DayResult> _runSecond(std::ifstream& data) override;

		virtual const unsigned int GetDay() const override;
	public:
		Day02(IO::InputDataReader& reader) : Day(reader) {};
	};



}}
