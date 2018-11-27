// Manuel Monforte



#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

int valores[8] = { 200, 100, 50, 20, 10, 5, 2, 1 };

struct tMoneda{
	int valor;
	int numMonedas;

	tMoneda(){};
	tMoneda(int v) : valor(v), numMonedas(0){};
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	int coste, entregado;
	std::cin >> coste >> entregado;
	int cambio = entregado - coste;
	if (cambio < 0) std::cout << "DEBE " << std::abs(cambio);
	else{
		std::vector<tMoneda>listaMonedas;
		for (int i = 0; i < 8; i++){
			listaMonedas.push_back({ valores[i] });
		}
		int i =0;
		while (cambio >0 && i < listaMonedas.size()){
			if (cambio >= listaMonedas[i].valor){
				listaMonedas[i].numMonedas += cambio / listaMonedas[i].valor;
				cambio = cambio % listaMonedas[i].valor;
			}
			i++;
		}

		for (int i = 0; i < listaMonedas.size(); i++){
			if (i == 0)
				std::cout << listaMonedas[i].numMonedas;
			else
				std::cout  << " " << listaMonedas[i].numMonedas;
		}

	}
	std::cout << "\n";
}

int main() {

	/*
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif */


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	/*
	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	*/
	return 0;
}