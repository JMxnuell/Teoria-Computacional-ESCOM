#pragma once
#include "SDL.h"
#include "board.h"

class Game{
private:
	Board * board;

public:

	//Board* board;
	static int boardTopLeftX;
	static int boardTopLeftY;

	void update();
	void render(int i, int j);
	void resize();

	void init(int tamTab);


	//void reset();
	~Game();
};
