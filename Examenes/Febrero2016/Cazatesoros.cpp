// Manuel Monforte

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
#include <algorithm>

/*
El ejercicio se plante como el problema de la mochila. Por tanto se crea una matriz donde las
filas serán el cofre N, y las columnas el tiempo transcurrido. Al terminar debemos recorrer el resultado
obtenido para saber que cofre hemos cogido exactamente.

Funcion--> cazateoros[i][j] = cazatesoros[i - 1][j] si el tiempo de ese cofre es mayor del que estamos actualmente
cazatesoros[i][j] = std::max(cazatesoros[i - 1][j], cazatesoros[i - 1][j - cofres[i].tiempo] + cofres[i].oro)
sino, podemos coger u nuevo cofre, y obtenemos el maximo entre el anterior y el valor de este sumado

Coste de la solcuion--> O(N*T) siendo n el numero de cofres y T el tiempo de la botella

*/
struct tCofre{
	int oro;
	int tiempo;

	tCofre(){};
	tCofre(int a, int b) : oro(a), tiempo(b){};
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int T, N, oro, p;
	std::cin >> T >> N;
	if (!std::cin)
		return false;
	std::vector<tCofre> listaTesoros;
	std::vector<int> seleccionadosIndex;
	//1 based vector
	listaTesoros.push_back({0,0});

	for (int i = 0; i < N; i++){
		std::cin >> p >> oro;
		listaTesoros.push_back({ oro, 3 *p});
	}
	Matriz<int> cofres(N + 1, T + 1,0);

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= T; j++){
			if (j > listaTesoros[i].tiempo)
				cofres[i][j] = std::max(cofres[i - 1][j], cofres[i - 1][j - listaTesoros[i].tiempo] + listaTesoros[i].oro);
			else cofres[i][j] = cofres[i - 1][j];
		}
	}
	
	int sol = cofres[N][T];
	std::cout << sol << "\n";
	
	int resto = T;
	for (int i = N; i > 0; i--){
		if (cofres[i][resto] != cofres[i - 1][resto]){
			seleccionadosIndex.push_back(i);
			resto -= listaTesoros[i].tiempo;
		}
	}

	std::sort(seleccionadosIndex.begin(), seleccionadosIndex.end());
	std::cout << seleccionadosIndex.size() << "\n";
	for (auto index : seleccionadosIndex){
		std::cout << listaTesoros[index].tiempo/3 << " " << listaTesoros[index].oro << "\n";
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