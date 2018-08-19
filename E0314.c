/* Universidade Federal do Espírito Santo - Ufes
   Centro Universitário Norte do Espírito Santo - Ceunes
   Teoria dos Grafos 2018/1 - TG20181
   Aula 12.03.2018
   Representação de grafos como lista de adjacências
   Autor: Elyabe Alves
*/

// #include <bits/stdc++.h>
// using namespace std;

typedef struct vertice 
{
	int no;
	struct vertice *prox;
} Vertice;

typedef struct grafo
{
	int V, E;
	Vertice *adj;
} Grafo;

// Cria e retorna ponteiro para grafo
// V : Quantidade de vértices 
Grafo *criarGrafo( int V )
{
	Grafo *G = (Grafo*)malloc(sizeof(Grafo));
	if ( G != NULL )
	{
		G -> V = V;
		G -> E = 0;
		G -> adj = (Vertice*)calloc( V, sizeof(Vertice));
		G -> adj[0].prox = NULL;
	}
	return G;
}

// Aloca e retorna ponteiro para novo vértice
// x : Valor/Rótulo do novo vértice
Vertice *novoVertice( int x )
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

// Exibe a matriz de adjacência na tela 
// G : Grafo a ser impresso
void exibirGrafo( Grafo *G )
{
	int v;
	Vertice *p;
	for ( v = 0; v < G -> V; v++ )
	{
		p = G -> adj[v].prox;
		printf("[%d] -> ", v );
		while ( p != NULL )
		{
			printf ("%d ", p -> no );
			p = p -> prox; 
		};
		printf("\n");
	}
}

// Insere aresta (v,w) considerando a simetria
// G : Ponteiro para o grafo
// v, w : Vértices extremidades da aresta
Grafo *inserirAresta( Grafo *G, int v, int w )
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
			Vertice *novo = novoVertice(w);
			novo -> prox = G -> adj[v].prox;
			G -> adj[v].prox = novo;
			
		
			//Inserção na lista do w
			novo = novoVertice(v);
			novo -> prox = G -> adj[w].prox;
			G -> adj[w].prox = novo;

			G -> E++;
		}
		
	}
}


// Calcula e retorna o grau de um vértice v num grafo G
// G : Grafo
// v : Rótulo do vértice 
unsigned int calcularGrau( Grafo *G, int v  )
{
	unsigned int grau = 0;
	Vertice *p = G -> adj[v].prox;
	while ( p != NULL ) 
	{ 
		grau++;
		p = p -> prox;
	}
	return grau;
}

// Cria e retorna vetor de de graus dos vértices de um grafo
// G : Ponteiro para o grafo
unsigned int *vetorGraus( Grafo *G )
{
	int q = G -> V;
	unsigned int *vetorGraus = (unsigned int*)malloc( q * sizeof(unsigned int));

 	for (int k = 0; k < q; k++ );
		vetorGraus[q] = calcularGrau(G, q);
}


//Ordena um vetor v de inteiros de tamanho tam
unsigned int *bubbleSort( unsigned int *v, int tam )
{
	unsigned temp;
	while ( tam )
	{
		for ( int i = 0; i < tam - 1; i++ )
			if ( v[i] < v[i+1] ) temp = v[i+1], v[i+1] = v[i], v[i] = temp;
		tam--;
	}
	return v;
}

// Exibe um vetor de inteiros na tela
// v : Ponteiro para vetor
// tam : Quantidade de elementos
void exibirVetor( unsigned int *v, int tam)
{
  for ( int j = 0; j < tam; j++ )
	printf("%d ", v[j] );

	printf("\n");
}

// Procedimento principal do exercício
void E0314_main(void)
{
	int V, E, v, w, cont;
	scanf("%d%d", &V, &E);
	
	
	Grafo *G = criarGrafo(V);
	
	cont = E;
	while (cont--)
	{
		scanf("%d%d", &v, &w );
		G = inserirAresta(G, v,w);
	}
	
	exibirGrafo( G );
	printf("%d \n", calcularGrau(G, 0) );
	//exibirVetor( vetorGraus(G), G -> V );
}

