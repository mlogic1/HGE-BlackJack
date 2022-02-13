#pragma once

#include "IAIDealer.h"

namespace BlackJack
{
	class AIDealer : public IAIDealer
	{
	public:
		virtual DealerAction DecideAction(const CardGame& game) override;
	};
}