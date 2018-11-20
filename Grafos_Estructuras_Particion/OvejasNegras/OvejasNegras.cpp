// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Grafo.h"
#include <string>

const std::vector<std::pair<int, int>> dirs = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, { -1, 1 }, { 1, -1 }, { 1, 1 }, { -1, 1 } };


//coste de la solucion --> O(V+E)
//suponemos que componente conexa de tam 27 == oveja negra
//suponemos que componente conexa de tam 22 == oveja negra
using imagen = std::vector<std::string>;
class OvejasNegras {
public:
	OvejasNegras(imagen const& M) : F(M.size()), C(M[0].size()),
		marked(F, std::vector<bool>(C, false)), _numero(0), ovejasBlancas(0){
		for (int i = 0; i < F; ++i) {
			for (int j = 0; j < C; ++j) {
				if (M[i][j] == 'X' && !marked[i][j]) {
					// se recorre una nueva mancha
					++_numero;
					int nuevotam = 0;
					dfs(M, i, j, nuevotam);
					if (nuevotam == 22)ovejasBlancas++;
				}
			}
		}
	}
	int numero() const { return _numero; }
	int blancas() const { return ovejasBlancas; }

private:
	int F, C; // tamaño del mapa
	std::vector<std::vector<bool>> marked; // marked[i][j] = se ha visitado <i,j>?
	int _numero; // número
	int ovejasBlancas;
	bool correcta(int i, int j) const {
		return 0 <= i && i<F && 0 <= j && j < C;
	}
	// recorrido en profundidad de la mancha del vértice <i,j>
	void dfs(imagen const& M, int i, int j, int & tam) {
		marked[i][j] = true;
		++tam;
		for (auto d : dirs) {
			int ni = i + d.first, nj = j + d.second;
			if (correcta(ni, nj) && M[ni][nj] == 'X' && !marked[ni][nj]) {
				dfs(M, ni, nj, tam);
			}
		}
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int F, C;
	std::cin >> C >> F; // número de filas y columnas
	if (!std::cin)
		return false;

	imagen img(F);
	// leemos la imagen
	for (std::string & linea : img) {
		std::cin >> linea;
	}
	// y la analizamos
	OvejasNegras grafo(img);
	std::cout << grafo.blancas() << "\n";

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