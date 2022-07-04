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
        VN = {'S'};
        VT = {'a', 'b', 'c'};
        S = 'S';
        P = {{'S',{"aSa","bSb","c"}}}; //@ = epsilon
    }

    void PDA(string cadena){

        stack<char> pila;
        pila.push('$');
        pila.push(S);

        cout << Q_loop(cadena,pila, "") << endl;

    }

    bool Q_loop(string cadena, stack<char> pila, string anterior){

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
            ans = Q_loop(cadena.substr(1,cadena.size()-1),pila, "");
        }else if(a == '@'){
            cout << "eps" << endl;
            pila.pop();
            ans = Q_loop(cadena,pila, "");
        }else{
            char px = pila.top();
            cout << "top: " << px << endl;
            pila.pop();
            cout << "produccion" << endl;
            for(const auto &pi : P[px]){
                cout << pi << endl;
                if(anterior == pi){
                    cout << "ciclado" << endl;
                    continue;
                }
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
