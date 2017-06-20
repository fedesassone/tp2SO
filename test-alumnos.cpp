#include <iostream>
#include "ConcurrentHashMap.hpp"
#include "ListaAtomica.hpp"
#include <thread>

using namespace std;
void pushearNumeros(int desde,int hasta,Lista<int>& lista){
	for (int i = desde; i <= hasta; i++){
		cout << "pusheo numero :  " << i <<  endl;
		lista.push_front(i);
	}
}

bool pertenece(int a,Lista<int>& lista){
	Lista<int>::Iterador it = lista.CrearIt();
	bool res = false;
	while ( it.HaySiguiente() ){
		if( it.Siguiente() == a ) res = true;
		it.Avanzar();
	}
	return res;
}
int main(void) {

	Lista<int> lista;
	std::thread t[50];
	for (int i = 0; i < 50; ++i)
	{
		int desde = i * ( 100000 / 50 );
		//cout << "desde: " << desde << endl;
		int hasta = (i+1) * ( 100000 / 50 ) - 1;
		//cout << "hasta: " << hasta << endl;
	 	t[i]=std::thread(pushearNumeros,desde,hasta,std::ref(lista));

	}

	for(int k=0;k<50;k++){
			t[k].join();
	}
	bool listaok = false;
	for(int j=0;j<100000;j++){
		listaok = pertenece(j,lista);
	}

	if(listaok) cout << "Funciona la lista" << endl;
	return 0;
}

