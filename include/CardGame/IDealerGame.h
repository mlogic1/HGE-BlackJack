#pragma once

#include "CardGame.h"

namespace BlackJack
{
	class IDealerGame
	{
	public:
		virtual ~IDealerGame() {};
		virtual bool DealerHit() = 0;
		virtual bool DealerStand() = 0;
	};
}