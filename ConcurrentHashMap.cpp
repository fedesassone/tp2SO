#include "ListaAtomica.hpp"
#include "ConcurrentHashMap.hpp"
#include <iostream>
#include <atomic>
#include <string>
#include <mutex>
#include <thread> 

using namespace std;

int dameLibre(vector<bool>& v){
	for(int i=0;i<v.size();i++)
	{
		if(v[i]==true)return i;
	}
	return 0; //solo para que no tire warning
}


//modificar esto de abajo para que sea void y modifiquen el mejor maximo hasta el momento

void obtenerMaximasRepeticiones(Lista<ParClaveApariciones> *lista,ParClaveApariciones& maximo){
	Lista< ParClaveApariciones >::Iterador iterador = lista->CrearIt();
	ParClaveApariciones parClaveAparicionesActual;
		while(iterador.HaySiguiente()){
			parClaveAparicionesActual = iterador.Siguiente();
			lockMaximum.lock();
			if(parClaveAparicionesActual.dameApariciones() >= maximo.dameApariciones()){
				maximo = parClaveAparicionesActual;	
			}
			lockMaximum.unlock();
		iterador.Avanzar();
	}	
}

void ConcurrentHashMap::addAndInc(string key){
	char PrimeraLetra = key[0];
	int indice = dameIndice(PrimeraLetra);
	
	Lista < ParClaveApariciones > *lista = &tabla[indice];
	//mutex mtx;
	lista->mtx.lock();
	Lista< ParClaveApariciones >::Iterador iterador = lista->CrearIt();

	//iterador tiene una lista y un nodo siguiente
	//arranca con esta lista y como nodo siguiente el head de lista.
	//vamos a iterar una lista de ClaveAparicion
	bool encontrada = false;
	while(iterador.HaySiguiente() && !encontrada){
		ParClaveApariciones parClaveApariciones = iterador.Siguiente();
		if (parClaveApariciones.dameClave() == key ) 
		{
			encontrada = true;
			parClaveApariciones.aumentarApariciones();
		}
		iterador.Avanzar();
	}
	
	if(!encontrada)
	{
		const ParClaveApariciones parNuevo = ParClaveApariciones(key,1);
		lista->push_front(parNuevo);
	}
	
	lista->mtx.unlock();
	
}

bool ConcurrentHashMap::member(string key){
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
	std::vector<bool> libres(26,true);
	// for (int j=0;j<libres->size();j++){
	// 	libres[j] = true;
	// }
	int libre;
	while(siguienteFilaALeer<26){

		libre = dameLibre(libres);
		Lista<ParClaveApariciones> *lista = &(this->tabla[siguienteFilaALeer]);
		siguienteFilaALeer++;
		t[libre] = std::thread(obtenerMaximasRepeticiones(lista,maximo));
		//t[libre] = new std::thread(obtenerMaximasRepeticiones(lista,maximo));		
	}

	for(int k=0;k<nt;k++){
		t[i]->join();
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