// Manuel Monforte
// TAIS62


/*
El problema nos pide el numero minimo de amigos para asistir a todas las conferencias. Para
ello las ordenamos por inicio, y las recorremos de tal forma que asignamos la primera conferencia
a nosotros mismos. Si la siguiente empieza antes de acabar neceistamos un amigo. Por tanto vamos
guardando de cada amigo que necesitamos cuando queda libre para poder asignarlo a una nueva actividad.

Coste de la solucion--> O(NlogN+NlogN) Ya que aplicamos sort(NlogN) y luego recorremos el
vector con coste lineal(N). 
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
struct tActividad{
	int ini;
	int fin;

	tActividad(int o, int d) : ini(o), fin(d){};
	tActividad(){};
};

bool operator <(const tActividad & a, const tActividad &b){
	return a.ini < b.ini;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N,a,b;
	std::cin >> N;
	if (!N)
		return false;
	std::vector<tActividad> actividades;
	std::priority_queue<int, std::vector<int>,
		std::greater<int>> amigos;
	for (int i = 0; i < N; i++){
		std::cin >> a >> b;
		actividades.push_back({ a, b });
	}

	std::sort(actividades.begin(), actividades.end());

	int min = 0;
	//la primera persona queda libre cuando acaba la primera actividad
	amigos.push(actividades[0].fin);

	//para cada actividad
	for (int i = 1; i < actividades.size(); i++){
		//si puede encargarse alguien se lo aginamos
		if (actividades[i].ini >= amigos.top()){
			amigos.pop();
			amigos.push(actividades[i].fin);
		}

		else if (amigos.top() >= actividades[i].ini){
			//sino quedan amigos necesitamos uno
			if (amigos.empty()){
				min++;
				amigos.push(actividades[i].fin);
			}
			// si hay un amigo que esta libre lo asignamos
			else if (amigos.top() <= actividades[i].ini){
				amigos.pop();
				amigos.push(actividades[i].fin);
			}
			//si hay amigos pero no estan libres necesitamos otro
			else{
				min++;
				amigos.push(actividades[i].fin);
			}
		}
	}
	

	// escribir sol
	std::cout << min << "\n";

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