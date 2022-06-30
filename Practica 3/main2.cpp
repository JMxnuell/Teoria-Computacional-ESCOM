#include "window.h"
#include "SDL.h"
#include "board.h"
#include <Windows.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <string>
#include <ctime>
#include <vector>
#include <stdio.h>
#pragma warning(disable : 4996)

#if defined(_WIN32) and defined(_MSC_VER)
#include <crtdbg.h>
#endif
#include <iostream>
using namespace std;
int eInicial = 1;
int eFinal;
int tamTablero;
bool valida(string&);
void NFA(string cad, int eActual, int tam, string imp, char color_eActual);
void color_eSig(char color_eActual, int tipo_mov, char& color_nuevo);
void calcula_coordenadas(int eActual, int& i, int& j);
int calcula_eSig(string aDonde, int eActual);
void genera(string&);
void writeV(string cad);
void writeNv(string cad);
vector<vector<int>>simulaciones;
vector<string> infValidas;
int main() {

	srand(time(NULL));
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart = SDL_GetTicks();
	int frameTime = 0;
	Window* gameWindow = new Window;

	float deltaTime;
	string mov = "";
	string imp;
	int opc; /*
	opc: eleccion del usuario
	*/

	printf("\n\nMovimientos en tablero de ajedrez.\n\n");
	cout << "Ingresa el tamanio del tablero: ";
	cin >> tamTablero;
	eFinal = tamTablero;
	printf("[1]Introducir movimientos (B,R)[max 20].\n");
	printf("[2]Determinar movimeintos aleatorioamente (B,R)[max 100].\n");
	cin >> opc;

	switch (opc) {
	case 1:
		printf("\n\nPor favor introduce una cadena de caracteres 'B' y  'R', maximo 20 caracteres:"); //n introducido por el usuario
		cin >> mov;
		break;
	case 2:
		genera(mov); //se genera aleatoriamente
		break;
	default:
		printf("Opcion no valida.\n");
	}
	//if(valida(mov)){ //comprobar valor válido
	cout << "La cadena de movimeintos es: " << mov << endl;
	cout << "Se generaran los posibles caminos.." << endl << endl;
	FILE* fValida;
	fValida = fopen("validos.txt", "w");
	fprintf(fValida, "Movimientos validos para: %s\n",mov.c_str());
	fclose(fValida);
	FILE* fNoValida;
	fNoValida = fopen("noValidos.txt", "w");
	fprintf(fNoValida, "Movimientos no validos para: %s\n", mov.c_str());
	fclose(fNoValida);
	NFA(mov, eInicial, (int)mov.size(), imp, 'B');
	bool aun = true;
	gameWindow->init("AFD ", 800, SDL_WINDOWPOS_CENTERED, false,tamTablero);
	int j, k;
	while (gameWindow->running()) {
		deltaTime = SDL_GetTicks() - frameStart;
		frameStart = SDL_GetTicks();
		gameWindow->handleEvents();
		gameWindow->update(float(deltaTime) / 1000.0);
		gameWindow->render(0,0);
		if (aun) {
			if(!simulaciones.empty()){
			cout << "A continuacion se simularan dos cadenas validas para " << mov <<  "..." << endl << endl;
			Sleep(1000);
			string mensaje2 = "A continuacion se mostraran cadenas validas para: " + mov;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
				"Resultados validos",
				mensaje2.c_str(),
				NULL);
			int r = 0;
			for (vector<int>& s : simulaciones) {
				gameWindow->render(0, 0);
				mensaje2 = "A continuacion se mostrara la simulacion para la cadena: " + infValidas[r++];
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
					"Resultados validos",
					mensaje2.c_str(),
					NULL);
				cout << "Cadena: ";
				for (int& estado : s) {
					cout << estado << " ";
					//if (estado == tamTablero*tamTablero)
						//j = k = tamTablero -1;
				//	else
					calcula_coordenadas(estado, j, k);
					gameWindow->render(k - 1, j - 1);
					Sleep(1000);
				}
				cout << endl << endl;
				gameWindow->render(0, 0);
				Sleep(1500);
				}
			string mensaje = "Cadenas mostradas con exito para: " + mov;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
				"Resultados validos",
				mensaje.c_str(),
				NULL);
			}
			else {
				cout << "No hay cadenas validas" << endl << endl;
				string mensaje = "No es posible llegar al estado final con la cadena: " + mov;
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
					"Sin resultados validos",
					mensaje.c_str(),
					NULL);
			}
			aun = false;
		}

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	gameWindow->clean();
	delete gameWindow;


#if defined(_WIN32) and defined(_MSC_VER)
	_CrtDumpMemoryLeaks(); //can be called only on Windows with MSVC compiler (e.g not mingw)
#endif

	return 0;
}
bool valida(string& cad) {

	if (cad.size() <= 20)
		return false;
	for (auto& c : cad)
		if (!(c == 'B' or c == 'R'))
			return false;

	return true;
}

void genera(string& cad) {

	int len, m;

	len = rand() % 9 + 1;

	for (int i = 0; i < len; i++) {
		m = rand() % 2;
		if (m == 0)
			cad += 'B';
		else
			cad += 'R';
	}
}

