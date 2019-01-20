// Manuel Monforte
//TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

/*

Coste de la solcuion--> Operaciones top() y pop() en cola de pripridad
					    O(NlogN) donde N es el numerod e edificios a analizar
*/
struct tEdificio{
	int ini;
	int fin;

	tEdificio(){};
	tEdificio(int a, int b) : ini(a), fin(b){};
};

bool operator < (const tEdificio & a, const tEdificio & b){
	return a.ini < b.ini;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N,a,b;
	std::cin >> N;
	if (N==0)
		return false;

	PriorityQueue<tEdificio> edificios;

	for (int i = 0; i < N; i++){
		std::cin >> a >> b;
		edificios.push({ a, b });
	}
	int ultimoFinal = edificios.top().fin;
	edificios.pop();
	int sol = 1;
	while (edificios.size() > 1){
		if (ultimoFinal <= edificios.top().ini){
			ultimoFinal = edificios.top().fin;
			sol++;
		}
		edificios.pop();
	}

	if (ultimoFinal <= edificios.top().ini){
		ultimoFinal = edificios.top().fin;
		sol++;
	}
	// escribir sol
	std::cout << sol << "\n";

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