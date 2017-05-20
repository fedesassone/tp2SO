#include <iostream>
#include "ConcurrentHashMap.hpp"

using namespace std;

int main(void) {

	ConcurrentHashMap h;

	h.addAndInc("hola");

	bool result = h.member("hola");	

	//test basico de agregar y consultar si está agregado.
	cout << endl;
	cout << result;
	cout << endl;

	return 0;
}
