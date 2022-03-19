#pragma once

#include "CardGame/CardGame.h"

class AIDealer
{
public:
	AIDealer(BlackJack::CardGame* game);
	void Update(float dt);

private:
	BlackJack::CardGame* m_game;

	static constexpr float DEALER_THINK_TIME = 1.2f;
	float m_dealerThinkTime = DEALER_THINK_TIME;
};