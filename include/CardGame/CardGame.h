#pragma once

#include "Card.h"
#include "ICardGameEventListener.h"
#include "CardGameDeckType.h"
#include "CardGameState.h"
#include "PlayerAction.h"
#include <utility>
#include <vector>

namespace BlackJack
{
	class CardGame
	{
	public:
		CardGame(CardGameDeckType deckType = CardGameDeckType::STANDARD, ICardGameEventListener* m_eventListener = nullptr);
		~CardGame();
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
		Card* DrawCardFromDeck();

		int GetDealerScore();
		int GetPlayerScore();

		void EndPlayerAction(PlayerAction action);

	private:	// utility functions
		static std::vector<Card*> GenerateDeck();
		static void ShuffleDeck(std::vector<Card*>& deck);
		static void ClearCardCollection(std::vector<Card*>& vector);

	private:	
		std::vector<Card*> m_currentDeck;
		std::vector<Card*> m_dealerHand;
		std::vector<Card*> m_playerHand;
		std::vector<Card*> m_playerSplitHand;

		CardGameState m_gameState;
		ICardGameEventListener* m_eventListener;

		static std::pair<const char*, int> CARDS_DATA[52];
		const CardGameDeckType m_deckType;
	};
}