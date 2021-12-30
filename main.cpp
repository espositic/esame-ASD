#include <iostream>
using namespace std;

#include "alberoBinarioC.h"
#include "List_vector.h"

typedef alberoBinarioC<double>::Nodo Nodo;
typedef List_vector<double>::position position;

List_vector<double> mediaValoriPerLivello(alberoBinarioC<double> &albero);
List_vector<double> passaAiNodiFiglio(List_vector<double> &lista, alberoBinarioC<double> &albero, Nodo n ,position p);

int main() {
	alberoBinarioC<double> albero;
	Nodo n0;
	albero.ins_root(n0);
	albero.write(n0,0.3);
	albero.ins_dx(n0);
	albero.ins_sx(n0);
	Nodo n1=albero.dx(n0);
	Nodo n2=albero.dx(n0);
	n1=albero.dx(n0);
	n2=albero.sx(n0);
	albero.write(n1,2.1);
	albero.write(n1,3.4);
	albero.ins_dx(n1);
	albero.ins_sx(n1);
	albero.ins_dx(n2);
	albero.ins_sx(n2);
	Nodo n3=albero.dx(n1);
	Nodo n4=albero.dx(n1);
	Nodo n5=albero.dx(n2);
	Nodo n6=albero.dx(n2);
	albero.write(n3,8.2);
	albero.write(n4,4.7);
	albero.write(n5,1.9);
	albero.write(n6,2.4);
	List_vector<double> lista;
	lista=mediaValoriPerLivello(albero);
	return 0;
}

List_vector<double> mediaValoriPerLivello(alberoBinarioC<double> &albero){
	List_vector<double> lista;
	position p=1;
	position i=1;
	Nodo n;
	if(!albero.empty()){
		n=albero.root();
		lista.insert(albero.read(n),p);
	}
	if(albero.dx_empty(n) && albero.sx_empty(n))
		return lista;
	else{
		p++;
		if(!albero.dx_empty(n))
			lista=passaAiNodiFiglio(lista,albero,albero.dx(n),p);
		if(!albero.sx_empty(n))
			lista=passaAiNodiFiglio(lista,albero,albero.sx(n),p);
		while(i<=albero.height()){
			lista.write(lista.read(i)/i,i);
			i++;
		}
		return lista;
	}
}

List_vector<double> passaAiNodiFiglio(List_vector<double> &lista, alberoBinarioC<double> &albero, Nodo n ,position p){
	lista.insert(albero.read(n),p);
	p++;
	if(albero.dx_empty(n) && albero.sx_empty(n))
		return lista;
	else{
		p++;
		if(!albero.dx_empty(n))
			lista=passaAiNodiFiglio(lista,albero,albero.dx(n),p);
		if(!albero.sx_empty(n))
			lista=passaAiNodiFiglio(lista,albero,albero.sx(n),p);
		return lista;
	}
}
