#include "CardGame/CardGame.h"
#include "CardGame/ICardGameEventListener.h"
#include <algorithm>
#include <random>

#define TRIGGER_EVENT(func, args) if(m_eventListener) { m_eventListener->func(args); }

namespace BlackJack
{
	CardGame::CardGame(CardGameDeckType deckType, ICardGameEventListener* eventListener) :
		m_deckType(deckType),
		m_eventListener(eventListener)
	{
		Reset();
	}

	CardGame::~CardGame()
	{
		ClearCardCollection(m_currentDeck);
		ClearCardCollection(m_dealerHand);
		ClearCardCollection(m_playerHand);
		ClearCardCollection(m_playerSplitHand);
	}
	
	void CardGame::Reset()
	{
		ClearCardCollection(m_currentDeck);
		ClearCardCollection(m_dealerHand);
		ClearCardCollection(m_playerHand);
		ClearCardCollection(m_playerSplitHand);
		
		ChangeGameState(CardGameState::PRE_START);
		const int decksToGenerate = static_cast<int>(m_deckType);
		for (int i = 0; i < decksToGenerate; ++i) 
		{
			std::vector<Card*> generatedDeck = GenerateDeck();

			for (Card* card : generatedDeck)
				m_currentDeck.emplace_back(card);
		}
		ShuffleDeck(m_currentDeck);
		StartRound();
	}

	bool CardGame::CanHit()
	{
		return (m_gameState == CardGameState::PLAYING || m_gameState == CardGameState::PLAYING_SPLIT_A || m_gameState == CardGameState::PLAYING_SPLIT_B);
	}

	bool CardGame::CanSplit()
	{
		return (m_playerHand.size() == 2 && m_playerSplitHand.empty() && m_playerHand[0]->GetDenominator() == m_playerHand[1]->GetDenominator() && m_gameState == CardGameState::PLAYING);
	}

	bool CardGame::CanDoubleDown()
	{
		const int playerScore = GetPlayerScore();
		return (m_playerHand.size() == 2 && m_dealerHand.empty() && playerScore >= 9 && playerScore <= 11);
	}

	bool CardGame::CanStand()
	{
		return (m_gameState == CardGameState::PLAYING || m_gameState == CardGameState::PLAYING_SPLIT_A || m_gameState == CardGameState::PLAYING_SPLIT_B);
	}

	bool CardGame::Hit()
	{
		if (!CanHit())
			return false;
		
		Card* card = DrawCardFromDeck();
		if (m_gameState == CardGameState::PLAYING || m_gameState == CardGameState::PLAYING_SPLIT_A)
		{
			m_playerHand.emplace_back(card);
		}
		else if (m_gameState == CardGameState::PLAYING_SPLIT_B) 
		{
			m_playerSplitHand.emplace_back(card);
		}
		else {
			throw std::string("Error - Hit was called, but gamestate is neither playing, playing split A, or playing split B");
			return false;
		}

		TRIGGER_EVENT(OnPlayerHit, card);
		EndPlayerAction(PlayerAction::HIT);
		return true;
	}

	bool CardGame::Split()
	{
		if (!CanSplit())
			return false;
		
		Card* card = m_playerHand.back();
		m_playerHand.pop_back();
		m_playerSplitHand.emplace_back(card);
		m_gameState = CardGameState::PLAYING_SPLIT_A;
		
		EndPlayerAction(PlayerAction::SPLIT);
		return true;
	}

	bool CardGame::DoubleDown()
	{
		if (!CanDoubleDown())
			return false;

		Card* card = DrawCardFromDeck();
		m_playerHand.emplace_back(card);

		EndPlayerAction(PlayerAction::DOUBLEDOWN);
		return true;
	}

	bool CardGame::Stand()
	{
		if (!CanStand())
			return false;

		EndPlayerAction(PlayerAction::STAND);
		return true;
	}
	
	bool CardGame::StartRound()
	{
		if ((m_gameState != CardGameState::PRE_START) && (m_gameState != CardGameState::DRAW) && (m_gameState != CardGameState::PLAYER_BUST) && (m_gameState != CardGameState::PLAYER_WIN) && (m_gameState != CardGameState::DEALER_WIN))
			return false;
		// TODO - check the deck - reshuffle if needed
		TRIGGER_EVENT(OnStartRound, m_deckType);

		ChangeGameState(CardGameState::PLAYING);

		m_dealerHand.clear();
		m_playerHand.clear();
		m_playerSplitHand.clear();
		
		Card* p1 = DrawCardFromDeck();
		Card* d1 = DrawCardFromDeck();
		Card* p2 = DrawCardFromDeck();
		Card* d2 = DrawCardFromDeck();
		
		m_playerHand.emplace_back(p1);
		m_dealerHand.emplace_back(d1);
		m_playerHand.emplace_back(p2);
		m_dealerHand.emplace_back(d2);

		TRIGGER_EVENT(OnPlayerHit, p1);
		TRIGGER_EVENT(OnPlayerHit, p2);
	}

	CardGameState CardGame::GetCardGameState() const
	{
		return m_gameState;
	}

	Card* CardGame::DrawCardFromDeck()
	{
		Card* card = m_currentDeck.back();
		m_currentDeck.pop_back();

		TRIGGER_EVENT(OnDrawCardFromDeck, card);

		return card;
	}

