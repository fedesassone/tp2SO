#include <iostream>
#include "ConcurrentHashMap.hpp"
#include "ListaAtomica.hpp"
#include <thread>

using namespace std;
void pushearNumeros(int desde,int hasta,Lista<int>& lista){
	for (int i = desde; i <= hasta; i++){
		lista.push_front(i);
		//cout << "pusheo numero :  " << i <<  endl;
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

	 //ConcurrentHashMap h;

	// cout << "hashmap construido!" << endl;
	 //h.addAndInc("hola");	
	 //h.addAndInc("hola");	
	// h.addAndInc("hola");
	 //h.addAndInc("a");
	// h.addAndInc("b");
	// h.addAndInc("c");
	// h.addAndInc("d");
	// h.addAndInc("e");
	// h.addAndInc("f");
	// h.addAndInc("g");
	// h.addAndInc("i");
	// h.addAndInc("j");
	// h.addAndInc("k");
	// h.addAndInc("l");
	// h.addAndInc("m");
	// h.addAndInc("chau");

	//bool result = h.member("hola");	
	//cout << result << endl;
	//result = h.member("a");
	//cout << result << endl;

	 //cout << "por hacer maximum" << endl;
	 //ParClaveApariciones maximo = h.maximum(2);

	//test basico de agregar y consultar si está agregado.
	// cout << endl;
	 //cout << maximo.dameApariciones() << endl;
	 //cout << maximo.dameClave() << endl;
	// cout << endl;



	// //test basico de agregar y consultar si está agregado.
	// cout << endl;
	// cout << maximo.dameApariciones() << endl;
	// cout << maximo.dameClave() << endl;
	// cout << endl;
	/*list<string> archs;
	archs.push_back("prueba");
	archs.push_back("pruebaa");

	ConcurrentHashMap h = count_words_list(archs);*/

	 // bool result = h.member("macri");
	 // cout << result << endl;
	 // result = h.member("gato");
	 // cout << result << endl;

	 //****test para probar count_words(string arch) (ej2)

	// ConcurrentHashMap i = count_words("corpus");
	// bool result = i.member("incorporacion");
	// cout << "incorporacion pertenece al ConcurrentHashMap ? : " << result << endl;
	// result = i.member("atenta");
	// cout << "atenta pertenece al ConcurrentHashMap ? : " << result << endl;
	
	//****test para probar count_words(list<string>arch) (ej3)
	
	// list<string> archs;
	// archs.push_back("prueba");
	// archs.push_back("corpus");
	// ConcurrentHashMap i = count_words(archs);
	// bool result = i.member("incorporacion");
	// cout << "incorporacion pertenece al ConcurrentHashMap ? : " << result << endl;
	// result = i.member("atenta");
	// cout << "atenta pertenece al ConcurrentHashMap ? : " << result << endl;
	// result = i.member("ginebra");
	// cout << "ginebra pertenece al ConcurrentHashMap ? : " << result << endl;
	// result = i.member("hola");
	// cout << "hola pertenece al ConcurrentHashMap ? : " << result << endl;
	// result = i.member("chau");
	// cout << "chau pertenece al ConcurrentHashMap ? : " << result << endl;
	// result = i.member("roto");
	// cout << "roto pertenece al ConcurrentHashMap ? : " << result << endl;
	// result = i.member("pepe");
	// cout << "pepe pertenece al ConcurrentHashMap ? : " << result << endl;
	
	
	//*****test para probar count words(unsigned int n, list<string>archs) (ej4) NO ESTA FUNCIONANDO SE ROMPE EN EL JOIN
	
	// list<string> archs;
	// archs.push_back("prueba");
	// archs.push_back("corpus");
	// ConcurrentHashMap i = count_words(2,archs);
	// bool result = i.member("incorporacion");
	// cout << "incorporacion pertenece al ConcurrentHashMap ? : " << result << endl;
	// result = i.member("atenta");
	// cout << "atenta pertenece al ConcurrentHashMap ? : " << result << endl;
	// result = i.member("ginebra");
	// cout << "ginebra pertenece al ConcurrentHashMap ? : " << result << endl;
	// result = i.member("hola");
	// cout << "hola pertenece al ConcurrentHashMap ? : " << result << endl;
	// result = i.member("chau");
	// cout << "chau pertenece al ConcurrentHashMap ? : " << result << endl;
	// result = i.member("roto");
	// cout << "roto pertenece al ConcurrentHashMap ? : " << result << endl;
	// result = i.member("pepe");
	// cout << "pepe pertenece al ConcurrentHashMap ? : " << result << endl;
	

	//*******test para probar maximumSinConcurrencia(unsigned int p_archivos, unsigned int p_maximos, list<string>archs) (ej5)

	// list<string> archs;
	// archs.push_back("prueba");
	// archs.push_back("corpus");
	// ParClaveApariciones par = maximumSinConcurrencia(2, 2,archs);
	// cout << "clave maxima : " << par.dameClave() << endl;
	// cout << "apariciones maxima : " << par.dameApariciones() << endl;


	//****test para probar push_front
	// creo 50 threads que van a estar agregar a la lista todo el tiempo numeros del 1 al 1000
	// cuando ya se agregaron todos los numeros verifico que se hayan agregado bien
	// recorro todos los numero y pregunto si pertenecen a la lista
	Lista<int> lista;
	std::thread t[50];
	for (int i = 0; i < 50; ++i)
	{
		int desde = i * ( 100000 / 50 );
		////cout << "desde: " << desde << endl;
		int hasta = (i+1) * ( 100000 / 50 ) - 1;
		////cout << "hasta: " << hasta << endl;
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

