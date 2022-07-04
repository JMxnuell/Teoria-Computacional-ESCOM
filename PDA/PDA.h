#include <bits/stdc++.h>
using namespace std;

typedef vector<char> vc;
typedef vector<string> vs;

class CFG{

protected:
    vc VT;
    vc VN;
    char S;
    unordered_map<char,vs> P;
public:
    CFG(){
        VN = {'E','M','X','I','R'};
        VT = {'+', '*', '(', ')', 'a', 'b', '0', '1'};
        S = 'E';
        P = {{'E',{"E+M","M"}},{'M',{"M*X","X"}},{'X',{"(E)","I"}},{'I',{"aR","bR"}},{'R',{"aR","bR","0R","1R","@"}}}; //@ = epsilon
    }

    void PDA(string cadena){

        stack<char> pila;
        pila.push('$');
        pila.push('E');

        cout << "La cadena " << (Q_loop(cadena,pila, "") ? "pertenece " : "no pertenece ") << "al lenguaje generado por la gramatica." << endl; 

    }

    bool Q_loop(string cadena, stack<char> pila, string anterior){

        if(cadena.empty() and pila.top() == '$')
            return true;
        else if(!cadena.empty() and pila.top() == '$')
            return false;
        char a = pila.top();
        bool ans = false;

        if(!cadena.empty() and cadena[0] == a){
            pila.pop();
            ans = Q_loop(cadena.substr(1,cadena.size()-1),pila, "");
        }else if(a == '@'){
            pila.pop();
            ans = Q_loop(cadena,pila, "");
        }else{
            char px = pila.top();
            pila.pop();
            for(const auto &pi : P[px]){
                if(anterior == pi)
                    continue;    
                for(int i = (int)pi.size()-1; i >= 0; i--)
                    pila.push(pi[i]);
                ans = Q_loop(cadena,pila,pi);
                if(ans)
                    break;
                for(int i = 0; i < (int)pi.size(); i++)
                    pila.pop();
            }
        }
        return ans;
    }
};
