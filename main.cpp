#include <hge.h>
#include <hgefont.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <iostream>
#include <list>
#include <vector>

#include "button.h"
#include "card.h"

// Main pointer
HGE *hge=0;

// Font pointer
hgeFont *text;

// Variable to display fps and dev stats,F12 toggles this
bool devstats = false;

//Variable to display help
bool helpbool = false;

//Quit game button bool
bool quitgame = false;

// Game Variables
Card *c[52];
HEFFECT flipsound;
hgeVector FirstCardLocation;
hgeVector FirstCardLocationDealer;

int PlayerScore;
int DealerScore;

// This keeps score of wins
int DealerWins = 0;
int PlayerWins = 0;
bool playerWonPrevious = false; //Can't figure out why when player wins his score goes up by 2 instead of 1, this is a workaround

// Dealer's first card ID (this tells which card is dealer's first and when to change its texture), card background texture
int DealerFirstCardID = 0;
HTEXTURE CardBackTexture;

// Game Status variable
int Gamestatus;
/*
*
0 - Playing
1 - Win
2 - Defeat
*
*/


// Buttons
Button *HitMe;
hgeVector HitMeLoc;
Button *Stand;
hgeVector StandLoc;
Button *ExitGame;
hgeVector ExitGameLoc;

// Mouse Location(x,y) used for buttons
float mouseX = 0;
float mouseY = 0;

// Object List used to say which cards are on the table and who owns them and render them.
std::list<Card*> Dealer;
std::list<Card*> Player;

// Iterator used to scroll through card lists
std::list<Card*>::iterator it;

// Drawncards is a vector that says which cards have been pulled from the deck
std::vector<int> Dcards;

// Background texture
HTEXTURE background;
hgeSprite *s_background;

// End round display textures and sprite
HTEXTURE winTexture;
HTEXTURE loseTexture;
hgeSprite *s_endgame;

// Music
HSTREAM song;

/*  END OF MAIN VARIABLES   */



 //Create 52 Cards and Load Their Textures
