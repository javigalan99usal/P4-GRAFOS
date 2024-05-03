# Sesión Grafos

#ejercicio1: ejercicio1.c grafos.h grafos.o cola.o
#	gcc -g ejercicio1.c grafos.o cola.o -o ejercicio1

#ejercicio2: ejercicio2.c grafos.h grafos.o cola.o 
#	gcc -g ejercicio2.c grafos.o cola.o -o ejercicio2

ejercicio3: ejercicio3.c grafos.h grafos.o cola.o monticulo.o pila.o
	gcc -g ejercicio3.c grafos.o cola.o monticulo.o pila.o -o ejercicio3

grafos.o: grafos.c grafos.h
	gcc -g -c grafos.c
cola.o: cola.c cola.h
	gcc -g -c cola.c
# hay que modificar tipoElemento de monticulo 	
# CUIDADO hay que cambiar tipoElemento de monticulo a tipoElementoM ....
monticulo.o:monticulo.c monticulo.h
	gcc -g -c monticulo.c
limpiar:
	rm *.o	


