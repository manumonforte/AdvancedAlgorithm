//Manuel Monforte

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "PriorityQueue.h"



/*

Coste de la solucion--> Aplicamos PriorityQueue
	-->Se aplican operaciones top y pop que tiene complejidad logN
	-->Se aplican K veces cada una de ella
	-->Total: O(2K*logN)
*/
struct tUsuario{
	int id;
	int periodo;
	int tiempo;

	tUsuario(){};
	tUsuario(int pk, int ped) : id(pk), periodo(ped),tiempo(ped){};
};

bool operator < (const tUsuario & a, const tUsuario & b){
	return a.tiempo < b.tiempo || ( a.tiempo == b.tiempo && a.id < b.id) ;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, K,id,periodo;
	std::string registro;
	std::cin >> N;
	if (N== 0)
		return false;
	PriorityQueue<tUsuario> UCM;
	
	for (int i = 0; i < N; i++){
		std::cin >> registro >> id >> periodo;
		UCM.push({ id, periodo });
	}
	std::cin >> K;

	for (int i = 0; i < K; i++){
		tUsuario aux = UCM.top();
		UCM.pop();
		std::cout << aux.id << "\n";
		aux.tiempo += aux.periodo;
		UCM.push(aux);
	}

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