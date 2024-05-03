#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"

/* ============== Implementación de un TAD pila con memoria dinámica ============== */

// Función para crear una pila vacía
void pilaCreaVacia(Pila *p) {
    p->tope = NULL;
}

// Función para verificar si la pila está vacía
bool pilaVacia(Pila *p) {
    return p->tope == NULL;
}

// Función para insertar un elemento en la pila
void pilaInserta(int x, Pila *p) {
    NodoPila* nuevoNodo = (NodoPila*)malloc(sizeof(NodoPila));
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo nodo.\n");
        exit(EXIT_FAILURE);
    }
    nuevoNodo->dato = x;
    nuevoNodo->siguiente = p->tope;
    p->tope = nuevoNodo;
}

// Función para suprimir el elemento en el tope de la pila y devolver su valor
int pilaSuprime(Pila *p) {
    if (pilaVacia(p)) {
        printf("Error: La pila está vacía.\n");
        exit(EXIT_FAILURE);
    }
    NodoPila* nodoSuprimido = p->tope;
    int datoSuprimido = nodoSuprimido->dato;
    p->tope = nodoSuprimido->siguiente;
    free(nodoSuprimido);
    return datoSuprimido;
}
