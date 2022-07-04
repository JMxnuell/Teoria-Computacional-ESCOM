#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<pair<int, char>> vic;
typedef vector<pair<char, char>> vcc;
const int INF = 1e9;
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
			vPosible = estados;
			for(auto &e : estados){
				vi dist(Q.size(),INF);
				vi r;
				//cout << "BFS: " << e << endl;
				r = BFS(e, dist);
				for(auto &e2 : r)
					if(find(vPosible.begin(), vPosible.end(),e2) == vPosible.end())
						vPosible.push_back(e2);
			}

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
						Q_AFD[Eact] = Q_AFD[conYa];
						break;
					}
				}
				if(!iguales){
					Q_AFD[Eact] = vPosible;
					//Eact++;
				}	
			}else{
				vPosible.push_back('@');
			}
			cout << "CE: \n";
			for(auto &e : vPosible){
				cout << e << ' ';
			}
			cout << endl;
			return vPosible;
		}

		vi BFS(const int &e, vi dist){
			int s = e;
			queue<int> q; q.push(s);
			dist[s] = 0;
			vi r;
			while(!q.empty()){
				 int u = q.front(); q.pop();
				 for(const auto &e2 : Delta[u]){
				 //	cout << "camino: " << u << " : " << e2.first << endl; 
				 	if(dist[e2.first] == INF and e2.second == 'E'){
				 		//cout << "dentro" << endl;
				 		dist[e2.first] = dist[u]+1;
				 		q.push(e2.first);
				 		r.push_back(e2.first);
				 	}
				 } 
			}

			return r;
		}

		vi Mover(const vi &estados,const char &alpha){

			vi vPosible;
			for(const auto &e : estados)
				for(const auto &p : Delta[e])
					if(p.second == alpha)
						vPosible.push_back(p.first);

			if(vPosible.empty())
				vPosible.push_back(-1);
			cout << "MOVER: \n";
			for(auto &e : vPosible){
				cout << e << ' ';
			}
			cout << endl;
			return vPosible;
		}	

		vi Ir_A(const vi &estados,const char &alpha){

			return C_E(Mover(estados, alpha));
		}

		void transformar(){
			vi ini = {0};
			C_E(ini);
			//Delta_AFD[Eact] = Q_AFD[Eact];
			S_AFD = Eact;
			Eact++;

			for(const auto &q : Q_AFD){
				for(const auto &c : Sigma){
					vi vPosible;
					cout << "IR_A" << q.first << ' ' << c << endl;
					vPosible = Ir_A(q.second,c);
					if(vPosible.empty()){
						cout << "conYa: " << conYa << endl;
						Delta_AFD[q.first].push_back({c,conYa});
					}else if(vPosible[0] == '@'){
						cout << "Error \n";
						Delta_AFD[q.first].push_back({c,'@'});
					}else{
						cout << "qF: " << q.first << endl;	
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
 