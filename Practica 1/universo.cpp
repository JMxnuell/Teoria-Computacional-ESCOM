#include <bits/stdc++.h>
using namespace std;

void sigma_n(const int &n);

int main() {

 	int opc, n; /*
 	opc: eleccion del usuario
 	n: límite de sigma.
 	*/
 	bool bandera; //bandera: saber si ejecutar o no sigma_n()
 	srand(time(NULL));
	do{
		bandera = false;
		printf("\n\nUniverso de cadenas binarias.\n\n");
		printf("[1]Introducir el limite del calculo del universo.\n");
		printf("[2]Determinar aleatorioamente.\n");
		printf("[3]Salir del programa.\n\n");
		cin >> opc;

		switch(opc){
			case 1:
				printf("Introduce un valor entre el rango de [0,1000]:"); //n introducido por el usuario
				cin >> n;
				if(n>=0 and n<=1000)  //comprobar valor válido
					bandera = true;
				else
					printf("Valor fuera de rango.\n"); //caso contrario
				break;
			case 2:
				bandera = true; 
				n = rand()%1001; //n se genera aleatoriamente
				break;
			case 3:
				break;
			default:
				printf("Opcion no valida.\n");
		}
		if(bandera)  //si la opción fue 1 o 2
			sigma_n(n); //generar cadenas

		printf("\n\n");
	}while(opc != 3);
	printf("Salimos del bucle.\n\n");
	return 0;
}

void sigma_n(const int &n){

	string str = ""; // str: variable para generar y almacenar la cadea binaria
	int j,unos, y,x;
	// unos: variable que aumenta los unos en una cadea. y = variable para el número de la cadena
	// j = variable que nos ayuda a invertir el orden de acceso a la cadena y editarla
	y = x = 0;
	FILE *ptrWrite, *ptrWriteUnos; // punteros de archivo, en ptrWrite se escribe la salida de conjuntos
	//ptrWriteUnos se utiliza para escribir 'y' y  'unos' para poder graficar en matlab.
	FILE *fp = NULL;
	FILE * gnupipe = NULL;
	char *GnuCommands [] = {"set title \"recopila unos\"","plot 'datos.tmp'"};
	fp = fopen("datos.tmp","w");
	gnupipe = _popen("gnuplot -persistent", "w");
	fprintf(fp,"%d %d\n",x++,0);
	if ( ( ptrWrite = fopen("universo.txt", "w" )) == NULL or ( ptrWriteUnos = fopen("unos.txt", "w" )) == NULL){
		printf( "\n\nEl archivo no pudo abrirse..");
		return;
	}else{
		cout << "sigma a la " << n << " = { e, ";
		fprintf(ptrWrite, "sigma a la %d = { e, ",n); //iniciamos con n = 0.
		for(int i = 1; i <= n; i++){
	    	j = 1;
	    	unos = 0;
	    	str.assign(i,'0'); //la primera cadena de n, siempre sera de 0*i
	    	// cerr << str << nl;
	    	cout << str << ", "; 
	    	fprintf(ptrWrite, "%s, ",str.c_str()); //ejemplo 0*5 = 00000
	    	while(j <= i){
	    		str[i-j] = '1'; //empezamos a agregar unos de izquierda a derecha
	    		unos++;
	        	do{
	        		fprintf(ptrWrite, "%s, ",str.c_str());
	        		fprintf(ptrWriteUnos, "%d %d \n",y++,unos);
	        		fprintf(fp,"%d %d\n",x++,j);
	            	cout << str << ", "; 
	        	}while(next_permutation(str.begin(),str.end())); //hacemos la permutación con el número de unos actuales
	        	j++;  
	     	}
		}
	}
	cout << " }";
	fprintf(ptrWrite, " }");
	for(int i = 0; i < 2; i++){
	     fprintf(gnupipe,"%s\n",GnuCommands[i]);
	}   
	fclose(ptrWriteUnos);
	fclose(ptrWrite);
	fclose(fp);
	printf("\n\nUniverso escrito correctamente en archivo universo.txt xd\n");
}