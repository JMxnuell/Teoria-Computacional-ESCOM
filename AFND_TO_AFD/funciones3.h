#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<pair<int, char>> vic;
typedef vector<pair<char, char>> vcc;
const int INF = 1e9;


class AFN_to_AFD{

	private:
		vi Q, F;
		int S;
		vc Sigma;
		unordered_map<int,vic> Delta;
		char Eact;

		unordered_map<char,vi> Q_AFD;
		unordered_map<char,bool>F_AFD;
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
			//cout << "CE: \n";
			// << "No hay " << endl;
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
			if(vPosible.empty())
				vPosible.push_back('@');

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
			
			return vPosible;
		}	

		vi Ir_A(const vi &estados,const char &alpha){

			return C_E(Mover(estados, alpha));
		}

		char noRepite(const vi &vPosible){
			char ya = '@';
			int iguales = 0;

			for(const auto &e : Q_AFD){
					iguales = 0;
					for(const auto &q : e.second){
						for(const auto &q2 : vPosible){
							if(q == q2){
								iguales++;
								break;
							}
						}
					}
					if(iguales == e.second.size() and iguales == vPosible.size()){
						//cout << iguales << ' ' << e.second.size() << endl;
						ya = e.first;
						break;
					}
					iguales = 0;
				}
				//cout << "Ya: " << ya << endl;
				return ya;
		}

		void transformar(){
			vi ini = {0};
			queue<char> g;
			Q_AFD[Eact] = C_E(ini);
			S_AFD = Eact;
			g.push(Eact);
			Eact++;

			while(!g.empty()){
				char e;
				e = g.front();
				g.pop();

				for(const auto &c : Sigma){
					vi vPosible;
				//	cout << "IR_A: " << e << ' ' << c << endl;
					vPosible = Ir_A(Q_AFD[e],c);
					bool posibleF = false;
					for(const auto &z : vPosible)
							if(find(F.begin(),F.end(),z) != F.end())
								posibleF = true;

					if(vPosible[0] == '@'){
					//	cout << "To delta \n";
						Delta_AFD[e].push_back({c,'@'});
					}else{
					//	cout << "posible nuevo" << endl;	
						char conYa = noRepite(vPosible);
						if(conYa == '@'){
							Delta_AFD[e].push_back({c,Eact});
							Q_AFD[Eact] = vPosible; 
							if(posibleF)
								F_AFD[Eact] = true;
					//		cout << "asigna nuevo: " << Eact << endl;
							g.push(Eact++);
						}else{
							Delta_AFD[e].push_back({c,conYa});
						}
					}
				}

			}
			
		}
		void mostrarAFD(){
			for(const auto &c : Sigma)
				printf("\t%c",c);
			printf("\n");
			char c = 'A';
			for(int i = 0; i < Delta_AFD.size(); i++){
				if(c+i == S_AFD)
					printf("\n->%c",c+i);
				else if(F_AFD[(char)(c+i)] == true)
					printf("\n*%c",c+i);
				else
					printf("\n%c",c+i);
				for(const auto &p : Delta_AFD[c+i]){
					printf("\t%c", p.second);
				}
			}

		}
};
 