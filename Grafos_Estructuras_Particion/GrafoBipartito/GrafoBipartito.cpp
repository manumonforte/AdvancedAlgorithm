
// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Grafo.h"


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int vertices , aristas;
	std::cin >> vertices >> aristas;
	int v, w;
	if (!std::cin)
		return false;
	Grafo grafo(vertices);
	for (int i = 0; i < aristas; i++) {
		std::cin >> v >> w;
		grafo.ponArista(v, w);
	}
	grafo.print();
	GrafoBipartito grafoB(grafo);
	// escribir sol

	if (grafoB.esBipartido()) std::cout << "SI\n";
	else  std::cout << "NO\n";

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
