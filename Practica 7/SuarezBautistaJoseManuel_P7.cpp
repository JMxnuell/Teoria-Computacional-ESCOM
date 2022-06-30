#include <bits/stdc++.h>
using namespace std;

//Palíndromos binarios
//Suarez Bautista Jose Manuel
//4CM2
//Teoria computacional
/*
	(1) P -> e
	(2) P -> 0
	(3) P -> 1
	(4) P -> 0P0
	(5) P -> 1P1

*/
//Condiciones
//1. Salida a un txt especificando reglas seleccionadas y mostrando cadena generada
//2. Longitud no mayor a 100k
//3.Definir longitud manual/aleatorio

//Hint:
/*
	Se tiene que verificar si la longitud restante es par o impar:
	1. Si el resto es par, se procede a procesar la regla 4 o 5
	2. Si el resto es impar, se procede a procesar la regla 2 o 3
	3. Si el resto es 0, se procesa la regla 1.
*/

void generaPal(int &l){

	FILE *ptr;
	string pal, izq, der;
	pal = izq = der = "";
	ptr = fopen("palindromos.txt","a");
	fprintf(ptr, "\t%s: %d\n","Palindromo aleatorio de longitud",l);
	printf("\t%s: %d\n","Palindromo aleatorio de longitud",l);
	// rand: si 0, se escogen reglas de 0, si 1 se escogen reglas de 1.
	int r;
	int tpar = l/2;
	int res = l%2;
	int i;
	for(i = 1; i<=tpar; i++){
			r = rand()%2;
			if(r){ //reglas de 1
				fprintf(ptr, "\t%d. P -> 1P1: ",i);
				//printf("\t%d. P -> 1P1: ",i);
				izq += "1";
				der = "1" + der;
				pal = izq + "P" + der;
			}else{
				fprintf(ptr, "\t%d. P -> 0P0: ",i);
				//printf("\t%d. P -> 0P0: ",i);
				izq += "0";
				der = "0" + der;
				pal = izq + "P" + der;
			}
		fprintf(ptr, "%s\n",pal.c_str());
	//	cout << pal << endl;
	}
	if(!res){ // No hay mas por procesar
		fprintf(ptr, "\t%d. P -> e: ",i);
	//	printf("\t%d. P -> e: ",i);
		pal = izq + "e" + der;
	}else{ //impar
		r = rand()%2;
		if(r){ //reglas de 1
			fprintf(ptr, "\t%d. P -> 1: ",i);
		//	printf("\t%d. P -> 1: ",i);
			pal = izq + "1" + der;
		}else{
			fprintf(ptr, "\t%d. P -> 0: ",i);
		//	printf("\t%d. P -> 0: ",i);
			pal = izq + "0" + der;
		}
	}
	fprintf(ptr, "%s\n",pal.c_str());
	cout << "El palindromo se ha generado con exito y se ha almacenado en palindromos.txt" << endl;

	fclose(ptr);
}
void generarAleatorio(){
	int l;
	l = rand()%100001; //rango de 0 a 100,000
	generaPal(l);
}

void readInput(){
	int l;
	cout << "\n\tIngresa la longitud de la cadena (no menor a 0, no mayor a 100,000): ";
	cin >> l;
	if(l >= 0 and l <= 100000)
		generaPal(l);
	else
		cout << "\n\tPor favor ingrese una longitud dentro del rango";
}
int main(int argc, char const *argv[]){

	srand(time(NULL));
	int opc;
	do{
		cout << "\n\tConstruccion de palindromos de un lenguaje binario\n" <<endl << endl;
		cout << "\n\t[1] Definir longitud del palindromo de forma manual| "
			 << "[2]  Definir longitud del palindromo de forma aleatoria| "
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