// Manuel Monforte	
// TAIS62


//Explicacion del problema y coste
/*Nos piden cuantas parejas de pila podemos hacer para conseguir la cantidad necesaria
entre ambas de tal forma que funcione un coche de carreras. La idea es ordenar las pilas de manera
creciente por su voltaje, tras esto coger la mas pequeña y la mas grande ( su diferencia es maxima)
y comprobar si tienen voltaje, si lo tienen, podemos hacer funcionar un coche de carreras.


Coste de la solcuion --> O(N+NlogN+N)-->O(NlogN)*/



#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	int V, P,valor;
	std::cin >> P >> V;
	std::vector<int>pilas;
	for (int t = 0;t < P; t++){
		std::cin >> valor;
		pilas.push_back(valor);
	}
	std::sort(pilas.begin(), pilas.end());

	int i = 0;
	int j = pilas.size() - 1;
	int coches = 0;
	while (i < pilas.size() && i<j){
		if (pilas[i] + pilas[j] >= V){
			coches++;
			j--;
		}
		i++;
	}

	std::cout << coches << "\n";

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
	
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	
	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}