#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "monticulo.h"

//
//  Fución que inicializa un montículo vacío.
//
void iniciaMonticulo(Monticulo *m)
{
    m->tamanno = 0; // Inicializa el tamaño del montículo a 0
}
//
//  Función que indica si el montículo está o no vacío
//
int vacioMonticulo(Monticulo m)
{
    if (m.tamanno == 0)
    {
        return 1; // Montículo vacío
    }
    else
    {
        return 0; // Montículo no vacío
    }
}
//
//  Función que inserta un elemento en el montículo
//
int insertar(tipoElementoM x, Monticulo *m)
{
    if (m->tamanno < MAXIMO) // Si el montículo no está lleno
    {
        m->tamanno++;                // Incrementa el tamaño del montículo
        m->elemento[m->tamanno] = x; // Inserta el elemento en la última posición
        //printf(" - Insertado elemento %d\n", x.clave);
        if (m->tamanno != 1)
            filtradoAscendente(m, m->tamanno); // Filtra el elemento hacia arriba
        return 0;                              // Inserción correcta
    }
    else
    {
        return 1; // Montículo lleno (no se pudo insertar el elemento)
    }
}
//
//  Función que elimina el mínimo del montículo
//
int eliminarMinimo(Monticulo *m, tipoElementoM *minimo)
{
    if (m->tamanno > 0) // Si el montículo no está vacío
    {
        *minimo = m->elemento[1];                 // Devuelve el mínimo por parámetro
        m->elemento[1] = m->elemento[m->tamanno]; // El último elemento ocupa el lugar del mínimo
        m->tamanno--;                             // Decrementa el tamaño del montículo
        filtradoDescendente(m, 1);                // Filtra el elemento hacia abajo
        return 0;                                 // Eliminación correcta
    }
    else
    {
        return 1; // Montículo vacío (no se pudo eliminar el mínimo)
    }
}
//
//  Función que decrementa la clave de un elemento del montículo
//
void decrementarClave(int pos, tipoClave cantidad, Monticulo *m)
{
    if (pos > 0 && pos < m->tamanno)
    {                                       // Si la posición es válida
        m->elemento[pos].clave -= cantidad; // Decrementa la clave del elemento
        filtradoAscendente(m, pos);         // Filtra el elemento hacia arriba
    }
    else
    {
        printf("Posición no válida, no se ha podido decrementar la clave\n");
    }
}
//
//  Función que incrementa la clave de un elemento del montículo
//
void incrementarClave(int pos, tipoClave cantidad, Monticulo *m)
{
    if (pos > 0 && pos < m->tamanno)
    {                                       // Si la posición es válida
        m->elemento[pos].clave += cantidad; // Incrementa la clave del elemento
        filtradoDescendente(m, pos);        // Filtra el elemento hacia abajo
    }
    else
    {
        printf("Posición no válida, no se ha podido incrementar la clave\n");
    }
}
//
//  Función que indica si un montículo es o no montículo
//
int esMonticulo(Monticulo m)
{
    int nodosInternos = m.tamanno / 2; // Número de nodos internos del montículo
    int clavePadre;
    for (int i; i < nodosInternos; i++) // Recorro los nodos internos comparando el padre con sus hijos, excepto el último
    {
        clavePadre = m.elemento[i].clave;
        if (clavePadre > m.elemento[2 * i].clave || clavePadre > m.elemento[2 * i + 1].clave)
        {             // Si el padre es mayor que alguno de sus hijos
            return 0; // No es montículo
        }
    }
    clavePadre = m.elemento[nodosInternos].clave;         // Compruebo el último nodo interno, que puede tener solo un hijo
    if (clavePadre > m.elemento[2 * nodosInternos].clave) // Si el padre es mayor que el hijo izquierdo
    {
        return 0; // No es montículo
    }
    if (2 * nodosInternos + 1 < m.tamanno) // Si existe el hijo derecho
    {
        if (clavePadre > m.elemento[2 * nodosInternos + 1].clave) // Si el padre es mayor que el hijo derecho
        {
            return 0; // No es montículo
        }
    }
    return 1; // Es montículo
}
//
//  Función que crea un montículo a partir de un vector de elementos
//
void crearMonticulo(Monticulo *m)
{
    int i;
    for (i = m->tamanno / 2; i >= 1; i--) // Recorro los nodos internos desde el último hasta el primero
    {
        filtradoDescendente(m, i); // Filtra el elemento hacia abajo
    }
}

