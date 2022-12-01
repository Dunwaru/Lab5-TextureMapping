#include "SDLHelper.h"
#include <SDL_ttf.h>
#include "Objects/GameObject2D.h"
#include "ShaderManager.h"

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"

#include <iostream>

SDL_Window* SDLHelper::window;
SDL_Renderer* SDLHelper::renderer;
SDL_GLContext SDLHelper::context;

bool SDLHelper::Init()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	// create little window with minimize and x to close 
	window = SDL_CreateWindow("Basic SDL Project",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL);

	if (!window)
	{
		cout << "error creating the window" << endl;
		return false;
	}

	// fill in that window with a virtual canvas to draw on called a renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		cout << "error creating the renderer" << endl;
		return false;
	}

	context = SDL_GL_CreateContext(window);
	if (!context)
	{
		cout << "error creating the context" << endl;
		return false;
	}

	glewInit();
	ShaderManager::GetInstance()->Startup();

	TTF_Init();

	return true;
}
// example based on the code from: https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
void SDLHelper::DrawText(const char* text, float x, float y, int width, int height, Colour color)
{
	TTF_Font* font = TTF_OpenFont("arialbd.ttf", 24);

	SDL_Color Red = { color.r*255, color.g * 255, color.b * 255 };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, Red);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect;
	Message_rect.x = (int)x;
	Message_rect.y = (int)y;
	Message_rect.w = width;
	Message_rect.h = height;

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void SDLHelper::DisplaySplashScreen()
{
	// this object is defined inside the GameObject2D file.
	GameObject2D SplashScreen;
	// this object is defined inside the GameObject2D file.
	SplashScreen.Init("Data\\Art\\SplashScreen.bmp", renderer);

	// Draw a black background
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	// Draw a black background
	for (int i = 0; i < 20;i++)
	{
		StartFrame();
		SplashScreen.Draw(window, renderer);
		DrawLoadingText(i);
		EndFrame();
	}

	SDL_Delay(100);
}

void SDLHelper::SwapSplash(Uint32 delay, GameObject2D screen)
{
	SDL_RenderClear(renderer);
	screen.Draw(window, renderer);

	// Update the screen!
	SDL_RenderPresent(renderer);
	SDL_Delay(delay);
}

void SDLHelper::DrawLoadingText(int dotMod)
{
	Colour TextColor;
	TextColor.b = 0.0f;

	if (dotMod % 2 == 0)
	{
		TextColor.r = 1.0f;
		TextColor.g = 0.0f;
	}
	else
	{
		TextColor.r = 0.0f;
		TextColor.g = 1.0f;
	}

	string output = "Loading";

	for (int dotCounter = 0; dotCounter < dotMod % 4; dotCounter++)
	{

		output += '.';
	}

	DrawText(output.c_str(), 10, 10, 100 + ((dotMod % 4) * 7), 20, TextColor);
	SDL_Delay(100);

}

void SDLHelper::SetColor(Colour color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
}

void SDLHelper::StartFrame()
{
	// pause to control framerate
	SDL_Delay(3);

	SDL_SetRenderDrawColor(renderer, 0x01, 0x01, 0x01, 0xFF);
	SDL_RenderClear(renderer);
}

void SDLHelper::EndFrame()
{
	// Update the screen!
	SDL_RenderPresent(renderer);
}