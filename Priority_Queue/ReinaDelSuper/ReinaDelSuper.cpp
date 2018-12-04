//Manuel Monforte
//TAIS62
#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

// El coste de la solucion es O(NlogN + ClogN) 
struct tCaja{
	int id = -1;
	int tiempo = 0;

	tCaja(){};
	tCaja(int i) : id(i){};
};

bool operator < (tCaja const & a, tCaja const & b){
	if (a.tiempo < b.tiempo) return true;
	else if (a.tiempo > b.tiempo) return false;
	else{
		if (a.id < b.id) return true;
		else  return false;
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int cajas, clientes, tiempo;
	std::cin >> cajas >> clientes;
	if (!cajas ||!clientes)
		return false;
	PriorityQueue<tCaja>filaUnica;
	//creamos cajas libres
	for (int i = 0; i < cajas; i++)
		filaUnica.push({ i + 1 });



	while (clientes--){
		tCaja aux = filaUnica.top();
		filaUnica.pop();
		std::cin >> tiempo;
		aux.tiempo += tiempo;
		filaUnica.push(aux);
	}
	std::cout << filaUnica.top().id << "\n";

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