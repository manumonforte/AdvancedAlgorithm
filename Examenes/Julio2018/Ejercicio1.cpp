// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"
#include <string>

/*

Coste de la solucion-->Operaciones top() y pop() sobre cola de prioridad
					   O(NlogN) siendo n el numerod e pacientes a tratar

*/
struct tPaciente{
	std::string nombre;
	int gravedad;

	tPaciente(){};
	tPaciente(std::string n, int g) : nombre(n), gravedad(g){};
};

bool operator < (const tPaciente & a, const tPaciente & b){
	return a.gravedad > b.gravedad;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N,g;
	char type;
	std::string n;

	std::cin >> N;
	if (N==0)
		return false;

	PriorityQueue<tPaciente>listaEspera;

	for (int i = 0; i < N; i++){
		std::cin >> type;
		if (type == 'I'){
			std::cin >> n >> g;
			listaEspera.push({ n, g });
		}
		else if (type == 'A'){
			std::cout << listaEspera.top().nombre << "\n";
			if(listaEspera.size()>1)listaEspera.pop();
		}
	}

	std::cout << "----\n";
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