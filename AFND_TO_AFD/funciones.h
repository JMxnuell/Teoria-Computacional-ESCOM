#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<pair<int, char>> vic;
typedef vector<pair<char, char>> vcc;

char conYa;

class AFN_to_AFD{

	private:
		vi Q, F;
		int S;
		vc Sigma;
		unordered_map<int,vic> Delta;
		char Eact;

		unordered_map<char,vi> Q_AFD;
		vc F_AFD;
		char S_AFD;
		//vc Sigma_AFD;
		unordered_map<char,vcc> Delta_AFD;

	public:
		AFN_to_AFD(vi Q, vi F, int S, vc Sigma, unordered_map<int,vic> Delta){
			this->Q = Q;
			this->F = F;
			this->S = S;
			this->Sigma = Sigma;
			this->Delta = Delta;
			this->Eact = 'A';
		}
		vi C_E(const vi &estados){
			vi vPosible;
			if(estados[0] == -1){
				vPosible.push_back('@');
				return vPosible;
			}
			for (const auto &e : estados)
				for(const auto &p : Delta[e])
					if(p.second == 'E')
						vPosible.push_back(p.first);
			
			bool iguales = false;
			bool si = false;

			if(!vPosible.empty()){
				for(const auto &e : Q_AFD){
					for(const auto &q : e.second){
						for(const auto &q2 : vPosible){
							if(q == q2){
								si = true;
								break;
							}
						}
						if(si)
							iguales = true;
						else
							iguales = false;
					}
					if(iguales){
						conYa = e.first;
						break;
					}
				}
				if(!iguales){
					Q_AFD[Eact] = vPosible;
					Eact++;
				}	
			}else{
				vPosible.push_back('@');
			}
			return vPosible;
		}
		vi Mover(const vi &estados,const char &alpha){

			vi vPosible;
			for(const auto &e : estados)
				for(const auto &p : Delta[e])
					if(p.second == alpha)
						vPosible.push_back(p.first);

			if(vPosible.empty())
				vPosible.push_back(-1);

			return vPosible;
		}
		vi Ir_A(const vi &estados,const char &alpha){
			return C_E(Mover(estados, alpha));
		}
		void transformar(){
			vi ini;
			ini.push_back(0);
			Q_AFD[Eact] = C_E(ini);
			for(auto &es : Q_AFD[Eact])
				cout << es << " ";

			S_AFD = Eact;
			Eact++;


			for(const auto &q : Q_AFD){
				for(const auto &c : Sigma){
					vi vPosible;
					vPosible = Ir_A(q.second,c);
					if(vPosible.empty()){
						Delta_AFD[q.first].push_back({c,conYa});
					}else if(vPosible[0] == '@'){
						Delta_AFD[q.first].push_back({c,'@'});
					}else{
						Q_AFD[Eact] = vPosible;
						Delta_AFD[q.first].push_back({c,Eact});
						Eact++;
					}
				}
			}
		}
		void mostrarAFD(){
			for(const auto &c : Sigma)
				printf("\t%c",c);
			printf("\n");

			for(const auto &q : Delta_AFD){
				cout << endl << q.first;
				for(const auto &p : q.second){
					printf("\t %c-%c",p.first,p.second);
				}
			}

		}
};
 