#include <stdlib.h>
#include <stdio.h>

/* Struct Aresta */
typedef struct{
    int v;
    int w;
} Aresta;

/* Struct Grafo representado por matriz */
struct grafo{
    int n;
    int m;
    int **adj;
};

/* Um Grafo é um ponteiro para um grafo, ou seja, Grafo contém o endereço de um grafo. */
typedef struct grafo *Grafo;

/* TAD GRAFO */
Grafo GRAFOcria(int);
void GRAFOinsereA(Grafo, Aresta);
void GRAFOremoveA(Grafo, Aresta);
void GRAFOimprime(Grafo);
void GRAFOdestroi(Grafo);
void GRAFOgrau(Grafo);

/* Construtores de grafos */
Grafo GRAFOconstroiCompleto(int);
Grafo GRAFOconstroiCiclo(int);
Grafo GRAFOconstroiGrade(int);

/* Algoritmos */
void BPrec(Grafo G);
void visitaBP(Grafo G, int v);
void BL(Grafo G);
void visitaBL(Grafo G, int v);
void Ponte(Grafo G);
void dijkstra(Grafo G, int v);
