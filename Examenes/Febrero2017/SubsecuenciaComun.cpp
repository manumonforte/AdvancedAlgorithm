// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
#include <string>
#include <algorithm>
/*
subsec(i,j) = maximo tamano de la subsecuencia una vex recorrida hasta la letra i de
			  la palabra X (x0..xi) y hasta la letra j de la palabra Y (y0..yj)

subsec(i,0) = 0
subsec(j,0) = 0
					subsec(i,j) = 1 +subsec(i-1,j-1) si x[i] == y[j]
					subsec(i,j) = max(subsec(i-1,j),subsec(i,j-1)) si x[i] != y[j]

*/

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	std::string x, y;
	std::cin >> x >> y;
	if (!std::cin)
		return false;
	x = ' ' + x;
	y = ' ' + y;
	int n = x.size() - 1;
	int m = y.size() - 1;
	Matriz<int>subsec(x.size(), y.size(), 0);

	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if (x[i] == y[j])
				subsec[i][j] = subsec[i - 1][j - 1] + 1;
			else
				subsec[i][j] = std::max(subsec[i - 1][j], subsec[i][j - 1]);
		}
	}

	std::cout << subsec[n][m] << "\n";
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