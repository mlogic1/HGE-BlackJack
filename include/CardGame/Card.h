#pragma once

namespace BlackJack
{
	class Card
	{
		public:
			Card(const char* ID, int value);
			Card(Card& other);
			Card(Card&& other) noexcept;

			int GetValue() const;
			const char* GetID() const;
			char GetDenominator() const;

			bool operator==(const Card& other);
			Card& operator=(const Card& other);

			bool IsAce() const;

		private:
			const char* m_ID;
			int m_value;
			char m_denominator;
	};
}