	int CardGame::GetDealerScore() const
	{
		int sum = 0;
		std::for_each(m_dealerHand.cbegin(), m_dealerHand.cend(), [&sum](const Card* card) { sum += card->GetValue(); });
		return sum;
	}

	int CardGame::GetPlayerScore() const
	{
		const std::vector<Card*>* ptrToHand = (m_gameState == CardGameState::PLAYING_SPLIT_B) ? &m_playerSplitHand : &m_playerHand;
		int sum = 0;
		std::for_each(m_playerHand.cbegin(), m_playerHand.cend(), [&sum](const Card* card) { sum += card->GetValue(); });
		return sum;
	}

	std::vector<const Card*> CardGame::GetPlayerHand() const
	{
		if (m_gameState == CardGameState::PLAYING_SPLIT_B) 
		{
			return std::vector<const Card*>(m_playerSplitHand.cbegin(), m_playerSplitHand.cend());
		}
		
		return std::vector<const Card*>(m_playerHand.cbegin(), m_playerHand.cend());
	}

	std::vector<const Card*> CardGame::GetDealerHand() const
	{
		return std::vector<const Card*>(m_dealerHand.cbegin(), m_dealerHand.cend());
	}

	void CardGame::EndPlayerAction(PlayerAction action)
	{
		TRIGGER_EVENT(OnEndPlayerAction, action);
		if (GetPlayerScore() > 21)
		{
			//if (goldenBlackjack)	// TODO implement this
			ChangeGameState(CardGameState::PLAYER_BUST);
		}
		else if (action == PlayerAction::STAND || action == PlayerAction::DOUBLEDOWN) 
		{
			ChangeGameState(CardGameState::DEALER_PLAYING);

			// dealer logic
		}
		else
		{
			// player keeps playing
		}
		// check if player busted
		// if busted, go to busted state and wait for startNewRound call
		// else check if action was stand or double down - if yes, move on to dealer's turn
	}

	void CardGame::ChangeGameState(CardGameState newState)
	{
		m_gameState = newState;
	}

	void CardGame::ClearCardCollection(std::vector<Card*>& vector)
	{
		std::for_each(vector.begin(), vector.end(), [](Card* card) { delete card; });
		vector.clear();
	}

	std::vector<Card*> CardGame::GenerateDeck()
	{
		std::vector<Card*> cardsInOrder;
		static constexpr int NUM_CARDS = 52;

		for (int i = 0; i < NUM_CARDS; ++i)
			cardsInOrder.emplace_back(new Card(CARDS_DATA[i].first, CARDS_DATA[i].second));

		return cardsInOrder;
	}
	
	void CardGame::ShuffleDeck(std::vector<Card*>& deck)
	{
		auto rng = std::default_random_engine{};
		std::shuffle(deck.begin(), deck.end(), rng);
	}
}

namespace BlackJack
{
	std::pair<const char*, int> CardGame::CARDS_DATA[52] =
	{
		{ "cardClubs2", 2 },
		{ "cardClubs3", 3 },
		{ "cardClubs4", 4 },
		{ "cardClubs5", 5 },
		{ "cardClubs6", 6 },
		{ "cardClubs7", 7 },
		{ "cardClubs8", 8 },
		{ "cardClubs9", 9 },
		{ "cardClubs10", 10 },
		{ "cardClubsA", 11 },
		{ "cardClubsJ", 10 },
		{ "cardClubsK", 10 },
		{ "cardClubsQ", 10 },
		{ "cardDiamonds2", 2 },
		{ "cardDiamonds3", 3 },
		{ "cardDiamonds4", 4 },
		{ "cardDiamonds5", 5 },
		{ "cardDiamonds6", 6 },
		{ "cardDiamonds7", 7 },
		{ "cardDiamonds8", 8 },
		{ "cardDiamonds9", 9 },
		{ "cardDiamonds10", 10 },
		{ "cardDiamondsA", 11 },
		{ "cardDiamondsJ", 10 },
		{ "cardDiamondsK", 10 },
		{ "cardDiamondsQ", 10 },
		{ "cardHearts2", 2 },
		{ "cardHearts3", 3 },
		{ "cardHearts4", 4 },
		{ "cardHearts5", 5 },
		{ "cardHearts6", 6 },
		{ "cardHearts7", 7 },
		{ "cardHearts8", 8 },
		{ "cardHearts9", 9 },
		{ "cardHearts10", 10 },
		{ "cardHeartsA", 11 },
		{ "cardHeartsJ", 10 },
		{ "cardHeartsK", 10 },
		{ "cardHeartsQ", 10 },
		{ "cardSpades2", 2 },
		{ "cardSpades3", 3 },
		{ "cardSpades4", 4 },
		{ "cardSpades5", 5 },
		{ "cardSpades6", 6 },
		{ "cardSpades7", 7 },
		{ "cardSpades8", 8 },
		{ "cardSpades9", 9 },
		{ "cardSpades10", 10 },
		{ "cardSpadesA", 11 },
		{ "cardSpadesJ", 10 },
		{ "cardSpadesK", 10 },
		{ "cardSpadesQ", 10 }
	};
}