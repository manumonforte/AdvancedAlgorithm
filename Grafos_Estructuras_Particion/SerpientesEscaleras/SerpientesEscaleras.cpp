// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoDirigido.h"
#include <queue>


//Coste del problema-->O(V+E)
//La idea coniste en colocar todasd las aristas, y aprovechar el recorrido en anchura para sacar el camino a la ultima casilla, a la hora de colocar aristas
//nos creamos un vector para saber si en ese vertice hay escalera y serpiente y donde apuntapara poder colocarlo como arista del vertice,

class juegoSyE{
public:

	juegoSyE(GrafoDirigido & G, int s, int k,int ser, int esc) :D(k), marked(G.V(), false), SyE(G.V(), -1), distTo(G.V()) {
		//leemos serpientes y escaleras
		leerSyE(G,ser, esc,D);
		bfs(G, s);
		int x = 1;
	}

	// ¿Hay camino del origen a v?
	bool hayCamino(int v) const {
		return marked[v];
	}
	// número de aristas entre s y v
	int distancia(int v) const {
		return distTo[v];
	}


private:
	int D;//caras del dado
	std::vector<bool> marked; // marked[v] = ¿hay camino de s a v?
	std::vector<int> distTo; // distTo[v] = aristas en el camino s-v más corto
	std::vector<int>SyE;//vector que marca si hay S o E en la casilla
	void bfs(GrafoDirigido & G, int s) {
		std::queue<int> q;
		distTo[s] = 0;
		marked[s] = true;
		q.push(s);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int w : G.ady(v)) {
				if (!marked[w]) {
					distTo[w] = distTo[v] +1;
					marked[w] = true;
					q.push(w);
				}
			}
		}
	}

	void leerSyE(GrafoDirigido & G,int s, int e,int K){
		int v, w;
		//leemos serpientes y las colocamos
		for (int i = 0; i < s; i++){
			std::cin >> v >> w;
			SyE[v - 1] = w-1;
		}
		//leemos escaleras y las colocamos
		for (int i = 0; i < e; i++){
			std::cin >> v >> w;
			SyE[v - 1] = w-1;
		}
		//colocamos aristas segun las caras del dado
		//ponemos todas las aristas para ir avanzando dependiendo de las caras del dado
		for (int i = 0; i < G.V(); i++){
			for (int j = i+1; j <= K+i && j <= G.V() - 1; j++){
				// si en esa casilla hay serpiente o escalera,colocamos el destino como arista
				if (SyE[j]!=-1)
					G.ponArista(i, SyE[j]);
				else G.ponArista(i, j);
			}
		}
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, K, S, E;
	std::cin >> N;
	if (!N)
		return false;
	std::cin >> K >> S >> E;

	GrafoDirigido tablero(N*N);
	
	
	juegoSyE mejorPartida(tablero,0,K,S,E);
	// escribir sol
	std::cout << mejorPartida.distancia(tablero.V()-1) << "\n";
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