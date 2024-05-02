#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

/* ============== Implementación de un TAD cola con memoria dinámica ============== */

// Función para crear una cola vacía
void colaCreaVacia(Cola *c) {
    c->frente = NULL;
    c->final = NULL;
}

// Función para verificar si la cola está vacía
bool colaVacia(Cola *c) {
    if (c->frente == NULL) {
        return true;
    } else {
        return false;
    }
}

// Función para insertar un elemento en la cola
void colaInserta(int x, Cola *c) {
    if (c == NULL) {
        printf("Error: La cola no ha sido inicializada.\n");
        exit(EXIT_FAILURE);
    }
    NodoCola* nuevoNodo = (NodoCola*)malloc(sizeof(NodoCola));
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo nodo.\n");
        exit(EXIT_FAILURE);
    }
    nuevoNodo->dato = x;
    nuevoNodo->siguiente = NULL;
    if (c->frente == NULL) {
        c->frente = nuevoNodo;
        c->final = nuevoNodo;
    } else {
        c->final->siguiente = nuevoNodo;
        c->final = nuevoNodo;
    }
}

// Función para suprimir el primer elemento de la cola y devolver su valor
int colaSuprime(Cola *c) {
    if (colaVacia(c)) {
        printf("Error: La cola está vacía.\n");
        exit(EXIT_FAILURE);
    }
    NodoCola* nodoSuprimido = c->frente;
    int datoSuprimido = nodoSuprimido->dato;
    c->frente = nodoSuprimido->siguiente;
    if (c->frente == NULL) {
        c->final = NULL;
    }
    free(nodoSuprimido);
    return datoSuprimido;
}