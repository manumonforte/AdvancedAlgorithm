// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "Matriz.h"
#include <algorithm>

/*
Funciones recursivas-->
Matriz de adyacencia
	
	        |0 si i = j
	G[i][j] |coste si hay arista de i a j
			|INF si no hay arista de i a j

Se aplica algoritmo de Floyd
Timepo-->O(n^3)
Espacio --> Co +tamHashMap en espacio adicional
*/
const int INF = 100000000;
void Floyd(Matriz<int> const& G, Matriz<int> & C,
	Matriz<int> & camino) {
	int n = G.numfils() - 1;
	// inicialización
	C = G;
	camino = Matriz<int>(n + 1, n + 1, 0);
	// actualizaciones de la matriz
	for (int k = 1; k <= n; ++k)
	for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= n; ++j) {
		int temp = C[i][k] + C[k][j];
		if (temp < C[i][j]) { // es mejor pasar por k
			C[i][j] = temp;
			camino[i][j] = k;
		}
	}
}

void imp_camino_int(int i, int j, Matriz<int> const& camino) {
	int k = camino[i][j];
	if (k > 0) {
		imp_camino_int(i, k, camino);
		std::cout << " " << k;
		imp_camino_int(k, j, camino);
	}
}

void imprimir_caminos(Matriz<int> const& C,
	Matriz<int> const& camino) {
	int n = C.numfils() - 1;
	for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= n; ++j)
	if (i != j && C[i][j] < INF) {
		std::cout << "Camino de " << i << " a " << j << "\n";
		std::cout << " Coste: " << C[i][j] << "\n";
		std::cout << " " << i;
		imp_camino_int(i, j, camino);
		std::cout << " " << j << "\n";
	}
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int P, R;
	std::cin >> P >> R;
	if (!std::cin)
		return false;
	//creamos un conjunto para saber que personas conocemos ya
	std::unordered_map<std::string, int> mapaPersonas;
	std::string a, b;
	int cont =1;
	//creamos la matriz de relaciones
	Matriz<int> relaciones(P + 1, P + 1, INF);

	//rellenamos la diagonal con 0
	for (int i = 0; i <= P; i++)
		relaciones[i][i] = 0;

	//Leemos relaciones
	for (int i = 0; i < R; i++){
		std::cin >> a >> b;
		//guardamos las personas sino las tenemos registradas
		if (mapaPersonas[a] == 0 ){
			mapaPersonas[a]= cont;
			cont++;
		}
		if (mapaPersonas[b] == 0){
			mapaPersonas[b] = cont;
			cont++;
		}

		//guardamos la relacion en la matriz
		relaciones[mapaPersonas[a]][mapaPersonas[b]] = 1;
		relaciones[mapaPersonas[b]][mapaPersonas[a]] = 1;
	}

	Matriz<int> C(0, 0); Matriz<int> camino(0, 0);
	Floyd(relaciones, C, camino);
	//imprimir_caminos(C, camino);
	int max = 0;

	for (int i = 1; i <= P; i++){
		for (int j = 1; j <= P; j++){
			max = std::max(max, C[i][j]);
		}
	}

	if (max == INF) std::cout << "DESCONECTADA\n";
	else std::cout << max << "\n";
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