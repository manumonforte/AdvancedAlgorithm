// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

/*
Algoritmo aplicado-> Dijkstra -->Coste ElogV
*/
const int INF = 1000000000;

class Ratones {
public:
	Ratones(const GrafoDirigidoValorado<int> & GV, int s):distTo(GV.V(),INF), pq(GV.V()){

		GrafoDirigidoValorado<int> GI = GV.inverso();
		distTo[s] = 0;
		pq.push(s, 0);

		while (!pq.empty()) {
			int v = pq.top().elem;
			pq.pop();
			for (auto a : GI.ady(v)) {
				relax(a);
			}
		}
	}

	int calculaRatones(int s, int T) {
		int contador = 0;
		for (int i = 0; i < distTo.size(); i++) {
			if (i != s && distTo[i] <= T)
				contador++;
		}
		return contador;
	}
private:
	std::vector<int> distTo;
	IndexPQ<int> pq;

	void relax(const AristaDirigida<int> & a) {
		int v = a.from();
		int w = a.to();
		if (distTo[w] > distTo[v] + a.valor()){
			distTo[w] = distTo[v] + a.valor();
			pq.update(w, distTo[w]);
		}
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio´n, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, S, T, P,a,b,valor;
	std::cin >> N >> S >> T >> P;
	if (!std::cin)
		return false;
	
	GrafoDirigidoValorado<int> laberinto(N);

	for (int i = 0; i < P; i++) {
		std::cin >> a >> b >> valor;
		laberinto.ponArista({ a - 1,b - 1,valor });
	}

	Ratones sol(laberinto, S-1);
	std::cout << sol.calculaRatones(S-1, T) << "\n";

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