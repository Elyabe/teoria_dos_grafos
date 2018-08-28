/* Universidade Federal do Espírito Santo - Ufes
   Centro Universitário Norte do Espírito Santo - Ceunes
   Teoria dos Grafos 2018/1 - TG20181
   Lista de exercícios III
   Fluxo em redes: Algoritmo de Ford-Fulkerson
   Autor: Elyabe Alves
*/

#include <bits/stdc++.h>

using namespace std;
 
#define V 11
 
// Retorna TRUE se existe caminho aumentante armazenado em pred[] e FALSE caso contrário
// s : fonte
// t : sorvedouro
// pred[]: Vetor de predecessores para armazenar o caminho
bool  caminho_aumentante( int grafo_res[V][V], int s, int t, int pred[] )
{
    
    bool visitado[V];
    queue<int> fila;

    // Seta visitado para FALSE 
    memset( visitado, 0, sizeof(visitado) );
 
    // Inicializa caminho
    fila.push(s);
    visitado[s] = true;
    pred[s] = -1;
 
    // Busca em largura
    while ( !fila.empty() )
    {
        int u = fila.front();
        fila.pop();
 
        for ( int v = 0; v < V; v++ )
        {
            if ( visitado[v] == false && grafo_res[u][v] > 0)
            {
                fila.push(v);
                pred[v] = u;
                visitado[v] = true;
            }
        }
    }
 
    // Retorna TRUE se existe caminho de s a t não visitado
    return (visitado[t] == true);
}

// Exibe caminho armazenado no vetor de predecessores
// pred : Vetor de predecessores
// s : Vértice fonte
// t : Vértice Sumidouro
void show( int pred[], int s, int t )
{
    if ( pred[t] < 0 || s == t )
    {
        printf("v_%d ", s);
    } else
    {
        show( pred, s, pred[t] );
        printf("v_%d ", t);
    }
}
 
// Retorna o maior fluxo possível na rede , de s a t
int ford_fulkerson( int rede[V][V], int s, int t  )
{
    int grafo_res[V][V], u, v, pred[V], fluxo_max; 

    // Inicializa o grafo residual
    for ( u = 0; u < V; u++ )
        for ( v = 0; v < V; v++ )
             grafo_res[u][v] = rede[u][v];
 
    fluxo_max = 0;

    // Se há caminho aumentante, então o fluxo é enviado
    while ( caminho_aumentante( grafo_res, s, t, pred ) )
    {

        // Percorre o caminho aumentante determinando o fluxo maximo
        int fluxo_cam = INT_MAX;
        for ( v = t; v != s; v = pred[v] )
        {
            u = pred[v];
            fluxo_cam = min( fluxo_cam, grafo_res[u][v] );
        }
        
        show( pred, s, t ); 
        printf("fluxo-menor %d\n",fluxo_cam );
 
        // Atualiza o grafo residual
        for ( v = t; v != s; v = pred[v] )
        {
            u = pred[v];
            grafo_res[u][v] -= fluxo_cam;
            grafo_res[v][u] += fluxo_cam;
        }
 
        // Atualização do fluxo máximo
        fluxo_max += fluxo_cam;
    }
 
    return fluxo_max;
}
 
void ford_fulkerson_main(void)
{
    // rede : Matriz de adjacência do exercício 10
    int fluxo_maximo,  rede[V][V] = { {0, 10, 15, 7, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 5, 7, 8, 0, 4, 0, 0, 0, 0},
                                    {0, 0, 0, 11, 0, 13, 10, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 12, 6, 0},
                                    {0, 0, 0, 0, 0, 16, 0, 0, 0, 12, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16},
                                    {0, 0, 0, 0, 10, 0, 0, 12, 0, 0, 10},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 26},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
                                  };
 
    fluxo_maximo = ford_fulkerson( rede, 0, 10 );
    cout << "Maior fluxo possível " << fluxo_maximo <<endl;
}