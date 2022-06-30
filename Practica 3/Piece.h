#pragma once
#include "SDL.h"
#include "SDL_image.h"
class Piece
{

public:
	static void init();
	static void loadImages();
	static void loadTypes();
	static void destroyImages();
	static SDL_Texture* blackKingTexture;
	

	static uint8_t black;
	static uint8_t king;

};

