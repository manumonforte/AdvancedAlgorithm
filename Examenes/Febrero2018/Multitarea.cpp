// Manuel Monforte
// TAIS62	

/*
Se ordenan las tareas por instante de comienzo, de tal forma,
que comprobamos si el comienzo dela siguiente tarea es menor que la
finalizacion de la anterior en cuyo caso hay conflicto

Se utiliza priorityQueue , con opraciones top() y pop(), por tanto
el coste de la solcuion es O(NlogN), donde N es el numero de tareas que se analizan

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

struct tTarea{
	int ini;
	int fin;
	int periodo;

	tTarea(){};
	tTarea(int a, int b, int p) : ini(a), fin(b), periodo(p){};
};



bool operator < (const tTarea & a, const tTarea & b){
	return a.ini < b.ini;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, M, T,a,b,p;
	std::cin >> N >> M >> T;
	if (!std::cin)
		return false;
	PriorityQueue<tTarea>tareas;
	
	for (int i = 0; i < N; i++){
		std::cin >> a >> b;
		tareas.push({ a, b,-1 });
	}

	for (int i = 0; i < M; i++){
		std::cin >> a >> b >> p;
		tareas.push({ a, b, p });
	}
	tTarea aux = tareas.top();
	bool valido = true;
	//mientras que este dentro de tiempo y no haya conflicto
	while (tareas.size() > 1 && aux.fin < T && valido){
		tareas.pop();
		//observamos si hay conflicto con la sigueinte tarea
		if (tareas.top().ini < aux.fin)
			valido = false;
		// si no lo hay comrpbamos si es periodica, la volvemos a introducir
		if (aux.periodo>-1)
			tareas.push({ aux.ini + aux.periodo, aux.fin + aux.periodo, aux.periodo });
		//obtenemos la siguiente tarea
		aux = tareas.top();
	}
	// escribir sol
	if (!valido) std::cout << "SI\n";
	else std::cout << "NO\n";

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