#include <iostream>
#include "ConcurrentHashMap.hpp"

using namespace std;

int main(void) {

	ConcurrentHashMap h;

	cout << "hashmap construido!" << endl;
	h.addAndInc("hola");	
	h.addAndInc("hola");	
	h.addAndInc("hola");
	h.addAndInc("a");
	h.addAndInc("b");
	h.addAndInc("c");
	h.addAndInc("d");
	h.addAndInc("e");
	h.addAndInc("f");
	h.addAndInc("g");
	h.addAndInc("i");
	h.addAndInc("j");
	h.addAndInc("k");
	h.addAndInc("l");
	h.addAndInc("m");
	h.addAndInc("chau");

	//bool result = h.member("hola");	

	cout << "por hacer maximum" << endl;
	ParClaveApariciones maximo = h.maximum(2);

	//test basico de agregar y consultar si está agregado.
	cout << endl;
	cout << maximo.dameApariciones() << endl;
	cout << maximo.dameClave() << endl;
	cout << endl;

	return 0;
}
