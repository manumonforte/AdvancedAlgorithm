// Manuel Monforte Escobar
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Matriz.h"
#include <algorithm>

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	std::string palabra;
	std::cin >> palabra;
	if (!std::cin)
		return false;

	Matriz<int>patindromo(palabra.length() + 1, palabra.length() + 1, 0);
	
	for (int i = 1; i <= palabra.length(); i++){
		for (int j = 1; j <= palabra.length(); j++){
			if (palabra[i-1] != palabra[palabra.length() - j])
				patindromo[i][j] = std::max(patindromo[i][j - 1],patindromo[i-1][j]);
			else patindromo[i][j] = patindromo[i - 1][j - 1]+1
				;
		}
	}

	// escribir sol
	std::cout << patindromo[palabra.length()][palabra.length()] << "\n";
	//escribimos palabra
	for (int i = 1; i <= palabra.length(); i++){
		if (patindromo[i - 1][i-1] !=patindromo[i][i]) std::cout << palabra[i - 1];
	}
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