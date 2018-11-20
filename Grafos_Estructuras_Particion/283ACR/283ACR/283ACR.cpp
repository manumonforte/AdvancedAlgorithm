#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "Grafo.h"
#include <algorithm>
using Mapa = std::vector<std::string>;

const std::vector<std::pair<int, int>> dirs = {{ 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 }};

class Olivares{
public:
	Olivares(Mapa const & M) :marked(M.size(), std::vector<bool>(M[0].size(), false)), max(0),
		F(M.size()), C(M[0].size()){
		for (int i = 0; i < F; i++){
			for (int j = 0; j < C; j++){
				if (!marked[i][j] && M[i][j]=='#'){
					int tam = 0;
					dfs(M, i, j, tam);
					max = std::max(max, tam);
				}
			}
		}
	}

	int getMax(){ return max;}

private:
	std::vector<std::vector<bool>>marked;
	int max;
	int F, C;
	bool esCorrecta(int i, int j){ return 0 <= i  && i < F && 0 <= j  && j < C; }

	void dfs(Mapa const & M, int i, int j, int &tam){
		marked[i][j] = true;
		tam++;
		for (auto dir : dirs){
			int ni = i + dir.first;
			int nj = j + dir.second;
			if (esCorrecta(ni, nj) && !marked[ni][nj] && M[ni][nj]== '#'){
				dfs(M,ni, nj, tam);
			}
		}
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int F, C;
	std::cin >> F >> C;
    if (! std::cin)
        return false;
	std::string line;
	Mapa mapa;
	std::cin.get();
	for (int i = 0; i < F; i++){
		std::getline(std::cin, line);
		mapa.push_back(line);
	}
    
	Olivares sol(mapa);
	std::cout << sol.getMax() << "\n";
    
    
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