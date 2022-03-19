#include "AI/AIDealer.h"

AIDealer::AIDealer(BlackJack::CardGame* game) :
	m_game(game)
{

}

void AIDealer::Update(float dt)
{
	if (m_game->GetCardGameState() != BlackJack::CardGameState::DEALER_PLAYING)
		return;

	if (m_dealerThinkTime > .0f) {
		m_dealerThinkTime -= dt;
		return;
	}
	else {
		m_dealerThinkTime = DEALER_THINK_TIME;
	}

	if (m_game->GetDealerScore() <= m_game->GetPlayerScore()) {
		m_game->DealerHit();
	}
	else {
		m_game->DealerStand();
	}
}
