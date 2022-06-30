#include <bits/stdc++.h>
using namespace std;

//expReg: (0+10)*(e+0+1)
//Suarez Bautista Jose Manuel
//4CM2
//Teoria computacional

//Condiciones
//1. Automatico (se usara el azar para parar o continuar)
//2. Cerradura de Kleene, se calcularan los 1000 posibles y se guardaran para uso posterior
//3. Acceder a cada parte de la ecuacion de manera aleatorio:
/*
   5 posibles operaciones:
   [1] Union, [2] Cerradura de Kleene, [3] Concatenacion, [4] Union, [5] Union
   Se deben respetar la prioridad de operadores y parentesis.
*/

vector<string> memCerr = {"e","0","10"};
void calculaKleene(){
	vector<string>cerradura = {"0","10"},cerraduraPotAct,cerraduraPotActCalc;
	cerraduraPotAct = cerradura;
	for(int i = 0; i<10; i++){ // 2^10
		for(auto exp1 : cerradura) 
			for(auto exp2 : cerraduraPotAct){
				cerraduraPotActCalc.push_back(exp1 + exp2);
				memCerr.push_back(exp1 + exp2);
			}
		cerraduraPotAct = cerraduraPotActCalc;
		cerraduraPotActCalc.clear();
	}
	
}
bool operar(const int &opc, string &expRand, const int tOpera){
	FILE *ptr;
	ptr = fopen("seleccion.txt","a");
	if((opc == 3) and tOpera > 1){
		// no se puede hacer esta operacion por precedencia de operadores
		fprintf(ptr, "No es posible hacer la cerradura (0+10)* por la precedencia de operadores\n");
		fclose(ptr);
		return false;
	}
	else if((opc == 2) and tOpera > 2){
	 // no se puede hacer esta operacion por precedencia de operadores
		fprintf(ptr, "No es posible hacer la concatenacion (0+10)*(e+0+1) por la precedencia de operadores\n");
		fclose(ptr);
		return false;
	}

	int r;
	string c;
	switch(opc){
		case 1:
			//poner en txt Union {0,10}
			fprintf(ptr, "Se hace la union (0+10): {0,10}\n");
			break;
		case 2:
			r = rand() % 15;
			//poner en txt cerradura: {0,10}
			fprintf(ptr, "Se hace la cerradura de Kleene({0,10})*: {0,10,00,1010...}\n");
			expRand = memCerr[r];
			break;
		case 3:
			r = rand() % 2;
			if(expRand == "e")
				expRand = c = "epsilon";
			else if(r == 0)
				expRand += "0", c = "0";
			else if(r == 1)
				expRand += "11", c = "11";
			//cout << "se escoge: " << c << "   ";
			fprintf(ptr, "Se hace la concatenacion (0+10)*(e+0+1): ({0,10})*{e,0,1}\n");
			// poner en txt concatenacion {0,10}*{e,0,1}
			break;
		case 4:
			fprintf(ptr, "Se hace la union (e+(0+1)): {e,(0+1)}\n");
			// poner en txt Union {e,(0+1)}
			break;
		case 5:
			fprintf(ptr, "Se hace la union (e+(0+1)): (e+{0,1})\n");
			// poner en txt Union e+{0,1}
			break;
	}
	fclose(ptr);
	return true;
}
void writeExpReg(const string &exp, const int n){
	FILE *ptr;
	ptr = fopen("expresiones.txt","a");
	fprintf(ptr, "\t%d. %s\n",n,exp.c_str());
	fclose(ptr);
}
int main(int argc, char const *argv[]){

	srand(time(NULL));
	calculaKleene();
	int r, opc;
	cout << "Generando de cadenas validas para: (0+10)*(e+0+1)" <<endl << endl;
	do{
			FILE *ptr, *ptr2;
			ptr = fopen("expresiones.txt","a");
			fprintf(ptr, "\tSe generaran 10 cadenas nuevas:\n");
			ptr2 = fopen("seleccion.txt","a");
			fprintf(ptr2, "\tSe mostrara la seleccion de 10 cadenas nuevas:\n");
			cout << "\tSe generaran 10 cadenas nuevas:\n";
			fclose(ptr);
			fclose(ptr2);
		for(int i = 0; i<10; i++){ //generamos las 10 cadenas
			vector<int>operaciones = {1,2,3,4,5}; // 1 = 1er union, 2 = cerradura, 3 =  concatenacion, 4 = 2da union, 5 = 3er union
			string expRand = "";
			ptr = fopen("seleccion.txt","a");
			fprintf(ptr, "\nProceso cadena %d:\n",i+1);
			fclose(ptr);
			while(!operaciones.empty()){ //hasta que las 5 operaciones se terminen de ejecutar
				r = rand()%((int)operaciones.size()); // random para las j posibles operaciones
				opc = operaciones[r];
				if(operar(opc,expRand,(int)operaciones.size())){
					//poner operacion en txt
					auto it = operaciones.begin() + r;
					operaciones.erase(it);
				}
				ptr2 = fopen("seleccion.txt","a");
				fprintf(ptr2, "\n");
				fclose(ptr2);

			}
			cout << i+1 << ": " << expRand << endl;
			writeExpReg(expRand,i+1);
		}
			ptr = fopen("expresiones.txt","a");
			fprintf(ptr, "\n\n");
			fclose(ptr);
			ptr2 = fopen("seleccion.txt","a");
			fprintf(ptr2, "\n\n");
			fclose(ptr2);
			cout << "\n\n";
	}while(rand()%2); // 1 continuar, 0 parar
	return 0;
}