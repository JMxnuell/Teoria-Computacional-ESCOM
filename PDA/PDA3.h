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
       // VN = {'E','M','X','I','R','Y','Z'};
        //VT = {'+', '*', '(', ')', 'a', 'b', '0', '1','-'};
        //S = 'E';
        //P = {{'E',{"MY"}},{'Y',{"+MY","-MY","@"}},{'M',{"XZ"}},{'Z',{"*XZ","@"}},{'X',{"(E)","I"}},{'I',{"aR","bR"}},{'R',{"aR","bR","0R","1R","@"}}}; //@ = epsilon
        VN = {'S'};
        VT = {'a','b'};
        S = {'S'};
        P = {{'S',{"aSa","bSb","b","a","@"}}};
    }

    void PDA(string cadena){

        stack<char> pila;
        pila.push('$');
        pila.push(S);

        cout << "La cadena " << (Q_loop(cadena,pila) ? "pertenece " : "no pertenece ") << "al lenguaje generado por la gramatica." << endl; 

    }

    bool Q_loop(string cadena, stack<char> pila){

        cout << "nueva iteracion " << cadena << endl;
        if(cadena.empty() and pila.top() == '$')
            return true;
        else if(!cadena.empty() and pila.top() == '$')
            return false;
        char a = pila.top();
        bool ans = false;

        if(!cadena.empty() and cadena[0] == a){
         cout << cadena << "iguales" << endl;
            pila.pop();
            ans = Q_loop(cadena.substr(1,cadena.size()-1),pila);
        }else if(a == '@'){
                cout << "eps" << endl;
                pila.pop();
                ans = Q_loop(cadena,pila);
            }else{
            char px = pila.top();
            cout << "top: " << px << endl;
            pila.pop();
            if(find(VN.begin(),VN.end(),px) != VN.end()){
                cout << "produccion" << endl;
                for(const auto &pi : P[px]){
                    cout << "de regreso: " << px << ' ' << pi << endl;
                    for(int i = (int)pi.size()-1; i >= 0; i--)
                        pila.push(pi[i]);
                    ans = Q_loop(cadena,pila);
                    if(ans)
                        break;
                    for(int i = 0; i < (int)pi.size(); i++)
                        pila.pop();
                }
            }
        }

        return ans;
    } 
};
