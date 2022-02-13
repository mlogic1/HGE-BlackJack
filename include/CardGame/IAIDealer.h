#pragma once

#include "CardGame.h"
#include "DealerAction.h"

namespace BlackJack
{
	class IAIDealer
	{
	public:
		virtual ~IAIDealer() {};
		virtual DealerAction DecideAction(const CardGame& game) = 0;
	};
}