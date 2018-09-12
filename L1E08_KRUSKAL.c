/* Universidade Federal do Espírito Santo - Ufes
   Centro Universitário Norte do Espírito Santo - Ceunes
   Teoria dos Grafos 2018/1 - TG20181
   Lista de exercícios I - Exercicio 08
   Árvore geradora mínima: Algoritmo de Kruskal
   Data: 06/04
   Autor: Elyabe Alves
*/

typedef struct  aresta
{
	int u,v, peso;
	struct aresta *prox;
} Aresta;

typedef struct fila
{
	Aresta *inicio, *fim;

} Fila;

typedef struct grafo 
{
	int V;
	Fila *A;
} Grafo;

// Cria, inicializa e retorna ponteiro para uma fila
Fila *criar_fila(void)
{
	Fila *nova = (Fila*)calloc(1,sizeof(Fila));
	if ( nova ) 
		nova -> inicio = nova -> fim = NULL;
	return nova;
}

// Cria, inicializa e retorna um grafo baseado numa fila de arestas
// v : Ordem do grafo
Grafo *criar_grafo( int v )
{
	Grafo *G = (Grafo*)calloc( 1, sizeof(Grafo));
	if ( G )
	{ 
		G -> A = criar_fila();
		G -> V = v;
	}
	return G;
}

// Libera memória ocupada pelo grafo e retorna o ponteiro
// G : Ponteiro para o grafo a ser desalocado
Grafo* desalocar_grafo( Grafo *G )
{

	Aresta *aux;

	while ( G -> A -> inicio )
	{
		aux = G -> A -> inicio ;
		G -> A -> inicio = aux ->  prox;
		free(aux);
	}
	
	free(G);
	G = NULL;
	
	return G;
} 

// Aloca e retorna ponteiro para nova aresta
// u, v : Vértices extremidades da aresta
// peso : Peso da aresta
Aresta *nova_aresta( int u, int v, int peso )
{
	Aresta *nova = (Aresta*)calloc(1,sizeof(Aresta));
	if ( nova ) 
	{ 
		nova -> u = u;
		nova -> v = v;
		nova -> peso = peso;
		nova -> prox = NULL;
	}
	return nova;
}

// Insere uma nova aresta na fila
// v, w : Vértices extremidades da aresta
// peso : Peso associada à aresta
Fila *inserir_aresta( Fila *G, int v, int w, int peso )
{
	if ( v != w )
	{
		Aresta *p = G -> inicio;
		while ( p!= NULL )
		{
			if ( p -> u == v && p -> v == w ) break;
			p = p -> prox;
		}	
		
		if ( p == NULL )
		{
			//Inserção na lista de v			
			Aresta *novo = nova_aresta( v, w, peso );
			
			//Não há elementos na fila
			if ( G -> fim == NULL )
				G -> inicio = G -> fim = novo;
			else
			{
				G -> fim -> prox = novo; 
				G -> fim = novo;
			}			
		}		
	}

	return G;
}


// Remove a aresta de uma fila
// G : Ponteiro para fila 
Aresta *remover_aresta( Fila **G  )
{
	Aresta *uvRetorno = NULL;
	Fila *G1 = *G;
	if ( (*G) -> fim != NULL )
	{
		uvRetorno = (*G) -> inicio;
		
		if ( (*G) -> fim == (*G) -> inicio ) 
			(*G) -> inicio = (*G) -> fim = NULL;
		else	
			(*G) -> inicio = (*G) -> inicio -> prox;
	}

	return uvRetorno;
}

// Exibe a fila na tela
// F : Ponteiro para a fila a ser exibida
void exibir_fila( Fila *F )
{
	Aresta *uv = F -> inicio;
	while ( uv != NULL )
	{
		printf("[(%d,%d), %d ] ", uv -> u, uv -> v, uv -> peso );
		uv = uv -> prox;
	}

	printf("\n");
}

// Operações Union-Find
// Aloca, inicializa e retorna ponteiro para conjuntos disjuntos
// n : Número de conjuntos iniciais / Ordem do grafo
int *alocar_conjuntos( int n )
{
	n++;
	int *novo = (int*)calloc( n, sizeof(int));
	memset(novo,-1, sizeof(int)*n );
	return novo;
}

