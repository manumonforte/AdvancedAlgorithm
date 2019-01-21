// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
#include <algorithm>


const int INF = 1000000000;
/*
diana(i,j) = minimo numero de lanzamienrtos para conseguir la puntuacion j con
sectores del 0 al i

diana(i,j) = min(diana(i,j-sector[i])+1,diana(i+1,j))

diana(i,j-sector[i])+1 ==>Tirar al sector i
diana(i+1,j) ==> No tirar arl sector i

diana(i,0) = 0
*/

bool myorden(int a, int b){ return a > b; }
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int P, S;
	std::cin >> P >> S;
	if (!std::cin)
		return false;
	std::vector<int>sectores(S + 1);

	for (int i = 1; i <= S; i++){
		std::cin >> sectores[i];
	}

	int N = sectores.size() - 1;

	Matriz<int> diana(N + 2, P + 1, INF);


	//caso base
	for (int i = 1; i <= N; i++){
		diana[i][0] = 0;
	}
	for (int i = N; i >= 1; i--){
		for (int j = 1; j <= P; j++){
			if (sectores[i] <= j)
				diana[i][j] = std::min(diana[i][j - sectores[i]] + 1, diana[i + 1][j]);
		}
	}
	if (diana[1][P] == INF) std::cout << "Imposble";
	else{
		std::vector<int>tiradas;
		std::cout << diana[1][P] << ":";
		int resto = P;
		/*for (int i = N; i >= 1; --i) {
		if(diana[i][resto] != diana[i - 1][resto] && resto > 0) {
		// hemos tirado tiramos
		int aux = resto / sectores[i];
		for (int j = 0; j < aux; j++)
		tiradas.push_back(sectores[i]);
		resto = resto % sectores[i];
		}
		}
		*/
		std::sort(tiradas.begin(), tiradas.end(), myorden);
		for (auto value : tiradas){
			std::cout << " " << value;
		}
	}
	std::cout << "\n";
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