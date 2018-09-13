/* Universidade Federal do Espírito Santo - Ufes
   Centro Universitário Norte do Espírito Santo - Ceunes
   Teoria dos Grafos 2018/1 - TG20181
   Percursos em Grafos simples não direcionados: Largura e profundidade  
   Data: 22/04
   Autor: Elyabe Alves
*/

// Apesar de ser um arquivo .cpp, a implementação utiliza apenas C
// Basta inserir as bibliotecas necessárias e remover a biblioteca stdc++

#include <bits/stdc++.h>

using namespace std;

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

typedef struct  aresta
{
	int u,v, peso;
	struct aresta *prox;
} Aresta;

typedef struct fila
{
	Aresta *inicio, *fim;

} Fila;

// Cria e retorna ponteiro para um grafo 
// V : Ordem do grafo
Grafo *criar_grafo( int V )
{
	Grafo *G = (Grafo*)malloc(sizeof(Grafo));
	int i;

	if ( G != NULL )
	{
		G -> V = V;
		G -> E = 0;
		G -> adj = (Vertice*)calloc( V, sizeof(Vertice) );

		for ( i = 0; i < V; i++ )
			G -> adj[i].prox = NULL;
	}
	return G;
}

// Libera memória ocupada pelo grafo
// G : Ponteiro para grafo 
Grafo* desalocar_grafo( Grafo *G )
{
	
	free( G -> adj );
	free( G );
	G = NULL;

	return G;
}


// Libera memória ocupada pela fila de vértices
// F : Ponteiro para fila
Fila* desalocar_fila( Fila *F )
{
	Aresta *aux;
	while ( F -> inicio )
	{
		aux = F -> inicio;
		F -> inicio = aux -> prox;
		free( aux );
	}

	free( F );
	F = NULL;

	return F;
}


// Cria e retorna um novo vértice
// x : Rótulo do novo vértice
// peso: Peso da aresta (Y,x)
Vertice *alocar_vertice( int x, int peso )
{
	Vertice *novo = (Vertice*)malloc(sizeof(Vertice));
	if ( novo != NULL )
	{	novo -> no = x;
		novo -> peso = peso;
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


// Insere o vértice no início da fila 
// l : Fila de vertices
// w : Novo vértice a ser inserido
// peso : Peso da aresta (x, w)
Vertice *inserir_inicio( Vertice *l, int w, int peso )
{
	Vertice *novo = alocar_vertice(w, peso);
	novo -> prox = l;
	return novo;
}

// Remove e retorna o primeiro elemento da fila 
// l : Fila de vértices
Vertice *remover_inicio( Vertice **l )
{
	Vertice *v = *l;
	if ( *l != NULL )
		*l = (*l) -> prox;
	return v;
}

// Remove e retorna o último elemento da fila 
// l : Fila de vértices
Vertice *remover_final( Vertice **l )
{
	Vertice *p = *l, *ant = NULL;
	while ( p != NULL && p -> prox != NULL )
	{
		ant = p;
		p = p -> prox;
	}

	if ( ant != NULL )
		ant -> prox = NULL;
	else
		*l = NULL;

	return p;
}

// Insere aresta (v,w) no grafo
// G : Grafo
// v, w : Extremidades da aresta a ser inserida 
// peso : Peso da aresta (v,w)
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
			G -> adj[v].prox = inserir_inicio( G -> adj[v].prox, w, peso );
			G -> adj[w].prox = inserir_inicio( G -> adj[w].prox, v, peso );
			G -> E++;
		}
		
	}
	return G;
}


// Remove aresta (v,w) do grafo
// G : Grafo
// v, w : Extremidades da aresta a ser inserida 
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

// Exibe na tela um vetor de inteiros
// v : Ponteiro para vetor
// tam : Quantidade de elementos do vetor
void exibir_vetor( unsigned int *v, int tam)
{
  for ( int j = 0; j < tam; j++ )
	printf("%d ", v[j] );

	printf("\n");
}

// Preenche e retorna o Grafo 
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


// Cria e retorna uma fila vazia
Fila *criar_fila(void)
{
	Fila *nova = (Fila*)calloc(1,sizeof(Fila));
	if ( nova ) 
		nova -> inicio = nova -> fim = NULL;
	return nova;
}

// Cria e retorna uma nova aresta ponderada
// u,v : Extremidades da nova aresta
// peso: Peso de (u,v)
Aresta *nova_aresta( int u, int v, int peso )
{
	Aresta *nova = (Aresta*)calloc(1, sizeof(Aresta) );
	if ( nova ) 
	{ 
		nova -> u = u;
		nova -> v = v;
		nova -> peso = peso;
		nova -> prox = NULL;
	}
	return nova;
}

// Insere nova aresta da fila
// G: Fila
// v, w : Extremidades da aresta 
// peso: Peso de (v,w)
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


// Remove a aresta (v,w) da fila
// G: Ponteiro para Fila de arestas
Aresta *remover_aresta_fila( Fila **G  )
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

// Exibe a fila de vértices na tela
// F : fila
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


