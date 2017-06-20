#ifndef CONCURRENTHASHMAP_H
#define CONCURRENTHASHMAP_H

#include "ListaAtomica.hpp"
#include <vector>
#include <string>
#include <mutex>
#include <list>

using namespace std;



class ParClaveApariciones{
private:
	atomic<int> apariciones;
 	string clave;
public:
	ParClaveApariciones(){};
	ParClaveApariciones(string clave,int apariciones)
	{
		this->clave = clave;
		this->apariciones = apariciones;
	}
	string dameClave(){
		return this->clave;
	}
	int dameApariciones(){
		return this->apariciones;
	}
	void aumentarApariciones(){
		this->apariciones++;
	}

};

class ConcurrentHashMap{
private:
public:
	mutable std::mutex lockMaximum;
	mutable std::mutex lockCargar;
	vector < Lista < ParClaveApariciones > > tabla{26};

  mutable vector<mutex> vectorMutex{26};

	ConcurrentHashMap(){};//Constructor por defecto

	void addAndInc(const string& key);
	bool member(const string& key);
	ParClaveApariciones maximum(unsigned int nt);

	  // Move initialization
  ConcurrentHashMap(ConcurrentHashMap&& other) {
    std::lock_guard<std::mutex> lock(other.lockMaximum);
    std::lock_guard<std::mutex> lock1(other.lockCargar);
    tabla = std::move(other.tabla);
  }

  // Copy initialization
  ConcurrentHashMap(const ConcurrentHashMap& other) {
    std::lock_guard<std::mutex> lock(other.lockMaximum);
    std::lock_guard<std::mutex> lock1(other.lockCargar);
    //tabla = other.tabla;

    for(int i = 0;i<other.tabla.size();i++)
    {
    	
    		Lista < ParClaveApariciones > lista = (other.tabla[i]);
			Lista< ParClaveApariciones >::Iterador iterador = lista.CrearIt();
			//iterador tiene una lista y un nodo siguiente
			//arranca con esta lista y como nodo siguiente el head de lista.
			//vamos a iterar una lista de ClaveAparicion
			while(iterador.HaySiguiente()){
				ParClaveApariciones parClaveApariciones = iterador.Siguiente();
				tabla[i].push_front(parClaveApariciones);
				iterador.Avanzar();
			}
    	
 	}
  }

  // Move assignment
  ConcurrentHashMap& operator = (ConcurrentHashMap&& other) {
    std::lock(lockMaximum, other.lockMaximum, lockCargar, other.lockCargar);
    std::lock_guard<std::mutex> self_lock(lockMaximum, std::adopt_lock);
    std::lock_guard<std::mutex> self_lock1(lockCargar, std::adopt_lock);
    std::lock_guard<std::mutex> other_lock(other.lockMaximum, std::adopt_lock);
    std::lock_guard<std::mutex> other_lock1(other.lockCargar, std::adopt_lock);
    tabla = std::move(other.tabla);
    return *this;
  }

  // Copy assignment
  ConcurrentHashMap& operator = (const ConcurrentHashMap& other) {
    std::lock(lockMaximum, other.lockMaximum, lockCargar, other.lockCargar);
    std::lock_guard<std::mutex> self_lock(lockMaximum, std::adopt_lock);
    std::lock_guard<std::mutex> self_lock1(lockCargar, std::adopt_lock);
    std::lock_guard<std::mutex> other_lock(other.lockMaximum, std::adopt_lock);
    std::lock_guard<std::mutex> other_lock1(other.lockCargar, std::adopt_lock);
    for(int i = 0;i<other.tabla.size();i++)
    {
    	tabla[i] = other.tabla[i];
    }
    return *this;
  }


};
void cargarConcurrentHashMap(ConcurrentHashMap& chp,string arch);
void cargarConcurrentHashMapThread(ConcurrentHashMap& chp,atomic<int>& siguiente,list<string>& archs);
void cargarConcurrentHashMapThreadMaximumLectura(std::vector<ConcurrentHashMap>& chms,list<string>::iterator it,int desde,int hasta);
ConcurrentHashMap count_words(string arch);
ConcurrentHashMap count_words(list<string>archs);
ConcurrentHashMap count_words(unsigned int n,list<string>archs);
ParClaveApariciones maximumSinConcurrencia(unsigned int p_archivos, unsigned int p_maximos, list<string>archs);
ParClaveApariciones maximumConConcurrencia(unsigned int p_archivos, unsigned int p_maximos, list<string>archs);
void obtenerMaximasRepeticiones(atomic<int> &siguienteFilaALeer, ParClaveApariciones &maximo, ConcurrentHashMap& chp);
int dameIndice(char a);
int dameLibre(vector<bool>& v);

#endif /* LISTA_ATOMICA_H__ */