#ifndef CONCURRENTHASHMAP_H
#define CONCURRENTHASHMAP_H

#include "ListaAtomica.hpp"
#include <vector>
#include <string>
#include <mutex>

using namespace std;



class ParClaveApariciones{
private:
	int apariciones;
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
	mutex lockMaximum;
public:
	vector < Lista < ParClaveApariciones > > tabla{26};

	ConcurrentHashMap(){};//Constructor por defecto

	void addAndInc(string key);
	bool member(string key);
	ParClaveApariciones maximum(unsigned int nt);

};

int dameIndice(char a);
int dameLibre(vector<bool>& v);
void obtenerMaximasRepeticiones(Lista<ParClaveApariciones> *lista,ParClaveApariciones& maximo);

#endif /* LISTA_ATOMICA_H__ */