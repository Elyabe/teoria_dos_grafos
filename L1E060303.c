/* Universidade Federal do Espírito Santo - Ufes
   Centro Universitário Norte do Espírito Santo - Ceunes
   Teoria dos Grafos 2018/1 - TG20181
   Lista de exercícios I - Exercício 06
   Matriz de adjacência sem desperdício de espaço de memória : Grafo simples não direcionado num vetor único
   Data: 30/03/2018
   Autor: Elyabe Alves
*/

// #include <bits/stdc++.h>

// using namespace std;

typedef struct grafo
{
	int V, E, *adj;
} Grafo;


// Retorna espaço de memória necessária sem desperdício
// n : Número de vértices do grafo
int N( unsigned n )
{
	return 0.5*n*(n-1);
}

// Transforma coordenadas bidimensionais em unidimensionais : (u,v) |-> x 
// u, v : Coordenadas bidimensionais na matriz de adjacência
// n : Ordem do grafo
unsigned int f( int u,  int v,  int n )
{
	if ( u <= v )
		return u*(n-1) - 0.5*u*(u+1) + v - 1; 
	else
		return f( v, u, n );
}

// Cria e retona ponteiro para o grafo
// v : Quantidade de vértices
Grafo *criarGrafo( unsigned int v )
{
	Grafo *G = (Grafo*)calloc( sizeof(int), 1);
	if ( G ) 
	{
		G -> V = v;
		G -> adj = (int*)calloc( sizeof(int), N(v) );
	}
	return G;
}


// Insere a aresta (u,v) ~ (v, u) no grafo
// G : Ponteiro para grafo
// u, v : Vértices extremidades da aresta
// peso: Peso da aresta  
Grafo *inserirAresta( Grafo *G, int u, int v, int peso )
{
	int k = f(u,v, G -> V);
	if ( u != v && G-> adj[k] == 0) 
	{	
		G->adj[k] = peso;
		G->E++;
	}
	return G;
}

// Preenche e retorna um grafo
// E : Quantidade de arestas
Grafo *preencherGrafo( Grafo *G, int E )
{
	int v, w, peso;
	while ( E--)
	{
		scanf("%d%d%d", &v, &w, &peso );
		G = inserirAresta(G, v, w, peso);
	}
	return G;
}

// Exibe na tela um grafo
// G : Ponteiro para o grafo em questão
void exibirGrafo( Grafo *G )
{
	int k, i, j;
	for ( i = 0; i < G -> V; i++ )
	{
		printf("[%d]-> ", i);
		for ( j = 0; j < G -> V; j++ )
		{
			k = f( i, j, G->V );
			if ( i != j && G -> adj[k] != 0 )
				printf("(%d | %d) ", j, G->adj[k] );
		}
		printf("\n");
	}
}

// Verifica se vértices são vizinho e o peso da aresta, caso exista
// G : Ponteiro para o grafo
// u, v : Vértices a serem analisados
unsigned int vizinho( Grafo *G, unsigned u, unsigned int v )
{
	return G -> adj[f(u,v,G->V)];
}

// Procedimento principal do exercício
void L1E060303_main(void)
{
	int u,v, V, E;
	Grafo *G;
	
	scanf("%d%d", &V, &E );
	G = criarGrafo(V);
	G = preencherGrafo( G, E );
	exibirGrafo(G);
	u = 0,  v = 6;
	printf("m[f(%d,%d) = %d] = %u \n", u, v, f( u,v, G->V ), vizinho( G, u, v ) );
	
}
