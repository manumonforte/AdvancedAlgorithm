// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoDirigido.h"

//Coste de la solucion --> V+E


class Arborescencia{
public: 
	Arborescencia(GrafoDirigido const & GD) : marked(GD.V(), false), root(-1){
		int tam = 0;
		bool out = false;
		//observamos el grafo diridigo al reves
		GrafoDirigido GDI = GD.inverso();
		for (int i = 0; i < GDI.V() && !out; i++){
			//si el inverso no tiene adyacentes es hoja
			if (GDI.ady(i).size() == 0){
				if (root == -1){
					tam = 1;
					//aplicamos dfs siguiendo aristas dirigidas , de esta manera si 
					// es igual al numero de los vetices llega a todos ellos la raiz
					if (dfs(GD, i, tam) &&  tam == GDI.V()  ){
						root = i;
						out = true;
					}
				}
				else out = true;
			}
		}
	}

	int getRoot(){ return root; }
private:
	std::vector<bool> marked;
	int root;
	//modificamos dfs returnando booleano con el objetivo de ver si se han recorrido todas las aristas para el camino unico
	bool dfs(GrafoDirigido const & GD, int v, int &tam){
		marked[v] = true;
		for (auto w : GD.ady(v)){
			if (!marked[w]){
				tam++;
				if (!dfs(GD, w, tam))
					return false;
			}
			else return false;
		}
		return true;
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int V, E;
	std::cin >> V >> E;
	if (!std::cin)
		return false;
	int origen, destino;
	GrafoDirigido grafo(V);
	for (int i = 0; i < E; i++){
		std::cin >> origen >> destino;
		grafo.ponArista(origen, destino);
	}
	Arborescencia sol(grafo);
	if (sol.getRoot() >=0) std::cout << "SI " << sol.getRoot();
	else std::cout << "NO";

	std::cout <<  "\n";
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