﻿// Manuel Monforte 
// TAIS62


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

struct tTarea {
	int ini = -1;
	int fin = -1;
	bool unica = true;
	int rep = -1;
	tTarea() : ini(-1), fin(-1), unica(false), rep(-1) {};
	tTarea(int a, int b, bool c, int r) :ini(a), fin(b), unica(c), rep(r) {};
};

bool operator < (const tTarea &a, const tTarea &b) {
	if (a.ini < b.ini) return true;
	else if (a.ini == b.ini  && a.fin < b.fin) return true;
	else return false;
}

// función que resuelve el problema
bool resolver(int unicas, int periodicas, int tiempo) {
	PriorityQueue<tTarea> calendario;
	int ini, fin, rep;
	bool valido = true;
	//introducimos tareas unicas
	for (int i = 0; i < unicas; i++) {
		std::cin >> ini >> fin;
		calendario.push({ ini, fin, true, -1 });
	}
	//Introducimos tareas periodicas
	for (int i = 0; i < periodicas; i++) {
		std::cin >> ini >> fin >> rep;
		calendario.push({ ini, fin, false, rep });
	}
	int iniSig = -1;
	// si hay mas de una tarea
	if (calendario.size() > 1) {
		tTarea aux = calendario.top();
		calendario.pop();
		iniSig = calendario.top().ini;
		calendario.push(aux);
	}
	// estudiamos intervalo
	while (calendario.size() > 1 && iniSig < tiempo && valido) {
		tTarea aux = calendario.top();
		calendario.pop();
		if (calendario.top().ini < aux.fin) valido = false;
		// si es periodica la introducimos
		if (!aux.unica) calendario.push({ aux.ini + aux.rep, aux.fin + aux.rep, false, aux.rep });
		//cogemos la segunda tardea de nuevo en el caso de que exista
		if (calendario.size() > 1) {
			tTarea aux2 = calendario.top();
			calendario.pop();
			iniSig = calendario.top().ini;
			calendario.push(aux2);
		}
	}
	return valido;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int unicas, periodicas, tiempo;
	std::cin >> unicas;
	if (!std::cin)
		return false;
	std::cin >> periodicas;
	std::cin >> tiempo;

	if (resolver(unicas, periodicas, tiempo)) std::cout << "NO\n";
	else std::cout << "SI\n";

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