/* Universidade Federal do Espírito Santo - Ufes
   Centro Universitário Norte do Espírito Santo - Ceunes
   Teoria dos Grafos 2018/1 - TG20181
   Encontrar árvore geradora mínima T de uma grafo G 
   Algoritmo PRIM
   Data: XX/03
   Autor: Elyabe Alves
*/

// #include <bits/stdc++.h>

#define INF 99999999

typedef struct  vertice
{
	int no, 
		peso;
	struct vertice *prox;
} Vertice;

typedef struct grafo
{
	int V, E;
	Vertice *adj;
} Grafo;


typedef struct heap
{
	Vertice **vetVertices;
	int size, space;
} Heap;

typedef struct prim
{
	Vertice *predecessor;
	int d;
} PRIM;



Vertice *novo_vertice( int x, int w );


// Cria e retorna ponteiro para heap a partir de grafo
// G : Ponteiro para grafo
Heap* criar_vetor ( Grafo *G )
{
	int k = G -> V;
	Heap *myHeap = (Heap*)calloc( 1, sizeof(Heap) );
	
	if ( myHeap )
	{
		myHeap -> space = k;
		// myHeap -> vetVertices = (Vertice**)calloc( k*(k-1) + 1, sizeof( Vertice* ) );
		myHeap -> vetVertices = (Vertice**)calloc( k, sizeof( Vertice* ) );

		// Inicializa vetor de ponteiros
		while ( k-- >= 0 )
			myHeap -> vetVertices[k] = NULL;
	}

	return myHeap;
}

// Realiza troca entre elementos no heap 
// heap : Ponteiro para heap
// j, k : Posições dos elementos a serem trocadas 
void trocar( Vertice** heap, int j, int k )
{
	Vertice *aux = heap[j];
	heap[j] = heap[k], heap[k] = aux;
}

// Procedimento subir
// myHeap : Ponteiro para heap
// pos : Posição a descer 
// T : Ponteiro para estrutura do PRIM - Acesso a vetor de estimativas
void subir( Heap** myHeap, int pos, PRIM *T )
{
	int j = pos/2;
	Vertice **heap = (*myHeap) -> vetVertices;
	if ( j > 0 )
	{
		if ( T[heap[pos] -> no].d < T[heap[j] -> no].d )
		{
			trocar( heap, pos, j );
			subir( myHeap, j, T );
		}
	}
}

// Procedimento descer no heap com base na estimativa
// myHeap : Ponteiro para heap
// pos : Posição do elemento a descer
// T : Ponteiro para estrutura com estimativa
void descer( Heap** myHeap, int pos, PRIM *T )
{
	int j = 2*pos;
	Vertice **heap = (*myHeap) -> vetVertices;
	if ( j <= (*myHeap) -> size )
	{
		if ( ( j+1 <= (*myHeap)->size ) && T[heap[j+1] -> no].d < T[heap[j] -> no].d  ) j++;
		if ( T[heap[pos] -> no].d > T[heap[j] -> no].d )
		{
			trocar( heap, pos, j );
			descer ( myHeap, j, T );
		}
	}
}

// Criar heap usando a função descer
// myHeap : Ponteiro para heap
// T : Ponteiro para estrutura com estimativa
void criar_heap( Heap** myHeap, PRIM *T )
{
	int j;
	( (*myHeap) -> vetVertices )[ 0 ] = NULL;
	for ( j = ((*myHeap) -> size - 1)/2; j > 0; j-- ) 
	{
		descer( myHeap, j, T );
	}
}

void criar_heap_v2( Heap** myHeap, PRIM *T )
{
	int j;
	for ( j = 1; j <= (*myHeap) -> size ; j++ )
	{
		subir ( myHeap, j, T );
	}
}

// Insere um vertice no Heap com base em sua estimativa
// myHeap : Ponteiro de ponteiro para heap
// v : Vértice a ser inserido
// T : Estrutura com estimativas
void inserir_vert_heap( Heap** myHeap, Vertice* v, PRIM *T )
{
	( (*myHeap) -> vetVertices )[ ++(*myHeap)->size ] = v ;
	subir ( myHeap, (*myHeap) -> size, T );
}

