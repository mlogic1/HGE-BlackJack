#include "CardGame/AIDealer.h"

#include <string.h>

namespace BlackJack
{
	DealerAction AIDealer::DecideAction(const CardGame& game)
	{
		if (game.GetPlayerScore() > game.GetDealerScore()) {
			return DealerAction::HIT;
		}
		else {
			return DealerAction::STAND;
		}
	}
}