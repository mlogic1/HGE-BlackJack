#pragma once

#include "IScene.h"
#include <hge.h>
#include <hgesprite.h>
#include "CardGame/ICardGameEventListener.h"

class SceneGame : public IScene, public BlackJack::ICardGameEventListener
{
public:
	SceneGame(HGE* hge);
	virtual ~SceneGame();
	void Update(float dt) override;
	void Render() override;

protected:
	virtual void OnStartRound(BlackJack::CardGameDeckType deckType) override;

private:
	HGE* m_hge;

	HTEXTURE m_backgroundTexture;
	hgeSprite* m_backgroundSprite;
};