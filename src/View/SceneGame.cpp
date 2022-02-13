#include "View/SceneGame.h"
#include "View/CardViewFactory.h"

SceneGame::SceneGame(HGE* hge) :
	m_hge(hge)
{
	m_backgroundTexture = m_hge->Texture_Load("assets\\textures\\table_background.jpg");
	m_cardBackTexture = m_hge->Texture_Load("assets\\textures\\Cards\\cardBack_blue5.png");
	
	m_backgroundSprite = new hgeSprite(m_backgroundTexture, 0, 0, 1280, 720);
	m_deckBackSprite = new hgeSprite(m_cardBackTexture, 0, 0, DIMEN_CARD_W, DIMEN_CARD_H);

#ifdef _DEBUG
	m_debugFont = new hgeFont("assets\\fonts\\debug.fnt");
#endif

	m_cardViewFactory = new CardViewFactory(m_hge);
	m_cardGame = new BlackJack::CardGame(BlackJack::CardGameDeckType::STANDARD, this);
}

SceneGame::~SceneGame()
{
#ifdef _DEBUG
	delete m_debugFont;
#endif

	delete m_backgroundSprite;
	delete m_deckBackSprite;

	m_hge->Texture_Free(m_backgroundTexture);
	m_hge->Texture_Free(m_cardBackTexture);

	delete m_cardGame;
	delete m_cardViewFactory;
	// TODO clean up card views
}

void SceneGame::Update(float dt)
{
	hgeInputEvent evnt;
	if (m_hge->Input_GetEvent(&evnt))
	{
		if (evnt.type == INPUT_KEYUP)
		{
			if (evnt.key == HGEK_H)
			{
				m_cardGame->Hit();
			}
			if (evnt.key == HGEK_S)
			{
				m_cardGame->Stand();
			}
			if (evnt.key == HGEK_SPACE)
			{
				// m_cardViews.back()->MoveToPosition(450.0f, 16.0f);
			}
			if (evnt.key == HGEK_R)
			{
				m_cardGame->StartRound();
			}
		#ifdef _DEBUG
			if (evnt.key == HGEK_F11)
			{
				ToggleDebugInfo();
			}
		#endif
		}
	}

	for (CardView* cardView : m_cardViews)
		cardView->Update(dt);
}

void SceneGame::Render()
{
	m_backgroundSprite->Render(.0f, .0f);
	for (CardView* cardView : m_cardViews)
	{
		cardView->Render(cardView->GetX(), cardView->GetY());
	}

	m_deckBackSprite->Render(DECK_POS_X, DECK_POS_Y);

#ifdef _DEBUG
	RenderDebugInfo();
#endif
}

void SceneGame::OnStartRound(BlackJack::CardGameDeckType deckType)
{
	for (CardView* cardView : m_cardViews)
	{
		delete cardView;
	}
	m_cardViews.clear();
}

void SceneGame::OnPlayerHit(const BlackJack::Card* card)
{
	CardView* cardView = m_cardViewFactory->Create(card);

	const float posX = PLAYER_FIRST_CARD_POS_X + (m_cardViews.size() * DIMEN_CARD_W) + CARDS_OFFSET_X;
	const float posY = PLAYER_FIRST_CARD_POS_Y;
	cardView->MoveToPosition(posX, posY);

	m_cardViews.emplace_back(cardView);

	// play the draw sound
}

#ifdef _DEBUG

constexpr const char* CardGameStateToStr(BlackJack::CardGameState state)
{
	switch (state)
	{
	case BlackJack::CardGameState::DEALER_WIN:
		return "Dealer Win";
		break;
	case BlackJack::CardGameState::DEALER_PLAYING:
		return "Dealer Playing";
		break;
	case BlackJack::CardGameState::DRAW:
		return "Draw";
		break;
	case BlackJack::CardGameState::PLAYER_BUST:
		return "Player Bust";
		break;
	case BlackJack::CardGameState::PLAYER_WIN:
		return "Player Win";
		break;
	case BlackJack::CardGameState::PLAYING:
		return "Playing";
		break;
	case BlackJack::CardGameState::PLAYING_SPLIT_A:
		return "Playing Split A";
		break;
	case BlackJack::CardGameState::PLAYING_SPLIT_B:
		return "Playing Split B";
		break;
	case BlackJack::CardGameState::PRE_START:
		return "Pre Start";
		break;
	default:
		return "Unknown";
		break;
	}
}

void SceneGame::RenderDebugInfo()
{
	if (!m_showDebugInfo)
		return;

	m_debugFont->printf(5, 5, HGETEXT_LEFT, "Can hit: %d", m_cardGame->CanHit());
	m_debugFont->printf(5, 15, HGETEXT_LEFT, "Can split: %d", m_cardGame->CanSplit());
	m_debugFont->printf(5, 25, HGETEXT_LEFT, "Can double down: %d", m_cardGame->CanDoubleDown());
	m_debugFont->printf(5, 35, HGETEXT_LEFT, "Can stand: %d", m_cardGame->CanStand());
	m_debugFont->printf(5, 45, HGETEXT_LEFT, "Game state: %s", CardGameStateToStr(m_cardGame->GetCardGameState()));
	m_debugFont->printf(5, 55, HGETEXT_LEFT, "Player hand: %d", m_cardGame->GetPlayerScore());
	m_debugFont->printf(5, 65, HGETEXT_LEFT, "Dealer hand: %d", m_cardGame->GetDealerScore());

	m_debugFont->printf(80, 5, HGETEXT_LEFT, "dt: %f", m_hge->Timer_GetDelta());	
	m_debugFont->printf(80, 15, HGETEXT_LEFT, "fps: %d", m_hge->Timer_GetFPS());
}
#endif