#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<pair<int, char>> vic;

bool hayValidas = false;

class automata{

	private:
		vi Q, F;
		int S;
		vc Sigma;
		unordered_map<int,vic> Delta;

	public:
		automata(vi Q, vi F, int S, vc Sigma, unordered_map<int,vic> Delta){
			this->Q = Q;
			this->F = F;
			this->S = S;
			this->Sigma = Sigma;
			this->Delta = Delta;
		}

		void transicion(string cadena, int &eActual, string imp, vic errores, bool ME){

			//auto it2 = find(Sigma.begin(), Sigma.end(), cadena[0]);
			//cout << "Cadena: " << cadena << " eActual: " << eActual << " imp: " << imp << endl;
			for(auto par : Delta[eActual])
				if(par.second == 'E')
					ME = false;

			if(!ME){
				imp += "q";
				imp += to_string(eActual);
				imp += " ";
			}

			if(cadena.size() == 0){
				auto it = find(F.begin(), F.end(), eActual);
				if(it != F.end()){
					cout << "T: " << imp << endl;
					hayValidas = true;
					if(!errores.empty()){
							cout << "ME: ";
							for(auto &par : errores)
								cout << "q" << par.first <<  "(" << par.second << ")->";
							
							cout << endl << endl;	
					}
				return;
				}else{
					bool continua;
					continua = false;
					for(auto par : Delta[eActual])
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
			if(!cadena.empty()){
				aux = cadena.substr(1,cadena.size()-1);
			 	c = cadena[0];
		 	}
			bool existe = false;
			for(auto par : Delta[eActual]){
				if(par.second == c){
				//	cout << "Dentro existe camino directo: " << c << endl;
					transicion(aux, par.first,imp,errores, false);
					existe  = true;
				}else if(par.second == 'E'){
					//cout << "Dentro existe camino con eps: " << c << endl;
					transicion(cadena, par.first,imp,errores, false);
					existe  = true;
				}
			}	
			auto it2 = find(Sigma.begin(), Sigma.end(), cadena[0]);
			if(!existe and (it2 == Sigma.end())){
				errores.push_back({eActual,c});
				transicion(aux, eActual,imp, errores, true);
			}

		}
};

int main(){

	fstream newfile;
	newfile.open("automataE.txt",ios::in);
	vi Q, F;
	int S;
	vc Sigma;
	unordered_map<int,vic> Delta;

	if(newfile.is_open()){
		string line;
		int nLine = 0;
		while(getline(newfile,line)){
			if(nLine == 0){
				 stringstream ss(line);
				  while (ss.good()) {
        			     string substr;
        			     getline(ss, substr, ',');
        			     Q.push_back(stoi(substr));
                  }     

			}else if(nLine == 1){
                    stringstream ss(line);
				  while (ss.good()) {
        			     string substr;
        			     getline(ss, substr, ',');
        			     F.push_back(stoi(substr));
                      }    
			}else if(nLine == 2){
				S = stoi(line);
			}else if(nLine == 3){
                     stringstream ss(line);
				  while (ss.good()) {
        			     string substr;
        			     getline(ss, substr, ',');
        			     Sigma.push_back(substr[0]);
                      }  
			}else{
                     stringstream ss(line);
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
			nLine++;
		}
		string cadena;
		cout << "Cadena a procesar: ";
		cin >> cadena;
		automata a1(Q,F,S, Sigma, Delta);
		vic errores;
		a1.transicion(cadena,S,"", errores, true);
		if(!hayValidas)
			cout << "La cadena no es valida" << endl;
	}
     return 0;
}