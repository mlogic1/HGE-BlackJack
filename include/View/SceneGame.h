#pragma once

#include "IScene.h"
#include <hge.h>
#include <hgesprite.h>
#include <hgefont.h>
#include "CardView.h"
#include "CardGame/ICardGameEventListener.h"
#include "CardGame/CardGame.h"

class CardViewFactory;

class SceneGame : public IScene, public BlackJack::ICardGameEventListener
{
	public:
		SceneGame(HGE* hge);
		virtual ~SceneGame();
		void Update(float dt) override;
		void Render() override;

	private:	// events from card game
		virtual void OnStartRound(BlackJack::CardGameDeckType deckType) override;
		virtual void OnPlayerHit(const BlackJack::Card* card) override;
		virtual void OnDealerHit(const BlackJack::Card* card) override;

	private:
		BlackJack::CardGame* m_cardGame;

		HGE* m_hge;

		HTEXTURE m_backgroundTexture;
		HTEXTURE m_cardBackTexture;
		hgeSprite* m_backgroundSprite;
		hgeSprite* m_deckBackSprite;
		// hgeFont* m_sceneFont;

		CardViewFactory* m_cardViewFactory;
		std::vector<CardView*> m_playerCardViews;
		std::vector<CardView*> m_dealerCardViews;
	
	#ifdef _DEBUG
		hgeFont* m_debugFont;
		bool m_showDebugInfo = true;
		inline void ToggleDebugInfo() { m_showDebugInfo = !m_showDebugInfo; }
		void RenderDebugInfo();
	#endif

		// constants
		static constexpr float DECK_POS_X = 150.0f;
		static constexpr float DECK_POS_Y = 65.0f;

		static constexpr float PLAYER_FIRST_CARD_POS_X = 65.0f;
		static constexpr float PLAYER_FIRST_CARD_POS_Y = 450.0f;
		static constexpr float DEALER_FIRST_CARD_POS_X = DECK_POS_X + 90.0f;
		static constexpr float DEALER_FIRST_CARD_POS_Y = DECK_POS_Y;
		static constexpr float CARDS_OFFSET_X = 164.0f;

		static constexpr int DIMEN_CARD_W = 140;
		static constexpr int DIMEN_CARD_H = 190;
};
