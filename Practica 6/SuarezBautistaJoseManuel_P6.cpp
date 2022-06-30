#include <bits/stdc++.h>
using namespace std;

//PDA para CFL
//Suarez Bautista Jose Manuel
//4CM2
//Teoria computacional

string contenido(stack<char> &pila){
	if(pila.empty())
		return  "Z0";
	else
		return "X";
}
void PDA(const string &cad){
	FILE *ptr;
	ptr = fopen("Evaluaciones.txt","a");
	stack<char> pila;
	char eActual = 'q';
	fprintf(ptr, "Cadena a procesar: %s\n",cad.c_str());
	cout << "Cadena a procesar: " << cad << endl;
	int current = 0;
	for(auto c : cad){
		printf("(%c,%s,%s..)",eActual,(cad.substr(current,(int)cad.size())).c_str(),contenido(pila).c_str());
		fprintf(ptr,"(%c,%s,%s..)",eActual,(cad.substr(current,(int)cad.size())).c_str(),contenido(pila).c_str());
		current++;
		if(eActual == 'q' and c == '0'){
			pila.push('X');
			cout << "|-\n";
			fprintf(ptr, "|-\n");
		}
		else if((eActual == 'q' or eActual == 'p') and c == '1'){
			eActual = 'p';
			if(!pila.empty()){
			  // si no está vacía
			  pila.pop();
			  cout << "|-\n";
			  fprintf(ptr, "|-\n");
			}
			else
				return;
		}else
			return;
	}
	if(pila.empty()){
		printf("(%c,%s,%s..)|-\n",eActual,"e",contenido(pila).c_str());
		fprintf(ptr,"(%c,%s,%s..)|-\n",eActual,"e",contenido(pila).c_str());
		eActual = 'f';
		printf("(%c,%s,%s..)\n",eActual,"e",contenido(pila).c_str());
		fprintf(ptr,"(%c,%s,%s..)\n",eActual,"e",contenido(pila).c_str());
	}
	fclose(ptr);
}
void generarAleatorio(){
	
	int r, l;
	l = rand()%100001;
	string cad = "";

	for(int i = 0; i<=l; i++)
			cad += to_string(rand()%2);
	
	PDA(cad);
}

void readInput(){
	string cad;
	cout << "\n\tIngresa la cadena de 0s y 1s a procesar : ";
	cin >> cad;
	PDA(cad);
}
int main(int argc, char const *argv[]){

	srand(time(NULL));
	int opc;
	do{
		cout << "\n\tPDA para CFL: {0^n 1^n | n >= 1}.\n" <<endl << endl;
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