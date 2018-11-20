// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"


struct tInfo{
	int id = -1;
	int periodo = -1;
	int momento = 0;
};

bool operator < (tInfo const & a, tInfo const & b){
	return a.momento < b.momento ||
		(a.momento == b.momento && a.id < b.id);
}



// función que resuelve el problema
void resolver(PriorityQueue<tInfo> & colap,int k) {
	
	int envios = 0;
	while (envios < k){
		tInfo aux = colap.top();
		colap.pop();
		std::cout << aux.id << "\n";
		aux.momento += aux.periodo;
		colap.push(aux);
		envios++;
	}
	std::cout << "----\n";
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int usuarios, idAux, perAux;
	std::cin >> usuarios;
	if (!usuarios)
		return false;
	PriorityQueue<tInfo> colap;
	for (int i = 0; i < usuarios; i++){
		std::cin >> idAux;
		std::cin >> perAux;
		tInfo aux;
		aux.id = idAux;
		aux.momento = perAux;
		aux.periodo = perAux;
		colap.push(aux);
	}
	int k = -1;
	std::cin >> k;
	resolver(colap,k);

	// escribir sol

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