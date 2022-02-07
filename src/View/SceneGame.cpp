#include "View/SceneGame.h"

SceneGame::SceneGame(HGE* hge) :
	m_hge(hge)
{
	m_backgroundTexture = m_hge->Texture_Load("assets\\textures\\table_background.jpg");
	m_backgroundSprite = new hgeSprite(m_backgroundTexture, 0, 0, 1024, 768);
}

SceneGame::~SceneGame()
{
	m_hge->Texture_Free(m_backgroundTexture);
}

void SceneGame::Update(float dt)
{
    
}

void SceneGame::Render()
{
	m_backgroundSprite->Render(0, 0);
}