void NFA(string cad, int eActual, int tam, string imp, char color_eActual) {

	imp += to_string(eActual);
	imp += " ";
	string aux = "";

	if (tam == 0) {
		if (eActual == tamTablero * tamTablero) {
			cout << "Es valido: " << imp << endl << endl;
			writeV(imp);
			string cadAux = "";
			vector<int> simula;
			for (auto& c : imp) {
				if (c == '\0')
					break;
				if (c == ' ') {
					if (!cadAux.empty())
						simula.push_back(stoi(cadAux));
					cadAux = "";
				}
				else
					cadAux += c;
			}
			if (!cadAux.empty()) {
				simula.push_back(stoi(cadAux));
			}
			if (simulaciones.size() < 2) {
				simulaciones.push_back(simula);
				infValidas.push_back(imp);
			}
		}
		else {
			cout << "No es valido: " << imp << endl << endl;
			writeNv(imp);
		}
			return;
		}

		aux = cad.substr(1, tam - 1);
		//	cout << "aux: " << aux << endl;
		char c = cad[0];
		int i, j;
		calcula_coordenadas(eActual, i, j);
		//cout << "i, j:" << i << ' ' << j << endl << endl;

		//arriba
		char color_nuevo;
		if (i - 1 != 0) {
			color_eSig(color_eActual, 1, color_nuevo);
			if (color_nuevo == c) {
				//	cout << color_nuevo << " " << c << " subo\n\n";
				NFA(aux, calcula_eSig("arriba", eActual), (int)aux.size(), imp, color_nuevo);
			}
		}
		//abajo
		if (i + 1 != tamTablero + 1) {
			//	cout << "entor abajo: " << endl;
			color_eSig(color_eActual, 1, color_nuevo);
			if (color_nuevo == c) {
				//	cout << color_nuevo << " " << c << " bajo\n\n";
				NFA(aux, calcula_eSig("abajo", eActual), (int)aux.size(), imp, color_nuevo);
			}
		}
		//izq
		if (j - 1 != 0) {
			color_eSig(color_eActual, 1, color_nuevo);
			if (color_nuevo == c) {
				//	cout << color_nuevo << " " << c << " izq\n\n";
				NFA(aux, calcula_eSig("izq", eActual), (int)aux.size(), imp, color_nuevo);
			}
		}
		//der
		if (j + 1 != tamTablero + 1) {
			//cout << "entor der: " << endl;
			color_eSig(color_eActual, 1, color_nuevo);
			if (color_nuevo == c) {
				//	cout << color_nuevo << " " << c << " der\n\n";
				NFA(aux, calcula_eSig("der", eActual), (int)aux.size(), imp, color_nuevo);
			}
		}
		//diagonal sup izq
		if (!(j - 1 == 0 or i - 1 == 0)) {
			color_eSig(color_eActual, 2, color_nuevo);
			if (color_nuevo == c) {
				//	cout << color_nuevo << " " << c << " sup izq\n\n";
				NFA(aux, calcula_eSig("sup_izq", eActual), (int)aux.size(), imp, color_nuevo);
			}
		}
		//diagonal inf der
		if (!(j + 1 == tamTablero + 1 or i + 1 == tamTablero + 1)) {
			//	cout << "entro" << endl;
			color_eSig(color_eActual, 2, color_nuevo);
			if (color_nuevo == c) {
				//	cout << color_nuevo << " " << c << " inf der\n\n";
				NFA(aux, calcula_eSig("inf_der", eActual), (int)aux.size(), imp, color_nuevo);
			}
		}
		//diagonal inf izq
		if (!(i + 1 == tamTablero + 1 or j - 1 == 0)) {
			color_eSig(color_eActual, 2, color_nuevo);
			if (color_nuevo == c) {
				//	cout << color_nuevo << " " << c << " inf izq\n\n";
				NFA(aux, calcula_eSig("inf_izq", eActual), (int)aux.size(), imp, color_nuevo);
			}
		}
		//diagonal sup der
		if (!(i - 1 == 0 or j + 1 == tamTablero + 1)) {
			color_eSig(color_eActual, 2, color_nuevo);
			if (color_nuevo == c) {
				//	cout << color_nuevo << " " << c << " sup der\n\n";
				NFA(aux, calcula_eSig("sup_der", eActual), (int)aux.size(), imp, color_nuevo);
			}
		}

}

void color_eSig(char color_eActual, int tipo_mov, char& color_nuevo) {

	if (tipo_mov == 1) {
		if (color_eActual == 'B') {
			color_nuevo = 'R';
		}
		else
			color_nuevo = 'B';
	}
	else {
		if (color_eActual == 'B') {
			//	cout << "regreso B" << endl;
			color_nuevo = 'B';
		}
		else
			color_nuevo = 'R';
	}
}
void calcula_coordenadas(const int eActual, int& i, int& j) {

	j = eActual % tamTablero;
	i = eActual / tamTablero + 1;
	if (!j) {
		j = tamTablero;
		i -= 1;
	}
}

int calcula_eSig(string aDonde, const int eActual) {

	int eSig = 0;
	if (aDonde == "arriba")
		eSig = eActual - tamTablero;
	else if (aDonde == "abajo")
		eSig = eActual + tamTablero;
	else if (aDonde == "der")
		eSig = eActual + 1;
	else if (aDonde == "izq")
		eSig = eActual - 1;
	else if (aDonde == "sup_izq")
		eSig = eActual + (tamTablero * (-1)) - 1;
	else if (aDonde == "inf_der")
		eSig = eActual + tamTablero + 1;
	else if (aDonde == "inf_izq")
		eSig = eActual + tamTablero - 1;
	else if (aDonde == "sup_der")
		eSig = eActual + (tamTablero * (-1)) + 1;

	return eSig;
}

void writeV(string cad) {

	FILE* fValida;
	fValida = fopen("validos.txt", "a+");
	fprintf(fValida, "%s\n",cad.c_str());
	fclose(fValida);
}

void writeNv(string cad) {

	FILE* fNoValida;
	fNoValida = fopen("noValidos.txt", "a+");
	fprintf(fNoValida, "%s\n", cad.c_str());
	fclose(fNoValida);
}