void InitiateDeck(){
    /*  NUMBER CARDS    */

    // Cards with Values of 2
    c[0] = new Card(hge, 2);
    c[1] = new Card(hge, 2);
    c[2] = new Card(hge, 2);
    c[3] = new Card(hge, 2);


    // Cards with Values of 3
    c[4] = new Card(hge, 3);
    c[5] = new Card(hge, 3);
    c[6] = new Card(hge, 3);
    c[7] = new Card(hge, 3);


    // Cards with Values of 4
    c[8] = new Card(hge, 4);
    c[9] = new Card(hge, 4);
    c[10] = new Card(hge, 4);
    c[11] = new Card(hge, 4);


    // Cards with Values of 5
    c[12] = new Card(hge, 5);
    c[13] = new Card(hge, 5);
    c[14] = new Card(hge, 5);
    c[15] = new Card(hge, 5);


    // Cards with Values of 6
    c[16] = new Card(hge, 6);
    c[17] = new Card(hge, 6);
    c[18] = new Card(hge, 6);
    c[19] = new Card(hge, 6);


    // Cards with Values of 7
    c[20] = new Card(hge, 7);
    c[21] = new Card(hge, 7);
    c[22] = new Card(hge, 7);
    c[23] = new Card(hge, 7);


    // Cards with Values of 8
    c[24] = new Card(hge, 8);
    c[25] = new Card(hge, 8);
    c[26] = new Card(hge, 8);
    c[27] = new Card(hge, 8);


    // Cards with Values of 9
    c[28] = new Card(hge, 9);
    c[29] = new Card(hge, 9);
    c[30] = new Card(hge, 9);
    c[31] = new Card(hge, 9);


    // Cards with Values of 10
    c[32] = new Card(hge, 10);
    c[33] = new Card(hge, 10);
    c[34] = new Card(hge, 10);
    c[35] = new Card(hge, 10);

    /*  FACE CARDS  */


    // Cards with Values of 10 (Jacks)
    c[36] = new Card(hge, 10);
    c[37] = new Card(hge, 10);
    c[38] = new Card(hge, 10);
    c[39] = new Card(hge, 10);


    // Cards with Values of 10 (Queens)
    c[40] = new Card(hge, 10);
    c[41] = new Card(hge, 10);
    c[42] = new Card(hge, 10);
    c[43] = new Card(hge, 10);


    // Cards with Values of 10 (Kings)
    c[44] = new Card(hge, 10);
    c[45] = new Card(hge, 10);
    c[46] = new Card(hge, 10);
    c[47] = new Card(hge, 10);


    // Cards with Values of 11/1 (Aces)
    c[48] = new Card(hge, 11);
    c[49] = new Card(hge, 11);
    c[50] = new Card(hge, 11);
    c[51] = new Card(hge, 11);

    // Load Textures

    // 2's
    std::cout<<"Loading cards two's"<<std::endl;
    c[0]->LoadTexture("Textures\\Cards\\2_of_clubs.png");
    c[1]->LoadTexture("Textures\\Cards\\2_of_diamonds.png");
    c[2]->LoadTexture("Textures\\Cards\\2_of_hearts.png");
    c[3]->LoadTexture("Textures\\Cards\\2_of_spades.png");

    // 3's
    std::cout<<"Loading cards three's"<<std::endl;
    c[4]->LoadTexture("Textures\\Cards\\3_of_clubs.png");
    c[5]->LoadTexture("Textures\\Cards\\3_of_diamonds.png");
    c[6]->LoadTexture("Textures\\Cards\\3_of_hearts.png");
    c[7]->LoadTexture("Textures\\Cards\\3_of_spades.png");

    // 4's
    std::cout<<"Loading cards four's"<<std::endl;
    c[8]->LoadTexture("Textures\\Cards\\4_of_clubs.png");
    c[9]->LoadTexture("Textures\\Cards\\4_of_diamonds.png");
    c[10]->LoadTexture("Textures\\Cards\\4_of_hearts.png");
    c[11]->LoadTexture("Textures\\Cards\\4_of_spades.png");

    // 5's
    std::cout<<"Loading cards five's"<<std::endl;
    c[12]->LoadTexture("Textures\\Cards\\5_of_clubs.png");
    c[13]->LoadTexture("Textures\\Cards\\5_of_diamonds.png");
    c[14]->LoadTexture("Textures\\Cards\\5_of_hearts.png");
    c[15]->LoadTexture("Textures\\Cards\\5_of_spades.png");

    // 6's
    std::cout<<"Loading cards six's"<<std::endl;
    c[16]->LoadTexture("Textures\\Cards\\6_of_clubs.png");
    c[17]->LoadTexture("Textures\\Cards\\6_of_diamonds.png");
    c[18]->LoadTexture("Textures\\Cards\\6_of_hearts.png");
    c[19]->LoadTexture("Textures\\Cards\\6_of_spades.png");

    // 7's
    std::cout<<"Loading cards seven's"<<std::endl;
    c[20]->LoadTexture("Textures\\Cards\\7_of_clubs.png");
    c[21]->LoadTexture("Textures\\Cards\\7_of_diamonds.png");
    c[22]->LoadTexture("Textures\\Cards\\7_of_hearts.png");
    c[23]->LoadTexture("Textures\\Cards\\7_of_spades.png");

    // 8's
    std::cout<<"Loading cards eight's"<<std::endl;
    c[24]->LoadTexture("Textures\\Cards\\8_of_clubs.png");
    c[25]->LoadTexture("Textures\\Cards\\8_of_diamonds.png");
    c[26]->LoadTexture("Textures\\Cards\\8_of_hearts.png");
    c[27]->LoadTexture("Textures\\Cards\\8_of_spades.png");

    // 9's
    std::cout<<"Loading cards nine's"<<std::endl;
    c[28]->LoadTexture("Textures\\Cards\\9_of_clubs.png");
    c[29]->LoadTexture("Textures\\Cards\\9_of_diamonds.png");
    c[30]->LoadTexture("Textures\\Cards\\9_of_hearts.png");
    c[31]->LoadTexture("Textures\\Cards\\9_of_spades.png");

    // 10's
    std::cout<<"Loading cards ten's"<<std::endl;
    c[32]->LoadTexture("Textures\\Cards\\10_of_clubs.png");
    c[33]->LoadTexture("Textures\\Cards\\10_of_diamonds.png");
    c[34]->LoadTexture("Textures\\Cards\\10_of_hearts.png");
    c[35]->LoadTexture("Textures\\Cards\\10_of_spades.png");

    /*  FACE CARDS  */

    // Jacks
    std::cout<<"Loading cards jack's"<<std::endl;
    c[36]->LoadTexture("Textures\\Cards\\jack_of_clubs2.png");
    c[37]->LoadTexture("Textures\\Cards\\jack_of_diamonds2.png");
    c[38]->LoadTexture("Textures\\Cards\\jack_of_hearts2.png");
    c[39]->LoadTexture("Textures\\Cards\\jack_of_spades2.png");

    // Queens
    std::cout<<"Loading cards queen's"<<std::endl;
    c[40]->LoadTexture("Textures\\Cards\\queen_of_clubs2.png");
    c[41]->LoadTexture("Textures\\Cards\\queen_of_diamonds2.png");
    c[42]->LoadTexture("Textures\\Cards\\queen_of_hearts2.png");
    c[43]->LoadTexture("Textures\\Cards\\queen_of_spades2.png");

    // Kings
    std::cout<<"Loading cards king's"<<std::endl;
    c[44]->LoadTexture("Textures\\Cards\\king_of_clubs2.png");
    c[45]->LoadTexture("Textures\\Cards\\king_of_diamonds2.png");
    c[46]->LoadTexture("Textures\\Cards\\king_of_hearts2.png");
    c[47]->LoadTexture("Textures\\Cards\\king_of_spades2.png");

    // Aces
    std::cout<<"Loading cards ace's"<<std::endl;
    c[48]->LoadTexture("Textures\\Cards\\ace_of_clubs.png");
    c[49]->LoadTexture("Textures\\Cards\\ace_of_diamonds.png");
    c[50]->LoadTexture("Textures\\Cards\\ace_of_hearts.png");
    c[51]->LoadTexture("Textures\\Cards\\ace_of_spades2.png");
}


