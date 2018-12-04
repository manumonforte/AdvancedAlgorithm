// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"
#include <string>


// función que resuelve el problema
long long int resolver(PriorityQueue<long long int> & colap) {
	long long int x, y;
	long long int esfuerzo = 0;
	while (colap.size() > 1){
		x = colap.top();
		colap.pop();
		y = colap.top();
		colap.pop();
		esfuerzo += x + y;
		colap.push(x + y);
	}
	return esfuerzo;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	long long int sumandos;
	std::cin >> sumandos;
	if (!sumandos)
		return false;
	PriorityQueue<long long int> colap;
	long long int num;
	for (long long int i = 0; i < sumandos; i++){
		std::cin >> num;
		colap.push(num);
	}
	if (colap.size() == 1) std::cout << "0";
	else std::cout << resolver(colap);
	
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