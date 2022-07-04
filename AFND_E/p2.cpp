#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<pair<int, char>> vic;

bool bandera = false;
vi Q, F;
int S;
vc Sigma;
unordered_map<int,vic> Delta;

void t(string cad, int &eac, string impresion, vic err, bool Manejo_errores);

int main(){

	fstream file;
	file.open("automataE.txt",ios::in);

	if(file.is_open()){
		string renglon;
		int nl = 0;
		while(getline(file,renglon)){
			if(nl == 0){
				 stringstream ss(renglon);
				  while (ss.good()) {
        			     string substr;
        			     getline(ss, substr, ',');
        			     Q.push_back(stoi(substr));
                  }     

			}else if(nl == 1){
                    stringstream ss(renglon);
				  while (ss.good()) {
        			     string substr;
        			     getline(ss, substr, ',');
        			     F.push_back(stoi(substr));
                      }    
			}else if(nl == 2){
				S = stoi(renglon);
			}else if(nl == 3){
                     stringstream ss(renglon);
				  while (ss.good()) {
        			     string substr;
        			     getline(ss, substr, ',');
        			     Sigma.push_back(substr[0]);
                      }  
			}else{
                     stringstream ss(renglon);
                     int l = 0;
                     int a,c;
                     char b;
				  while (ss.good()) {
        			     string substr;
        			     getline(ss, substr, ',');
        			     if(l == 0)
        			          a = stoi(substr);
        			     else if(l == 1)
        			          b = substr[0];
        			     else
        			          c = stoi(substr);
        			     l++;
                      }  
                         l = 0;
        			     Delta[a].push_back({c,b});
			}
			nl++;
		}
		string cad;
		cout << "Cadena: ";
		cin >> cad;
		vic err;
		t(cad,S,"", err, true);
		if(!bandera)
			cout << "La cadena no es valida para este lenguaje" << endl;
	}
     return 0;
}

void t(string cad, int &eac, string impresion, vic err, bool Manejo_errores){

			for(auto par : Delta[eac])
				if(par.second == 'E')
					Manejo_errores = false;

			if(!Manejo_errores){
				impresion += "q";
				impresion += to_string(eac);
				impresion += " ";
			}

			if(cad.size() == 0){
				auto it = find(F.begin(), F.end(), eac);
				if(it != F.end()){
					cout << "T: " << impresion << endl;
					bandera = true;
					if(!err.empty()){
							cout << "Manejo_errores: ";
							for(auto &par : err)
								cout << "q" << par.first <<  "(" << par.second << ")->";
							
							cout << endl << endl;	
					}
				return;
				}else{
					bool continua;
					continua = false;
					for(auto par : Delta[eac])
						if(par.second == 'E'){
							continua = true;
							break;
						}
					if(!continua)
						return;
				}
				
			}
			string aux;
			char c = '-';
			if(!cad.empty()){
				aux = cad.substr(1,cad.size()-1);
			 	c = cad[0];
		 	}
			bool existe = false;
			for(auto par : Delta[eac]){
				if(par.second == c){
				//	cout << "Dentro existe camino directo: " << c << endl;
					t(aux, par.first,impresion,err, false);
					existe  = true;
				}else if(par.second == 'E'){
					//cout << "Dentro existe camino con eps: " << c << endl;
					t(cad, par.first,impresion,err, false);
					existe  = true;
				}
			}	
			auto it2 = find(Sigma.begin(), Sigma.end(), cad[0]);
			if(!existe and (it2 == Sigma.end())){
				err.push_back({eac,c});
				t(aux, eac,impresion, err, true);
			}

}
