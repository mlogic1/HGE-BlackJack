#pragma once

#include "CardView.h"
#include <hge.h>
#include <map>

class CardViewFactory
{
public:
	CardViewFactory(HGE* hge);
	CardView* Create(const BlackJack::Card* card);

private:
	HGE* m_hge;
	using textureMapIter = std::map<const char*, HTEXTURE>::iterator;
	std::map<const char*, HTEXTURE> m_textureMap =	// maps card IDS to textures
	{
		{ "cardClubs2", 0 },
		{ "cardClubs3", 0 },
		{ "cardClubs4", 0 },
		{ "cardClubs5", 0 },
		{ "cardClubs6", 0 },
		{ "cardClubs7", 0 },
		{ "cardClubs8", 0 },
		{ "cardClubs9", 0 },
		{ "cardClubs10", 0 },
		{ "cardClubsA", 0 },
		{ "cardClubsJ", 0 },
		{ "cardClubsK", 0 },
		{ "cardClubsQ", 0 },
		{ "cardDiamonds2", 0 },
		{ "cardDiamonds3", 0 },
		{ "cardDiamonds4", 0 },
		{ "cardDiamonds5", 0 },
		{ "cardDiamonds6", 0 },
		{ "cardDiamonds7", 0 },
		{ "cardDiamonds8", 0 },
		{ "cardDiamonds9", 0 },
		{ "cardDiamonds10", 0 },
		{ "cardDiamondsA", 0 },
		{ "cardDiamondsJ", 0 },
		{ "cardDiamondsK", 0 },
		{ "cardDiamondsQ", 0 },
		{ "cardHearts2", 0 },
		{ "cardHearts3", 0 },
		{ "cardHearts4", 0 },
		{ "cardHearts5", 0 },
		{ "cardHearts6", 0 },
		{ "cardHearts7", 0 },
		{ "cardHearts8", 0 },
		{ "cardHearts9", 0 },
		{ "cardHearts10", 0 },
		{ "cardHeartsA", 0 },
		{ "cardHeartsJ", 0 },
		{ "cardHeartsK", 0 },
		{ "cardHeartsQ", 0 },
		{ "cardSpades2", 0 },
		{ "cardSpades3", 0 },
		{ "cardSpades4", 0 },
		{ "cardSpades5", 0 },
		{ "cardSpades6", 0 },
		{ "cardSpades7", 0 },
		{ "cardSpades8", 0 },
		{ "cardSpades9", 0 },
		{ "cardSpades10", 0 },
		{ "cardSpadesA", 0 },
		{ "cardSpadesJ", 0 },
		{ "cardSpadesK", 0 },
		{ "cardSpadesQ", 0 }
	};
};