void ResetCardTextures(){
    c[DealerFirstCardID]->SetDefaultTexture();
}

void Sound_FlipCard(){
    hge->Effect_Play(flipsound);
}

// Toggle any bool on or off
void ToggleBool(bool &b){
    if(b){
        b = false;
    }else{
        b = true;
    }
}


// This function renders the dev statistics to screen if enabled
void RenderStats(bool render){
    if(render){
        //display stats on screen
        text->printf(5, 5, HGETEXT_LEFT, "FPS:%d\nDealerScore: %d\nPlayerScore: %d\nTime playing: %.2f\nMouseX: %d, MouseY: %d\nGame Status: %d\nHelp: %d", hge->Timer_GetFPS(), DealerScore, PlayerScore, hge->Timer_GetTime(), (int)mouseX, (int)mouseY, Gamestatus, helpbool);
    }else{
        //render nothing
    }

    if(Gamestatus == 0){
        text->printf(200, 45, HGETEXT_LEFT, "Dealer(%d)", DealerWins);
        text->printf(10, 470, HGETEXT_LEFT, "Player(%d)", PlayerWins);
        text->printf(1000, 600, HGETEXT_RIGHT, "Controls");
    }

    text->printf(1020,5,  HGETEXT_RIGHT, "Press H for help.");
    text->printf(5, 740, HGETEXT_LEFT, "Your Cards: %d", PlayerScore);
}

void RenderHelp(bool render){
    //Help requested, render it
    if(render){
        text->printf(1020, 80, HGETEXT_RIGHT, "Press ESC to Exit\nProjekt Blackjack kreiran za LV\nPress F12 for various Developer info\nCheck Credits.txt for Credits");
    }else{

    }
}

void RenderCards(){
    // Render Dealer's Cards
    for(it=Dealer.begin(); it!=Dealer.end(); it++)
        {
           (*it)->RenderCard();
        }

    // Render Player's Cards
    for(it=Player.begin(); it!=Player.end(); it++)
        {
           (*it)->RenderCard();
        }
}

void RenderButtons(){
    HitMe->RenderButton();
    Stand->RenderButton();
    ExitGame->RenderButton();
}

void SendMouseCordsToButtons(){
    HitMe->MouseIn(mouseX, mouseY);
    HitMe->MouseOut(mouseX, mouseY);
    Stand->MouseIn(mouseX, mouseY);
    Stand->MouseOut(mouseX, mouseY);
    ExitGame->MouseIn(mouseX, mouseY);
    ExitGame->MouseOut(mouseX, mouseY);
}

void CheckForDealerBust(){
    if(DealerScore > 21){
        //Aces check
        for(it=Dealer.begin(); it!=Dealer.end(); it++)
        {
            if((*it)->GetValue() == 11){
                (*it)->SetValue(1);
                DealerScore -= 10;
                // Do not trigger end game screen, return.
                return;
            }
        }
        // WIN, END THE ROUND
        s_endgame->SetTexture(winTexture);
        Gamestatus = 1;
        PlayerWins++;
        playerWonPrevious = true;
        ResetCardTextures();
    }
}

