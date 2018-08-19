/* Universidade Federal do Espírito Santo - Ufes
   Centro Universitário Norte do Espírito Santo - Ceunes
   Teoria dos Grafos 2018/1 - TG20181
   Aula 12.03.2018
   Representação de grafos como matriz de adjacências
   Autor: Elyabe Alves
*/
// #include <bits/stdc++.h>
// using namespace std;

typedef struct grafo
{
	int V,
		E,
		**adj;
} Grafo;

// Aloca e retorna matriz 
// r, c : dimensões da matriz linhas/colunas 
// val : Valor default da matriz
int **alocarMatrixAdj( int r, int c, int val )
{
	int i, j, **m = (int**)malloc( r * sizeof(int*));
	for ( i = 0; i < r; i++ )
		m[i] = (int*)malloc( c * sizeof(int));
		
	for ( i = 0; i < r; i++ )
	 for( j = 0; j <c ; j++ )
		m[i][j] = val;
	
	return m;	
}

// Cria um grafo G como matriz
// V : Quantidade de vértices do grafo
Grafo *criarGrafo( int V )
{
	Grafo *G = (Grafo*)malloc(sizeof(Grafo));
	G -> V = V;
	G -> E = 0;
	G -> adj = alocarMatrixAdj( V, V, 0 );
	return G;
}

// Insere a aresta a_ij num grafo 
// G : Ponteiro para grafo simples
// i, j : Vértices extremidades da aresta (i,j) ~ (j,i)
Grafo *inserirAresta( Grafo *G, int i, int j )
{
	if ( i != j && G -> adj[i][j] == 0 )
	{
		G -> adj[i][j] = G -> adj[j][i] = 1;
		G -> E++;
	}
	return G;
}

// Remove a aresta a_ij do grafo
// G : Ponteiro para grafo
// i,j : Vértices extremidades da aresta a ser deletada
Grafo *removerAresta( Grafo *G, int i, int j )
{
	if ( i != j && G -> adj[i][j] == 1 )
	{
		G -> adj[i][j] = G -> adj[j][i] = 0;
		G -> E--;
	}
	return G;
}

// Exibe na tela o grafo G como matriz de adjacências
// G : Ponteiro para o grafo a ser exibido
void imprimirGrafo( Grafo *G )
{
	int v, w;
	for ( v = 0; v < G -> V; v++ )
	{
		printf("%d: ", v);
		for ( w = 0; w  < G -> V; w++ ) 
			if ( G -> adj[v][w] == 1 )
				printf(" %2d", w );
				printf("\n");
	}
}

// Retorna 1 se os vértices v e w são adjacentes e 0 caso contrário
// G : Ponteiro para o grafo 
// v, w : Vértices a serem analisados
short int vertivesAdjacentes( Grafo *G, int v, int w )
{
	return (short int)(G -> adj[v][w]);
}


// Calcula e retorna o grau de um vértice
// G : Ponteiro para o grafo
// v : Vértice cujo grau deseja-se saber
unsigned grauVertice( Grafo *G, int v)
{
	int q = G -> V, grau = 0;
	while ( q-- >= 0 )
		grau += G -> adj[v][q];

	return (unsigned)grau;
}
	
// Exibe todos os vértices adjacentes a um vertice
// G : Ponteiro para o grafo
// v : Vértice analisado
void exibirVerticesAdjacentes( Grafo *G, int v )
{
	int q = G -> V;
	for ( int j = 0; j < q; j++ )
		if ( j != v && G -> adj[v][j] == 1 ) printf(" %d", j ); 

	printf("\n");
}

// Procedimento principal do Exercício 
void E0312_main(void)
{
	int V, E, i, j, q;
	Grafo *G = NULL;
	
	scanf("%d %d", &V, &E);
	
	G = criarGrafo( V );
	
	if ( G != NULL )
	{
	   for ( q = 0; q < E; q++ )
		{ 
			scanf("%d %d", &i, &j);
			G = inserirAresta( G, i, j );
		}
	}

	imprimirGrafo( G );
	printf(" (0,1) São vertices adjacentes? %d\n", vertivesAdjacentes(G, 0, 1) );
	printf("Grau do vertice 0 : %d\n", grauVertice(G, 0) ) ;
	printf("Exibir vertices adjacentes a 0: \n");
	exibirVerticesAdjacentes(G, 0);
}
