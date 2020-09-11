#include "GRAFOmatriz.h"
#include "FILA.h"

/********** TAD GRAFO **********/

/* Cria matriz [ l ] [ c ] vazia */
int **MATRIZint(int l, int c){
    int i, j;
    int ** m = malloc(l * sizeof(int *));
    for (i = 0; i < l; i++)
        m[i] = malloc(c * sizeof(int));
    for (i = 0; i < l; i++)
        for (j = 0; j < c; j++)
            m[i][j] = 0;
    return m;
}

/* Cria um grafo vazio de n vertices */
Grafo GRAFOcria(int n){
    Grafo G = malloc(sizeof(Grafo));
    G->n = n;
    G->m = 0;
    G->adj = MATRIZint(n,n);
    return G;
}

/* Funcao para inserir uma aresta em um grafo */
void GRAFOinsereA(Grafo G, Aresta e){
    int v = e.v;
    int w = e.w;
    if (G->adj[v][w] == 0) {
        G->m++;
        G->adj[v][w] = 1;
        G->adj[w][v] = 1;
    }
}

/* Funcao para remover uma aresta de um grafo */
void GRAFOremoveA(Grafo G, Aresta e){
    int v = e.v;
    int w = e.w;
    if (G->adj[v][w] == 1) {
        G->m--;
        G->adj[v][w] = 0;
        G->adj[w][v] = 0;
    }
}

/* Funcao para imprimir um grafo */
void GRAFOimprime(Grafo G) {
    int v, w;
    printf("%d vertices, %d arestas\n", G->n, G->m);
    printf("   ");
    for (v = 0; v < G->n; v++)
      printf(" %2d", v);
    printf("\n");
    for (v = 0; v < G->n; v++) {
        printf( "%2d:", v);
        for (w = 0; w < G->n; w++)
            printf( " %2d", G->adj[v][w]);
        printf( "\n");
    }
}

/* Funcao para destruir um grafo */
void GRAFOdestroi(Grafo G){
    int i;
    for (i = 0; i < G->n; i++) {
        free(G->adj[i]);
    }
    free(G->adj);
    free(G);
}

/* Funcao para exibir os graus dos vertices de um grafo */
void GRAFOgrau(Grafo G){
    int v, w, grau;

    for (v = 0; v < G->n; v++) {
	      grau = 0;
        for (w = 0; w < G->n; w++){
            if (G->adj[v][w] == 1) {
                grau++;
            }
        }
	printf("grau[%d] = %d\n", v, grau);
    }
}

/********** CONSTRUTORES **********/

Grafo GRAFOconstroiCompleto(int n){
    int i, j;
    Grafo G = GRAFOcria(n);
    for (i = 0; i < n; i++){
	for (j = i+1; j < n; j++){
	    Aresta e;
	    e.v = i;
            e.w = j;
	    GRAFOinsereA(G, e);
	}
    }
    return G;
}

Grafo GRAFOconstroiCiclo(int n){
    int i;
    Grafo G = GRAFOcria(n);
    for (i = 0; i < n; i++){
	Aresta e;
	e.v = i;
        e.w = i+1;

	if (i == n-1) e.w = 0;

	GRAFOinsereA(G, e);
    }
    return G;
}

/********** ALGORITMOS **********/
int cont;
int *ordem, *pai, *menor;

void BPrec(Grafo G){
  int i;
  ordem = (int*) malloc (G->n * sizeof(int));
  cont = 0;

  for (i = 0; i < G->n; i++)
    ordem[i] = -1;

  for (i = 0; i < G->n; i++){
    if (ordem[i] < 0){
      visitaBP(G, i);
    }
  }
}

void visitaBP (Grafo G, int v){
  int j;
  ordem[v] = cont ++;
  for (j = 0; j < G->n; j++){
    if (G->adj[v][j] == 1 && ordem[j] < 0)
        visitaBP(G, j);
  }
}


void BL(Grafo G){
  int i;
  cont = 0;
  ordem = (int*) malloc (G->n * sizeof(int));
  for (i = 0; i < G->n; i++)
    ordem[i] = -1;

  for (i = 0; i < G->n; i++){
    if (ordem[i] < 0)
      visitaBL(G, i);
  }
}

void visitaBL(Grafo G, int i){
  int j, v;
  FILAcria(G->n);
  FILAinsere(i);

  while(FILAvazia() != 1){
    v = FILAremove();
    ordem[v] = cont ++;
    for (j = 0; j < G->n; j++){
      if (G->adj[v][j] == 1 && ordem[j] < 0){
          FILAinsere(j);
      }
    }
  }
}

void PonteRec(Grafo G, int v){
  int i, min;
  ordem[v] = cont ++;
  min = ordem[v];

  for(i = 0 ; i < G->n; i++){
    if(ordem[i] < 0){
      pai[i] = v;
      PonteRec(G, i);
      if(menor[i] < min){
        min = menor[i];
      }else{
        if(ordem[i] < min && i != pai[v]){
          min = ordem[i];
        }
      }
    }
    menor[v] = min;
  }
}

void Ponte(Grafo G){
  int i;
  cont = 0;
  ordem = malloc(G->n * sizeof(int));
  pai = malloc(G->n * sizeof(int));
  menor = malloc(G->n * sizeof(int));

  for(i = 0; i < G->n; i++){
    pai[i] = -1;
    ordem[i] = -1;
    menor[i] = -1;
  }

  for(i = 0; i < G->n; i++){
    if(ordem[i] < 0){
      pai[i] = i;
      PonteRec(G, i);
    }
  }

  for(i = 0; i < G->n; i++){
    if(menor[i] == ordem[i] && pai[i] != i)
      printf("%d - %d\n", pai[i], i);
  }
}

int pesquisaMenor(Grafo G, int *dist, int *aberto){
  int menor = 99999999;
  int i, r;
  for(i = 0 ; i < G->n ; i++){
    if(dist[i] < menor && aberto[i] == 1){
      menor = dist[i];
      r = i;
    }
  }

  if( menor == 99999999){
    return -1;
  } else {
    return r;
  }
}

int min(int i , int j ){
  if(i < j){
    return i ;
  }else{
    return j ;
  }
}

void dijkstra(Grafo G, int v){
  int i;
  int *dist = (int*) malloc(G->n * (sizeof(int)));
  int *pred = (int*) malloc(G->n * (sizeof(int)));
  int *aberto = (int*) malloc(G->n * (sizeof(int)));
  int acabou = 0;

  for(i = 0 ; i < G->n ; i++){
    dist[i] = 0 ;
    pred[i] = -1;
    aberto[i] = 1;
  }

  while(!acabou){
    int r = pesquisaMenor(G, dist, aberto);
    if(r >= 0){
      aberto[r] = 0;
    }else{
      acabou = 1;
    }

    for(i = 0 ; i < G->n ; i++){
      if(G->adj[r][i] == 1 && aberto[i] == 1){
        int p = min(dist[i],dist[r]) + G->adj[r][i];
        if(p < dist[i]){
          dist[i] = p;
          pred[i] = r;
        }
      }
    }
  }

  for(i = 0 ; i < G->n ; i++){
    printf("Distancia de %d para %d: %d\n", v, i, dist[i]);
  }
}
