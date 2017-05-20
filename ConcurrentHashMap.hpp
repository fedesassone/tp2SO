#ifndef CONCURRENTHASHMAP_H
#define CONCURRENTHASHMAP_H

#include "ListaAtomica.hpp"
#include <vector>
#include <string>

using namespace std;



class ParClaveApariciones{
private:
	int apariciones;
 	string clave;
public:
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
	vector < Lista < ParClaveApariciones > > tabla{26};
public:
	ConcurrentHashMap(){};//Constructor por defecto
	
	void addAndInc(string key);
	bool member(string key);

};

int dameIndice(char a);


#endif /* LISTA_ATOMICA_H__ */