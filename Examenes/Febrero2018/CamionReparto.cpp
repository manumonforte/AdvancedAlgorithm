// Manuel Monforte Escobar
//TAIS62

/*
Coste de la solucion--> SDe aplica DFS, por tanto V+E, donde V son las intersecciones
y e las calles que las unen.
*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoValorado.h"


class Reparto{
public:
	Reparto(const GrafoValorado<int> & G, int origen,int anchura) :marked(G.V(), false){
		dfs(G, origen, anchura);
	}

	bool repartoPosible(int destino)const{ return marked[destino]; }
private:
	std::vector<bool>marked;

	void dfs(const GrafoValorado<int> & G, int v, int anchura){
		marked[v] = true;
		for (auto a : G.ady(v)){
			int w = a.otro(v);
			if (!marked[w] && a.valor()>=anchura)
				dfs(G, w, anchura);
		}
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int V, E, a, b, valor,origen,destino,anchura;
	std::cin >> V >> E;
	if (!std::cin)
		return false;

	GrafoValorado<int> ciudad(V);

	for (int i = 0; i < E; i++){
		std::cin >> a >> b >> valor;
		ciudad.ponArista({ a - 1, b - 1, valor });
	}
	int K;
	std::cin >> K;
	for (int i = 0; i < K; i++){
		std::cin >> origen >> destino >> anchura;
		Reparto sol(ciudad, origen-1, anchura);
		if (sol.repartoPosible(destino-1)) std::cout << "SI\n";
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