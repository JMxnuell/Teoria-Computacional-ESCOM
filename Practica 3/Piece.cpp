#include "Piece.h"
#include "Window.h"
SDL_Texture* Piece::blackKingTexture;


uint8_t Piece::black;
uint8_t Piece::king;


void Piece::init() {
	loadImages();
	loadTypes();
}


void Piece::loadImages() {
	SDL_Surface* surface;
	surface = IMG_Load("images/blackKing.png");
	blackKingTexture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	SDL_FreeSurface(surface);
}

void Piece::destroyImages() {
	SDL_DestroyTexture(blackKingTexture);

}


void Piece::loadTypes() {
	//first 3 bits for type
	king = 32;
	black = 128;

}