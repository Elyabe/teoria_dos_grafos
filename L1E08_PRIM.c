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



Vertice *novoVertice( int x, int w );


// Cria e retorna ponteiro para heap a partir de grafo
// G : Ponteiro para grafo
Heap* criarVetor ( Grafo *G )
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
void swap( Vertice** heap, int j, int k )
{
	Vertice *aux = heap[j];
	heap[j] = heap[k], heap[k] = aux;
}

// Procedimento subir
// myHeap : Ponteiro para heap
// pos : Posição a descer 
// T : Ponteiro para estrutura do PRIM - Acesso a vetor de estimativas
void up ( Heap** myHeap, int pos, PRIM *T )
{
	int j = pos/2;
	Vertice **heap = (*myHeap) -> vetVertices;
	if ( j > 0 )
	{
		if ( T[heap[pos] -> no].d < T[heap[j] -> no].d )
		{
			swap( heap, pos, j );
			up( myHeap, j, T );
		}
	}
}

// Procedimento descer no heap com base na estimativa
// myHeap : Ponteiro para heap
// pos : Posição do elemento a descer
// T : Ponteiro para estrutura com estimativa
void down ( Heap** myHeap, int pos, PRIM *T )
{
	int j = 2*pos;
	Vertice **heap = (*myHeap) -> vetVertices;
	if ( j <= (*myHeap) -> size )
	{
		if ( ( j+1 <= (*myHeap)->size ) && T[heap[j+1] -> no].d < T[heap[j] -> no].d  ) j++;
		if ( T[heap[pos] -> no].d > T[heap[j] -> no].d )
		{
			swap( heap, pos, j );
			down ( myHeap, j, T );
		}
	}
}

// Criar heap usando a função descer
// myHeap : Ponteiro para heap
// T : Ponteiro para estrutura com estimativa
void criarHeap ( Heap** myHeap, PRIM *T )
{
	int j;
	( (*myHeap) -> vetVertices )[ 0 ] = NULL;
	for ( j = ((*myHeap) -> size - 1)/2; j > 0; j-- ) 
	{
		down( myHeap, j, T );
	}
}

void criarHeap2 ( Heap** myHeap, PRIM *T )
{
	int j;
	for ( j = 1; j <= (*myHeap) -> size ; j++ )
	{
		up ( myHeap, j, T );
	}
}

// Insere um vertice v no Heap com base em sua estimativa
void inserirNovoVerticeH ( Heap** myHeap, Vertice* v, PRIM *T )
{
	( (*myHeap) -> vetVertices )[ ++(*myHeap)->size ] = v ;
	up ( myHeap, (*myHeap) -> size, T );
}

// Gera um heap a partir de um grafo G utilizando as estimativas
void gerarHeapGrafo( Grafo *G, Heap **myHeap, PRIM *T )
{
	for ( int i = 0; i < G -> V; i++ )
		inserirNovoVerticeH( myHeap, novoVertice( i, 0 ) , T );
}

//Exibe vetor heap na tela com Rótulo e estimativa
void exibirHeap ( Heap* myHeap, PRIM *T )
{
	int cont;
	for ( cont = 1; cont <= myHeap -> size; cont++ )
			printf ("[%d / %d] ", (myHeap -> vetVertices)[cont] -> no, T[(myHeap -> vetVertices)[cont] -> no].d );
	printf("\n");
}

// Remove e retorna do Heap de vértices de estimativas 
Vertice* removeMinHeap ( Heap** myHeap, PRIM *T )
{
	Vertice *rt = NULL;
	if ( (*myHeap) -> size > 0)
		{ 
			swap( (*myHeap) -> vetVertices, 1, (*myHeap) -> size );
			rt = ( (*myHeap) -> vetVertices )[ (*myHeap) -> size-- ];
			
			//Reorganiza o  heap caso seja necessário
			if ( (*myHeap) -> size > 1 )
				down ( myHeap, 1, T );
		}
	return rt;
}


//Cria um grafo com V vértices
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

//Cria e retorna um novo vértice com rótulo x e peso w
Vertice *novoVertice( int x, int w )
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

//Exibe o grafo G na tela
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
			printf ("(%d | %d) ", p -> no, p -> peso );
			p = p -> prox; 
		}
		printf("\n");
	}
	printf("\n");
}

//Insere aresta (v,w) considerando a simetria
Grafo *inserirAresta( Grafo *G, int v, int w, int peso )
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
			Vertice *novo = novoVertice(w, peso);
			novo -> prox = G -> adj[v].prox;
			G -> adj[v].prox = novo;
			
		
			//Inserção na lista do w
			novo = novoVertice(v,peso);
			novo -> prox = G -> adj[w].prox;
			G -> adj[w].prox = novo;

			G -> E++;
		}
		
	}
	return G;
}


//Remove a aresta (v,w)
Grafo *removerAresta( Grafo *G, int v, int w )
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


//Dados dois vértices verificar se os mesmos são adjacentes

//Exibe na tela um vetor v  de inteiros com tamanho tam 
void exibirVetor( unsigned int *v, int tam)
{
  for ( int j = 0; j < tam; j++ )
	printf("%d ", v[j] );

	printf("\n");
}

//Preenche o Grafo G com E arestas
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

PRIM* alocarPrim( Grafo *G )
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


void showPrim( PRIM *T, int k )
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
int pertenceQ( Heap *Q, Vertice *v )
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


// Criar arvore geradora minima do Grafo G conexo
PRIM* primAlgoritmo( Grafo *G, int r )
{
	PRIM *T = alocarPrim( G );
	// showPrim( T, G->V );

	T[r].d = 0;
	// showPrim( T, G->V );
	
	Heap *Q = criarVetor(G);
	gerarHeapGrafo(  G, &Q, T );
	// exibirHeap(Q, T );

	int vertAtualizado;
	Vertice *u, *v;

	while ( Q -> size )
	{
		u = removeMinHeap(&Q, T);
		// exibirHeap(Q);0
		for ( v = G -> adj[u -> no].prox; v != NULL; v = v -> prox )
		{
			vertAtualizado = pertenceQ(Q,v);
			if ( vertAtualizado && v -> peso < T[v -> no].d )
			{
				T[ v -> no].predecessor = u;
				T[ v -> no].d = v -> peso;
				
				// Reorganiza o Heap
				if ( vertAtualizado <= Q -> size )
					up ( &Q, vertAtualizado, T );

				// exibirHeap( Q, T);
			}
		}

	}

	return T;
}

void L1E08_PRIM_main(void)
{
	int V, E, initPRIM;
	Grafo *G;


	scanf("%d%d", &V, &E);
	G = criarGrafo(V);
	G = preencherGrafo(G, E);
	exibirGrafo( G );

	scanf("%d", &initPRIM );
	PRIM *T_min = primAlgoritmo( G, initPRIM);
	showPrim( T_min, G -> V );
}
