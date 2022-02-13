#include "View/CardViewFactory.h"
#include <algorithm>
#include <assert.h>
#include <string>

CardViewFactory::CardViewFactory(HGE* hge) :
	m_hge(hge)
{
	for (textureMapIter it = m_textureMap.begin(); it != m_textureMap.end(); ++it)
	{
		const std::string textureName("assets\\textures\\cards\\" + std::string(it->first) + std::string(".png"));
		it->second = hge->Texture_Load(textureName.c_str());

		assert(it->second != 0);
	}
}

CardView* CardViewFactory::Create(const BlackJack::Card* card)
{
	return new CardView(m_textureMap[card->GetID()], card);
}