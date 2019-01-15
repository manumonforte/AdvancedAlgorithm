// Manuel Monforte
// TAIS62

/*El problmea nos pregunta que a cuantas peliculas puede acceder como maximo Deborah, para ello
ordenamos las peliculas dependiendo de su hora final de manera creciente. De manera que para cada pelicula
comprobamos si ocupa parte de la siguiente, si no es asi aumentamos las peliculas que puede ver

La solucion tiene coste o(NlogN) donde N es el numero de peliculas, ya que se realizan operaciones
push/top sobre la cola de prioridad que tiene logN, y se realizan N veces.*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <functional>
struct tHora {
	int hora;
	int min;

	tHora() {};
	tHora(int a, int b) : hora(a), min(b) {};
};

tHora operator+(tHora const &a, int const &minutos) {
	tHora horaFin = a;
	horaFin.min += minutos;
	while (horaFin.min >= 60) {
		horaFin.min -= 60;
		++horaFin.hora;
	}
	return horaFin;
}

bool operator==(tHora const &a, tHora const &b) {
	return a.hora == b.hora && a.min == b.min;
}

bool operator<(tHora const &a, tHora const &b) {
	return (a.hora < b.hora) || (a.hora == b.hora && a.min < b.min);
}

bool operator>(tHora const &a, tHora const &b) {
	return (a.hora > b.hora) || (a.hora == b.hora && a.min > b.min);
}

struct tPelicula {
	tHora horaIni;
	tHora horaFin;

	tPelicula() {};
	tPelicula(tHora ini, tHora fin) : horaIni(ini), horaFin(fin) {};
};

bool operator < (const tPelicula & a, const tPelicula & b) {
	return a.horaFin > b.horaFin || (a.horaFin == b.horaFin && a.horaIni > b.horaIni);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, hora, min, duracion;
	std::cin >> N;
	if (!N)
		return false;
	std::priority_queue<tPelicula, std::vector<tPelicula>, std::less<tPelicula>> cine;

	char aux;

	for (int i = 0; i < N; i++) {
		std::cin >> hora >> aux >> min >> duracion;
		tHora ini = { hora, min };
		tHora fin = ini + duracion;
		cine.push({ ini ,fin });
	}

	int numPelis = 1;
	tPelicula elem = cine.top();
	cine.pop();
	while (!cine.empty()) {
		if (elem.horaFin + 9 < cine.top().horaIni && cine.top().horaIni > elem.horaIni) {
			elem = cine.top();
			numPelis++;
		}
		cine.pop();
	}

	std::cout << numPelis << "\n";

	return true;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("dats.txt");
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
