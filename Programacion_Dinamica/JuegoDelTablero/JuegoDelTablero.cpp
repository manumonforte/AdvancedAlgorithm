// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
#include <algorithm>

/*
Funciones recursivas
-->tabla(i,j) Maximo valor posible hasta la fila i del tablero y la columna j del mismo.

tabla(i,j) = tablero[i][j] si tabla[i-1][j] == -1
tabla(i,j) = max(diagonalIzq,diagonalDerec,casillaSuperior) +tablero[i][j] si tabla[i][j] !=-1

Coste de la funcion--> N es la dimension de la matriz
	Tiempo--> N+1*N+2 + N+2 
	Espacio--> N+1*N+2
*/


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	std::cin >> N;
	if (!std::cin)
		return false;
	Matriz<int>tablero(N + 1, N + 2, -1);
	//leemos tablero
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			std::cin >> tablero[i][j];

	Matriz<int>tabla (N + 1, N + 2, -1) ;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			if (tabla[i - 1][j] == -1) tabla[i][j] = tablero[i][j];
			else{
				int izqDer = std::max(tabla[i - 1][j - 1], tabla[i - 1][j + 1]);
				int max = std::max(izqDer, tabla[i - 1][j]);
				tabla[i][j] =max + tablero[i][j];
			}
		}
	}
	
	int column=1;
	// cálculo de los objetos
	for (int j = 1; j <= N; j++) {
		if (tabla[N][j] > tabla[N][column]) {
			column = j;
		}
	}
	std::cout << tabla[N][column] << " " << column << "\n";

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