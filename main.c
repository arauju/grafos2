#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "GRAFOmatriz.h"
#include "FILA.h"
//#include "GRAFOlista.h"

int menuPrincipal(){
    int escolha, r;
    do {
        printf("********** GRAFOS **********\n\n");
        printf("1. Gerar grafo\n");
        printf("2. Manipular grafo\n");
	      printf("3. Algoritmos\n");
        printf("0. Sair\n");
        printf("> ");
        r = scanf("%d",&escolha);
    } while (escolha < 0 || escolha > 3);
    return escolha;
}

int menuConstrucao(){
    int escolha, r;
    do {
        printf("*** Construcao ***\n\n");
        printf("1. Grafo vazio\n");
        printf("2. Grafo completo\n");
        printf("3. Grafo ciclo\n");
        printf("> ");
        r = scanf("%d",&escolha);
    } while (escolha < 1 || escolha > 3);
    return escolha;
}

int menuManipulacao(){
    int escolha, r;
    do {
        printf("*** Manipulacao ***\n\n");
        printf("1. Imprime\n");
        printf("2. Lista graus\n");
        printf("3. Destroi\n");
        printf("> ");
        r = scanf("%d",&escolha);
    } while (escolha < 1 || escolha > 3);
    return escolha;
}

int menuAlgoritmos(){
    int escolha, r;
    do {
        printf("*** Manipulacao ***\n\n");
        printf("1. Busca em Profundidade\n");
        printf("2. Busca em Largura\n");
        printf("3. Ponte\n");
        printf("4. Dijkstra\n");
        printf("> ");
        r = scanf("%d",&escolha);
    } while (escolha < 1 || escolha > 4);
    return escolha;
}

int main(int argc, char *argv[]){

    int escolha, n, r;

    Grafo G;

    do {
	escolha = menuPrincipal();
	switch (escolha) {
	    case 1: /* Geracao de um grafo */
		switch(menuConstrucao()) {
		    case 1: /* Grafo vazio */
			printf("Entre com o valor de n: ");
			r = scanf("%d",&n);
			G = GRAFOcria(n);
    			GRAFOimprime(G);
			break;
		    case 2: /* Grafo completo */
		        printf("Entre com o valor de n: ");
			r = scanf("%d",&n);
			G = GRAFOconstroiCompleto(n);
    			GRAFOimprime(G);
			break;
		    case 3: /* Grafo Ciclo */
			printf("Entre com o valor de n: ");
			r = scanf("%d",&n);
			G = GRAFOconstroiCiclo(n);
    			GRAFOimprime(G);
			break;
		}
		break;
	    case 2: /* Manipulacao de um grafo */
		switch(menuManipulacao()) {
		    case 1: /* Imprime */
			GRAFOimprime(G);
			break;
		    case 2: /* Lista graus */
			GRAFOgrau(G);
			break;
		    case 3: /* Destroi */
			GRAFOdestroi(G);
			break;
		}
		break;
	    case 3: /* Algoritmos */
		switch(menuAlgoritmos()) {
		    case 1: /* BP */
			BPrec(G);
			break;
		    case 2: /* BL */
			BL(G);
			break;
		    case 3: /* Ponte */
			Ponte(G);
			break;
        case 4: /* Dijkstra */
      dijkstra(G);
		}
		break;
	    default:
	        break;
	}
    } while (escolha != 0);
}
