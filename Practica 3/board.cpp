#include "board.h"
#include "Game.h"
#include "window.h"
#include "Piece.h"
#include <iostream>
#include <Windows.h>
using namespace std;



int Board::boxXWidth;
int Board::boxYWidth;
int Board::boardXBoxes;
int Board::boardYBoxes;

Board::~Board() {
	Piece::destroyImages();
}
void Board::render(int i, int j){
	renderBoard();
	if(i != -1 and j != -1)
	renderPieceTexture(Piece::blackKingTexture, i, j);
	//renderPieces();
	//if(i != -1 and j != -1)
	//	renderMove(i, j);
}

void Board::renderMove(int i, int j){
	int w, h;
	SDL_QueryTexture(Piece::blackKingTexture, NULL, NULL, &w, &h);
	SDL_Rect fromRect, toRect;
	fromRect.w = w;
	fromRect.h = h;
	fromRect.x = fromRect.y = 0;
	toRect.w = Game::boardTopLeftX + i * boxXWidth;
	toRect.h = Game::boardTopLeftY + j * boxYWidth;

	toRect.x = (i - (w / 2));
	toRect.y = (j - (h / 2));

	SDL_RenderCopy(Window::renderer, Piece::blackKingTexture, &fromRect, &toRect);
}
void Board::renderBoard() {
	SDL_Rect drawRect;
	drawRect.w = boxXWidth;
	drawRect.h = boxYWidth;
	
	for (int x = 0; x < boardXBoxes; ++x) {
		for (int y = 0; y < boardYBoxes; ++y) {
			SDL_Color currentColor = (x + y) % 2 == 0 ? boardColor2 : boardColor1;
			drawRect.x = Game::boardTopLeftX + x * boxXWidth;
			drawRect.y = Game::boardTopLeftY + y * boxYWidth;

			SDL_SetRenderDrawColor(Window::renderer, currentColor.r,currentColor.g, currentColor.b, currentColor.a);
			SDL_RenderFillRect(Window::renderer, &drawRect);
		}
	}

}

void Board::renderPieces() {
	for (int x = 0; x < boardXBoxes; ++x) {
		for (int y = 0; y < boardYBoxes; ++y) {
			if (board[x][y] != 0)
				renderPiece(x, y);
		}
	}
}

void Board::renderPiece(int x, int y) {
	unsigned int  currentPlace = board[x][y];
	if (currentPlace ==  Piece::king) {
		renderPieceTexture(Piece::blackKingTexture, x, y);
	}
}

void Board::renderPieceTexture(SDL_Texture* texture, int x, int y) {
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_Rect fromRect, toRect;
	fromRect.w = w;
	fromRect.h = h;
	fromRect.x = fromRect.y = 0;

	toRect.x = Game::boardTopLeftX + x * boxXWidth;
	toRect.y = Game::boardTopLeftY + y * boxYWidth;
	toRect.w = boxXWidth;
	toRect.h = boxYWidth;

	SDL_RenderCopy(Window::renderer, texture, &fromRect, &toRect);
}

void Board::update() {

}
void Board::init(int tamTab, int i, int j) {
	Piece::init();
	boardXBoxes = tamTab;
	boardYBoxes = tamTab;
	boxXWidth = Window::screenWidth / boardXBoxes;
	boxYWidth = Window::screenHeight / boardYBoxes;

	boardColor1 = { 184,15,10,255 };
	boardColor2 = { 0,0,0,255 };

	board = new uint8_t * [boardXBoxes];
	for (int i = 0; i < boardXBoxes; ++i) {
		board[i] = new uint8_t[boardYBoxes];
	}
	for (int x = 0; x < boardXBoxes; ++x) {
		for (int y = 0; y < boardYBoxes; ++y) {

			board[x][y] = 0;
		}
	}
	cout << i << " " << j << endl;
	board[i][j] = Piece::king;

	Piece::loadImages();
	Piece::loadTypes();

}

void Board::resize() {
	boxXWidth = Window::screenWidth / boardXBoxes;
	boxYWidth = Window::screenHeight / boardYBoxes;

	if (boxXWidth > boxYWidth) {
		boxXWidth = boxYWidth;
	}
	else {
		boxYWidth = boxXWidth;	
	}
}

int Board::getWidth() {
	return boardXBoxes * boxXWidth;
}

int Board::getHeigth() {
	return boardYBoxes * boxYWidth;
}

void Board::secuenciaa(vector <pair<int,int> > valida,int tamTab){
	int xant, yant;

	xant = yant = 0;
	for (int i = 1; i < 4; i++) {
//		Sleep(1000);
	}
}




