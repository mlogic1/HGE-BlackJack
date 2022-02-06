#include <hge.h>
#include <hgefont.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <iostream>
#include <list>
#include <vector>

HGE* hge = nullptr;

bool FrameFunc()
{
	return false;
}

// This function will be called by HGE when
// the application window should be redrawn.
// Put your rendering code here.
bool RenderFunc()
{
	// This function must be called
	// before any actual rendering.
	//hge->Gfx_BeginScene();

	// Clear screen with black color
	//hge->Gfx_Clear(0);

	// End rendering and update the screen
	// hge->Gfx_EndScene();

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

	bool error = false;
	if (hge->System_Initiate())
	{
		hge->System_Start();
	}
	else {
		error = true;
	}
		
	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();

	if (error)
		return -1;
	return 0;
}
