#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
vector<vector<pair<int,int>>> encontrados(7);
vector<string> reserv = {"WEB","PAGE", "SITE", "MASTER","HOME","COIN", "EBAY"};
void viewDFA(){
	int pid;
	pid = fork();
	if(pid == 0){
		//cout << "\n\n\tAbriendo grafo DFA...";
		execlp("gnome-terminal","gnome-terminal","--","eog","DFA.png",(char*)NULL);
	}
}
void vieweNFA(){
	int pid;
	pid = fork();
	if(pid == 0){
		//cout << "\n\n\tAbriendo grafo eNFA...";
		execlp("gnome-terminal","gnome-terminal","--","eog","eNFA.png",(char*)NULL);
	}
}
void comparaEFinal(const string &eActual, const int &i, const int &j){


	if(eActual == "Z5"){ //WEB
		cout << "Se encontro WEB" << endl;
		encontrados[0].push_back({i,j});
	}else if(eActual == "I"){ //PAGE
		encontrados[1].push_back({i,j});
		cout << "Se encontro PAGE" << endl;
	}else if(eActual == "M"){ //SITE
		encontrados[2].push_back({i,j});
		cout << "Se encontro SITE" <<endl;
	}else if(eActual == "S"){ //MASTER
		encontrados[3].push_back({i,j});
		cout << "Se encontro MASTER" <<endl;
	}else if(eActual == "W"){ //HOME
		encontrados[4].push_back({i,j});
		cout << "Se encontro HOME" <<endl;
	}else if(eActual == "Z2"){ //COIN
		encontrados[5].push_back({i,j});
		cout << "Se encontro COIN" <<endl;
	}else if(eActual == "Z4"){ //EBAY
		encontrados[6].push_back({i,j});
		cout << "Se encontro EBAY" <<endl;
	}
}
string grupo(const string &eActual, const char &c){

	if(((eActual == "A") or (eActual == "B") or (eActual == "H") or (eActual == "L") or (eActual=="O") or (eActual== "Q")
		or (eActual == "S") or (eActual == "U") or (eActual == "Z2") or (eActual == "Z4")) and ((c != 'w') and (c != 'e')
		and (c != 'p') and (c != 's') and (c != 'm') and (c != 'h') and (c != 'c')))
			return "mismo1";
	else if(((eActual == "C") or (eActual == "D") or (eActual == "I") or (eActual == "W") or (eActual == "M")) and ((c != 'w') and (c != 'e')
		and (c != 'b') and (c != 'p') and (c != 's') and (c != 'm') and (c != 'h') and (c != 'c')))
			return "mismo2";
	else if(((eActual == "E") or (eActual == "F") or (eActual == "N") or (eActual == "V") or (eActual=="Z5")) and ((c != 'w') and (c != 'e')
		and (c != 'p') and (c != 'a') and (c != 's') and (c != 'm') and (c != 'h') and (c != 'c')))
			return "mismo3";
	else if((eActual == "G") and ((c != 'w') and (c != 'e') and (c != 'p') and (c != 'g') and (c != 's') and 
		(c != 'm') and (c != 'h') and (c != 'c')))
			return "solo1";
	else if(((eActual == "J") or (eActual == "Y")) and ((c != 'w') and (c != 'e')
		and (c != 'p') and (c != 's') and (c != 'i') and (c != 'm') and (c != 'h') and (c != 'c')))
			return "mismo4";
	else if((eActual == "K") and ((c != 'w') and (c != 'e')
		and (c != 'p') and (c != 's') and (c != 'm') and (c != 't') and (c != 'h') and (c != 'c')))
			return "solo2";
	else if((eActual == "P") and ((c != 'w') and (c != 'e')
		and (c != 'p') and (c != 's') and (c != 'i') and (c != 't') and (c != 'm') and (c != 'h') and (c != 'c')))
			return "solo3";
	else if((eActual == "R") and ((c != 'w') and (c != 'e')
		and (c != 'b') and (c != 'p') and (c != 's') and (c != 'm') and (c != 'r') and (c != 'h') and (c != 'c')))
			return "solo4";
	else if(((eActual == "T") or (eActual == "X")) and ((c != 'w') and (c != 'e')
		and (c != 'p') and (c != 's') and (c != 'm') and (c != 'h') and (c != 'o') and (c != 'c')))
			return "mismo5";
	else if((eActual == "Z") and ((c != 'w') and (c != 'e')
		and (c != 'p') and (c != 's') and (c != 'm') and (c != 'h') and (c != 'c') and (c != 'n')))
			return "solo5";
	else if((eActual == "Z3") and ((c != 'w') and (c != 'e')
		and (c != 'p') and (c != 's') and (c != 'm') and (c != 'h') and (c != 'y') and (c != 'c')))
			return "solo6";
	else if(((eActual == "A") or (eActual == "B") or (eActual == "C") or (eActual == "D") or (eActual == "E")
		or (eActual == "F") or (eActual == "G") or (eActual == "H") or (eActual == "I") or (eActual == "J")
		or (eActual == "K") or (eActual == "L") or (eActual == "M") or (eActual == "N") or (eActual == "O") or (eActual == "P")
		or (eActual == "Q") or (eActual == "R") or (eActual == "S") or (eActual == "T") or (eActual == "U") or (eActual == "V")
		or (eActual == "W") or (eActual == "X") or (eActual == "Y") or (eActual == "Z") or (eActual == "Z2") or (eActual == "Z3")
		or (eActual == "Z4") or (eActual == "Z5")) and (c == 'w'))
			return "mismoBw";
	else if(((eActual == "A") or (eActual == "C") or (eActual == "D") or (eActual == "E")
		or (eActual == "F") or (eActual == "G") or (eActual == "I") or (eActual == "J")
		or (eActual == "K") or (eActual == "M") or (eActual == "N") or (eActual == "O") or (eActual == "P")
	    or (eActual == "R") or (eActual == "S") or (eActual == "T") or (eActual == "U") 
		or (eActual == "W") or (eActual == "X") or (eActual == "Y") or (eActual == "Z") or (eActual == "Z2") or (eActual == "Z3")
		or (eActual == "Z4") or (eActual == "Z5")) and (c == 'e'))
			return "mismoDe";
	else if(((eActual == "A") or (eActual == "B") or (eActual == "C") or (eActual == "D") or (eActual == "E")
		or (eActual == "F") or (eActual == "G") or (eActual == "H") or (eActual == "I") or (eActual == "J")
		or (eActual == "K") or (eActual == "L") or (eActual == "M") or (eActual == "N") or (eActual == "O") or (eActual == "P")
		or (eActual == "Q") or (eActual == "R") or (eActual == "S") or (eActual == "T") or (eActual == "U") or (eActual == "V")
		or (eActual == "W") or (eActual == "X") or (eActual == "Y") or (eActual == "Z") or (eActual == "Z2") or (eActual == "Z3")
		or (eActual == "Z4") or (eActual == "Z5")) and (c == 'p'))
			return "mismoFp";
	else if(((eActual == "A") or (eActual == "B") or (eActual == "C") or (eActual == "D") or (eActual == "E")
		or (eActual == "F") or (eActual == "G") or (eActual == "H") or (eActual == "I") or (eActual == "J")
		or (eActual == "K") or (eActual == "L") or (eActual == "M") or (eActual == "N") or (eActual == "P")
		or (eActual == "Q") or (eActual == "R") or (eActual == "S") or (eActual == "T") or (eActual == "U") or (eActual == "V")
		or (eActual == "W") or (eActual == "X") or (eActual == "Y") or (eActual == "Z") or (eActual == "Z2") or (eActual == "Z3")
		or (eActual == "Z4") or (eActual == "Z5")) and (c == 's'))
			return "mismoJs";
	else if(((eActual == "A") or (eActual == "B") or (eActual == "C") or (eActual == "D") or (eActual == "E")
		or (eActual == "F") or (eActual == "G") or (eActual == "H") or (eActual == "I") or (eActual == "J")
		or (eActual == "K") or (eActual == "L") or (eActual == "M") or (eActual == "N") or (eActual == "O") or (eActual == "P")
		or (eActual == "Q") or (eActual == "R") or (eActual == "S") or (eActual == "T") or (eActual == "V")
		or (eActual == "W") or (eActual == "X") or (eActual == "Y") or (eActual == "Z") or (eActual == "Z2") or (eActual == "Z3")
		or (eActual == "Z4") or (eActual == "Z5")) and (c == 'm'))
			return "mismoNm";
	else if(((eActual == "A") or (eActual == "B") or (eActual == "C") or (eActual == "D") or (eActual == "E")
		or (eActual == "F") or (eActual == "G") or (eActual == "H") or (eActual == "I") or (eActual == "J")
		or (eActual == "K") or (eActual == "L") or (eActual == "M") or (eActual == "N") or (eActual == "O") or (eActual == "P")
		or (eActual == "Q") or (eActual == "R") or (eActual == "S") or (eActual == "T") or (eActual == "U") or (eActual == "V")
		or (eActual == "W") or (eActual == "X") or (eActual == "Y") or (eActual == "Z") or (eActual == "Z2") or (eActual == "Z3")
		or (eActual == "Z4") or (eActual == "Z5")) and (c == 'h'))
			return "mismoTh";
	else if(((eActual == "A") or (eActual == "B") or (eActual == "C") or (eActual == "D") or (eActual == "E")
		or (eActual == "F") or (eActual == "G") or (eActual == "H") or (eActual == "I") or (eActual == "J")
		or (eActual == "K") or (eActual == "L") or (eActual == "M") or (eActual == "N") or (eActual == "O") or (eActual == "P")
		or (eActual == "Q") or (eActual == "R") or (eActual == "S") or (eActual == "T") or (eActual == "U") or (eActual == "V")
		or (eActual == "W") or (eActual == "X") or (eActual == "Y") or (eActual == "Z") or (eActual == "Z2") or (eActual == "Z3")
		or (eActual == "Z4") or (eActual == "Z5")) and (c == 'c'))
			return "mismoXc";
	else if((eActual == "B") and (c == 'e'))
			return "soloCe";
	else if((eActual == "C") and (c == 'b'))
			return "soloZ5b";
	else if(((eActual == "D") or (eActual == "M") or (eActual == "R") or (eActual == "W") or (eActual == "I")) and (c == 'b'))
			return "mismoEb";
	else if(((eActual == "E") or (eActual == "Z5")) and (c == 'a'))
			return "mismoZ3a";
	else if((eActual == "F") and (c == 'a'))
			return "soloGa";
	else if((eActual == "G") and (c == 'g'))
			return "soloHg";
	else if((eActual == "H") and (c == 'e'))
			return "soloIe";
	else if(((eActual == "J") or (eActual == "P")) and (c == 'i'))
			return "mismoKi";
	else if((eActual == "K") and (c == 't'))
			return "soloLt";
	else if((eActual == "L") and (c == 'e'))
			return "soloMe";
	else if(((eActual == "N") or (eActual == "V")) and (c == 'a'))
			return "mismoOa";
	else if((eActual == "O") and (c == 's'))
			return "soloPs";
	else if((eActual == "P") and (c == 't'))
			return "soloQt";
	else if((eActual == "Q") and (c == 'e'))
			return "soloRe";
	else if((eActual == "R") and (c == 'r'))
			return "soloSr";
	else if((eActual == "T") and (c == 'o'))
			return "soloUo";
	else if((eActual == "U") and (c == 'm'))
			return "soloVm";
	else if((eActual == "V") and (c == 'e'))
			return "soloWe";
	else if((eActual == "X") and (c == 'o'))
			return "soloYo";
	else if((eActual == "Y") and (c == 'i'))
			return "soloZi";
	else if((eActual == "Z") and (c == 'n'))
			return "soloZ2n";
	else if((eActual == "Z3") and (c == 'y'))
			return "soloZ4y";
}
void DFA(const string &texto){
	string eActual = "A",grupoActual;
		FILE *ptrFILE, *ptrFILE2;
		ptrFILE = fopen("estados.txt","w");
		ptrFILE2 = fopen("encontrados.txt","w");
		int i,j;
		i = j = 0;
	for(auto & c : texto){
		fprintf(ptrFILE, "\tEstado actual: %s | ",eActual.c_str());
		grupoActual = grupo(eActual,c); 
		if((grupoActual == "mismo1") or
			(grupoActual == "mismo2") or 
			(grupoActual == "mismo3") or 
		    (grupoActual == "solo1") or
			(grupoActual == "mismo4") or
			(grupoActual == "solo2") or
			(grupoActual == "solo3") or
			(grupoActual == "solo4") or
			(grupoActual == "mismo5") or 
			(grupoActual == "solo5") or 
			(grupoActual == "solo6"))
				eActual = "A";
		else if(grupoActual == "mismoBw")
				eActual = "B";
		else if(grupoActual == "mismoDe")
				eActual = "D";
		else if(grupoActual == "mismoFp")
				eActual = "F";
		else if(grupoActual == "mismoJs")
				eActual = "J";
		else if(grupoActual == "mismoNm")
				eActual = "N";
		else if(grupoActual == "mismoTh")
				eActual = "T";
		else if(grupoActual == "mismoXc")
				eActual = "X";
		else if(grupoActual == "soloCe")
				eActual = "C";
		else if(grupoActual == "soloZ5b")
				eActual = "Z5";
		else if(grupoActual == "mismoEb")
				eActual = "E";
		else if(grupoActual == "mismoZ3a")
				eActual = "Z3";
		else if(grupoActual == "soloGa")
				eActual = "G";
		else if(grupoActual == "soloHg")
				eActual = "H";
		else if(grupoActual == "soloIe")
				eActual = "I";
		else if(grupoActual == "mismoKi")
				eActual = "K";
		else if(grupoActual == "soloLt")
				eActual = "L";
		else if(grupoActual == "soloMe")
				eActual = "M";
		else if(grupoActual == "mismoOa")
				eActual = "O";
		else if(grupoActual == "soloPs")
				eActual = "P";
		else if(grupoActual == "soloQt")
				eActual = "Q";
		else if(grupoActual == "soloRe")
				eActual = "R";
		else if(grupoActual == "soloSr")
				eActual = "S";
		else if(grupoActual == "soloUo")
				eActual = "U";
		else if(grupoActual == "soloVm")
				eActual = "V";
		else if(grupoActual == "soloWe")
				eActual = "W";
		else if(grupoActual == "soloYo")
				eActual = "Y";
		else if(grupoActual == "soloZi")
				eActual = "Z";
		else if(grupoActual == "soloZ2n")
				eActual = "Z2";
		else if(grupoActual == "soloZ4y")
				eActual = "Z4";

		fprintf(ptrFILE, "transicion a : %s con carcater: %c\n",eActual.c_str(),c);
		comparaEFinal(eActual,i,j);	
		j++;
		if(c == '\n'){
			i++;
			j = 0;
		}
	}
	int k;
	k = 0;
	for(auto palabra : encontrados){
		fprintf(ptrFILE2,"\tPalabra reservada: %s | total encontrados: %d\n",reserv[k++].c_str(),(int)palabra.size());
		int l;
		l = 1;
		for(auto coord : palabra){
			fprintf(ptrFILE2, "\t%d. [%d,%d]\n",l++,coord.first,coord.second);
		}
		fprintf(ptrFILE2,"\n\n");
	}
	fclose(ptrFILE);
	fclose(ptrFILE2);
}
void readInput(){
	string inp;
	cout << "\n\tIngresa el texto de entrada: ";
	getline(cin,inp);
	getline(cin,inp);
	DFA(inp);
}
void readTXT(){
	string inp, arch;
	fstream lectura;
	inp = "";
	cout << "\n\tDireccion del archivo de lectura: ";
	cin >> arch;
	lectura.open(arch,ios::in);
	if(lectura.is_open()){
		string line;
		while(getline(lectura,line))
			inp += line;
		lectura.close();
		DFA(inp);
	}else{
		cout << "\n\tNO se encontro tal archivo";
	}
}
int main(int argc, char const *argv[]){

	int opc;
	do{
		cout << "\n\tIdentificador de palabras\n";
		cout << "\n\t[1]Lectura desde archivo de texto | "
			 << "[2] Lectura desde entrada definida por el usuario | "
			 << "[3] Mostrar grafo del eNFA | "
		 	 << "[4] Mostrar grafo del DFA | "
		 	 << "[5] Salir"
		 	 << "\n\n\tOpcion: ";
		cin >> opc;
		switch(opc){
			case 1:
				readTXT();
				break;
			case 2:
				readInput();
				break;
			case 3:
			    vieweNFA();
				break;
			case 4:
				viewDFA();
				break;
			case 5:
				break;
			default:
				cout << "\n\n\tOPCION NO VALIDA";
		}
		cout << "\n\n\tPresione una tecla para continuar...";
		cin.get();
		cin.get();
		system("clear");

	}while(opc != 5);

	return 0;
}