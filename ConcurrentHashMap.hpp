#ifndef CONCURRENTHASHMAP_H
#define CONCURRENTHASHMAP_H

#include "ListaAtomica.hpp"
#include <vector>

using namespace std;

typedef int apariciones;
typedef string clave;

class ConcurrentHashMap{
private:
	vector < Lista < pair<clave,apariciones> > > tabla{26};

public:
	ConcurrentHashMap(){};//Constructor por defecto
	
	void addAndInc(string key);
	bool member(clave key);

};

#endif /* LISTA_ATOMICA_H__ */