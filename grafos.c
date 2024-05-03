/*
 * grafos.c
 *
 *  Created on: 21/04/2014
 *      Author: MJ Polo
 */
#include <stdio.h>
#include <stdlib.h>
#include "cola.h"
#include "monticulo.h"
#include "grafos.h"
#include "pila.h"
/**********************************************
/ Inicia correctamente directorio de vertices *
***********************************************/
int buscarGradoEntrada(int v, tipoGrafo *g) // Función auxiliar que calcula el grado de entrada de un vértice buscando en todas las listas de adyacencia
{
  int i, grado = 0;
  pArco p;
  for (i = 1; i <= g->orden; i++)
  {
    p = g->directorio[i].lista;
    while (p != NULL)
    {
      if (p->v == v)
        grado++;
      p = p->sig;
    }
  }
  return grado;
}
/**********************************************************************************************/
void iniciar(tipoGrafo *g) // Función que inicia todas las variables que almacenan los vértices de un grafo
{
  int i;
  for (i = 1; i <= g->orden; i++)
  {
    g->directorio[i].alcanzado = 0;
    g->directorio[i].gradoEntrada = buscarGradoEntrada(i, g);
    g->directorio[i].ordenTop = 0;
    g->directorio[i].distancia = INF;
    g->directorio[i].peso = INF;
    g->directorio[i].anterior = 0;
  }
}
/**********************************************************************************************/
void profundidadMejorado(int v_inicio, tipoGrafo *g) // Recorrido en profundidad que recorre todos los vértices del grafo
{
  int i;
  Cola c;
  colaCreaVacia(&c);
  colaInserta(v_inicio, &c);
  profundidad(v_inicio, g);
  for (i = 1; i <= g->orden; i++)
  {
    if (!g->directorio[i].alcanzado)
    {
      colaInserta(i, &c);
      profundidad(i, g);
    }
  }
}
/**********************************************************************************************/
void amplitudMejorado(int v_inicio, tipoGrafo *g)
{
  int i;
  Cola c;
  colaCreaVacia(&c);
  colaInserta(v_inicio, &c);
  amplitud(v_inicio, g);
  for (i = 1; i <= g->orden; i++)
  {
    if (!g->directorio[i].alcanzado)
    {
      colaInserta(i, &c);
      amplitud(i, g);
    }
  }
}
/**********************************************************************************************/
/* Ejercicio 2*/
int ordenTop(tipoGrafo *grafo) // Orden topológico del grafo utilizando un TAD Cola
{
  int i, v, w;
  pArco p;
  Cola c;
  colaCreaVacia(&c);
  for (i = 1; i <= grafo->orden; i++) // Busco en todo el grafo los vértices con grado de entrada 0
  {
    if (grafo->directorio[i].gradoEntrada == 0) // Si el grado de entrada es 0
      colaInserta(i, &c);                       // Se inserta en la cola
  }
  i = 1;
  while (!colaVacia(&c))
  {
    v = colaSuprime(&c);
    grafo->directorio[v].ordenTop = i++;
    p = grafo->directorio[v].lista;
    while (p != NULL)
    {
      w = p->v;
      grafo->directorio[w].gradoEntrada--;
      if (grafo->directorio[w].gradoEntrada == 0)
        colaInserta(w, &c);
      p = p->sig;
    }
  }
  if (i <= grafo->orden)
    return -1; // Si el grafo es cíclico
}
/**********************************************************************************************/
/* Ejercicio 3*/
void caminos1(int vInicio, tipoGrafo *g) // Algoritmo para grafos no ponderados
{
  iniciar(g);
  pArco p;
  int v, w;
  int distActual;
  iniciar(g);
  g->directorio[vInicio].distancia = 0;
  for (distActual = 0; distActual < g->orden; distActual++)
  {
    for (v = 1; v <= g->orden; v++)
    {
      if (!g->directorio[v].alcanzado && g->directorio[v].distancia == distActual)
      {
        g->directorio[v].alcanzado = 1;
        p = g->directorio[v].lista;
        while (p != NULL)
        {
          w = p->v;
          if (g->directorio[w].distancia == INF)
          {
            g->directorio[w].distancia = g->directorio[v].distancia + 1;
            g->directorio[w].anterior = v;
          }
          p = p->sig;
        }
      }
    }
  }
}
void caminos2(int vInicio, tipoGrafo *g) // Algoritmo para grafos no ponderados mejorado
{
  iniciar(g);
  int i, v, w;
  pArco p;
  Cola c;
  g->directorio[vInicio].distancia = 0;
  colaCreaVacia(&c);
  colaInserta(vInicio, &c);
  while (!colaVacia(&c))
  {
    v = colaSuprime(&c);
    p = g->directorio[v].lista;
    while (p != NULL)
    {
      w = p->v;
      if (g->directorio[w].distancia == INF)
      {
        g->directorio[w].distancia = g->directorio[v].distancia + 1;
        g->directorio[w].anterior = v;
        colaInserta(w, &c);
      }
      p = p->sig;
    }
  }
}
void dijkstra1(int vInicio, tipoGrafo *g) // Algoritmo de Dijkstra para grafos ponderados TAD Cola
{
  iniciar(g);
  int i, v, w;
  pArco p;
  Cola c;
  colaCreaVacia(&c);
  g->directorio[vInicio].peso = 0;
  colaInserta(vInicio, &c);
  while (!colaVacia(&c))
  {
    v = colaSuprime(&c);
    printf(" %d", v);
    p = g->directorio[v].lista;
    while (p != NULL)
    {
      w = p->v;
      if (g->directorio[w].peso > g->directorio[v].peso + p->peso)
      {
        g->directorio[w].peso = g->directorio[v].peso + p->peso;
        g->directorio[w].anterior = v;
        colaInserta(w, &c);
      }
      p = p->sig;
    }
  }
}
void dijkstra2(int vInicio, tipoGrafo *g) // Algoritmo de Dijkstra para grafos ponderados TAD Monticulo
{
  int i, v, w;
  pArco p;
  Monticulo m;
  tipoElementoM x;

  iniciar(g);          // Inicia el grafo
  iniciaMonticulo(&m); // Inicia el montículo con tamaño 0

  g->directorio[vInicio].distancia = 0;

  x.clave = 0;
  x.informacion = vInicio;
  insertar(x, &m); // Inserta el vértice inicial en el montículo
  while (!vacioMonticulo(m))
  {
    eliminarMinimo(&m, &x);
    v = x.informacion;
    if (!g->directorio[v].alcanzado)
    {
      g->directorio[v].alcanzado = 1;
      p = g->directorio[v].lista;
      while (p != NULL)
      {
        w = p->v;
        if (!g->directorio[w].alcanzado)
        {
          if (g->directorio[w].distancia > g->directorio[v].distancia + p->peso)
          {
            g->directorio[w].distancia = g->directorio[v].distancia + p->peso;
            g->directorio[w].anterior = v;
            x.clave = g->directorio[w].distancia;
            x.informacion = w;
            insertar(x, &m);
          }
        }
        p = p->sig;
      }
    }
  }
}
int costeyTrayectoria(int vIni, int vFin, tipoGrafo *g) // Algoritmo que muestra el camino mínimo entre dos vértices
{
  if (g->directorio[vFin].distancia == INF) // Si no se puede llegar del vértice inicial al final
    return INF;                             // Devuelve infinito
  else
  {
    Pila p;
    pilaCreaVacia(&p);
    int v = vFin;
    pilaInserta(v, &p);
    while (v != vIni)
    {
      v = g->directorio[v].anterior;
      pilaInserta(v, &p);
    }
    v = pilaSuprime(&p);
    printf(" %d", v);
    while (!pilaVacia(&p))
    {
      v = pilaSuprime(&p);
      printf(" -> %d", v);
    }
    printf(" = Camino de coste %d", g->directorio[vFin].distancia);
    return g->directorio[vFin].distancia;
  }
}
void todosCaminosMin(int vIni, tipoGrafo *g) // Algoritmo que muestra todos los caminos mínimos desde un vértice
{
  int i;
  dijkstra2(vIni, g); // Calculo los caminos mínimos desde vIni con djikstra
  printf("\nCaminos mínimos posibles desde el vértice %d:", vIni);
  for (i = 1; i <= g->orden; i++)
  {
    if (i != vIni && g->directorio[i].distancia != INF)
    {
      printf("\n - Camino mínimo entre %d y %d: ", vIni, i);
      costeyTrayectoria(vIni, i, g);
    }
    else if (i == vIni)
    {
      printf("\n - Camino mínimo entre %d y %d:  %d = Camino de coste 0", vIni, vIni, vIni);
    }
    else
    {
      printf("\n - No hay camino entre %d y %d", vIni, i);
    }
  }
  printf("\n");
}
/******************************************************************************/
/* Recorrido en PROFUNDIDAD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/*********************************************************************************/
void profundidad(int v_inicio, tipoGrafo *grafo)
{
  int w;
  pArco p;
  printf("%d ", v_inicio);
  grafo->directorio[v_inicio].alcanzado = 1;
  p = grafo->directorio[v_inicio].lista;
  while (p != NULL)
  {
    w = p->v;
    if (!grafo->directorio[w].alcanzado)
      profundidad(w, grafo);
    p = p->sig;
  }
}
/************************************************************************************************/
/* Recorrido en AMPLITUD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/************************************************************************************************/
void amplitud(int v_inicio, tipoGrafo *grafo)
{
  int w;
  pArco p;
  Cola c;

  colaCreaVacia(&c);
  colaInserta(v_inicio, &c);
  while (!colaVacia(&c))
  {
    w = colaSuprime(&c);
    if (!grafo->directorio[w].alcanzado)
    {
      printf("%d ", w);
      grafo->directorio[w].alcanzado = 1;
      p = grafo->directorio[w].lista;
      while (p != NULL)
      {
        w = p->v;
        colaInserta(w, &c);
        p = p->sig;
      }
    }
  }
}
/**********************************************************************************************/
/* Función auxiliar para ver el contenido de la estructura que representa un grafo en memoria */
/**********************************************************************************************/
void verGrafo(tipoGrafo *g)
{
  int i;
  pArco p;

  printf("\nGrafo  (Orden %d)\n\n", g->orden);
  printf("       alc gEnt oTop dist peso ant \n");
  printf("     +----+----+----+----+----+----+\n");

  for (i = 1; i <= g->orden; i++)
  {
    printf("  %2d | %2d | %2d | %2d |", i, g->directorio[i].alcanzado,
           g->directorio[i].gradoEntrada, g->directorio[i].ordenTop);
    if (g->directorio[i].distancia == INF)
      printf("  * |");
    else
      printf(" %2d |", g->directorio[i].distancia);
    if (g->directorio[i].peso == INF)
      printf("  * |");
    else
      printf(" %2d |", g->directorio[i].peso);
    printf(" %2d |", g->directorio[i].anterior);
    p = g->directorio[i].lista;
    while (p != NULL)
    {
      printf(" ->%2d", p->v); // Grafos no ponderados
      // printf(" ->%2d, %2d", p->v, p->peso); // Grafos ponderados
      p = p->sig;
    }
    printf("\n");
  }
  printf("     +----+----+----+----+----+----+\n\n");
}
