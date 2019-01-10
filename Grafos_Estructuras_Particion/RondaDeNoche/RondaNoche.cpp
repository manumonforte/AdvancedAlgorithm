// Manuel Monforte
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "Matriz.h"
#include <queue>

/*
****ANOTACION DEL PROBLEMA*****
He tenido que escrbir la solcuion dentro de la clase al acabar BFS, ya que lo que tengo comentado es lo que hacía antes pero al preguntar por si hay 
camino se me sobreescibia los atributos distTO y marked y no se el porque de ello.

Nos piden la forma de llegar a la salida del laberinto. La idea es tratar el problema como un grafo, donde cada casilla es un vertice,
colocaremos sobre el grafo los sensores marcado la casilla con un '*', de esta forma despues aplicaremos el algortimo de busqueda en 
anchura o bfs para clacular la distancia en caso de que sea posible salir del laberinto sin ser pillados.

Coste de algoritmo --> BFS --> v +E donde V es el numero de casillas y E el numero de aristas, una casilla con la contigua forman aristas
					 -->Leer tablero es F *C  = V

*/
//Variables Globales
const int INF = 1000000000;

const std::vector<std::pair<int, int>>  dirs = { {-1,0}, {1,0},{0,-1},{0,1} };
//Estructura
struct tMuro {
	int x;
	int y;
	int valor;

	tMuro() {};
	tMuro(int fila, int columna, int val) :x(fila), y(columna), valor(val) {};
};

//Clase que resuelve el problema
class RondaNoche {
public:
	RondaNoche(const Matriz<char> & mapa, std::pair<int, int> E, std::pair<int, int> P):
	distTo(mapa.numfils(),mapa.numcols(),INF),
	marked(mapa.numfils(),mapa.numcols(),false)
	{
		bfs(mapa, E);

		if (hayCamino(P.first, P.second)) 
			std::cout << distTo[P.first][P.second] << "\n";
		else std::cout << "NO\n";
		
	}

	bool hayCamino(int i, int j) const { return marked[i][j]; }
	bool distancia(int i, int j)const  { return distTo[i][j]; }

private:
	Matriz<int>distTo;
	Matriz<bool> marked;

	void bfs(const Matriz<char> & mapa, std::pair<int, int> E) {
		std::queue<std::pair<int, int>>q;
		distTo[E.first][E.second] = 0;
		marked[E.first][E.second] = true;
		q.push(E);
		while (!q.empty()) {
			std::pair<int, int> v = q.front();
			q.pop();
			// es la pos es correcta, no hay sensor, muro y no lo hemos recorrido 
			for (auto d : dirs) {
				if (mapa.posCorrecta(v.first + d.first,v.second + d.second)
					&&mapa[v.first + d.first][v.second + d.second] != '#'
					&& mapa[v.first + d.first][v.second + d.second] != '*'
					&& !marked[v.first + d.first][v.second + d.second]) {
					distTo[v.first + d.first][v.second + d.second] = distTo[v.first][v.second] + 1;
					marked[v.first + d.first][v.second + d.second] = true;
					q.push({ v.first + d.first ,v.second + d.second });
				}
			}
		}	
	}
};

//Funciones auxiliares
void colocaSensor(const tMuro & sensor, Matriz<char> & mapa) {
	int x = sensor.x;
	int y = sensor.y;
	int valor = sensor.valor;

	//colocamos arriba
	int i = 0;
	while (i < valor && mapa.posCorrecta(x - 1, y) && mapa[x-1][y] != '#') {
		mapa[x - 1][y] = '*';
		x--;
		i++;
	}
	//colocamos abajo
	x = sensor.x;
	i = 0;
	while (i < valor && mapa.posCorrecta(x + 1, y) && mapa[x+1][y] != '#') {
		mapa[x +1][y] = '*';
		x++;
		i++;
	}
	//colocamos izq
	x = sensor.x;
	int j = 0;
	while (j < valor && mapa.posCorrecta(x, y-1) && mapa[x][y-1] != '#') {
		mapa[x][y-1] = '*';
		y--;
		j++;
	}
	//colocamos derec
	y = sensor.y;
	j = 0;
	while (j < valor && mapa.posCorrecta(x, y + 1) && mapa[x][y + 1] != '#') {
		mapa[x][y + 1] = '*';
		y++;
		j++;
	}
}

void colocaSensores(const std::vector<tMuro> & sensores, Matriz<char> & mapa) {
	for (auto elem : sensores) {
		colocaSensor(elem, mapa);
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio´n, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	int F, C;
	std::cin >> C >> F;

	Matriz<char> mapa(F,C);
	std::vector<tMuro> sensores;

	std::pair<int, int>ini;
	std::pair<int, int>fin;

	for (int i = 0; i < F; i++) {
		for (int j = 0; j < C; j++) {
			std::cin >> mapa[i][j];
			//comprobamos si es un numero
			if (int(mapa[i][j]) >= 48 && int(mapa[i][j]) <= 57) {
				sensores.push_back({ i,j,int(mapa[i][j])-48 });
				mapa[i][j] = '*';
			}
			if (mapa[i][j] == 'E') ini = { i,j };
			if (mapa[i][j] == 'P') fin = { i,j };
		}
	}
	//una vez leido el mapa procedemos a colocar los sensores
	colocaSensores(sensores, mapa);

	//si hay sensor en salida o entrada no se puede, en otro caso estudiamos
	if (mapa[ini.first][ini.second] == '*') std::cout <<  "NO\n";
	else if (mapa[fin.first][fin.second] == '*') std::cout << "NO\n";
	else RondaNoche sol(mapa, ini,fin);
	
	/*if (sol.hayCamino(fin.first, fin.second)) {
		std::cout << sol.distancia(fin.first, fin.second) << "\n";
	}
	else std::cout << "NO\n";
	*/
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}