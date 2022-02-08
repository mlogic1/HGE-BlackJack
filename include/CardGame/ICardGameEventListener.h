#pragma once

namespace BlackJack
{
	enum class CardGameDeckType;
	enum class PlayerAction;
	class Card;

	class ICardGameEventListener
	{
	public:
		virtual ~ICardGameEventListener() {};
	protected:
		virtual void OnStartRound(CardGameDeckType deckType) {};
		virtual void OnDrawCardFromDeck(const Card* card) {};
		virtual void OnEndPlayerAction(PlayerAction action) {};

		friend class CardGame;
	};
}