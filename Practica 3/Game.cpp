#include "Game.h"
#include "window.h"
int Game::boardTopLeftX;
int Game::boardTopLeftY;

Game::~Game(){
	delete(board);
}

void Game::render(int i, int j) {
	board->render(i,j);
}

void Game::update() {

}

void Game::init(int tamTab) {
	boardTopLeftX = boardTopLeftY = 0;
	board = new Board();
	board->init(tamTab,0,0);
}


void Game::resize() {
	board->resize();
	boardTopLeftX = (Window::screenWidth - board->getWidth()) / 2;
	boardTopLeftY = (Window::screenHeight - board->getHeigth()) / 2;
}

/*
void Game::reset() {
//	board->reset();
}

*/