// Cria um Heap a partir de um grafo
// myHeap : Ponteiro de ponteiro para heap a ser criado
// G : Ponteiro para o grafo
// T : Estrutura com estimativas de distância
void gerar_heap_grafo( Grafo *G, Heap **myHeap, PRIM *T )
{
	for ( int i = 0; i < G -> V; i++ )
		inserir_vert_heap( myHeap, novo_vertice( i, 0 ) , T );
}

// Exibe vetor heap na tela com Rótulo e estimativa
// myHeap : Ponteiro de ponteiro para heap
// T : Estrutura com estimativas
void exibir_heap ( Heap* myHeap, PRIM *T )
{
	int cont;
	for ( cont = 1; cont <= myHeap -> size; cont++ )
			printf ("[%d / %d] ", (myHeap -> vetVertices)[cont] -> no, T[(myHeap -> vetVertices)[cont] -> no].d );
	printf("\n");
}

// Remove e retorna do Heap de vértices de estimativas 
// myHeap : Ponteiro de ponteiro para heap
// T : Estrutura com estimativas
Vertice* remover_min_heap ( Heap** myHeap, PRIM *T )
{
	Vertice *rt = NULL;
	if ( (*myHeap) -> size > 0)
		{ 
			trocar( (*myHeap) -> vetVertices, 1, (*myHeap) -> size );
			rt = ( (*myHeap) -> vetVertices )[ (*myHeap) -> size-- ];
			
			//Reorganiza o  heap caso seja necessário
			if ( (*myHeap) -> size > 1 )
				descer ( myHeap, 1, T );
		}
	return rt;
}


// Cria e retorna ponteiro para um grafo com V vértices
// V : Ordem do grafo
Grafo *criar_grafo( int V )
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
// x : Rótulo do vértice
// w : Peso da aresta associada
Vertice *novo_vertice( int x, int w )
{
	Vertice *novo = (Vertice*)malloc(sizeof(Vertice));
	if ( novo != NULL )
	{	novo -> no = x;
		novo -> peso = w;
		novo -> prox = NULL;
	} else
	  {  printf("Erro.\n");
		exit(1);
	  }
	
	return novo;
}

// Exibe o grafo na tela
// G : Ponteiro para o grafo
void exibir_grafo( Grafo *G )
{
	int v;
	Vertice *p;
	for ( v = 0; v < G -> V; v++ )
	{
		p = G -> adj[v].prox;
		printf("[%d] -> ", v );
		while ( p != NULL )
		{
			printf ("(%d | %d) ", p -> no, p -> peso );
			p = p -> prox; 
		}
		printf("\n");
	}
	printf("\n");
}

// Insere aresta no grafo considerando a simetria
// G : Ponteiro para grafo
// v, w : Extremidades da aresta
// peso : Peso associado
Grafo *inserir_aresta( Grafo *G, int v, int w, int peso )
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
			Vertice *novo = novo_vertice(w, peso);
			novo -> prox = G -> adj[v].prox;
			G -> adj[v].prox = novo;
			
		
			//Inserção na lista do w
			novo = novo_vertice(v,peso);
			novo -> prox = G -> adj[w].prox;
			G -> adj[w].prox = novo;

			G -> E++;
		}
		
	}
	return G;
}


// Remove aresta no grafo considerando a simetria
// G : Ponteiro para grafo
// v, w : Extremidades da aresta
Grafo *remover_aresta( Grafo *G, int v, int w )
{
	Vertice *aux, *preaux;
	
	if ( G -> adj[v].prox != NULL )
	{
		
		// Remove w da lista de v, se existir
		aux = G -> adj[v].prox;
		preaux = &(G -> adj[v]);
		
		while ( aux != NULL )
		{
			if ( aux -> no == w ) break;
			preaux = aux;
			aux = aux -> prox;
		}

		if ( aux != NULL )
		{
			preaux -> prox = aux -> prox;
			free(aux);
			G -> E--;
		}
	}

	if ( G -> adj[w].prox != NULL )	
	{
		// Remove v da lista de w, se existir
		aux = G -> adj[w].prox;
		preaux = &(G -> adj[w]);
		
		while ( aux != NULL )
		{
			if ( aux -> no == v ) break;
			
			preaux = aux;
			aux = aux -> prox;
		}

		if ( aux != NULL )
		{
			preaux -> prox = aux -> prox;
			free(aux);
		}

	}
	return G;
}

// Libera memória ocupada pela fila de vértices
// G : Ponteiro para grafo formado pela fila
Grafo* desalocar_fila( Grafo *G )
{
	Vertice *aux;
	while ( G -> adj )
	{
		aux = G -> adj;
		G -> adj = aux -> prox;
		free( aux );
	}

	free( G );
	G = NULL;
	return G;
}


