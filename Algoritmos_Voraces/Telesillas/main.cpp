// Manuel Monforte
// TAIS62


/*
El problema pregunta el numero de viajes minimos a realizar. Para ello ordenamos
los usuarios por peso de manera creciente y jugamos con dos indices, uno al primer
usuario y otro al ultimo, si el primero y el ultimo forman parejas avanzan los dos,
sino solo se asigna viaje al que tiene mas peso.

coste de la solucion --> O(NlogN) se aplica sort
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int P, U, p ;
	std::cin >> P >>  U;
	if (!std::cin)
		return false;
	int viajes = 0;
	std::vector<int>usuarios;
	for (int i = 0; i < U; i++){
		std::cin >> p;
		usuarios.push_back(p);
	}
	std::sort(usuarios.begin(), usuarios.end());
	int i = 0;
	int j = usuarios.size() - 1;

	while (i <= j){
		// si el usuario pesa mas de lo permitido no puede realizar viaje
		if (usuarios[j] > P){
			j--;
		}
		// si el usuario j pesa menos que el permitido 
		else{
			// si la suma es menor que el peso asignamos viajes y movemos indices
			if (usuarios[i] + usuarios[j] <= P){
				i++;
				j--;
			}
			// si la suma de ambos es mayor asignamos viaje al de mayor peso
			else{
				j--;
			}
			viajes++;
		}
	}
	std::cout << viajes << "\n";


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