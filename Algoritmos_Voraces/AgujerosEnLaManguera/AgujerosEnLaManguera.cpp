// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>

//Explicacion de la solucion y coste 
/*El ejercicio habla de tapar los agujeros en la mangera para comprar el menor número de parches
posibles, para ello, como siempre hay un agujero, asignamos el primer parche al primer agujero,
a partir de ahi vamos tratando cada uno de los agujeros. Si el parche no es suficientemente largo, se utilizará
otro y se reajustará el valor de un variable que nos irá marcando el inicio del ultimo parche colocado.

Coste de la solucion --> O(N) siendo N el numero de agujeros de la manguera*/



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, L;
	std::cin >> N >> L;
	if (!std::cin)
		return false;
	int parches = 1;
	int ini;
	int actual;
	//asignamos el primer parche al primer agujero
	std::cin >> actual;
	ini = actual;
	//vamos reasignando el valor de ini
	for (int i= 0; i < N-1; i++){
		std::cin >> actual;
		if (ini + L < actual){
			parches++;
			ini = actual;
		}
	}


	std::cout << parches << "\n";

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