#include <iostream>
#include "ConcurrentHashMap.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cassert>

#include <vector>
#include <queue>
#include <tuple>
#include <math.h>   
#include <cmath>
#include <algorithm>
#include <functional>
#include <ctime>
#include <chrono>
#include <limits>
#include <climits>
#include "time.h"
#include <utility>  
#include <random>

#include <iostream>
#include <sstream>
#include <exception>

#define TIMESTAMP chrono::high_resolution_clock::now


#define GRANULARIDAD nanoseconds


void TiemposExp1(int cantIteraciones){   
	
	ofstream myfile;
	myfile.open("TiemposExp1.csv");
	list<string> l = { "8000", "2000-1", "2000-2", "2000-3", "2000-4", "2000-5", "2000-6", "2000-7", "2000-8", "2000-9" };
	myfile << "Cantidad de p_archivos;";
	myfile << "Sin concurrencia;";
	myfile << "Con concurrencia;\n";
	ParClaveApariciones p;
	vector< chrono::GRANULARIDAD >  tiempos(cantIteraciones);//vector donde voy poniendo los tiempos de las iteraciones para luego calcularle la mediana
	for(int j=1; j<=10; j++){// j es p_archivos 
		cout << " Midiendo con p_archivos: " << j << endl;
		for(int i = 0; i<cantIteraciones ;i++){//hago 50 iteraciones para despues tomar la mediana
			
			auto start = TIMESTAMP();
			p = maximumSinConcurrencia(j, 10,l);
			auto end = TIMESTAMP();
			tiempos[i] = chrono::duration_cast<chrono::GRANULARIDAD>(end - start) ;
		}
		std::sort(tiempos.begin(), tiempos.end());//ordeno para saber la mediana
		myfile << j << ";";
		myfile << tiempos.at(tiempos.size()/2).count() << ";";//pongo la mediana de maximoConConcurrencia con p_archivos = j	
		for(int i = 0; i<cantIteraciones ;i++){//hago 50 iteraciones para despues tomar la mediana
			auto start = TIMESTAMP();
			p = maximumConConcurrencia(j, 10,l);
			auto end = TIMESTAMP();
			tiempos[i] = chrono::duration_cast<chrono::GRANULARIDAD>(end - start) ;
		}
		std::sort(tiempos.begin(), tiempos.end());//ordeno para saber la mediana
		myfile << tiempos.at(tiempos.size()/2).count() << ";\n";//pongo la mediana de maximoSinConcurrencia con p_archivos = j
	}
}

void TiemposExp2(int cantIteraciones){   
	
	ofstream myfile;
	myfile.open("TiemposExp2.csv");
	list<string> l = { "corpus-0", "corpus-1", "corpus-2", "corpus-3","corpus-4", "corpus-5","corpus-6", "corpus-7","corpus-8", "corpus-9", };
	myfile << "Cantidad de p_archivos;";
	myfile << "Sin concurrencia;";
	myfile << "Con concurrencia;\n";
	ParClaveApariciones p;
	vector< chrono::GRANULARIDAD >  tiempos(cantIteraciones);//vector donde voy poniendo los tiempos de las iteraciones para luego calcularle la mediana
	for(int j=1; j<=10; j++){// j es p_archivos 
		cout << " Midiendo con p_archivos: " << j << endl;
		for(int i = 0; i<cantIteraciones ;i++){//hago 50 iteraciones para despues tomar la mediana
			
			auto start = TIMESTAMP();
			p = maximumSinConcurrencia(j, 10,l);
			auto end = TIMESTAMP();
			tiempos[i] = chrono::duration_cast<chrono::GRANULARIDAD>(end - start) ;
		}
		std::sort(tiempos.begin(), tiempos.end());//ordeno para saber la mediana
		myfile << j << ";";
		if(tiempos.size() % 2)
			myfile << (tiempos.at(tiempos.size()/2).count() + tiempos.at(tiempos.size()/2 + 1).count()) / 2 << ";";//pongo la mediana de maximoSinConcurrencia con p_archivos = j
		else
			myfile << tiempos.at(tiempos.size()/2 + 1).count() << ";";

		for(int i = 0; i<cantIteraciones ;i++){//hago 50 iteraciones para despues tomar la mediana
			auto start = TIMESTAMP();
			p = maximumConConcurrencia(j, 10,l);
			auto end = TIMESTAMP();
			tiempos[i] = chrono::duration_cast<chrono::GRANULARIDAD>(end - start) ;
		}
		std::sort(tiempos.begin(), tiempos.end());//ordeno para saber la mediana
		if(tiempos.size() % 2)
			myfile << (tiempos.at(tiempos.size()/2).count() + tiempos.at(tiempos.size()/2 + 1).count()) / 2 << ";\n";//pongo la mediana de maximoSinConcurrencia con p_archivos = j
		else
			myfile << tiempos.at(tiempos.size()/2 + 1).count() << ";\n";
	}
}

