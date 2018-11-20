// Manuel Monforte
//TAIS 62


/*El problema explica como se debe realizar Lucas el camino al cole. Se resolverá mediante el algoritmo de Disjkstra donde las intersecciones serán los
vértices de la solución y las calles serán las aristas de la misma. Observamos que debemos aplicar el algorimo, para sacar los caminos mínimos hasta cada una de las intersecciones, por tanto tendremos
guardado el numero de camino minimo de caminos para llegar a cada inerseccion, y de esta forma porder saber cuantos llegan a la interseccion final /colegio.

El coste de la solucion es o(ElogV)--> O(Calles * logIntersecciones) ya que se realizan por cada arista operaciones de coste logV por la IndexPQ.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoValorado.h"
#include "IndexPQ.h"

const int INF = 1000000000;

class CaminoCole {
public:

	CaminoCole(const GrafoValorado<int> & GV) : distTo(GV.V(), INF), caminos(GV.V(), 0), pq(GV.V()), V(GV.V()){
		//se aplica algorimo Disjkstra 

		distTo[0] = 0;
		pq.push(0, 0);
		caminos[0] = 1;
		while (!pq.empty()) {
			auto v = pq.top();
			pq.pop();
			for (auto w : GV.ady(v.elem))
				visita(w, v.elem);
		}
	}

	int getCaminos() { return caminos[caminos.size() - 1]; }

private:
	std::vector<int>distTo;
	std::vector<int>caminos;//vector que calcula el numero de caminos minimos hasta v
	IndexPQ<int>pq;
	int V;

	void visita(const Arista<int> & a, int v) {
		int w = a.otro(v);
		//actualizamos distancias
		if (distTo[w] > distTo[v] + a.valor()) {
			distTo[w] = distTo[v] + a.valor();
			caminos[w] = caminos[v];
			pq.update(w, distTo[w]);
		}
		// si es otro camino con igual coste al minimo, sumamos los caminos minimos de la interseccion anterior a este
		else if (distTo[w] == distTo[v] + a.valor()) caminos[w] += caminos[v];
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, C, v, w, valor;
	std::cin >> N >> C;
	if (!std::cin)
		return false;

	GrafoValorado<int> GV(N);

	for (int i = 0; i < C; i++) {// O(E)
		std::cin >> v >> w >> valor;
		GV.ponArista({ v - 1, w - 1, valor });
	}

	// escribir sol
	CaminoCole sol(GV);
	std::cout << sol.getCaminos() << "\n";

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
