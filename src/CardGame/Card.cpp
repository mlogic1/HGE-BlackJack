#include "CardGame/Card.h"

#include <string.h>

namespace BlackJack
{
	Card::Card(const char* ID, int value) :
		m_ID(ID),
		m_value(value)
	{
		m_denominator = ID[strlen(ID) - 1];
	}
	
	Card::Card(Card& other) :
		m_ID(other.m_ID),
		m_value(other.m_value),
		m_denominator(other.m_denominator)
	{
	}

	Card::Card(Card&& other) noexcept :
		m_ID(other.m_ID),
		m_value(other.m_value),
		m_denominator(other.m_denominator)
	{
	}

	int Card::GetValue() const
	{
		return m_value;
	}
	
	const char* Card::GetID() const
	{
		return m_ID;
	}

	char Card::GetDenominator() const
	{
		return m_denominator;
	}

	bool Card::operator==(const Card& other)
	{
		return strcmp(m_ID, other.m_ID) == 0;
	}
	
	Card& Card::operator=(const Card& other)
	{
		m_ID = other.m_ID;
		m_value = other.m_value;
		return *this;
	}

	bool Card::IsAce() const
	{
		return m_value == 11;
	}
}