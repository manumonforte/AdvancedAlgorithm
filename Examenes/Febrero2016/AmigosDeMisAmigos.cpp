// Manuel Monforte


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Grafo.h"
#include <algorithm>

/*
Coste de la solucion--> Se ha aplicado algoritmo DFS por tato el coste es V+E
						donde V indica el numero de personas y E el numero de
						relaciones.
*/
class Amigos{
public:
	Amigos(const Grafo & G) :marked(G.V(), false){
		for (int i = 0; i < G.V(); i++){
			int tam = 0;
			if (!marked[i])
				dfs(G,i,tam);
			max = std::max(max, tam);
		}
	}
	int getMaxGrupo() const {
		return max;
	}
private:
	std::vector<int>marked;
	int max;

	void dfs(const Grafo & G, int v, int & tam){
		tam++;
		marked[v] = true;
		for (auto w : G.ady(v)){
			if (!marked[w])
				dfs(G, w,tam);
		}
	}
};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	int N, M,a,b;
	std::cin >> N >> M;
	Grafo grafo(N);
	for (int i = 0; i < M; i++){
		std::cin >> a >> b;
		grafo.ponArista(a-1, b-1);
	}
	
	Amigos sol(grafo);

	std::cout << sol.getMaxGrupo() << "\n";
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}