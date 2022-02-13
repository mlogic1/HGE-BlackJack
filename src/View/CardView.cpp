#include "View/CardView.h"
#include <cmath>

CardView::CardView(HTEXTURE texture, const BlackJack::Card* card) :
	hgeSprite(texture, 0, 0, DIMEN_CARD_W, DIMEN_CARD_H),
	m_x(SPAWN_POS_X),
	m_y(SPAWN_POS_Y),
	m_tx(SPAWN_POS_X),
	m_ty(SPAWN_POS_Y),
	m_card(card)
{
}

CardView::~CardView()
{
	
}

void CardView::Update(float dt)
{
	if (m_isMoving)
	{
		const float diffX = std::abs(m_tx - m_x);
		const float diffY = std::abs(m_ty - m_y);
		if (diffX <= 3.0f && diffY <= 3.0f)
		{
			m_x = m_tx;
			m_y = m_ty;
			m_isMoving = false;
		}
		else {
			m_x = m_x + (m_tx - m_x) * dt * MOVING_VELOCITY;
			m_y = m_y + (m_ty - m_y) * dt * MOVING_VELOCITY;
		}
	}
}

void CardView::MoveToPosition(float x, float y)
{
	m_tx = x;
	m_ty = y;
	m_isMoving = true;
}
