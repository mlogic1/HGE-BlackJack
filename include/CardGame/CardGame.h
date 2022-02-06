#pragma once

#include "Card.h"
#include <utility>
#include <vector>

namespace BlackJack
{
	enum class CardGameDeckType
	{
		STANDARD = 6,	// 6 decks
		SMALL = 1,		// 1 deck 
		BIG	= 9		// 9 decks
	};

	enum class CardGameState 
	{
		PRE_START = 0,
		PLAYING,
		PLAYING_SPLIT_A,
		PLAYING_SPLIT_B,
		PLAYER_BUST,
		PLAYER_WIN,
		DEALER_WIN,
		DRAW
	};

	class CardGame
	{
		enum class PlayerAction;
	public:
		CardGame(CardGameDeckType deckType = CardGameDeckType::STANDARD);
		void Reset();

		bool CanHit();
		bool CanSplit();
		bool CanDoubleDown();
		bool CanStand();

		bool Hit();
		bool Split();
		bool DoubleDown();
		bool Stand();

		bool StartRound();

	private:
		Card DrawCardFromDeck();

		int GetDealerScore();
		int GetPlayerScore();

		void EndPlayerAction(PlayerAction action);

	private:	// utility functions
		static std::vector<Card> GenerateDeck();
		static void ShuffleDeck(std::vector<Card>& deck);

	private:	
		std::vector<Card> m_currentDeck;
		std::vector<Card> m_dealerHand;
		std::vector<Card> m_playerHand;
		std::vector<Card> m_playerSplitHand;

		CardGameState m_gameState;

		enum class PlayerAction
		{
			HIT = 0,
			SPLIT,
			DOUBLEDOWN,
			STAND
		};

		static std::pair<const char*, int> CARDS_DATA[52];
		const CardGameDeckType m_deckType;
	};
}