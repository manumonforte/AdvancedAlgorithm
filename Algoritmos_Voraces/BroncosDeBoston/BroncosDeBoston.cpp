// Manuel Monforte
// TAIS62


//Explicacion del problema y coste
/*Se pide como podemos conseguir la suma maxima entre los broncos y sus rivales.Ya que los
partidos estan desorganizados, guardaremos en un vestor los rivales y otro los broncos.Tras esto
ordenaremos los primos de manera creciente y los segundos de manera decreciente, para al comparando
solo sumar aquellos cuyo bi-ri sea positivo, consiguiendo de esta forma la suma máxima.

Coste de la solcuion O(2P +2NlogN)--> O(NlogN)*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>


struct myclass {
	bool operator() (int i, int j) { return (i>j); }
} myoperator;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int P;
	std::cin >> P;
	if (!P)
		return false;
	int aux;
	std::vector<int> rivales;
	std::vector<int> broncos;

	
	for (int i = 0; i < P; i++){
		std::cin >> aux;
		rivales.push_back(aux);
	}

	for (int i = 0; i < P; i++){
		std::cin >> aux;
		broncos.push_back(aux);
	}

	std::sort(broncos.begin(), broncos.end(),myoperator);
	std::sort(rivales.begin(), rivales.end());

	// escribir sol
	bool valido = true;
	int i = 0;
	int sol= 0;
	while (valido && i < P){
		if (broncos[i] <= rivales[i]) valido = false;
		else sol += broncos[i] - rivales[i];
		i++;
	}

	std::cout << sol << "\n";
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