//
//  Función auxiliar: Filtrado Ascendente
//
void filtradoAscendente(Monticulo *m, int i)
{
    tipoElementoM nodo = m->elemento[i];
    int hueco = i;
    while (hueco > 1) // Mientras el hueco no este en la raiz del monticulo
    {
        if (nodo.clave < m->elemento[hueco / 2].clave) // Si el padre es mayor que el hueco
        {
            m->elemento[hueco] = m->elemento[hueco / 2]; // Movemos el padre el hueco, y el hueco al lugar del padre
            hueco = hueco / 2;
        }
        else // El padre es menor que el hueco
        {
            m->elemento[hueco] = nodo; // Asigno el nodo que ha ido ascendiendo al hueco
            return;
        }
    }
    if (hueco == 1)                // Si el hueco ha llegado a la raiz del monticulo
        m->elemento[hueco] = nodo; // Asigno el nodo que ha ido ascendiendo a la raíz
}
//
//  Función auxiliar: Filtrado Descendente
//
void filtradoDescendente(Monticulo *m, int i)
{
    int hijoUsado, hueco = i;
    tipoElementoM raiz = m->elemento[i]; // Guarda el elemento a filtrar
    tipoElementoM hijoMenor;
    bool finFiltrado = false;
    while (hueco * 2 <= m->tamanno && finFiltrado == false) // Mientras el hueco tenga al menos un hijo, hacer
    {
        hijoMenor = m->elemento[hueco * 2]; // Por ahora, su hijo más pequeño es el izquierdo
        hijoUsado = 0;                      // Si utilizo el hijo izquierdo para el filtrado, hijoUsado = 0
        if (hueco * 2 + 1 <= m->tamanno)    // Tiene hijo derecho
        {
            if (hijoMenor.clave > m->elemento[hueco * 2 + 1].clave) // Comparamos los hijos izquierdo y derecho
            {
                hijoMenor = m->elemento[hueco * 2 + 1]; // Si el hijo derecho es el más pequeño, se guarda
                hijoUsado = 1;                          // Si utilizo el hijo izquierdo para el filtrado, hijoUsado = 1
            }
        }
        if (hijoMenor.clave < raiz.clave) // Si el hijo menor es más pequeño que el padre, sube a su posición
        {
            m->elemento[hueco] = hijoMenor;
            if (hijoUsado == 0) // Si el hijo usado es el izquiedo
            {
                hueco = hueco * 2; // Movemos el hueco al lugar del hijo izquierdo
            }
            else // Si el hijo usado es el derecho
            {
                hueco = hueco * 2 + 1; // Movemos el hueco al lugar del hijo derecho
            }
        }
        else // Si el hijo menor no es más pequeño que el padre
        {
            finFiltrado = true;
        }
    }
    m->elemento[hueco] = raiz; // Asigno la raíz en el hueco (en caso de que sus hijos no sean menores o en caso de no tener hijos)
}
//
//  Implementación del algoritmo de ordenación por montículo (heapsort)
//
void heapsort(Monticulo *m)
{

    int i, tamOriginal = m->tamanno;
    tipoElementoM raiz;

    crearMonticulo(m); // Creo un montículo con los elementos del array

    printf("El monticulo creado a partir del array es:\n"); // Imprimo el monticulo formado
    for (i = 1; i <= m->tamanno; i++)
        printf("%d ", m->elemento[i].clave);
    printf("\n");

    for (i = 0; i < tamOriginal; i++) // Para cada uno de los elementos del array
    {
        if (eliminarMinimo(m, &raiz)) // Si no puede eliminar el elemento mínimo
        {
            printf("Error al intentar eliminar la raiz del monticulo.\n");
            return;
        }
        else // Si elimina la raíz correctamente
        {
            printf("\t- Elemento eliminado %d\n", raiz.clave);
            m->elemento[tamOriginal - i] = raiz; // Almaceno la raiz eliminada en el hueco que ha quedado al final del monticulo
        }
    }
    m->tamanno = tamOriginal; // Restauro el tamanno original del monticulo para poder utilizarlo ya que al eliminar todos sus elementos, habría quedado vacío
}