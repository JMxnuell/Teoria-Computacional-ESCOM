#include <string>
#include <iostream>
//#include <unistd.h>

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

void inicial() {

	string mov = "";
	string imp;
	int opc; /*
	opc: eleccion del usuario
	*/
	srand(time(NULL));

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
	NFA(mov, eInicial, (int)mov.size(), imp, 'B');
	//	}else
	//		printf("Cadena no valida.\n"); //caso contrario
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

	len = rand() % 101 + 1;

	for (int i = 0; i < len; i++) {
		m = rand() % 2;
		if (m == 0)
			cad += 'B';
		else
			cad += 'R';
	}
}

void NFA(string cad, int eActual, int tam, string imp, char color_eActual) {

	//cout << "color actual: " << color_eActual << endl;
	imp += to_string(eActual);
	imp += " ";
	string aux = "";

	if (tam == 0) {
		if (eActual == tamTablero * tamTablero)
			cout << "Es valido: ";
		else
			cout << "No es valido: ";

		cout << imp << endl << endl;

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

	int eSig;
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