void CheckForPlayerBust(){
    if(PlayerScore > 21){
        //Aces check
        for(it=Player.begin(); it!=Player.end(); it++)
        {
            if((*it)->GetValue() == 11){
                (*it)->SetValue(1);
                PlayerScore -= 10;
                // Do not trigger end game screen, return.
                return;
            }
        }
        // LOSE, END THE ROUND
        s_endgame->SetTexture(loseTexture);
        Gamestatus = 2;
        DealerWins++;
        ResetCardTextures();
    }
}

void SetAcesToDefault(){
    c[48]->SetValue(11);
    c[49]->SetValue(11);
    c[50]->SetValue(11);
    c[51]->SetValue(11);
}

// This should occur  when the player clicks Hit Me button
void PlayerDrawCard(){
    bool same;
    int  randm;

        same = true;
        while(same){
            same = false;
            randm = hge->Random_Int(0,51);
            std::cout<<"Drawn int: "<<randm<<std::endl;

            for(int i=0 ; i<(int)Dcards.size() ; i++)
            {
                if(Dcards[i] == randm)
                {
                    std::cout<<"Duplicate hit, going again: "<<Dcards[i]<<std::endl;
                    same = true;
                }
            }
        }

        std::cout<<"Passed the check"<<std::endl;
        Dcards.push_back(randm);
        std::cout<<"Player's new card: "<<randm<<std::endl;
        Player.push_back(c[randm]);

        // Set  up  the values are card location
        PlayerScore += c[randm]->GetValue();
        c[randm]->SetLocation(FirstCardLocation);
        FirstCardLocation.x += 150;

        CheckForPlayerBust();

}

// This should be called when the player ends his turns, BUT when  he doesn't bust.
// This is the part of the Dealer AI.
void DealerDrawCard(){
    bool same;
    int  randm;

    same = true;
        while(same){
            same = false;
            randm = hge->Random_Int(0,51);
            std::cout<<"Drawn int: "<<randm<<std::endl;

            for(int i=0 ; i<(int)Dcards.size() ; i++)
            {
                if(Dcards[i] == randm)
                {
                    std::cout<<"Duplicate hit, going again: "<<Dcards[i]<<std::endl;
                    same = true;
                }
            }
        }

        std::cout<<"Passed the check"<<std::endl;
        Dcards.push_back(randm);
        std::cout<<"Dealer's new card: "<<randm<<std::endl;
        Dealer.push_back(c[randm]);

        // Set  up  the values are card location
        DealerScore += c[randm]->GetValue();
        c[randm]->SetLocation(FirstCardLocationDealer);
        FirstCardLocationDealer.x += 150;

        CheckForDealerBust();
}

