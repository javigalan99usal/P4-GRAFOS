#ifndef PILA_H
#define PILA_H

#include <stdbool.h>

/* ============== Implementación de un TAD pila con memoria dinámica ============== */

// Definición del tipo de dato para los nodos de la pila
typedef struct NodoPila {
    int dato;
    struct NodoPila* siguiente;
} NodoPila;

// Definición del tipo de dato Pila
typedef struct Pila {
    NodoPila* tope;
} Pila;

// Funciones públicas de la Pila
void pilaCreaVacia(Pila* pila); // Inicia o crea la pila como una pila vacía sin ningún elemento
bool pilaVacia(Pila* pila); // Devuelve verdadero si la pila est vacía y falso en caso contrario
void pilaInserta(int dato, Pila* pila); // Inserta un elemento al final de la pila
int pilaSuprime(Pila* pila); // Suprime el elemento que está al final de la pila y devuelve su valor

#endif

