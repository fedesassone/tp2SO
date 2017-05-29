#include <iostream>
#include "ConcurrentHashMap.hpp"

using namespace std;

int main(void) {
	ConcurrentHashMap h;
	int i;
	
	h = count_words("corpus");
	cout << "por entrar a for " << endl;
	for (i = 0; i < 26; i++) {
		cout << "entro for " << endl;
		for (auto it = h.tabla[i].CrearIt(); it.HaySiguiente(); it.Avanzar()) {
			auto t = it.Siguiente();
			cout << t.dameClave() << " " << t.dameApariciones() << endl;
		}
	}

	return 0;
}