void RoundStart(){
        Gamestatus = 0;
        // Clear the Player and Dealer lists as well as drawncards vector
        Dealer.clear();
        Player.clear();
        Dcards.clear();

        // Set all of the starting variables
        FirstCardLocation.x = 10;
        FirstCardLocation.y = 500;
        FirstCardLocationDealer.x = 200;
        FirstCardLocationDealer.y = 80;
        SetAcesToDefault();

        DealerScore = 0;
        PlayerScore = 0;
        Gamestatus = 0;

        if(playerWonPrevious){
            PlayerWins--;
        }
        playerWonPrevious = false;

        bool same;

        // Draw first card - that's the dealer's first one
        int randm;
        randm = hge->Random_Int(0,51);
        Dcards.push_back(randm);
        Dealer.push_back(c[randm]);
        std::cout<<"Dealer's first card: "<<randm<<std::endl;

        // Set dealer's first card id so the card's texture can be changed back later
        DealerFirstCardID = randm;
        // Hide dealer's first card
        c[DealerFirstCardID]->SetTexture(CardBackTexture);


        // Deal second card to the dealer
        same = true;
        while(same){
            same = false;
            randm = hge->Random_Int(0,51);
            std::cout<<"Drawn int: "<<randm<<std::endl;

            for(int i=0 ; i<(int)Dcards.size() ; i++)
            {
                if(Dcards[i] == randm)
                {
                    std::cout<<"Duplicate hit, going again: "<<Dcards[i]<<std::endl;
                    same = true;
                }
            }
        }

        std::cout<<"Passed the check"<<std::endl;
        Dcards.push_back(randm);
        std::cout<<"Dealer's second card: "<<randm<<std::endl;
        Dealer.push_back(c[randm]);

        // Set Cards Locations and Add up the values for the dealer
        for(it=Dealer.begin(); it!=Dealer.end(); it++)
        {
           DealerScore += (*it)->GetValue();
           (*it)->SetLocation(FirstCardLocationDealer);
           FirstCardLocationDealer.x += 150;
        }


        // Deal 2 Cards to the player
        same = true;
        while(same){
            same = false;
            randm = hge->Random_Int(0,51);
            std::cout<<"Drawn int: "<<randm<<std::endl;

            for(int i=0 ; i<(int)Dcards.size() ; i++)
            {
                if(Dcards[i] == randm)
                {
                    std::cout<<"Duplicate hit, going again: "<<Dcards[i]<<std::endl;
                    same = true;
                }
            }
        }

        std::cout<<"Passed the check"<<std::endl;
        Dcards.push_back(randm);
        std::cout<<"Player's first card: "<<randm<<std::endl;
        Player.push_back(c[randm]);

        // Second card for the player
        same = true;
        while(same){
            same = false;
            randm = hge->Random_Int(0,51);
            std::cout<<"Drawn int: "<<randm<<std::endl;

            for(int i=0 ; i<(int)Dcards.size() ; i++)
            {
                if(Dcards[i] == randm)
                {
                    std::cout<<"Duplicate hit, going again: "<<Dcards[i]<<std::endl;
                    same = true;
                }
            }
        }

        std::cout<<"Passed the check"<<std::endl;
        Dcards.push_back(randm);
        std::cout<<"Player's second card: "<<randm<<std::endl;
        Player.push_back(c[randm]);

        // Set Cards Locations and Add up the values for the player
        for(it=Player.begin(); it!=Player.end(); it++)
        {
           PlayerScore += (*it)->GetValue();
           (*it)->SetLocation(FirstCardLocation);
           FirstCardLocation.x += 150;
        }

        Sound_FlipCard();
}

void DealerStand(){
    if(DealerScore > 21){
        s_endgame->SetTexture(winTexture);
        Gamestatus = 1;
        PlayerWins++;
        playerWonPrevious = true;
        ResetCardTextures();
        return;
    }
    if(DealerScore > PlayerScore){
        s_endgame->SetTexture(loseTexture);
        Gamestatus = 2;
        DealerWins++;
        ResetCardTextures();
    }else{
        s_endgame->SetTexture(winTexture);
        Gamestatus = 1;
        PlayerWins++;
        playerWonPrevious = true;
        ResetCardTextures();
    }
}

/*  DEALER AI   */
void DealerPlay(){
    while(DealerScore <= PlayerScore){
        DealerDrawCard();
    }
    DealerStand();
}

/* Buttons presses  */
void Hit_Me(){
    std::cout<<"You pressed Hit Me!"<<std::endl;
    Sound_FlipCard();
    PlayerDrawCard();
}

void Stand_Down(){
    std::cout<<"You pressed Stand!"<<std::endl;
    // Do dealer logic
    DealerPlay();
}

void Exit_Game(){
    quitgame = true;
}

bool FrameFunc()
{
	// Process keys for movement and ESC to stop the game
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;

	if(quitgame) return true;

	// Toggle FPS Display / Dev Stats
	if(hge->Input_KeyDown(HGEK_F12)){
        ToggleBool(devstats);
	}

	if(hge->Input_KeyDown(HGEK_H)){
        ToggleBool(helpbool);
	}

    hge->Input_GetMousePos(&mouseX, &mouseY);
    SendMouseCordsToButtons();

    // Gamestatus 0 means the game is in progress and Left click is used for
    // button clicks, ELSE happens when the round is over
    // and left click will restart the game.
    if(Gamestatus == 0){
            if(hge->Input_KeyDown(HGEK_LBUTTON)){
                if(HitMe->GetState()){
                    Hit_Me();
                }else if(Stand->GetState()){
                    Stand_Down();
                }else if(ExitGame->GetState()){
                    Exit_Game();
                }else{
                    // Do nothing, player didn't click a button
                }
        }
    }else{
        if(hge->Input_KeyDown(HGEK_LBUTTON)){
            // Start a new Game
            RoundStart();
        }
    }


	// Continue execution
	return false;
}

