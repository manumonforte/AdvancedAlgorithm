// Manuel Monforte Escobar
// TAIS62

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>


/*
Coste de la solucion --> O(NlogN) donde N es el numero de personas que esperan al telesilla
*/
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int P, N,valor;
	std::cin >> P >> N;
	if (!std::cin)
		return false;
	std::vector<int> espera;

	for (int i = 0; i < N; i++){
		std::cin >> valor;
		espera.push_back(valor);
	}

	std::sort(espera.begin(), espera.end());
	int i = 0; 
	int j = espera.size() - 1;
	int sillas = 0;
	while (i < j){
		if (espera[i] + espera[j] <= P){
			i++;
			j--;
		}
		else{
			j--;
		}
		sillas++;
	}

	if (i == j) sillas++;
	std::cout << sillas << "\n";

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