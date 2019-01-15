// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

/*
El problema nos pregunta cuantas ciudades como maximo podemos proteger. Para ello agrupmos por un lado
los enemigos y por otro nuestros soldados, ordenandolos ambos de manera creciente. De tal forma
que vamos observando, si nuestro soldado puede con los enemigos, los asignamos y por tanto podemos proteger
una ciudad más, en otro caso ese "ejército" se ignora y pasamos al siguiente "ejército" ya que tendrá mayor
numero de efectivos y puede que sea capaz de hacerse cargo del grupo de enemigos.

Coste de la solución--> O(2NlogN + N)-> Ya que aplicamos 2 veces algortimo sort y luego se recorre el vector*/


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, elem;
	std::cin >> N;
	if (!std::cin)
		return false;
	
	std::vector<int> enemigos;
	std::vector<int> soldados;

	//leemos enemigos
	for (int i = 0; i < N; i++){
		std::cin >> elem;
		enemigos.push_back(elem);
	}
	//leemos soldados
	for (int i = 0; i < N; i++){
		std::cin >> elem;
		soldados.push_back(elem);
	}
	//ordenamos ambos vectores
	std::sort(enemigos.begin(), enemigos.end());
	std::sort(soldados.begin(), soldados.end());

	int i = 0;
	int j = 0;
	int ciudades = 0;
	while (i < N && j < N){
		if (enemigos[i] <= soldados[j]){
			i++;
			j++;
			ciudades++;
		}
		else
			j++;
	}

	std::cout << ciudades << "\n";


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