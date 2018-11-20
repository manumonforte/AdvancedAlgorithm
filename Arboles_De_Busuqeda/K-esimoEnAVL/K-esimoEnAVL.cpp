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
	int claves, clave;
	std::cin >> claves;
	if (!claves)
		return false;
	map<int,int>arbol;
	for (int i = 0; i < claves; i++){
		std::cin >> clave;
		arbol.insert(clave);
	}
	int consultas, consulta;
	std::cin >> consultas;
	for (int i = 0; i < consultas; i++){
		std::cin >> consulta;
		try{
			std::cout << arbol.goK(consulta) << "\n";
		}
		catch (std::domain_error & e){
			std::cout << "??\n";
		}
	}
	std::cout << "----\n";
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
