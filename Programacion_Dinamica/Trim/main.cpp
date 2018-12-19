// Manuel Monforte Escobar
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
#include <algorithm>
#include <string>
/*
trim(i,j)= minimo numero de llamadas a la funcion trim para eliminar la palabra completamente
		   con letras xi .... xj

trim(i,j) = trim(i+1,j-1) + 1 si letra[i]==letra[j]
			max(trim(i+ki,j)+1, trim(i,j-kj) +1 ) si letra[i]!=letra[j]

Caso base
trim(i,j) == 0 si i >j
trim(i,j) == 1 si i == j

Coste en espacio--> (N+1)^2 donde n denota el tamano de la palabra
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
	int n = palabra.size() - 1;
	
	
	Matriz<int> trim(n + 2, n + 2, 0);

	for (int i = 1; i <= n + 1; i++) {
		trim[i][i] = 1;
	}
	
	for (int i = n;  i >= 1; i--){
		for (int j = i; j <= n; j++){

			//buscamos indice ki e indice kj
			int ki = 0;
			while (palabra[ki + i] == palabra[i]){
				ki++;
			}

			int kj = 0;
			while (palabra[j - kj] == palabra[j]){
				kj++;
			}

			//planteamos recursividad
			if (palabra[i] == palabra[j])
				trim[i][j] = trim[i + ki][j - kj] + 1;
			else
				trim[i][j] = std::min(trim[i + ki][j] + 1, trim[i][j - kj] + 1);
		}
	}

	std::cout << trim[1][n] << "\n";

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