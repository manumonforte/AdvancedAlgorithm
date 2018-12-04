// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>


/*
Explicacion de la solucion: Tenemos un conjunto de varillas con sus longitudes y precios. Tras leer
los apartados se ha decidido aplicar programación dinámica al problema. Para ello planteamos
un vector, en la cual, el número de elementos será, la longitud de la varilla a construir. La funcion recursiva se describe en los propios apartados,
con el coste de la misma.

Coste total --> O(4(L)) --> O(L)
*/
const int INF = 1000000000;

struct tVarilla{
	int precio;
	int longitud;

	tVarilla(){};
	tVarilla(int l, int p) : longitud(l), precio(p){};
};

bool varillaDeseada(const std::vector<tVarilla> & listaVarillas, int L, int N){
	/*
	Coste --> O(L)
	varillas[j]= varillas[j] si longitud de varilla j > j
	varillas[j]= varillas[j] || varillas[j - listaVarillas[i].longitud] si longitud de varilla j < j --> con que una de las dos sea manera nos vale para ver si podemos llegar a L
	varillas[j]= 1 (o true) si longitud de varilla j = j --> ya que podemos utilizar esa varilla
	*/
	std::vector<bool> varillas(L + 1, false);
	varillas[0] = true;
	for (int i = 1; i <= N; i++){
		for (int j = L; j >= 1; j--){
			if (listaVarillas[i - 1].longitud <= j)  varillas[j] = varillas[j] || varillas[j - listaVarillas[i - 1].longitud];
		}
	}
	return varillas[L];
}

int calculaManeras(const std::vector<tVarilla> & listaVarillas, int L, int N){
	/*
	Coste --> O(L)
	varillas[j]= varillas[j] si longitud de varilla j > j
	varillas[j]= varillas[j] + varillas[j - listaVarillas[i].longitud] si longitud de varilla j <= j --> ahora sumamos ya ambas son maeras de llegar a la varilla L
	*/
	std::vector<int> varillas(L + 1, 0);
	varillas[0] = 1;
	for (int i = 1; i <= N; i++){
		for (int j = L; j >= 1; j--){
			if (listaVarillas[i - 1].longitud <= j)  varillas[j] = varillas[j] + varillas[j - listaVarillas[i - 1].longitud];
		}
	}
	return varillas[L];
;}

int minVarillaDeseada(const std::vector<tVarilla> & listaVarillas, int L, int N){
	/*
	Coste --> O(L)
	varillas[j]= varillas[j] si longitud de varilla j > j
	varillas[j]= std::min(varillas[j] , varillas[j - listaVarillas[i].longitud]+1) nos quedamos con la menor de las dos maneras
	*/
	std::vector<int> varillas(L + 1, INF);
	varillas[0] = 0;
	for (int i = 1; i <= N; i++){
		for (int j = L; j >= 1; j--){
			if (listaVarillas[i - 1].longitud <= j) varillas[j] = std::min(varillas[j], varillas[j - listaVarillas[i - 1].longitud] + 1);
		}
	}

	return varillas[L];
}

int minCosteVarilla(const std::vector<tVarilla> & listaVarillas, int L, int N){
	
	/*
	Coste --> O(L)
	varillas[j]= varillas[j] si longitud de varilla j > j
	varillas[j]= std::min(varillas[j] , varillas[j - listaVarillas[i].longitud]+ listaVarillas[i].longitud] + listaVarillas[i].precio)  si longitud de varilla j >= j
					nos quedamos con la menor de las dos maneras, pero ahora teniendo en cuenta el precio 
	*/
	std::vector<int>varillas(L + 1, INF);
	varillas[0] = 0;
	for (int i = 1; i <= N; i++){
		for (int j = L; j >= 1; j--){
			if (listaVarillas[i - 1].longitud <= j)  varillas[j] = std::min(varillas[j], varillas[j - listaVarillas[i - 1].longitud] + listaVarillas[i - 1].precio);
		}
	}

	return varillas[L];
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, L, p, l;
	std::cin >> N >> L;
	if (!std::cin)
	return false;
	std::vector<tVarilla> varillas;

	for (int i = 0; i < N; i++){
		std::cin >> l >> p;
		varillas.push_back({ l, p });
	}
	//std::sort(varillas.begin() + 1, varillas.end());
	bool esPosible = varillaDeseada(varillas, L, N);
	if (esPosible){
		int maneras = calculaManeras(varillas, L, N);
		int minDeseada = minVarillaDeseada(varillas, L, N);
		int minCoste = minCosteVarilla(varillas, L, N);
		std::cout << "SI " << maneras << " " << minDeseada << " " << minCoste << "\n";
	}
	else std::cout << "NO\n";
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