// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "Matriz.h"
/*
vacas(i,j) == maxima comida si estan disponibles los cubos de la i..j

vacas(i,j) == max(cogemosIzq,cogemosDerec)


			  cogemosIzq = vacas(i+1,j-1) + comida[i] si comida[j] > comdia[i+1]
						   vacas(i+2,j) + comida[i] si comida[j] <= comida[i+1]

			  cogemosDerec = vacas(i+1,j-1) + comida[j] si comida[j-1] < comida[i]
							 vacas(i,j-2) + comida[j] si comida[j-1] >= comida[i]

		vacas[i][i] = comida[i]
		vacas[i][i+1] = max(comida[i],comida[i+1]


Coste --> Espacio y Tiempo --> N*N donde N denota el numero de cubos, al realizar recorrido
en diagonales recorremos toda la matriz
*/


// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio´n, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, valor;
	std::cin >> N;
	if (N == 0)
		return false;
	std::vector<int> comida;

	//creamos vector 1-based
	comida.push_back(0);
	for (int i = 0; i < N; i++) {
		std::cin >> valor;
		comida.push_back(valor);
	}

	Matriz<int> vacas(N + 1, N + 1, 0);

	//inicializamos casos base
	for (int i = 1; i < N; i++) {
		vacas[i][i + 1] = std::max(comida[i], comida[i + 1]);
	}
	for (int i = 1; i <= N; i++) {
		vacas[i][i] = comida[i];
	}


	for (int d = 2 ; d <= N -1 ; d++){
		for (int i = 1; i <= N-d; i++) {
			int j = i + d;

			int cogemosIzq, cogemosDerec;

			//calculamos si como de la parte izq

			if (comida[j] > comida[i + 1])
				cogemosIzq = vacas[i + 1][j - 1] + comida[i];
			else
				cogemosIzq = vacas[i + 2][j] + comida[i];

			//calculamos si como de la parte derecha
			if (comida[j - 1] > comida[i])
				cogemosDerec = vacas[i][j - 2] + comida[j];
			else
				cogemosDerec = vacas[i + 1][j - 1] + comida[j];

			vacas[i][j] = std::max(cogemosIzq,cogemosDerec);
		}
	}
	std::cout << vacas[1][N] << "\n";
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