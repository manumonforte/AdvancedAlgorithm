// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
#include <algorithm>

/*
Se tratara el problema como un grafo donde los vertices son las casillas y las aristas seran
la conexion de un vertice con susadyacentes verticales u horizontales. Se aplicar dfs para calcular el
numero de manchas y el tamano de la mayor.

Coste de la solucion--> O(V+E) donde v son los vertices y E las aristas.

*/
const std::vector<std::pair<int, int>>direcciones = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

class ManchasNegras{
public:
	ManchasNegras(const Matriz<char> & mapa) :num(0),marked(mapa.numfils(),mapa.numcols(),false){
		int tam;
		for (int i = 0; i < mapa.numfils(); i++){
			for (int j = 0; j < mapa.numcols(); j++){
				if (!marked[i][j] && mapa[i][j] == '#'){
					tam = 0;
					num++;
					dfs(mapa, i, j, tam);
					max = std::max(tam,max);
				}
			}
		}
	}

	int getManchas()const { return num; }
	int getMayorMancha()const { return max; }
private:
	Matriz<bool> marked;
	int max;
	int num;
	void dfs(const Matriz<char> & mapa, int i, int j, int & tam){
		tam++;
		marked[i][j] = true;
		for (auto dir : direcciones){
			int ni = i + dir.first;
			int nj = j + dir.second;
			if (mapa.posCorrecta(ni, nj) && !marked[ni][nj] && mapa[ni][nj] == '#')
				dfs(mapa, ni, nj, tam);
		}
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int F, C;
	std::cin >> F >> C;
	if (!std::cin)
		return false;
	Matriz<char>mapa(F, C);
	for (int i = 0; i < F; i++){
		for (int j = 0; j < C; j++){
			std::cin >> mapa[i][j];
		}
	}

	ManchasNegras sol(mapa);
	std::cout <<sol.getManchas() << " " << sol.getMayorMancha() << "\n";
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