// Manuel Monforte
// TAIS62

/*El problme nos pide usaber cuantos tuneles minimos habrá que hacer para conectar todos los edificios 
con la playa. Para ello creamos una cola de prioridad de todos los edificios, ordenados primero,
por su componente Wi de manera creciente. Tras esto analizamos cada edificio
y si el extremo Wi del uno es menor que el extremo Ei del sigguiente no hace falta colocar pasillo.

Coste de la solucion--> O(NlogN) siendo N el numero de edficios, ya que realizamos N veces la operacion
top/pop que tiene coste logN*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>

struct tEdificio{
	int izq;
	int derec;
	tEdificio(int a, int b) : izq(a), derec(b){};
	tEdificio(){};
};

bool operator <(const tEdificio & a, const tEdificio & b){
	return a.derec > b.derec;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, a, b;
	std::cin >> N;
	if (!N)
		return false;
	std::priority_queue<tEdificio> playa;
	for (int i = 0; i < N; i++){
		std::cin >> a >> b;
		playa.push({ a, b });
	}

	tEdificio elem = playa.top();
	playa.pop();
	int edificios = 1;
	int min = elem.derec;
	while (!playa.empty()){
		if (playa.top().izq >= min){
			edificios++;
			min = playa.top().derec;
		}
		elem = playa.top();
		playa.pop();
	}

	std::cout << edificios << "\n";
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