/* Universidade Federal do Espírito Santo - Ufes
   Centro Universitário Norte do Espírito Santo - Ceunes
   Teoria dos Grafos 2018/1 - TG20181
   Tarefa exercícios URI2440
   Data: 20/04
   Autor: Elyabe Alves
*/ 

#include <bits/stdc++.h>
using namespace std;

typedef struct  vertice
{
	int no;
	struct vertice *prox;
} Vertice;

typedef struct grafo
{
	int V, E;
	Vertice *adj;
} Grafo;


// Cria e retorna ponteiro para um grafo
// V : Quantidade de vértices
Grafo *criar_grafo( int V )
{
	Grafo *G = (Grafo*)malloc(sizeof(Grafo));
	if ( G != NULL )
	{
		G -> V = V;
		G -> E = 0;
		G -> adj = (Vertice*)calloc( sizeof(Vertice), V );
		for ( int i = 0; i < V; i++ )
			G -> adj[i].prox = NULL;
	}
	return G;
}

// Desaloca e libera a memória ocupada pelo grafo
// G : Ponteiro para o grafo
Grafo *desalocar_grafo( Grafo *G )
{
	if ( G )
	{	
		free( G -> adj );
		free( G );
		G = NULL;
	}

	return G;
}

// Cria e retorna ponteiro para um novo vértice
// x : Rótulo do vértice a ser adicionado
Vertice *alocar_vertice( int x )
{
	Vertice *novo = (Vertice*)malloc(sizeof(Vertice));
	if ( novo != NULL )
	{	novo -> no = x;
		novo -> prox = NULL;
	} else
	  {  printf("Erro.\n");
		exit(1);
	  }
	
	return novo;
}


// Insere uma aresta num grafo simples considerando a simetria
// G : Ponteiro para o grafo
// v,w : Vértices extremidades da aresta 
Grafo *inserir_aresta( Grafo *G, int v, int w)
{
	if ( v != w )
	{
		Vertice *p = G -> adj[v].prox;
		while ( p!= NULL )
		{
			if ( p -> no == w ) break;
			p = p -> prox;
		}	
		
		if ( p == NULL )
		{
			//Inserção na lista de v			
			Vertice *novo = alocar_vertice(w);
			novo -> prox = G -> adj[v].prox;
			G -> adj[v].prox = novo;
			
		
			//Inserção na lista do w
			novo = alocar_vertice(v);
			novo -> prox = G -> adj[w].prox;
			G -> adj[w].prox = novo;

			G -> E++;
		}
		
	}
	return G;
}

// Preenche um grafo
// G : Ponteiro para o grafo a ser analisado
// E : Quantidade de arestas a serem inseridas
Grafo *preencher_grafo( Grafo *G, int E )
{
	int v, w;
	while ( E--)
	{
		scanf("%d%d", &v, &w );
		G = inserir_aresta(G, v-1, w-1);
	}
	return G;
}

// Determina recursivamente a qual componente conexa o vértice pertence
// G : Ponteiro para o grafo
// r : Ponteiro para vértice a ser analisado
// vtComponentes: Ponteiro para vetor que armazena componentes
// numComp : Controle de umeração das componentes 
void determinar_componente( Grafo *G, Vertice *r, int *vtComponentes, int numComp )
{
	//Lista de vértices adjacentes a r
	Vertice *lst = G -> adj[ r -> no ].prox;
	vtComponentes[r -> no] = numComp;

	//Enquanto não determinar todas as componentes
	while ( lst )
	{
		// Se não foi determinada, determina para os adjacentes a ele
		if ( vtComponentes[lst -> no ] < 0 )
			determinar_componente( G, lst, vtComponentes, numComp );
		lst = lst -> prox;
	}
}

// Calcula e retorna a quantidade de Componentes conexas do grafo G
// G : Ponteiro para o grafo a ser analisado
int qtd_componentes( Grafo *G )
{
	//Vetor que armazena a numeração da componente conexa ao qual o vértice pertence 
	int *vtComponentes = (int*)calloc(sizeof(int), G->V), numComp = 0, r;
	//Seta todas as posições do vetor para -1
	//Todos os vértices pertencem a componentes distintas
	memset(vtComponentes, -1, (G->V)*sizeof(int) );

	Vertice *v = alocar_vertice(0);
	for ( v -> no = 0; v -> no < G -> V; v -> no++ )
	{
		if ( vtComponentes[v -> no] < 0 )
			determinar_componente( G, v, vtComponentes, numComp++ );
	}
	
	return numComp;
}


int main()
{
	int  N, M ;
	Grafo *G;
	scanf("%d%d", &N, &M );
	G = criar_grafo(N);
	G = preencher_grafo(G, M);
	
	//Se houver apenas uma componente, então a cidade foi conectada
	//Senão, precisaríamos de, no mínimo n-1 arestas para conectá-las
	printf("%d\n", qtd_componentes(G) );
	return 0;
}