// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include <algorithm>


/*
Explicacion de la solucion: Tenemos un conjunto de varillas con sus longitudes y precios. Tras leer
los apartados se ha decidido aplicar programación dinámica al problema. Para ello planteamos
una matriz, en la cual, el número de filas será en numero de varillas disponibles(N) y el numero de
columnas será, la longitud de la varilla a construir. La funcion recursiva se describe en los propios apartados,
con el coste de la misma.

Coste total --> O(4(N*L)) --> O(N*L)
*/
const int INF = 1000000000;

struct tVarilla{
	int precio;
	int longitud;

	tVarilla(){};
	tVarilla(int l, int p) : longitud(l), precio(p){};
};

bool varillaDeseada(const std::vector<tVarilla> & listaVarillas, int L, int N){
	/*
	Coste --> O(N*L)
	varillas[i][j]= varillas[i - 1][j] si longitud de varilla j > j
	varillas[i][j]= varillas[i - 1][j] || varillas[i - 1][j - listaVarillas[i-1].longitud] si longitud de varilla j < j --> con que una de las dos sea manera nos vale para ver si podemos llegar a L
	varillas[i][j]= 1 (o true) si longitud de varilla j = j --> ya que podemos utilizar esa varilla
	*/

	
	Matriz<bool> varillas(N + 1, L + 1, false);


	for (int i = 0; i <= N; i++){
		varillas[i][0] = true;
	}

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= L; j++){
			if (listaVarillas[i-1].longitud > j) varillas[i][j] = varillas[i - 1][j];
			else varillas[i][j] = varillas[i - 1][j] || varillas[i - 1][j - listaVarillas[i-1].longitud];
		}
	}
	return varillas[N][L];
	
}

int calculaManeras(const std::vector<tVarilla> & listaVarillas, int L, int N){
	/*
	Coste --> O(N*L)
	varillas[i][j]= varillas[i - 1][j] si longitud de varilla j > j
	varillas[i][j]= varillas[i - 1][j] + varillas[i - 1][j - listaVarillas[i-1].longitud] si longitud de varilla j < j --> ahora sumamos ya ambas son maeras de llegar a la varilla L
	varillas[i][j]= varillas[i - 1][j]+1 si longitud de varilla j = j --> sumamos 1 porque al poderse utilizar esa varilla es otra manera para llegar al final soldandolas
	*/

	Matriz<int> varillas(N + 1, L + 1, 0);

	for (int i = 0; i <= N; i++){
		varillas[i][0] = 1;
	}

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= L; j++){
			if (listaVarillas[i - 1].longitud > j) varillas[i][j] = varillas[i - 1][j];
			else varillas[i][j] = varillas[i - 1][j] + varillas[i - 1][j - listaVarillas[i - 1].longitud];
		}
	}

	return varillas[N][L];
}

int minVarillaDeseada(const std::vector<tVarilla> & listaVarillas, int L, int N){
	/*
	Coste --> O(N*L)
	varillas[i][j]= varillas[i - 1][j] si longitud de varilla j > j
	varillas[i][j]= std::min(varillas[i - 1][j] , varillas[i - 1][j - listaVarillas[i-1].longitud]+1) nos quedamos con la menor de las dos maneras
	varillas[i][j]= varillas[i - 1][j] = 1, nos quedamos con 1 ya que hay una varilla mayor Longitud, por lo que será em mejor punto de partida para llegar a L
	*/

	Matriz<int> varillas(N + 1, L + 1, INF);


	for (int i = 0; i <= N; i++) {
		varillas[i][0] = 0;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= L; j++) {
			if (listaVarillas[i - 1].longitud > j) varillas[i][j] = varillas[i - 1][j];
			else varillas[i][j] = std::min(varillas[i - 1][j], varillas[i - 1][j - listaVarillas[i - 1].longitud] + 1);
		}
	}
	return varillas[N][L];
}

int minCosteVarilla(const std::vector<tVarilla> & listaVarillas, int L, int N){

	/*
	Coste --> O(N*L)
	varillas[i][j]= varillas[i - 1][j] si longitud de varilla j > j
	varillas[i][j]= std::min(varillas[i - 1][j] , varillas[i - 1][j - listaVarillas[i-1].longitud]+ listaVarillas[i].longitud] + listaVarillas[i-1].precio)  si longitud de varilla j >= j
	nos quedamos con la menor de las dos maneras, pero ahora teniendo en cuenta el precio
	*/

	Matriz<int> varillas(N + 1, L + 1, INF);

	for (int i = 0; i <= N; i++) {
		varillas[i][0] = 0;
	}

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= L; j++){
			if (listaVarillas[i-1].longitud > j) varillas[i][j] = varillas[i - 1][j];
			else varillas[i][j] = std::min(varillas[i - 1][j], varillas[i - 1][j - listaVarillas[i-1].longitud] + listaVarillas[i-1].precio);
		}
	}
	return varillas[N][L];
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio´n, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, L, p, l;
	std::cin >> N >> L;
	if (!std::cin)
		return false;
	std::vector<tVarilla> varillas;

	for (int i = 0; i < N; i++){
		std::cin >> l >> p;
		varillas.push_back({ l, p });
	}

	bool esPosible = varillaDeseada(varillas, L, N);
	if (esPosible){
		int maneras = calculaManeras(varillas, L, N);
		int minDeseada = minVarillaDeseada(varillas, L, N);
		int minCoste = minCosteVarilla(varillas, L, N);
		std::cout << "SI " << maneras << " " << minDeseada << " " << minCoste << "\n";
	}
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