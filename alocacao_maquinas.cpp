/* Universidade Federal do Espírito Santo - Ufes
   Centro Universitário Norte do Espírito Santo - Ceunes
   Teoria dos Grafos 2018/1 - TG20181
   Lista de exercícios II 
   Coloração de grafos: Alocação de recursos
   Autor: Elyabe Alves
*/

#include <bits/stdc++.h>

using namespace std;

typedef pair< double, double > Intervalo;

// Sobreescreve a comparação
bool cmp_intervalo( Intervalo A, Intervalo B ) 
{
	return A.first < B.first;
}

// Gera intervalos [a,b) e amazena em op_maquina
// op_maquina[0] armazena os extremos do intervalo [a,b)
// qtd_intervalos: número de intervalos desejados
void gerar_intervalos( vector<Intervalo> &op_maquina, unsigned int qtd_intervalos )
{
	double t_i, t_f, t_0, t, tam;
	unsigned int id;
	t_0 = op_maquina[0].first;
	t = op_maquina[0].second;

	while ( qtd_intervalos )
	{

		t_i = (t_0 + rand()%( (int)(t*100)) )/100.0;
		do
		{
			t_f = (t_0 + rand()%( (int)(t*100)) )/100.0;
		} while( t_i >= t_f  );
			
		id = 1;
		while ( id < op_maquina.size() && op_maquina[id].first != t_i && op_maquina[id].second != t_f ) id++;
		
		if ( id == op_maquina.size() )
		{	
			op_maquina.push_back( make_pair( t_i, t_f ) );
			qtd_intervalos--;
		}
	}
}

// Exibe o vetor de intervalos
// v : Vetor de intervalos
void exibir_vetor( vector<Intervalo> v )
{
	for ( int c = 1; c < v.size(); c++ )
		cout<<c<< ": ["<<v[c].first<<","<< v[c].second <<")"<<endl;
}

// Colore sequencialmente o grafo de intervalos
// intervalos: Grafo de intervalos <t_i, t_f>
int colorir_sequencialmente( vector<Intervalo> intervalos )
{
	unsigned int id_cor, j, i, qtd_cores, qtd_intervalos = intervalos.size();

	queue<int> cores[ qtd_intervalos + 1 ];
	double l[ qtd_intervalos + 1 ];
	
	// Ordena os intervalos de acordo com o tempo inicial de cada um
	sort( intervalos.begin(), intervalos.end(), cmp_intervalo );
	exibir_vetor( intervalos );

	
	// Determina menor número de cores usando algoritmo de coloração sequencial
	for ( i = 1, id_cor = 0; i < intervalos.size(); i++ )
	{
		// J : cada cor já existente
		// Enquanto puder anexar o intervalo a alguma cor pré-existente, assim o faz
		j = 1;
		while ( j <= id_cor && l[j] > intervalos[i].first ) j++;

		// Se não foi possivel anexá-lo em alguma das cores, então atribui nova cor
		if ( j > id_cor )
		{
			id_cor++;
			cores[id_cor].push(i);
			l[id_cor] = intervalos[i].second;
		} else
		{
			// Senão coloca tarefas não conflitantes no mesma cor
			cores[j].push(i);
			l[j] = intervalos[i].second;
		}
	}

	// Exibe os intervalos e a quais cores pertencem
	for ( int k = 1; k <= id_cor; k++ )
	{
		printf("cor %d\n", k );
		while( !cores[k].empty() )
		{
			cout<<cores[k].front()<<endl;
			cores[k].pop();
		}
	}

	return id_cor;
}

// Procedimento principal do exercicio
// t_i : inicio do intervalo
// t_f : fim do intervalo
void alocacao_maquinas_main()
{
	double t_i, t_f;
	unsigned int qtd_intervalos;
	
	vector<Intervalo> operador_maquina;

	cin>>qtd_intervalos>>t_i>>t_f;

	operador_maquina.push_back( make_pair(t_i,t_f) );
	
	// Geração pseudoaleatória de intervalos
	gerar_intervalos( operador_maquina, qtd_intervalos );
	
	// Entrada via teclado de intervalos 
	/*while( qtd_intervalos-- )
	{
		cin>>t_i>>t_f;
		operador_maquina.push_back( make_pair( t_i, t_f ) );
	}*/

	printf("Quantidade minima de cores: %u\n", colorir_sequencialmente( operador_maquina ) );
}