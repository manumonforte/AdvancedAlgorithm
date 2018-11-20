// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "TreeMap_AVL.h"


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int claves, clave, k1, k2;
	std::cin >> claves;
	if (!claves)
		return false;
	map<int,int>arbol;
	for (int i = 0; i < claves; i++){
		std::cin >> clave;
		arbol.insert(clave);
	}
	std::cin >> k1 >> k2;
	std::vector<int> sol;
	arbol.rango(sol,k1,k2);
	// escribir sol
	for (auto elem : sol) std::cout << elem << " ";
	std::cout << "\n";
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
