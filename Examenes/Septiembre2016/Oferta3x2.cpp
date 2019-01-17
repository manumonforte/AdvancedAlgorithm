// Manuel Monforte 
// TAIS62

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

/*
El problema nos pide como podemos comprar los libres en grupos de tres para obtener el mayor
descuencto. Para ello, se ordenador los libros por precio dereciente y por cada tres libros
seleccionados nos ahorraremos el tercero, siendo el maximo ahorro posible. Al hacer esto nos 
aseguramos que la suma de los maximos ahorros parciales, consecuenctemente da luegar al mejor ahorro 
total.

Coste de la operacion--> Operacion top() y pop() con priorityQueue por lo que dan lugar logN, y se recorrem
todos los libros comprados, por tanto el coste totral es O(NlogN) donde N signifaca el numero de libros comprados

*/

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, valor;
	std::cin >> N;
	if (!std::cin)
		return false;
	std::priority_queue<int>libros;

	for (int i = 0; i < N; i++){
		std::cin >> valor;
		libros.push(valor);
	}
	int contador=1;
	int ahorro = 0;
	while (!libros.empty()){
		if (contador % 3 == 0)
			ahorro += libros.top();
		libros.pop();
		contador++;
	}
	
	std::cout << ahorro << "\n";

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