#pragma once

#include "View/IUpdatable.h"
#include "CardGame/Card.h"
#include <hgesprite.h>

class CardView : public hgeSprite, public IUpdatable
{
	public:
		CardView(HTEXTURE texture, const BlackJack::Card* card);
		virtual ~CardView();

		void Update(float dt) override;
		void MoveToPosition(float x, float y);

		inline float GetX() const { return m_x; }
		inline float GetY() const { return m_y; }

	private:
		float m_x;	// actual position
		float m_y;
		float m_tx;	// target position
		float m_ty;

		bool m_isMoving = false;
		float m_lerpTimer = 0.0f;

		const BlackJack::Card* m_card;

		// constants
		static constexpr float MOVING_VELOCITY = 16.0f;
		static constexpr float SPAWN_POS_X = 150.0f;
		static constexpr float SPAWN_POS_Y = 65.0f;

		static constexpr int DIMEN_CARD_W = 140;
		static constexpr int DIMEN_CARD_H = 190;
};