// Exibe na tela um vetor de inteiros na tela
// v : Ponteiro para vetor
// tam : Quantidade de elementos do vetor
void exibir_vetor( unsigned int *v, int tam)
{
  for ( int j = 0; j < tam; j++ )
	printf("%d ", v[j] );

	printf("\n");
}

// Preenche o Grafo a partir de entradas
// G : Ponteiro para o grafo
// E : Quantidade de arestas
Grafo *preencher_grafo( Grafo *G, int E )
{
	int v, w, peso;
	while ( E--)
	{
		scanf("%d%d%d", &v, &w, &peso );
		G = inserir_aresta(G, v, w, peso);
	}
	return G;
}

// Aloca, inicializa e retorna ponteiro para estrutura de estimativas e predecessores
// G : Ponteiro para o grafo G
PRIM* alocar_TAD_PRIM( Grafo *G )
{
	int i;
	PRIM *novo = (PRIM*)malloc(sizeof(PRIM)*(G -> V) );

	if ( novo != NULL )
	{	for (i = 0; i < G -> V; i++ )
			{
				novo[i].predecessor = NULL;
				novo[i].d = INF;
			}
	}
	return novo;
}

// Libera memória ocupada pelo TAD
// T : Ponteiro para estrutura 
PRIM* desalocar_TAD_PRIM( PRIM* T )
{
	free( T -> predecessor 	);
	free( T );

	T = NULL;

	return T;
}


// Exibe na tela o vetor de estimativas e predecessores
// T : Ponteiro para estrutura a ser exibida
// k : Quantidade de vértices da estrutura
void exibir_PRIM( PRIM *T, int k )
{
	int i;
	printf("\n");
	for (i = 0; i < k; i++ )
		{
			printf("[%d] ", i);
			if ( T[i].predecessor == NULL) printf("NULL ");
			else printf("%d ", T[i].predecessor->no );

			printf("%d \n", T[i].d );
		}
}


// Retorna 0, se não pertence e x > 0 se pertence, sendo x a posicao deste no heap
// Q : Ponteiro para o heap
// v : Vértice a ser analisado
int pertence_Q( Heap *Q, Vertice *v )
{
	int i, pertence = 0;
	Vertice *p;
	for ( i = 1; i <= Q -> size && !pertence ; i++ )
	{
		p = Q -> vetVertices[i];
		pertence = ( p -> no == v -> no );
	}
	
	return ( pertence != 0 ) ? i - 1 : pertence;
}


// Criar arvore geradora e retorna estrutura com as informações
// G : Ponteiro para o grafo analisado
// r : Vértice inicial da árvore
PRIM* prim_algoritmo( Grafo *G, int r )
{
	PRIM *T = alocar_TAD_PRIM( G );
	// exibir_PRIM( T, G->V );

	T[r].d = 0;
	// exibir_PRIM( T, G->V );
	
	Heap *Q = criar_vetor(G);
	gerar_heap_grafo(  G, &Q, T );
	// exibir_heap(Q, T );

	int vertAtualizado;
	Vertice *u, *v;

	while ( Q -> size )
	{
		u = remover_min_heap(&Q, T);
		// exibir_heap(Q);0
		for ( v = G -> adj[u -> no].prox; v != NULL; v = v -> prox )
		{
			vertAtualizado = pertence_Q(Q,v);
			if ( vertAtualizado && v -> peso < T[v -> no].d )
			{
				T[ v -> no].predecessor = u;
				T[ v -> no].d = v -> peso;
				
				// Reorganiza o Heap
				subir ( &Q, vertAtualizado, T );
				// exibir_heap( Q, T);
			}
		}

	}

	return T;
}

// Procedimento principal do exercício
void L1E08_PRIM_main(void)
{
	int V, E, initPRIM;
	Grafo *G;


	scanf("%d%d", &V, &E);
	G = criar_grafo(V);
	G = preencher_grafo(G, E);
	exibir_grafo( G );

	scanf("%d", &initPRIM );
	PRIM *T_min = prim_algoritmo( G, initPRIM);
	exibir_PRIM( T_min, G -> V );
	
	T_min = desalocar_TAD_PRIM( T_min );
	G = desalocar_fila( G );

}
