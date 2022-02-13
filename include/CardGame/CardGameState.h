#pragma once

namespace BlackJack
{
	enum class CardGameState 
	{
		PRE_START = 0,
		PLAYING,
		DEALER_PLAYING,
		PLAYING_SPLIT_A,
		PLAYING_SPLIT_B,
		PLAYER_BUST,
		PLAYER_WIN,
		DEALER_WIN,
		DRAW
	};
}
	