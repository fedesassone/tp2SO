#include "ListaAtomica.hpp"
#include "ConcurrentHashMap.hpp"
#include <iostream>
#include <istream>
#include <fstream>
#include <atomic>
#include <string>
#include <mutex>
#include <thread>
#include <list> 

using namespace std;

int dameLibre(vector<bool>& v){
	for(int i=0;i<v.size();i++)
	{
		if(v[i]==true)return i;
	}
	return 0; //solo para que no tire warning
}


//modificar esto de abajo para que sea void y modifiquen el mejor maximo hasta el momento

void obtenerMaximasRepeticiones(atomic<int>& siguienteFilaALeer, ParClaveApariciones& maximo, ConcurrentHashMap& chp){
	
	int actual = atomic_fetch_add(&siguienteFilaALeer, 1);

	while(actual<26){
		Lista<ParClaveApariciones> *lista = &chp.tabla[actual];
		lista->mtx.lock();


		Lista< ParClaveApariciones >::Iterador iterador = lista->CrearIt();
		ParClaveApariciones parClaveAparicionesActual;
		ParClaveApariciones maximoLocal = ParClaveApariciones("a",0);
			while(iterador.HaySiguiente()){
				parClaveAparicionesActual = iterador.Siguiente();
				if(parClaveAparicionesActual.dameApariciones() >= maximoLocal.dameApariciones()){
					maximoLocal = parClaveAparicionesActual;	
				}
				
			iterador.Avanzar();
			}	
		lista->mtx.unlock();	
		chp.lockMaximum.lock();
		if(maximoLocal.dameApariciones() >= maximo.dameApariciones()){
			maximo = maximoLocal;
		}	
		chp.lockMaximum.unlock();
		actual = atomic_fetch_add(&siguienteFilaALeer, 1);
	}
}

void ConcurrentHashMap::addAndInc(const string& key){
	char PrimeraLetra = key[0];
	int indice = dameIndice(PrimeraLetra);
	this->vectorMutex[indice].lock();
	
	Lista < ParClaveApariciones > *lista = &tabla[indice];
	//mutex mtx;
	//lista->mtx.lock();	
	
	Lista< ParClaveApariciones >::Iterador iterador = lista->CrearIt();

	//iterador tiene una lista y un nodo siguiente
	//arranca con esta lista y como nodo siguiente el head de lista.
	//vamos a iterar una lista de ClaveAparicion
	bool encontrada = false;
	cout << "addAndInc: por recorrer lista" << endl;
	while(iterador.HaySiguiente() && !encontrada){
		ParClaveApariciones& parClaveApariciones = iterador.Siguiente();
		if (parClaveApariciones.dameClave() == key ) 
		{
			encontrada = true;
			cout << "addAndInc: clave encontrada!" << endl;
			cout << parClaveApariciones.dameApariciones() << endl;
			parClaveApariciones.aumentarApariciones();
			cout << parClaveApariciones.dameApariciones() << endl;
		}
		iterador.Avanzar();
	}
	cout << "addAndInc: lista recorrida" << endl;
	if(!encontrada)
	{
		const ParClaveApariciones parNuevo = ParClaveApariciones(key,1);
		lista->push_front(parNuevo);
	}
	
	cout << "addAndInc: por hacer unlock" << endl;
	
	//lista->mtx.unlock();
	this->vectorMutex[indice].unlock();
	cout << "addAndInc: saliendo..." << endl;
}

bool ConcurrentHashMap::member(const string& key){
	bool res = false;
	//me pasan una key
	//qvq <key,x> existe
	char primeraLetra = key[0];
	int indice = dameIndice(primeraLetra);
	//ahora buscamos en la tabla si está el par <key,x>
	Lista < ParClaveApariciones > *lista = &tabla[indice];
	Lista< ParClaveApariciones >::Iterador iterador = lista->CrearIt();
	//iterador tiene una lista y un nodo siguiente
	//arranca con esta lista y como nodo siguiente el head de lista.
	//vamos a iterar una lista de ClaveAparicion
	while(iterador.HaySiguiente()){
		ParClaveApariciones parClaveApariciones = iterador.Siguiente();
		if (parClaveApariciones.dameClave() == key ) return true;
		iterador.Avanzar();
	}
	return res;
}

