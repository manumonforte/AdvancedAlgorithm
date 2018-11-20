// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"


//Coste de la solucion O(nlogN) lineal en el numero de partituras totales

struct tInstrumento{
	int musicos;
	int actual;

	tInstrumento(int m) :musicos(m), actual(1){};
};

// ordenamos la cola por el tam del grupo despues de dividir
bool operator <(const tInstrumento &a, const tInstrumento &b){
	int solA = a.musicos / a.actual;
	int solB = b.musicos / b.actual;
	if (a.musicos % a.actual != 0) solA++;
	if (b.musicos % b.actual != 0) solB++;
	return solA > solB;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int partituras, instrumentos;
	std::cin >> partituras >> instrumentos;
	if (!std::cin)
		return false;

	PriorityQueue<tInstrumento, std::greater<tInstrumento>> colap;
	int elem;
	int atrilesOcupados = instrumentos;
	//metemos los primeros musicos
	for (int i = 0; i < instrumentos; i++){
		std::cin >>elem;
		colap.push({ elem });
	}
	//resolvemos
	int libres = partituras - instrumentos;

	//estudiamos a quien dar cada partitura libre
	for (int i = 0; i < libres; i++){
		tInstrumento aux = colap.top();
		colap.pop();
		aux.actual++;
		colap.push(aux);
	}
	//cogemos el grupo con mayor numero de musicos;
	tInstrumento max = colap.top();
	int sol = max.musicos / max.actual;
	std::cout << colap.top().musicos << "\n";

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