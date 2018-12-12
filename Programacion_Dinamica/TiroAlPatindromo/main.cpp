//Manuel Monforte 
//TAIS62


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Matriz.h"
#include <vector>

using namespace std;


string patindromo(string letras) {
	
	int N = letras.size() - 1;

	//creamos matriz de N x N
	Matriz<int> tabla(N + 1, N + 1, 0);

	//rellenamos la diagonal con 1 ya que si los indices son iguales el tam del palindromo es 1
	for (int i = 1; i <= N - 1; i++)
		tabla[i][i] = 1;

	for (int d = 1; d <= N - 1; d++)
		for (int i = 1; i <= N - d; i++){
			int j = i + d;
			if (letras[i] == letras[j])
				tabla[i][j] = 2 + tabla[i + 1][j - 1];
			else
				tabla[i][j] = max(tabla[i + 1][j], tabla[i][j - 1]);
		}

	int tam = tabla[1][N];
	
	std::string sol(tam + 1, ' ');

	//creamos indice de palabra original
	int origenIni = 1;
	int origenFin = N;
	//creamos indice palabrta final
	int solIni = 1;
	int solFin = tam;

	while (tam > 0) {
		//si las letras son iguales las colocamos y disminuimos el tam
		if (letras[origenIni] == letras[origenFin]) {
			sol[solIni] = letras[origenIni];
			sol[solFin] = letras[origenFin];
			origenIni++;
			origenFin--;
			solIni++;
			solFin--;
			tam -= 2;
		}
		
		else if (letras[origenIni] != letras[origenFin]) {
			if (tabla[origenIni][origenFin - 1] > tabla[origenIni + 1][origenFin])
				origenFin--;
			else origenIni++;
		}
		else if (tam == 1) {
			sol[solIni] = letras[origenIni];
			tam--;
		}
		
	}

	return sol.substr(1,sol.size()-1);
}

bool resuelveCaso() {

	string palabra;
	cin >> palabra;

	if (!cin) return false;

	string sol = "";
	if (palabra.size() == 1) {
		cout << palabra << endl;
	}
	else {
		palabra = " " + palabra;
		sol = patindromo(palabra);
		cout << sol << endl;
	}

	return true;
}


int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif

	return 0;
}
