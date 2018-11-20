// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoValorado.h"
#include <queue>

//coste de la solucion-->Aplicamos algoritmo dfs por tanto el coste es V+E
class Camion{
public:
	Camion(GrafoValorado<int> const & GV, int origen,int anchura): 
		marked(GV.V(),false){
		dfs(GV,origen, anchura);
	}

	// ¿Hay camino del origen a v?
	bool hayCamino(int v) const {
		return marked[v];
	}

private:
	std::vector<bool> marked; // marked[v] = ¿hay camino de s a v?

	void dfs(GrafoValorado<int> const & GV, int v, int anchura) {
		marked[v] = true;
		for (auto w : GV.ady(v)){
			if (!marked[w.otro(v)] && w.valor() >= anchura){
				dfs(GV, w.otro(v), anchura);
			}
		}
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int V, E, K, origen, destino, anchura;
	std::cin >> V >> E;
	if (!std::cin)
		return false;

	GrafoValorado<int> grafoVal(V);
	//colocamos grafo
	for (int i = 0; i < E; i++){
		std::cin >> origen >> destino >> anchura;
		grafoVal.ponArista({ origen-1, destino-1, anchura });
	}
	std::cin >> K;
	for (int i = 0; i < K; i++){
		std::cin >> origen >> destino >> anchura;
		Camion camion(grafoVal, origen-1, anchura);
		if (camion.hayCamino(destino-1)) std::cout << "SI\n";
		else std::cout << "NO\n";
	}


	return true;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso())
		;


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}