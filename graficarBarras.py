#!/usr/bin/python
import pandas as pd
import seaborn as sns #es "opcional". Si lo sacas el grafico queda poco estetico, pero sirve igual
import matplotlib.pyplot as plt
import sys

#utiiza los archivos btPuroAleatorio.res y btPodaAleatorio.res para compararlos y correlacionar con 3^n

if __name__ == "__main__":

	p_archivos = None
	sinConcurr = None
	conConcurr = None

	with open(sys.argv[1]) as f:
		lines = f.readlines()
		lines.pop(0) #Borrar encabezados
		p_archivos = map(int, [line.split(";")[0] for line in  lines])
		sinConcurr = map(float, [line.split(";")[1] for line in lines])
		conConcurr = map(float, [line.split(";")[2] for line in lines])


	df = pd.DataFrame()
	#df["p_archivos"] = p_archivos
	df["sin concurrencia"] = sinConcurr
	df["con concurrencia"] = conConcurr

	ax = df.plot(kind="bar", legend=True)
	ax.set_xlabel("cantidad de archivos")
	ax.set_ylabel("tiempo (nanosegundos)")
	plt.show()
	#plt.savefig("fig.png")
