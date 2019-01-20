// Manuel Monforte
//Tais62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Grafo.h"
/*
Para comprobar si es conexo basta con aplicar DFS y comprobar que el numerod e nodos recorridos
es igual al numero de vertices del grafo

Para comprobar que no hay ciclo basta con ver que no tiene mas de N-1 vertices

Coste de la solucion--> Aplicacion de DFS--> V+E
*/

class ArbolLibre{
public:
	ArbolLibre(const Grafo & G) :marked(G.V(), false), conexo(false){
		int tam = 0;
		dfs(G, 0, tam);
		if (tam == G.V()) conexo = true;
	}

	bool esLibre(const Grafo & G, int E)const { return conexo && G.V() - 1 == E; }
private:
	std::vector<bool>marked;
	bool conexo;

	void dfs(const Grafo & G, int v,int & tam){
		tam++;
		marked[v] = true;
		for (auto w : G.ady(v)){
			 if (!marked[w])
				dfs(G, w, tam); 
		}
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int V, E,a,b;
	std::cin >> V >> E;
	if (!std::cin)
		return false;
	
	Grafo grafo(V);

	for (int i = 0; i < E; i++){
		std::cin >> a >> b;
		grafo.ponArista(a,b);
	}

	ArbolLibre sol (grafo);
	if (sol.esLibre(grafo,E)) std::cout << "SI\n";
	else std::cout << "NO\n";

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