ParClaveApariciones ConcurrentHashMap::maximum(unsigned int nt){
	
	std::thread t[nt];
	std::atomic<int> siguienteFilaALeer;
	ParClaveApariciones maximo = ParClaveApariciones("a",0);
	siguienteFilaALeer = 0;
	
	for (int i = 0; i <nt; ++i)
	{
		t[i]=std::thread(obtenerMaximasRepeticiones,std::ref(siguienteFilaALeer), std::ref(maximo), std::ref(*this));
	}

	for(int k=0;k<nt;k++){
		t[k].join();
	}

	return maximo;

}



int dameIndice(char a){
	int indice;
	switch(a) 
	{ 
	   case 'a': indice = 0;
	   case 'b': indice = 1;
	   case 'c': indice = 2;
	   case 'd': indice = 3;
	   case 'e': indice = 4;
	   case 'f': indice = 5;
	   case 'g': indice = 6;
	   case 'h': indice = 7;
	   case 'i': indice = 8;
	   case 'j': indice = 9;
	   case 'k': indice = 10;
	   case 'l': indice = 11;
	   case 'm': indice = 12;
	   case 'n': indice = 13;
	   case 'o': indice = 14;
	   case 'p': indice = 15;
	   case 'q': indice = 16;
	   case 'r': indice = 17;
	   case 's': indice = 18;
	   case 't': indice = 19;
	   case 'u': indice = 20;
	   case 'v': indice = 21;
	   case 'w': indice = 22;
	   case 'x': indice = 23;
	   case 'y': indice = 24;
	   case 'z': indice = 25;

	}
	return indice;
}


ConcurrentHashMap count_words(string arch){
	ConcurrentHashMap j;
	ifstream TestEntrada;
	string aux;
	TestEntrada.open(arch.c_str());
	while(!TestEntrada.eof()){
		TestEntrada >> aux;
		j.addAndInc(aux);
	}
	return j;
}

void cargarConcurrentHashMap(ConcurrentHashMap& chp,string arch){
	ifstream TestEntrada;
	string aux;
	TestEntrada.open(arch.c_str());
	while(!TestEntrada.eof()){
		TestEntrada >> aux;
		chp.addAndInc(aux);
	}
}

ConcurrentHashMap count_words_list(list<string>archs){
	 ConcurrentHashMap res;
	 std::thread t[archs.size()];
	 list<string>::iterator pos;
	 pos = archs.begin();
	 int i = 0;
	  while( pos != archs.end())
	  {
	  	t[i]=std::thread(cargarConcurrentHashMap,std::ref(res),std::ref(*pos));
	 	cout << *pos << endl;
	 	pos++;
	 	i++;
	  }
	  	for(int k=0;k<archs.size();k++){
			t[k].join();
		}

	 return res;
}


void cargarConcurrentHashMapThread(ConcurrentHashMap& chp,list<string>::iterator& pos,list<string>archs)
{
	chp.lockCargar.lock();
	list<string>::iterator it = pos;
	pos ++;
	chp.lockCargar.unlock();
	string archivo;
	while( it != archs.end())
	{
		archivo = *it;
		cargarConcurrentHashMap(chp,archivo);
		
		chp.lockCargar.lock();
		it = pos;
		pos ++;
		chp.lockCargar.unlock();
	}

}

ConcurrentHashMap count_words_list_n(unsigned int n,list<string>archs){
	ConcurrentHashMap res;
	std::thread t[n];
	list<string>::iterator pos;
	pos = archs.begin();
	for (int i = 0; i < n; ++i)
	{
		t[i]=std::thread(cargarConcurrentHashMapThread,std::ref(res),std::ref(pos),std::ref(archs));
	}

	for(int k=0;k<n;k++){
		t[k].join();
	}
	return res;
}

/*ParClaveApariciones maximum(unsigned int p_archivos, unsigned int p_maximos, list<string>archs){
	ConcurrentHashMap chm;

}*/
