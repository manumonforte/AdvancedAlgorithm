// TAIS62
// Manuel Monforte

#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoDirigidoValorado.h"
#include <queue>
#include "IndexPQ.h"

/*El problema explica como se debe realizar el reparto de paquetes en una comarca. Se resolverá mediante el algoritmo de Disjkstra donde las casas serán los
vértices de la solución y las calles serán las aristas de la misma. Observamos que debemos aplicar dos veces el algorimo, una vez para sacar los caminos mínimos hasta los
domicilios donde se desea repartir, y otra vez aprovechando el grafo inverso, calculamos lo que cuesta volver desde los respectivos domicilos a la base de reparto.

El coste de la solucion es o(2 * ElogV) ya que se realizan por cada arista operaciones de coste logV por la IndexPQ.
*/



const int INF = 1000000000;

struct tInfo {
	int origin;
	std::vector<int>entregados;
};


class Mensajeria {

public:
	Mensajeria(const GrafoDirigidoValorado<int> & GDV, int origen) : distTo(GDV.V(), INF),
		pq(GDV.V()), posible(true), tiempo(0), distBack(GDV.V(), INF) {


		//creamos un Disjkstra para calcular los caminos de vuelta con grafo inverson
		GrafoDirigidoValorado<int> inverso = GDV.inverso();

		//la distancia al origen siempre es cero
		distBack[origen] = 0;
		//introducimos en la cola el elemento y la prioridad(su distancia al origen)
		pq.push(origen, 0.0);

		while (!pq.empty()) {// ElogV
			auto v = pq.top();
			pq.pop();
			for (auto w : inverso.ady(v.elem)) {
				visitaBack(w); //logV
			}
		}

		//creamos otro Disjkstra para calcular los caminos minimos y con el anterior sumarle la vuelta
		distTo[origen] = 0;
		//introducimos en la cola el elemento y la prioridad(su distancia al origen)
		pq.push(origen, 0.0);

		while (!pq.empty()) { // ElogV
			auto v = pq.top();
			pq.pop();
			for (auto w : GDV.ady(v.elem)) {
				visita(w); // logV
			}
		}
	}

	int getTiempo(const tInfo & info) {//Coste lineal en el numero de paquetes a repartir O(envios)
		for (int i = 0; i < info.entregados.size(); i++){
			if (distTo[info.entregados[i]] == INF || distBack[info.entregados[i]] == INF)
				posible = false;
			tiempo += distTo[info.entregados[i]] + distBack[info.entregados[i]];
		}
		if (!posible) return -1;
		else return tiempo;
	}

private:
	IndexPQ<double>pq;
	std::vector<int>distTo;
	std::vector<int>distBack;
	int tiempo;
	bool posible;

	void visita(const AristaDirigida<int> & a) {//logV
		int v = a.from();
		int w = a.to();
		if (distTo[w] > distTo[v] + a.valor()) {
			distTo[w] = distTo[v] + a.valor();
			//actualizamos dicho elem
			pq.update(a.to(), distTo[w]);
		}

	}
	void visitaBack(const AristaDirigida<int> & a) {//logV
		int v = a.from();
		int w = a.to();
		if (distBack[w] > distBack[v] + a.valor()) {
			distBack[w] = distBack[v] + a.valor();
			//actualizamos dicho elem
			pq.update(a.to(), distBack[w]);
		}

	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, C, O, v, w, valor;
	std::cin >> N;
	if (!std::cin)
		return false;

	GrafoDirigidoValorado<int> GDV(N);
	std::cin >> C;
	//leemos los caminos que conectan con casas
	for (int i = 0; i < C; i++) {
		std::cin >> v >> w >> valor;
		GDV.ponArista({ v - 1, w - 1, valor });
	}
	//leemos las casas a las que enviar paquetes
	tInfo info;
	std::cin >> info.origin >> O;
	info.origin--;
	int domicilio;
	for (int i = 0; i < O; i++) {
		std::cin >> domicilio;
		info.entregados.push_back(domicilio - 1);
	}

	Mensajeria sol(GDV, info.origin);

	int tiempo = sol.getTiempo(info);
	if (tiempo == -1) std::cout << "Imposible\n";
	else std::cout << tiempo << "\n";

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
