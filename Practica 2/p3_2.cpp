#include <bits/stdc++.h>
#include <Windows.h>

using namespace std;


bool generador();
bool validador();
bool automata(char *cad);

int main(){

	bool estado;
	srand(time(NULL));
	while(estado = rand()%2){ //qActivo (inicial)
		printf("Protocolo encendido\n\n");
		printf("A continuacion se generanan 10000000 cadenas de longitud 64\n");
		printf("y se almacenaran en el archivo cadenas.txt\n");
		if(!generador()){ //Generador.
			printf("A ocurrido un error mientras se enviaban los datos, lo sentimos...\n");
			return 0;
		} 
		//sleep(1); //espera
		printf("Las cadenas se han generado con exito, se procede\n");
		printf("a verificar la paridad.\n\n");
		printf("pares.txt: ACEPTADAS\n");
		printf("impares,txt: NO ACEPTADAS\n\n");
		validador();
		if(!validador()){
			printf("A ocurrido un error mientras se validaban los datos, lo sentimos...\n");
			return 0;
		}
		printf("Validacion generada con exito\n");
	}
	printf("Protocolo apagado\n\n");
	return 0;
}

bool generador(){

	FILE *ptrWrite;
	string cadena;
	cadena = "";
	ptrWrite = fopen("cadenas.txt", "a+" );
	if ( ptrWrite == NULL){
		printf( "\n\nEl archivo no pudo abrirse..\n\n");
		return false;
	}

	for(int i = 0; i < 1e6; i++){
		for(int j = 0; j < 64; j++)
			cadena += '0' + rand()%2;

		fprintf(ptrWrite,"%s\n",cadena.c_str());
		cadena = "";
	}
	fclose(ptrWrite);
	return true;
}

bool validador(){

	FILE *ptrWritePar, *ptrWriteImp, *ptrReadCad;
	char cadena[100];
	 ptrReadCad = fopen("cadenas.txt", "r" );
	 ptrWriteImp = fopen("impar.txt", "w" );
	 ptrWritePar = fopen("pares.txt", "w" ); 
	if ((ptrReadCad == NULL) or ( ptrWritePar == NULL) or (ptrWriteImp == NULL)){
		printf( "\n\nHubo un problema con los archivos..\n\n");
		return false;
	}

	while(fgets(cadena, sizeof(cadena), ptrReadCad)){
		if(automata(cadena))
			fprintf(ptrWritePar,"%s",cadena);
		else
			fprintf(ptrWriteImp,"%s",cadena);

	}
	fclose(ptrWriteImp);
	fclose(ptrWritePar);
	fclose(ptrReadCad);
	return true;
}

bool automata(char *cad){
	int e = 0;
	char c;
	FILE *ptrWriteCamino;
	ptrWriteCamino = fopen("Camino.txt", "a+" );
	fprintf(ptrWriteCamino,"%s: q%d ",cad,e);
	for(int  i = 0; cad[i] != '\0'; i++){
		c = cad[i];
		if(c == '\n')
			continue;
		if(e == 0){
			if(c == '1')
				e = 1;
			else
				e = 2;
		}else if(e == 1){
			if(c == '1')
				e = 0;
			else
				e = 3;
		}else if(e == 3){
			if(c == '1')
				e = 2;
			else
				e = 1;
		}else if(e == 2){
			if(c == '1')
				e = 3;
			else
				e = 0;
		}
		fprintf(ptrWriteCamino,"q%d ",e);
	}
	fprintf(ptrWriteCamino,"\n");
	return e == 0;
}