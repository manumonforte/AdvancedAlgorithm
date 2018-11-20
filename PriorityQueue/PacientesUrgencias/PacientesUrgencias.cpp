// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"
#include <string>

struct tEnfermo{
	std::string id = "";
	int gravedad = -1;
	int time = -1;
};
bool operator < (tEnfermo const & a, tEnfermo const & b){
	return a.gravedad > b.gravedad ||
		(a.gravedad == b.gravedad && a.time < b.time);
}



// función que resuelve el problema
void resolver(PriorityQueue<tEnfermo> & colap,int k) {
	int cont = 0;
	std::string idAux;
	int gravAux;
	char tipo;
	while (k--){
		std::cin >> tipo;
		if (tipo == 'I'){
			std::cin >> idAux;
			std::cin >> gravAux;
			tEnfermo aux;
			aux.id = idAux;
			aux.gravedad = gravAux;
			aux.time = cont;
			colap.push(aux);
			cont++;
		}
		else{
			std::cout << colap.top().id << "\n";
			colap.pop();
		}
	}
	std::cout << "----\n";
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int eventos;
	std::cin >> eventos;
	if (!eventos)
		return false;
	PriorityQueue<tEnfermo> colap;
	
	resolver(colap,eventos);

	// escribir sol

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