// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"
#include <algorithm>


// función que resuelve el problema
void resolver(int datos) { 
	//coste de la funcion O(nlogn), lineal en el numero de valores a introducir
	//ya que se pueden llegar a realizar n veces la llamada hundir o flotar 
	//al realizar pop o push

	PriorityQueue<int, std::greater<int>> colaIzq; // almacenamos 0 ... xn
	PriorityQueue<int> colaDerec;//almacenamos xn+1 ....xk
	//colocamos los dos primeros valores fuera
	int elem;
	int elem2;
	std::cin >> elem;
	std::cout << 2 * elem << " ";
	if (datos > 1){
		std::cin >> elem2;
		colaDerec.push(std::max(elem, elem2));
		colaIzq.push(std::min(elem, elem2));

		std::cout << elem +elem2 << " ";
		//para cada valor nuevo
		for (int i = 0; i < datos - 2; i++){
			std::cin >> elem;
			// si el elem es mayor que xn , lo colocamos en la cola derecha
			if (!colaIzq.empty() && elem > colaIzq.top()){
				// metemos el top de la cola derecha en la min 
				colaDerec.push(elem);
			}
			// si el elem es menor que xn+1, lo colocamos en la cola izq
			else if (!colaDerec.empty() && elem < colaDerec.top()){
				colaIzq.push(elem);
			}
			// para mantener colas equilibradas y tener en ambos top xn, xn+1
			if (colaDerec.size() > colaIzq.size()){
				colaIzq.push(colaDerec.top());
				colaDerec.pop();
			}
			//sumamos +1 para asegurarnos que siempre esta a la izq.top() xn
			else if (colaDerec.size()+1 < colaIzq.size()){
				colaDerec.push(colaIzq.top());
				colaIzq.pop();
			}

			//pintamos dependiendo de paridad
			if (i % 2 != 0){
				std::cout << colaIzq.top() + colaDerec.top();
			}
			else std::cout << 2 * colaIzq.top();
			std::cout << " ";
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int datos;
	std::cin >> datos;
	if (!datos)
		return false;

	resolver(datos);

	// escribir sol
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