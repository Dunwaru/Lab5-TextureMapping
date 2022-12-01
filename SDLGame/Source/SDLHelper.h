#pragma once
#include "SDL.h"
#include <string>
#include "Objects/GameObject2D.h"

class SDLHelper
{
public:
	struct Colour
	{
		int r;
		int g;
		int b;
	};

	// should be called only once on boot.
	static bool Init();

	static void DisplaySplashScreen();
	// needs to be called once at the start and end of game loops rendering
	static void StartFrame();
	static void EndFrame();

	//SDL drawing specific functions
	static void SetColor(Colour color);
	static void DrawText(const char* text, float x, float y, int width, int height, Colour color);
	static void DrawLoadingText(int dotMod);
	static void SwapSplash(Uint32 delay, GameObject2D screen);

	static SDL_Window* GetWindow() { return window; }

private:
	// some SDL specific variables:
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static SDL_GLContext context;
};

