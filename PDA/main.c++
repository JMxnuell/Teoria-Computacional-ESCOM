#include "PDA3.h"

int main(int argc, char const *argv[]){

	string cad;
	CFG gramatica;
	cout << "Cadena: ";
	cin >> cad;
	gramatica.PDA(cad);
	
	return 0;
}

/*
G = (VT, VN, E, P)
Donde:

VN = {E,M,X,I,R,Y,Z}
VT = {+, *, (, ), a, b, 0, 1}
P =
    //////E ⟶ E+M | M
    E ⟶ MY
    Y ⟶ +MY | λ

    /////M ⟶ M*X | X
    M ⟶ XZ
    Z ⟶ *XZ | λ 

    X ⟶ (E) | I

    //////I ⟶ a | b | IDa | IDb | ID0 | ID1
    I ⟶ aR | bR
    R ⟶ aR | bR | 0R | 1R | λ

PDA:

R({Q0,Q1,Qloop, Q3}, VT, {VT u VN}, δ, Q0, {Q3})

primera y única vez: δ(Q0, λ, λ) → (Q1, $) 
segunda y única vez: δ(Q1, λ, λ) → (Qloop, E)

en loop:

 δ(Qloop, +,+ ) → (Qloop,  λ)
 δ(Qloop, *,* ) → (Qloop,  λ)
 δ(Qloop, (,( ) → (Qloop,  λ)
 δ(Qloop, ),) ) → (Qloop,  λ)
 δ(Qloop, a,a ) → (Qloop,  λ)
 δ(Qloop, b,b ) → (Qloop,  λ)
 δ(Qloop, 0,0 ) → (Qloop,  λ)
 δ(Qloop, 1,1 ) → (Qloop,  λ)

 δ(Qloop, λ, E ) → (Qloop,  MY)
 δ(Qloop, λ, Y ) → (Qloop,  +MY)
 δ(Qloop, λ, Y ) → (Qloop,  λ)
 δ(Qloop, λ, M ) → (Qloop,  XZ)
 δ(Qloop, λ, Z ) → (Qloop,  *XZ)
 δ(Qloop, λ, Z ) → (Qloop,  λ)
 δ(Qloop, λ, M ) → (Qloop,  X)
 δ(Qloop, λ, X ) → (Qloop,  (E))
 δ(Qloop, λ, X ) → (Qloop,  ID)
 δ(Qloop, λ, ID ) → (Qloop,  aR)
 δ(Qloop, λ, ID ) → (Qloop,  bR)
 δ(Qloop, λ, R ) → (Qloop,  aR)
 δ(Qloop, λ, R ) → (Qloop,  bR)
 δ(Qloop, λ, R ) → (Qloop,  0R)
 δ(Qloop, λ, R ) → (Qloop,  1R)
 δ(Qloop, λ, R ) → (Qloop,  λ)

salir del loop:
 δ(Qloop, λ, $ ) → (Q3, λ)
*/