// Retorna o índice do conjunto ao qual um elemento pertence
// C : Ponteiro para vetor com conjuntos
// i : inteiro entre 1 e tam(C)
int find_set( int *C, int i)
{
	while ( C[i] >= 0 )
		i = C[i];
		
	return i;
}

// Une dois conjunto disjuntos e retorna ponteiro para resultado
// C : Ponteiro para vetor de conjuntos
//  i,j : Índice dos elementos cujos conjuntos devem ser unidos
int *unir( int *C, int i, int j)
{
	int k, w;
	k = find_set( C, i );
	w = find_set( C, j );
	// printf("k %d - w %d\n", k,w );
	if ( fabs(C[k]) > fabs(C[w]) )
	{
		C[w] = k;
	} else 
	{
		if ( fabs(C[w]) == fabs(C[k]) ) C[w]--;
		C[k] = w;
	}

	return C;
}


// Ordenação bubbleSort teste 
// Recomenda-se utilizar algoritmos mais eficientes já implementados
// Utilizar algoritmos prontos de C é uma solução
int *bubbleSort( int *v, int tam )
{
	int temp;
	while ( tam )
	{
		for ( int i = 0; i < tam - 1; i++ )
			if ( v[i] < v[i+1] ) temp = v[i+1], v[i+1] = v[i], v[i] = temp;
		tam--;
	}
	return v;
}


// Exibe um vetor de inteiros na tela
// p : Ponteiro para vetor
// tam : Quantidade de elementos no vetor
void exibir_vetor( int *p, int tam  )
{
	for (int k = 0; k < tam; k++ )
		printf("[%d|%d]", k, p[k] );
	printf("\n");
}


// Realiza troca de conteúdo entre duas arestas
// A, B : Ponteiro para arestas a serem trocadas
void trocar( Aresta **A, Aresta **B )
{
	Aresta C;
	C.u =(*A) -> u;
	C.v = (*A) -> v;
	C.peso = (*A) -> peso;

	(*A) -> u = (*B) -> u;
	(*A) -> v = (*B) -> v;
	(*A) -> peso = (*B) -> peso;

	(*B) -> u = C.u;
	(*B) -> v = C.v;
	(*B) -> peso = C.peso;

}

// Ordenação da fila
// Recomenda-se utilizar algoritmos mais eficientes
// F : Ponteiro para fila a ser ordenada
Fila *selectionSort( Fila *F )
{
	Aresta *min = NULL, *p, *q;
	for ( p = F -> inicio; p -> prox -> prox != NULL; p = p -> prox )
	{
		min = p;
		for (  q = p -> prox; q != NULL; q = q -> prox )
			if ( q -> peso < min -> peso ) min = q;

		if ( min != p )
			trocar( &min, &p );
	}

	return  F;
}

// Retorna ponteiro para árvore geradora mínima de um grafo
// G : Ponteiro para grafo
Grafo *Kruskal( Grafo *G )
{
	int *C = alocar_conjuntos( G -> V ); 
	Fila *A = G -> A;
	Aresta *uv; 
	Grafo *Gl = criar_grafo( G -> V );

	A = selectionSort(A);
	// exibir_fila(A);	

	while ( A -> inicio )
	{
		uv = remover_aresta(&A);
		// printf("remove %d %d %d \n", uv -> u, uv -> v, uv -> peso );
		if ( find_set( C, uv -> u) != find_set( C, uv -> v ) )
		{
			Gl -> A = inserir_aresta( Gl -> A, uv -> u, uv -> v, uv -> peso );
			C = unir( C, uv -> v, uv -> u );
			free(uv); 
			uv = NULL;
		}		
	}
	free( C );
	free( G );
	
	return Gl;
}

// Procedimento principal do exercício
void L1E08_KRUSKAL_main(void)
{
	int V, E, u, v, peso, *C;
	Grafo *G;

	scanf("%d%d", &V, &E );
	G = criar_grafo( V );

	while ( E-- )
	{
		scanf("%d%d%d", &u, &v, &peso );
		G -> A = inserir_aresta( G -> A, u, v, peso );
	}

	printf("\n\nFila de arestas:\n\n");
	exibir_fila( G -> A );
	G = Kruskal( G );
	printf("\nArvore Geradora min\n\n");
	exibir_fila( G -> A );

	G = desalocar_grafo( G );
}
