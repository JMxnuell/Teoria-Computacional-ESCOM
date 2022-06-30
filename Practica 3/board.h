#pragma once
#include "SDL.h"
#include <vector>
using namespace std;
class Board{
private:
	SDL_Color boardColor1;
	SDL_Color boardColor2;
	uint8_t** board;
	int T;

public:
	static int boxXWidth;
	static int boxYWidth;
	static int boardXBoxes;
	static int boardYBoxes;

	~Board();
	void secuenciaa(vector<pair<int,int>> valida, int tamTab);
	void update();
	void render(int i, int j);
	void renderMove(int i, int j);
	//void reset();
	void resize();
	void init(int tamTab,int i, int j);
	void renderBoard();

	int getWidth();
	int getHeigth();

	void renderPieces();
	void renderPiece(int x, int y);
	void renderPieceTexture(SDL_Texture*, int x, int y);
};
