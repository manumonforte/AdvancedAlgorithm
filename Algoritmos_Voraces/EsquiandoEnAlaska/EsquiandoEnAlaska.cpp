// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>


//Explicacion y coste de la solucion
/*El problema nos pide como distribuir atletas y esquis para que la diferencia de la suma
entre ambos sea minima. Para ello gaudamos en un vector ambos conjuntos y los ordenamos por
de forma creciente. Asi luego cuando cojamos el primer elemento de cada uno seran los minimos por tanto
al ir haciendo el valor absoluto de su diferencia, iremos garantizando la suma minima en todo momento.

Coste de la solucion --> O(2*N + 2* NlogN +N)--> O(NlogN) siendo N el numero de esquiadores o esquis
*/

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	std::cin >> N;
	if (!N)
		return false;
	std::vector<int>esquiadores;
	std::vector<int>esquis;
	int valor;
	
	//leemos esquiadores
	for (int i = 0; i < N; i++){
		std::cin >> valor;
		esquiadores.push_back(valor);
	}
	//leemos esquis
	for (int i = 0; i < N; i++){
		std::cin >> valor;
		esquis.push_back(valor);
	}
	//ordenamos de menor a mayor
	std::sort(esquiadores.begin(), esquiadores.end());
	std::sort(esquis.begin(), esquis.end());

	int sumaMinima = 0;
	for (int i = 0; i < N; i++){
		sumaMinima += std::abs(esquiadores[i] - esquis[i]);
	}

	// escribir sol
	std::cout << sumaMinima << "\n";
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