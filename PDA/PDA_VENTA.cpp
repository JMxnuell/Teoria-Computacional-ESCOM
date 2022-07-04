#include <bits/stdc++.h>
using namespace std;

typedef vector<char> vc;
typedef vector<string> vs;


class gramatica{

protected:
    vc terminales;
    vc no_terminales;
    char S;
    unordered_map<char,vs> r_produccion;
public:
    gramatica(){
        no_terminales = {'S'}; //no terminales
        terminales = {'top','b'}; //terminales
        S = {'S'}; //inicial
        r_produccion = {{'S',{"aSa","bSb","b","top","@"}}}; //reglas de produccion
    }

    void automata_pila(string str){

        stack<char> pila;
        pila.push('$');
        pila.push(S);

        cout << "La cadena " << (Q_loop(str,pila) ? "pertenece " : "no pertenece ") << "al lenguaje..." << endl; 

    }

    bool Q_loop(string str, stack<char> pila){

        if(str.empty() and pila.top() == '$')
            return true;
        else if(!str.empty() and pila.top() == '$')
            return false;
        char top = pila.top();
        bool valida = false;

        if(!str.empty() and str[0] == top){
            pila.pop();
            valida = Q_loop(str.substr(1,str.size()-1),pila);
        }else if(top == '@'){
                pila.pop();
                valida = Q_loop(str,pila);
            }else{
            char px = pila.top();
            pila.pop();
            if(find(no_terminales.begin(),no_terminales.end(),px) != no_terminales.end()){
                for(const auto &pi : r_produccion[px]){
                    for(int i = (int)pi.size()-1; i >= 0; i--)
                        pila.push(pi[i]);
                    valida = Q_loop(str,pila);
                    if(valida)
                        break;
                    for(int i = 0; i < (int)pi.size(); i++)
                        pila.pop();
                }
            }
        }

        return valida;
    } 
};

int main(int argc, char const *argv[]){

    string str;
    grammar gramatica;
    cout << "Ingresa la cadena: ";
    cin >> str;
    gramatica.automata_pila(str);
    
    return 0;
}

