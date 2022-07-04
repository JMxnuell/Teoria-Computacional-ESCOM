#include "funciones3.h"


int main(int argc, char const *argv[]){
	
	fstream newfile;
	newfile.open("automataE2.txt",ios::in);
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
	AFN_to_AFD AFN(Q,F,S, Sigma, Delta);
	AFN.transformar();
	AFN.mostrarAFD();	
}
	return 0;
}