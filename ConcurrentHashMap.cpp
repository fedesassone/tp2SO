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
	for(int i=0;i<v.size();i++) {
		if(v[i]==true)return i;
	}
	return 0; 
}

void obtenerMaximasRepeticiones(atomic<int>& siguienteFilaALeer, ParClaveApariciones& maximo, ConcurrentHashMap& chp){
	
	int actual = atomic_fetch_add(&siguienteFilaALeer, 1);

	while(actual<26){
		Lista<ParClaveApariciones> *lista = &chp.tabla[actual];
		lista->mtx.lock();

		Lista< ParClaveApariciones >::Iterador iterador = lista->CrearIt();
		ParClaveApariciones parClaveAparicionesActual;
		ParClaveApariciones maximoLocal("a",0);
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

	char primeraLetra = key[0];
	int indice = dameIndice(primeraLetra);
	Lista < ParClaveApariciones > *lista = &tabla[indice];

	if(!this->member(key)){
		//agregar
		lista->push_front(ParClaveApariciones(key,1));
	} else {
		//incrementar
		Lista< ParClaveApariciones >::Iterador iterador = lista->CrearIt();
		
		while(iterador.HaySiguiente()){

			ParClaveApariciones& parClaveApariciones = iterador.Siguiente();

			if (parClaveApariciones.dameClave() == key ){
				parClaveApariciones.aumentarApariciones();
				break;
			}
			iterador.Avanzar();
		}
	}
}

bool ConcurrentHashMap::member(const string& key){
	char primeraLetra = key[0];
	int indice = dameIndice(primeraLetra);
	Lista < ParClaveApariciones > *lista = &tabla[indice];

	this->vectorMutex[indice].lock();	
	Lista< ParClaveApariciones >::Iterador iterador = lista->CrearIt();

	while(iterador.HaySiguiente()){
		ParClaveApariciones parClaveApariciones = iterador.Siguiente();
		if (parClaveApariciones.dameClave() == key ) {
			this->vectorMutex[indice].unlock();	
			return true;
		}
		iterador.Avanzar();
	}
	this->vectorMutex[indice].unlock();	
	return false;
}

ParClaveApariciones ConcurrentHashMap::maximum(unsigned int nt){
	
	std::thread t[nt];
	std::atomic<int> siguienteFilaALeer;
	ParClaveApariciones maximo("a",0);
	siguienteFilaALeer = 0;
	
	for (int i = 0; i <nt; ++i) {
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
	   break;
	   case 'b': indice = 1;
	   break;
	   case 'c': indice = 2;
	   break;
	   case 'd': indice = 3;
	   break;
	   case 'e': indice = 4;
	   break;
	   case 'f': indice = 5;
	   break;
	   case 'g': indice = 6;
	   break;
	   case 'h': indice = 7;
	   break;
	   case 'i': indice = 8;
	   break;
	   case 'j': indice = 9;
	   break;
	   case 'k': indice = 10;
	   break;
	   case 'l': indice = 11;
	   break;
	   case 'm': indice = 12;
	   break;
	   case 'n': indice = 13;
	   break;
	   case 'o': indice = 14;
	   break;
	   case 'p': indice = 15;
	   break;
	   case 'q': indice = 16;
	   break;
	   case 'r': indice = 17;
	   break;
	   case 's': indice = 18;
	   break;
	   case 't': indice = 19;
	   break;
	   case 'u': indice = 20;
	   break;
	   case 'v': indice = 21;
	   break;
	   case 'w': indice = 22;
	   break;
	   case 'x': indice = 23;
	   break;
	   case 'y': indice = 24;
	   break;
	   case 'z': indice = 25;
	   break;

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
		if(TestEntrada.eof()) break;
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
		if(TestEntrada.eof()) break;
		chp.addAndInc(aux);
	}
}

ConcurrentHashMap count_words(list<string>archs){
	 ConcurrentHashMap res;
	 std::thread t[archs.size()];
	 list<string>::iterator pos;
	 pos = archs.begin();
	 int i = 0;
	  while( pos != archs.end())
	  {
	  	t[i]=std::thread(cargarConcurrentHashMap,std::ref(res),std::ref(*pos));
	 	pos++;
	 	i++;
	  }
	  	for(int k=0;k<archs.size();k++){
			t[k].join();
		}

	 return res;
}


void cargarConcurrentHashMapThread(ConcurrentHashMap& chp,atomic<int>& siguiente,list<string>& archs)
{
		int actual = atomic_fetch_add(&siguiente, 1);
		while(actual < archs.size()){
			auto it = archs.begin();
			std::advance(it, actual);
			string archivo(*it);
			cargarConcurrentHashMap(chp, archivo);
			actual = atomic_fetch_add(&siguiente, 1);
		}

}


ConcurrentHashMap count_words(unsigned int n,list<string>archs){
	ConcurrentHashMap res;
	std::thread t[n];
	atomic<int> siguiente(0);
	for (int i = 0; i < n; ++i) {	
		t[i]=std::thread(cargarConcurrentHashMapThread,std::ref(res),std::ref(siguiente),std::ref(archs));

	}

	for(int k=0;k<n;k++){
		t[k].join();
	}

	return res;
}


void cargarConcurrentHashMapThreadMaximumLectura(std::vector<ConcurrentHashMap>& chms,list<string>::iterator it,int desde,int hasta){

	std::advance(it, desde);
	int actual = desde;
	while( actual <= hasta ){

		string archivo(*it);
		chms[actual] = count_words(archivo);
		it++;
		actual++;
	}
}

ParClaveApariciones maximumSinConcurrencia(unsigned int p_archivos, unsigned int p_maximos, list<string>archs){
	int n = archs.size();
	std::vector<ConcurrentHashMap> chms(n, ConcurrentHashMap());
	std::thread t_archivos[p_archivos];
	auto it = archs.begin();
	for (int i = 0; i < p_archivos; ++i)
	{
		int desde = i * ( archs.size() / p_archivos );
		int hasta = (i+1) * ( archs.size() / p_archivos ) - 1;
		if ( i == p_archivos - 1 ) hasta = archs.size()-1;
	 	t_archivos[i]=std::thread(cargarConcurrentHashMapThreadMaximumLectura,std::ref(chms),it,desde,hasta);
	}

	for(int k=0;k<p_archivos;k++){
			t_archivos[k].join();
	}
	int apariciones;
	for(int i=1;i<n;i++){
		for (int j = 0; j < 26; j++) {
			for (auto it = chms[i].tabla[j].CrearIt(); it.HaySiguiente(); it.Avanzar()) {
				auto t = it.Siguiente();
				apariciones = t.dameApariciones();
				for(int r=0;r<apariciones;r++){
					chms[0].addAndInc(t.dameClave());				
				}
			}
		}
	}
	ParClaveApariciones maximo = chms[0].maximum(p_maximos);
	
	return maximo;
}
ParClaveApariciones maximumConConcurrencia(unsigned int p_archivos, unsigned int p_maximos, list<string>archs){

	ConcurrentHashMap chm = count_words(p_archivos,archs);
	ParClaveApariciones res = chm.maximum(p_maximos);
	return res;

}

