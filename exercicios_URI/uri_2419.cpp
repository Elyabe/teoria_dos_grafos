/* Universidade Federal do Espírito Santo - Ufes
   Centro Universitário Norte do Espírito Santo - Ceunes
   Teoria dos Grafos 2018/1 - TG20181
   Tarefa exercícios URI - 2419
   Data: 20/04
   Autor: Elyabe Alves
*/ 

#include <bits/stdc++.h>

#define NM_MAX 1001

using namespace std;

struct Movimento 
{
	int dx, dy;

	Movimento(int dx, int dy) :
		dx(dx), dy(dy){}
};

	//Deslocamento para direita/cima/esquerda/baixo - facilitar
	Movimento caminhos[] = { Movimento(1,0), Movimento(0,1), Movimento(-1,0), Movimento(0,-1) };
	//Mapeamento da ilha
	char mapa[NM_MAX][NM_MAX];
	int  x, y, N, M, qtdCosta = 0, i, j, k, Dx, Dy;

int main()
{

	// Entrada 1 <= M, N <=100
	scanf("%d%d", &M, &N );
	
	//Mapeia o mapa na memória
	for ( i = 1; i <= M; i++ )
		scanf("%s", &mapa[i][1] );
	
	//Percorre o mapa
	for ( i = 1; i <= M; i++ )
		for ( j = 1; j <= N; j++ )
		{	
			//Se for um porção de terra
			if( mapa[i][j] == '#' ) 
			{
				x = 0;
				for ( k = 0; k < 4; k++ )
				{
					//Determina deslocamentos em todas as regiões
					Dx = caminhos[k].dx, Dy = caminhos[k].dy; 
					
					// Se a porção vizinha for terra firme 
					x += ( mapa[ i + Dx ][j + Dy ] == '#' );
				}

				//Se for costa: 0, 1, 2 ou 3 vizinhos terra firme
				qtdCosta += ( x/4 == 0 );
			}
		}

	printf("%d\n", qtdCosta );

	return 0;
}
