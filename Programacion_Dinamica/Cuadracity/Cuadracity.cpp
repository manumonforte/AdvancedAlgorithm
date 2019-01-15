// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include "Matriz.h"

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio´n, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, M;
	std::cin >> N >> M;
	if (!std::cin)
		return false;
	/*
	cuadravity(i,j) = numero de caminos distintos desde el origen 
	una vez recorridas las calles este-oeste de 0..i y las norte.. sur de 0..j

	Casos base
		-->Cuadracity(0,1) = 1
	Funcion recursiva
	cuadracity(i,j) = cuadracity(i-1,j) + cuadracity(i,j-1)

	Coste --> Tras pasarlo a vector la complejidad queda
		Tiempo--> N*M (para leer el mapa) + N*M para el algoritmo recursivo
		Espacio--> N*M ( para el mapa) + N para el vector
	*/


	//creamos el mapa
	Matriz<char>mapa(N, M);
	std::vector<int>cuadracity(M+1,0);
	//leemos el mapa
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			std::cin >> mapa[i][j];
		}
		std::cin.get();
	}

	cuadracity[1] = 1;
	

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if(mapa[i-1][j-1]!= 'P')
				cuadracity[j] = cuadracity[j] + cuadracity[j - 1];
			else cuadracity[j] = 0;
		}
	}
	std::cout << cuadracity[M] << "\n";
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