//
//  Grafo.h
//
//  Implementación de grafos no dirigidos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2015-2018  Alberto Verdejo
//

#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <stdexcept>
using Adys = std::vector<int>;  // lista de adyacentes a un vértice


class Grafo {

	int _V;   // número de vértices
	int _E;   // número de aristas
	std::vector<Adys> _ady;   // vector de listas de adyacentes

public:

	/**
	* Crea un grafo con V vértices.
	*/
	Grafo(int v) : _V(v), _E(0), _ady(_V) {}

	/**
	* Devuelve el número de vértices del grafo.
	*/
	int V() const { return _V; }

	/**
	* Devuelve el número de aristas del grafo.
	*/
	int E() const { return _E; }


	/**
	* Añade la arista v-w al grafo.
	* @throws invalid_argument si algún vértice no existe
	*/
	void ponArista(int v, int w) {
		if (v >= _V || w >= _V)
			throw std::invalid_argument("Vertice inexistente");
		++_E;
		_ady[v].push_back(w);
		_ady[w].push_back(v);
	}


	/**
	* Devuelve la lista de adyacencia de v.
	* @throws invalid_argument si v no existe
	*/
	Adys const& ady(int v) const {
		if (v >= _V)
			throw std::invalid_argument("Vertice inexistente");
		return _ady[v];
	}


	/**
	* Muestra el grafo en el stream de salida o (para depurar)
	*/
	void print(std::ostream & o = std::cout) const {
		o << _V << " vértices, " << _E << " aristas\n";
		for (auto v = 0; v < _V; ++v) {
			o << v << ": ";
			for (auto w : _ady[v]) {
				o << w << " ";
			}
			o << "\n";
		}
	}

};

class GrafoBipartito {//coste de la solucion --> O(V+E) 
private:
	bool bipartito;
	std::vector<bool> marked;
	std::vector<bool> red;//vertices de color rojo
	std::vector<bool> blue;//vertices de color azul
public:
	GrafoBipartito(const Grafo &gf) : marked(gf.V(), false), red(gf.V(), false), blue(gf.V(), false), bipartito(true) {
		bool color = false; // false --> rojo, true --> azul
		for (int v = 0; v < gf.V(); v++) {
			if (!marked[v]) {// si no esta marcado
				grafoBipartido(v,gf,color);
			}
		}
	}

	void grafoBipartido(int v, const Grafo &gf,bool color) {
		marked[v] = true;
		// pintamos el vertice
		if (color) blue[v] = true;
		else red[v] = true;
		//cambiamos color
		if (color) color = false;
		else color = true;
		//recorremos sus adyacentes
		for (int w : gf.ady(v)) {
			if (!marked[w]) {
				grafoBipartido(w,gf,color);
			}
			// si ya estaba marcado
			else{
				// si el color es rojo y esta pintado de rojo
				//o el color es azul y esta pintado de azul
				if (color && red[w] || !color && blue[w]) bipartito = false;
			}
		}
	}
	bool esBipartido() { return bipartito; }


};
/**
* Para mostrar grafos por la salida estándar
*/
inline std::ostream & operator<<(std::ostream & o, Grafo const& g) {
	g.print(o);
	return o;
}


#endif /* GRAFO_H_ */