void RenderEndGame(){
    s_endgame->Render(256, 192);
    text->printf(255, 455, HGETEXT_LEFT, "Dealer had: %d", DealerScore);
}

// This function will be called by HGE when
// the application window should be redrawn.
// Put your rendering code here.
bool RenderFunc()
{
	// This function must be called
	// before any actual rendering.
	hge->Gfx_BeginScene();

	// Clear screen with black color
	hge->Gfx_Clear(0);

    // Render Background and stats first
    s_background->Render(0, 0);
    RenderHelp(helpbool);

    if(Gamestatus == 0){
        RenderCards();
        RenderButtons();
    }else if(Gamestatus == 1 || Gamestatus == 2){
        RenderEndGame();
    }
    RenderStats(devstats);

	// End rendering and update the screen
	hge->Gfx_EndScene();

	// RenderFunc should always return false
	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Get HGE interface
	hge = hgeCreate(HGE_VERSION);

	// Set up log file, frame function, render function and window title
	hge->System_SetState(HGE_LOGFILE, "hge-blackjack-log.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "BlackJack Card Game");
	hge->System_SetState(HGE_HIDEMOUSE, false);

	// Set up video mode
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 1024);
	hge->System_SetState(HGE_SCREENHEIGHT, 768);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_FPS, 62);

	// Load icon
    hge->System_SetState(HGE_ICON, MAKEINTRESOURCE(1337));

	if(hge->System_Initiate())
	{
	    /* BEGIN LOADING ASSETS */

		// Load sounds and textures
        background = hge->Texture_Load("Textures\\background.png");
        std::cout<<"Loading: "<<"Textures\\background.png"<<std::endl;
        winTexture = hge->Texture_Load("Textures\\you_win.png");
        std::cout<<"Loading: "<<"Textures\\you_win.png"<<std::endl;
        loseTexture = hge->Texture_Load("Textures\\you_lose.png");
        std::cout<<"Loading: "<<"Textures\\you_lose.png"<<std::endl;
        CardBackTexture = hge->Texture_Load("Textures\\Cards\\back_black.png");
        std::cout<<"Loading: "<<"Textures\\Cards\\back_black.png"<<std::endl;
        flipsound = hge->Effect_Load("Sounds\\flipcard.wav");


        // Buttons
        HitMeLoc.x = 890;
        HitMeLoc.y = 630;
        HitMe = new Button(hge, HitMeLoc, "Textures\\Buttons\\Hit_Me.png", "Textures\\Buttons\\Hit_Me_enter.png", 1);

        StandLoc.x = 890;
        StandLoc.y = 680;
        Stand = new Button(hge, StandLoc, "Textures\\Buttons\\Stand.png", "Textures\\Buttons\\Stand_enter.png", 2);

        ExitGameLoc.x = 890;
        ExitGameLoc.y = 730;
        ExitGame = new Button(hge, ExitGameLoc, "Textures\\Buttons\\Exit.png", "Textures\\Buttons\\Exit_enter.png", 3);


        // Load Font
        text = new hgeFont("Fonts\\font1.fnt");
        s_background = new hgeSprite(background, 0,0, 1024, 768);
        s_endgame = new hgeSprite(0, 0, 0, 512, 256);

        // Music
        song = hge->Stream_Load("Sounds\\Music\\the_elevator_bossanova.mp3");
        std::cout<<"Loading: "<<"Sounds\\Music\\the_elevator_bossanova.mp3"<<std::endl;

        // Load Cards (Takes the longest)
        InitiateDeck();

        // End of Loading

        // Play background song
        hge->Stream_Play(song, true, 20);

        RoundStart();

        if(!background){

            MessageBox(NULL, "Can't load something! Please check files", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
        }

		// Let's rock now!
		hge->System_Start();

        //Start releasing resources
		hge->Texture_Free(background);
		hge->Texture_Free(winTexture);
		hge->Texture_Free(loseTexture);
		hge->Texture_Free(CardBackTexture);
		hge->Effect_Free(flipsound);
		hge->Stream_Free(song);
		delete s_background;
		delete s_endgame;
		delete text;
		HitMe->~Button();
		Stand->~Button();
		ExitGame->~Button();

        // Release all cards from memory
		for(int i=0;i<52;i++){
            c[i]->~Card();
		}

	}
	else MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();

	return 0;
}
