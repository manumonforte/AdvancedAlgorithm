// Manuel Monforte Escobar
// TAIS62

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"

/*


Coste de la solucion --> O(V+E) ya que se aplica bfs, donde V son las casillas y E,
las casillas adyacentes.

*/
const std::vector<std::pair<int, int>> dirs = { { -1, 0 }, { 1, 0 }, { 0, 1 }, {0, -1} };

class Ovejas{
public:
	Ovejas(const Matriz<char> & imagen) :negras(-1),
		marked(imagen.numfils(),imagen.numcols(),false){
		for (int i = 0; i < imagen.numfils(); i++){
			for (int j = 0; j < imagen.numcols(); j++){
				if (!marked[i][j] && imagen[i][j] == '.'){
					negras++;
					dfs(imagen, i, j);
				}
			}
		}
	}

	int getNegras()const { return negras; }
private:
	Matriz<bool>marked;
	int negras;

	void dfs(const Matriz<char> & imagen, int i, int j){
		marked[i][j] = true;
		for (auto dir : dirs){
			int ni = i + dir.first;
			int nj = j + dir.second;
			if (imagen.posCorrecta(ni, nj) && !marked[ni][nj] && imagen[ni][nj] == '.')
				dfs(imagen, ni, nj);
		}
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int F, C;
	std::cin >> C >> F;
	if (!std::cin)
		return false;
	Matriz<char> imagen(F, C);

	for (int i = 0; i < F; i++){
		for (int j = 0; j < C; j++){
			std::cin >> imagen[i][j];
		}
	}

	Ovejas sol(imagen);
	std::cout << sol.getNegras() << "\n";

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