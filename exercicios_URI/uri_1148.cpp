/* Universidade Federal do Espírito Santo - Ufes
   Centro Universitário Norte do Espírito Santo - Ceunes
   Teoria dos Grafos 2018/1 - TG20181
   Tarefa exercícios URI 
   Data: 04/04
   Autor: Elyabe Alves
*/ 

#include <bits/stdc++.h>

using namespace std;

#define INF 9999
#define MAX 503

typedef pair<int, int> iPair;

class Grafo
{
   public:
	int V, adj[MAX][MAX];
    Grafo( int V );  
 
    void inserir_aresta(int u, int v, int w);
    void dijkstra_algoritmo(int src, int dest );
};
 
// Cria e inicializa o grafo todo o grafo
// V : Ordem do grafo
Grafo::Grafo( int V )
{
    this -> V = V;
    for ( int i = 0; i < V; ++i )
    	for ( int j = 0; j < V; ++j )
    		adj[i][j] = INF;
}
 
// Adiciona aresta ao grafo
// u,v : Vértices extremidades da aresta
// w : Peso associado à aresta
void Grafo::inserir_aresta( int u, int v, int w )
{
    adj[u][v] = w;
    // Se as cidades pertencem ao mesmo país
    if ( adj[v][u] != INF )
    	adj[u][v] = adj[v][u] = 0;
}
 
// Determina o caminho mínimo de uma origem
// src : Vértice origem do caminho
// dest : Vértice destino do percurso
void Grafo::dijkstra_algoritmo( int src, int dest )
{
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    vector<int> dist(V, INF), pred(V,-1);

   
    pq.push(make_pair(0, src));
    dist[src] = 0;
 
    // Enquanto existirem vértices a seren adicionados 
    while ( !pq.empty() )
    {
        int u = pq.top().second;
        pq.pop();

        // Vértices adjacentes
        for ( int v = 0; v < V; v++ )
        { 
			if ( adj[u][v] != INF )
            {
				// Relaxação 
				if ( dist[v] > dist[u] + adj[u][v] )
				{
					dist[v] = dist[u] + adj[u][v];
					pq.push( make_pair( dist[v], v ) );
					pred[v] = u;
				}
			}
        }
    }
    
    // Se existe caminho da origem ao destino
    if ( pred[dest] >= 0 )
		cout<<dist[dest]<<endl;
	else
		cout<<"Nao e possivel entregar a carta"<<endl;
}

 

int main()
{
 
    int V, N, E, X, Y, H, K;
    vector<int> dist, pred;
	
	while ( scanf("%d%d", &N, &E ) && ( N || E ) )
	{
		Grafo g(N);
		
		for ( int k = 0; k < E; k++ )
		{
			cin>>X>>Y>>H;
			g.inserir_aresta(X-1, Y-1, H);
		}
		
		cin>>K;
		
		while ( K-- )
		{
			cin>>X>>Y;
			g.dijkstra_algoritmo( X-1, Y-1 );
			
		}
		cout<<endl;
	}
 
    return 0;
}
