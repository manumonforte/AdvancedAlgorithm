// Manuel Monforte
// TAIS62

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
#include <string>
#include <algorithm>
/*
aibofobia(i,j) = minimo de letras a anadir para que la palabra situada entre 0.. i e j..palabra.size() sea
palindromo

aibofobia(i,j) = aibofobia(i+1,j-1) letra[i]==letra[j]
min(aibofobia(i+1,j)1,aibofobia(i,j1))+1

*/
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	std::string palabra;
	std::cin >> palabra;
	if (!std::cin)
		return false;
	palabra = ' ' + palabra;
	int N = palabra.size() - 1;
	Matriz<int>aibofobia(N + 1, N + 1, 0);
	// escribir sol

	for (int d = 1; d <= N - 1; d++){
		for (int i = 1; i <= N - d; i++){
			int j = i + d;
			if (palabra[i] == palabra[j])
				aibofobia[i][j] = aibofobia[i + 1][j - 1];
			else
				aibofobia[i][j] = std::min(aibofobia[i + 1][j], aibofobia[i][j - 1]) + 1;
		}
	}

	std::cout << aibofobia[1][N] << "\n";
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