// Realiza percurso em largura no grafo G
// E_tree : Fila de arestas da árvore
// Alc: Vetor com rótulos de alcançados
// r: Raíz do percurso
void percurso_largura( Grafo *G, Fila **E_tree, unsigned int *Alc, int r )
{
	Vertice *fila_vert = NULL, *w, *v;
	unsigned int alc;

	fila_vert = inserir_inicio( fila_vert, r, 0 );
	Alc[r] = alc = 1;
	*E_tree = criar_fila();

	while ( fila_vert )
	{
		v = remover_final( &fila_vert );
		
		//Vertices ajacentes a v
		w = G -> adj[ v -> no ].prox;
		while ( w )
		{
			//Se não foi alcançado adiciona aos alcancados
			if ( Alc[ w -> no ] == 0 )
			{	
				fila_vert = inserir_inicio( fila_vert, w -> no, 0 );
				Alc[ w -> no ] = ++alc;
				//Une ao conjunto de arestas da árvore
				*E_tree = inserir_aresta( *E_tree, v -> no, w -> no, w -> peso );
			}
			
			if ( Alc[ v -> no ] < Alc[ w -> no ] )
				printf("(%d,%d) explorada: \n", v -> no, w -> no );
			w = w -> prox;
		}
		printf("\t\t%d explorado\n", v->no );
	}
}

// Realiza percurso em profunidade em G
// G: Grafo
// v: Vértice raiz do percurso
// pai: Pai de v
// E_tree : Arestas da árvore
// Alc : Vetor de rótulos de alcançados
// Exp : Vetor de rótulos de explorados
// alc : Rótulo alcançado
// exp : Rótulo explorado
void percurso_profundidade( Grafo *G, Vertice *v, Vertice *pai, Fila **E_tree, unsigned int **Alc,
 unsigned int **Exp, unsigned int *alc, unsigned int *exp)
{
	Vertice  *w;
	// Se for a raiz do percurso
	if ( pai == NULL ) 
		(*Alc)[v->no] = ++(*alc);

	// Para todos os vértices adjacentes a v realiza percurso
	w = G -> adj[v->no].prox;
	while ( w != NULL)
	{
		// Se não foi alcançado, então atualiza como alcançado 
		if ( (*Alc)[ w -> no ] == 0 )
		{	
			(*Alc)[ w -> no ] = ++(*alc);
			// Insere na árvore 		
			*E_tree = inserir_aresta( *E_tree, v -> no, w -> no, w -> peso );
			
			printf("(%d,%d) explorada: \n", v -> no, w -> no );
			percurso_profundidade( G, w, v, E_tree, Alc, Exp, alc, exp );
		} else if ( pai && w -> no != pai -> no && (*Alc)[ v -> no ] > (*Alc)[ w -> no ] )
				printf("(%d,%d) explorada: \n", v -> no, w -> no );
		w = w -> prox;
	}

	printf("\t\t%d explorado\n", v->no );
	(*Exp)[ v -> no ] = ++(*exp);
}

// Procedimento principal do percurso em largura
void percurso_largura_main(void)
{
	int V, E, rPercurso;
	unsigned int *Alc;  //Alcançados
	Fila *E_tree; //Arestas da árvore
	Grafo *G;


	scanf("%d%d", &V, &E);
	G = criar_grafo(V);
	G = preencher_grafo(G, E);
	scanf("%d", &rPercurso );
	exibir_grafo( G );

	// Inicializa variáveis elementos do percurso
	Alc = (unsigned int*)calloc( G -> V, sizeof(unsigned int) );
	percurso_largura( G, &E_tree, Alc, rPercurso );

	printf("Alcançados:\n");
	exibir_vetor( Alc, G -> V );

	printf("Arestas da árvore:\n");
	exibir_fila( E_tree );

	// Libera Memória
	E_tree = desalocar_fila( E_tree );
	G = desalocar_grafo( G );
	free( Alc );
}

// Procedimento principal do percurso em profundidade
void percurso_profundidade_main(void)
{
	unsigned int alc, exp, *Alc, *Exp, V, E, rPercurso;
	Grafo *G;

	scanf("%d%d", &V, &E);
	G = criar_grafo(V);
	G = preencher_grafo(G, E);
	scanf("%d", &rPercurso );
	exibir_grafo( G );

	// Inicializa variáveis elementos do percurso
	alc = exp = 0;
	Alc = (unsigned int*)calloc( G -> V, sizeof(unsigned int) );
	Exp = (unsigned int*)calloc( G -> V, sizeof(unsigned int) );
	Fila *E_tree = criar_fila();
	
	// Cria vértice raiz do percurso 
	percurso_profundidade( G, alocar_vertice( rPercurso, 0 ) , NULL, &E_tree, &Alc, &Exp, &alc, &exp );
	
	printf("Alcançados:\n");
	exibir_vetor( Alc, G -> V );
	
	printf("Explorados:\n");
	exibir_vetor( Exp, G -> V );

	printf("Arestas da árvore:\n");
	exibir_fila( E_tree );

	// Libera memória
	E_tree = desalocar_fila( E_tree );
	G = desalocar_grafo( G );
	free( Alc );
	free( Exp );
}









