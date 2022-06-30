#include <bits/stdc++.h>
using namespace std;
//P8
//Gramática no ambiagua
//Suarez Bautista Jose Manuel
//4CM2
//Teoria computacional
/*
B -> (RB | ε
R -> ) | (RR
*/
//Condiciones
//1. La cadena puede ser ingresada por el usuario o generada automáticamente.
//2. Mandar a un archivo y/o en pantalla la evaluación de la gramática imprimiendo el símbolo que está evaluando, indicando que producción se aplicó y la cadena generada.
//3. La longitud máxima será manejar cadenas de 1,000 caracteres.

//Hint:
/*
	1. Expandir B, '(RB' si next "(" y 'e' si es el final
	2. Expandir R, ')' Si next ")" y "(RR" si next '('
*/
void subs(string &cad, string &subizq, string &subder, int current){
	if(current-1 >= 0)
		subizq = cad.substr(0,current);
	if(current + 1 < (int)cad.size())
		subder = cad.substr(current+1,((int)cad.size()));

//	cout << "izq: " << subizq << endl;
//	cout << "der: " << subder << endl;
}
void solve(const string &cad){
	//ILE *ptr;
	//ptr = fopen("Evaluaciones.txt","a");
	//fprintf(ptr, "\tCadena a procesar: %s\n",cad.c_str());
	cout << "\tCadena a procesar: " << cad << endl << endl;
	string actual = "B";
	cout << "\t" << actual << endl;
	for(auto c : cad){

		int current = 0;
		for(auto caux : actual){
			if(caux == 'B' or caux == 'R')
				break;
		current++;
		}
		string subizq, subder;
		subizq = subder = "";
		subs(actual,subizq,subder, current);
		if(actual[current] == 'B'){
			if(c == '('){
				actual = subizq + "(RB" + subder;
				cout << "\tB -> (RB: " << actual << endl;
			}else{
				actual = subizq + "e" + subder;
				cout << "\tB -> e: " << actual << endl;
			}
		}else{
			if(c == ')'){
				actual = subizq + ")" + subder;
				cout << "\tR -> ): " << actual << endl;
			}else{
				actual = subizq + "(RR" + subder;
				cout << "\tR -> (RR: " << actual << endl;
			}
		}
	}
	int current = 0;
	for(auto caux : actual){
		if(caux == 'B')
			break;
		current++;
	}
	actual[current] = 'e';
	cout << "\tB -> e: " << actual << endl;

	//fclose(ptr);
}
void generarAleatorio(){
	
	int r, l;
	l = rand()%1001;
	string cad = "";
	string left('(',l/2);
	string right(')',l/2);
	cad = left + right;
	solve(cad);
}

void readInput(){
	string cad;
	cout << "\n\tIngresa la cadena de '(' y ')' a procesar (menor a 1,000 caracteres): ";
	cin >> cad;

	if((int)cad.size() <= 1000)
		solve(cad);
	else
		cout << "Por favor ingrese una cadena de menor longitud." << endl;
}
int main(int argc, char const *argv[]){

	srand(time(NULL));
	int opc;
	do{
		cout << "\n\tProcesamiento de gramatica no ambigua.\n" <<endl << endl;
		cout << "\tB -> (RB | e\n"
			 << "\tR -> ) | (RR\n\n";
		cout << "\n\t[1] Ingresar la cadena manualmente | "
			 << "[2]  Generar la cadena aleatoriamente | "
			 << "[3]  Salir| "
		 	 << "\n\n\tOpcion: ";
		cin >> opc;
		switch(opc){
			case 1:
				readInput();
				break;
			case 2:
				generarAleatorio();
				break;
			case 3:
				break;
			default:
				cout << "\n\n\tOPCION NO VALIDA";
		}
		cout << "\n\n\tPresione una tecla para continuar...";
		cin.get();
		cin.get();
		system("cls");

	}while(opc != 3);
	return 0;
}