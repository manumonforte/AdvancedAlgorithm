// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include <queue>

//Coste de la solucion--> Aplicacion algortimo de Prim(Lazy Implementation) --> O(E log V)
class Archipielago{
public:
	Archipielago(GrafoValorado<int> const & GV) :
		min(-1), marked(GV.V(),false){
		visit(GV, 0);
		while (!pq.empty() &&  colap.size() < GV.V() - 1){
			Arista<int> aux = pq.top();
			pq.pop();
			int v = aux.uno();
			int w = aux.otro(v);
			// si alguno no esta marcado visitamos--> sustituye al continue de Java
			if (!marked[v] || !marked[w]){
				colap.push(aux);
				if (!marked[v]) visit(GV, v);
				if (!marked[w]) visit(GV, w);
			}
		}
		int tamCola = colap.size();
		int coste = calculaCoste();
		//nos aseguramos de que el arbol entero sea conexo, para ello debe tener 
		//exactamente V-1 aristas
		if (tamCola == GV.V()-1) min = coste;
	}

	int calculaCoste() {
		int rdo = 0;
		int tam = colap.size();
		for (int i = 0; i < tam; ++i) {
			rdo += colap.front().valor();
			colap.pop();
		}
		return rdo;
	}

	int getMin(){ return min;}
private:
	int min;
	std::queue<Arista<int>> colap;
	std::vector<bool> marked;
	std::priority_queue<Arista<int>, std::vector<Arista<int>>,std::greater<Arista<int>>> pq;

	void visit(GrafoValorado<int> const &  G, int v) { // Add v to tree; update data structures.
		marked[v] = true;
		for (auto w : G.ady(v)){
			if (!marked[w.otro(v)]){
				pq.push(w);
			}
		}
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int V, E, v, w,valor;
	std::cin >> V >> E;
	if (!std::cin)
		return false;
	GrafoValorado<int> grafo(V);

	for (int i = 0; i < E; i++){
		std::cin >> v >> w >> valor;
		grafo.ponArista({ v-1, w-1, valor });
	}

	Archipielago sol(grafo);
	if (sol.getMin() != -1) std::cout << sol.getMin() << "\n";
	else std::cout << "No hay puentes suficientes\n";

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