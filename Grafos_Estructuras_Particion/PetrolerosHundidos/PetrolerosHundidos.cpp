// Manuel Monforte
//TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "ConjuntosDisjuntos.h"

//Coste de la solucion --> O(N+M lg*N) Aprovechamos recorrido en profundidad para buscar componentes conexa e
//introducimos atributo para llevar el tamaño de la mayor. Luego sobre el tablero/mapa, asignamos la nueva
//mancha y para cada una de las direcciones posibles, observamos si hay una mancha para unir ambos conjuntos en el nuevo
//direcciones posibles
const std::vector<std::pair<int, int>> dirs = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, { -1, -1 }, { -1, 1 },
{ 1, -1 }, { 1, 1 } };
using Mapa = std::vector<std::string>; // grafo implícito en el mapa

class Petrolero {
public:
	Petrolero(Mapa const& M) : F(M.size()), C(M[0].size()),
		marked(F, std::vector<bool>(C, false)), _maximo(0), grafo(F*C){
		for (int i = 0; i < F; ++i) {
			for (int j = 0; j < C; ++j) {
				if (M[i][j] == '#' && !marked[i][j]) {
					// se recorre una nueva mancha
					int nuevotam = 0;
					dfs(M, i, j, nuevotam);
					_maximo = std::max(_maximo, nuevotam);
				}
			}
		}
	}

	int maximo() const { return _maximo; }

	void actualizar(Mapa const& M,int i, int j){
		bool wasEmpty = true;
		//calculamos vertice
		int v = i*C + j;			
		//unir las direcciones
		for (auto d : dirs) {
			int ni = i + d.first, nj = j + d.second;
			int w = ni *C + nj;
			if (correcta(ni, nj) && M[ni][nj] == '#'){
				grafo.unir(v, w);
				/*int x = grafo.tam(v);
				int y = grafo.tam(w);*/
				_maximo = std::max(grafo.tam(v), _maximo);
				wasEmpty = false;
			}
		}
		//si la matriz era blanca antes de pintar
		if (wasEmpty) _maximo =std::max(grafo.tam(v), _maximo);
	}
private:
	int F, C; // tamaño del mapa
	std::vector<std::vector<bool>> marked; // marked[i][j] = se ha visitado <i,j>?
	int _maximo; // tamaño de la mancha más grande
	ConjuntosDisjuntos grafo;


	//metodo que comprueba si la direccion es correcta
	bool correcta(int i, int j) const {
		return 0 <= i && i<F && 0 <= j && j < C;
	}
	
	
	// recorrido en profundidad de la mancha del vértice <i,j>
	void dfs(Mapa const& M, int i, int j, int & tam) {
		marked[i][j] = true;
		tam++;
		//calculamos vertice
		for (auto d : dirs) {
			int v = i*C + j;
			int ni = i + d.first, nj = j + d.second;
			if (correcta(ni, nj) && M[ni][nj] == '#' && !marked[ni][nj]) {
				int w = ni *C + nj;
				grafo.unir(v, w);
				dfs(M, ni, nj, tam);
			}
		}
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int F, C, fotos,x,y;
	std::cin >> F >> C;
	if (!std::cin)
		return false;
	Mapa mapa(F);
	// leemos la imagen
	std::cin.get();
	for (int i = 0; i < F;i++) {
		getline(std::cin, mapa[i]);
	}
	// y la analizamos

	Petrolero sol(mapa);
	std::cout << sol.maximo();
	std::cin >> fotos;
	//para cada foto marcamos la casilla del mapa que se contamina y repetimos dfs
	//buscando max compponente conexa
	for (int i = 0; i < fotos; i++){
		std::cin >> x >> y;
		mapa[x-1][y-1] = '#';
		sol.actualizar(mapa,x - 1, y - 1);
		std::cout << " " << sol.maximo();
	}
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