void TiemposExp3(int cantIteraciones){   
	
	auto max_threads = 26;

	ofstream myfile;
	myfile.open("TiemposExp3.csv");
	list<string> l = {"corpus-letra-0",  "corpus-letra-1",  "corpus-letra-2",  "corpus-letra-3",  "corpus-letra-4",  "corpus-letra-5",  "corpus-letra-6",  "corpus-letra-7",  "corpus-letra-8",  "corpus-letra-9",  "corpus-letra-10",  "corpus-letra-11",  "corpus-letra-12",  "corpus-letra-13",  "corpus-letra-14",  "corpus-letra-15",  "corpus-letra-16",  "corpus-letra-17",  "corpus-letra-18",  "corpus-letra-19",  "corpus-letra-20",  "corpus-letra-21",  "corpus-letra-22",  "corpus-letra-23",  "corpus-letra-24",  "corpus-letra-25" };
	myfile << "Cantidad de p_archivos;";
	myfile << "Sin concurrencia;";
	myfile << "Con concurrencia;\n";
	ParClaveApariciones p;
	vector< chrono::GRANULARIDAD >  tiempos(cantIteraciones);//vector donde voy poniendo los tiempos de las iteraciones para luego calcularle la mediana
	for(int j=1; j<=max_threads; j++){// j es p_archivos 
		cout << " Midiendo con p_archivos: " << j << endl;
		for(int i = 0; i<cantIteraciones ;i++){//hago 50 iteraciones para despues tomar la mediana
			
			auto start = TIMESTAMP();
			p = maximumSinConcurrencia(j, 10,l);
			auto end = TIMESTAMP();
			tiempos[i] = chrono::duration_cast<chrono::GRANULARIDAD>(end - start) ;
		}
		std::sort(tiempos.begin(), tiempos.end());//ordeno para saber la mediana
		myfile << j << ";";
		if(tiempos.size() % 2)
			myfile << (tiempos.at(tiempos.size()/2).count() + tiempos.at(tiempos.size()/2 + 1).count()) / 2 << ";";//pongo la mediana de maximoSinConcurrencia con p_archivos = j
		else
			myfile << tiempos.at(tiempos.size()/2 + 1).count() << ";";

		for(int i = 0; i<cantIteraciones ;i++){//hago 50 iteraciones para despues tomar la mediana
			auto start = TIMESTAMP();
			p = maximumConConcurrencia(j, 10,l);
			auto end = TIMESTAMP();
			tiempos[i] = chrono::duration_cast<chrono::GRANULARIDAD>(end - start) ;
		}
		std::sort(tiempos.begin(), tiempos.end());//ordeno para saber la mediana
		if(tiempos.size() % 2)
			myfile << (tiempos.at(tiempos.size()/2).count() + tiempos.at(tiempos.size()/2 + 1).count()) / 2 << ";\n";//pongo la mediana de maximoSinConcurrencia con p_archivos = j
		else
			myfile << tiempos.at(tiempos.size()/2 + 1).count() << ";\n";
	}
}

int main(){
	//TiemposExp1(3);
	TiemposExp2(3);// MIDE CON 10 ARCHIVOS DEL MISMO TAMAÑO
	//TiemposExp3(25);
	return 0;
}
