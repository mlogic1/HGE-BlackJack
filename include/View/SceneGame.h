#pragma once

#include "IScene.h"
#include <hge.h>
#include <hgesprite.h>

class SceneGame : public IScene
{
public:
	SceneGame(HGE* hge);
	virtual ~SceneGame();
	void Update(float dt) override;
	void Render() override;

private:
	HGE* m_hge;

	HTEXTURE m_backgroundTexture;
	hgeSprite* m_backgroundSprite;
};