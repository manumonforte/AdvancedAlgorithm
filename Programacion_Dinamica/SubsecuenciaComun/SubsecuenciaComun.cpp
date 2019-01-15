// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include "Matriz.h"
/*
Funciones recursivas
subsecuencia(i,j) = El tam de la secuancia mas larga hasta la letra i de la lapabra X, para
la letra j de la palabra Y.

subsecuencia(i,j) = subseuencia(i-1,j-1) +1 si i = j
subsecuencia(i,j) = max(subsecuencia(i-1,j),subsecuencia(i,j-1) si i !=j

Coste de la solucion-->
	Tiempo --> X * Y siendo x el tam de la secuencia x e Y el tam de la secuencia Y
	Espacio --> X * Y siendo x el tam de la secuencia x e Y el tam de la secuencia Y

*/

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	std::string x, y;
	std::cin >> x >> y;
	if (!std::cin)
		return false;

	Matriz<int> tabla(x.length()+1, y.length()+1,0);

	for (int i = 1; i <= x.length(); i++){
		for (int j = 1; j <= y.length(); j++){
			if (x[i - 1] != y[j - 1]) tabla[i][j] = std::max(tabla[i - 1][j], tabla[i][j - 1]);
			else tabla[i][j] = tabla[i - 1][j-1]+1;
		}
	}

	// escribir sol
	std::cout << tabla[x.length()][y.length()] << "\n";

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