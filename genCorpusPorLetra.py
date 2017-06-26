#!/usr/bin/python
import random 
import sys

#utiiza los archivos btPuroAleatorio.res y btPodaAleatorio.res para compararlos y correlacionar con 3^n

if __name__ == "__main__":

	
	palabras = [[] for x in range (0, 26)]
	
	#cargar palabras
	with open(sys.argv[1]) as f:
		lines = f.readlines()
		for palabra in lines:
			if len(palabra) > 0:
				hash_func = ord(palabra[0]) - ord('a')
				palabras[hash_func].append(palabra.replace("\n", ""))


	#generar archivos
	for x in range(0, len(palabras)):
		f = open("corpus-letra-" + str(x), "w")
		len_lista = len(palabras[x])
		if len_lista is not 0:
			for y in range(0, int(sys.argv[2])):
				num = random.randint(0, len_lista - 1)
				f.write("{0}\n".format(palabras[x][num]))

		f.close()
