// Manuel Monforte Escobar
//Tais62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
#include <algorithm>
/*

tablero(i,j) = maxima puntuacion posible una vez recorrida las filas de la
			   N a la i en la columna j

tablero(i,j) = puntuaciones(i,j) + max(tablero(i+1,j-1),tablero(i+1,j), tablero(i+1,j+1)

*/

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	std::cin >> N;
	if (!std::cin)
		return false;
	Matriz<int> puntuaciones(N+1,N+2,0);
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			std::cin >> puntuaciones[i][j];
		}
	}

	Matriz<int> tablero(N+1, N+2,0);

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			int maxCasillas = std::max(std::max(tablero[i - 1][j - 1], tablero[i - 1][j]), tablero[i - 1][j + 1]);
			tablero[i][j] = puntuaciones[i][j] + maxCasillas;
		}
	}

	int max = -1;
	int columna = -1;
	for (int j = 1; j <= N; j++){
		if (tablero[N][j] > max){
			max = tablero[N][j];
			columna = j;
		}
	}

	std::cout << max << " " << columna << "\n";

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