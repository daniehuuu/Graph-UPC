#pragma once 
#include <vector>
#include <fstream>
using namespace std;
template<class T,T vacio=-1>
class CGrafo {
private:
  class CArco {
  public:
    T info;
    int v; //indice del vertice de llegada del Arco
    CArco(int vLlegada) {
      info = vacio;
      v = vLlegada;
    }
  };

  class CVertice {
  public:
    T info;
    vector<CArco*>* ady; //Lista(Vector) de adyacencia
    CVertice() {
      info = vacio;
      ady = new vector<CArco*>();
    }
  };

  //Vector(o "Lista") de vértices
  vector<CVertice*>* vertices;

public:
  CGrafo() {
    vertices = new vector<CVertice*>();
  }

  //Operaciones del Grafo
  int adicionarVertice(T info) {
    CVertice * vert = new CVertice();
    vert->info = info;
    vertices->push_back(vert);
    return vertices->size() - 1; //retorna posicion del vertice agregado (al final)
  }

  int cantidadVertices() {
    return vertices->size();
  }

  T obtenerVertice(int v) { //Obtener Vertice dado su posicion en el vector
    return (vertices->at(v))->info;
  }
  void modificarVertice(int v, T info) {
    (vertices->at(v))->info = info;
  }
  //Operaciones del arco
  int adicionarArco(int v, int vLlegada) { //v: posicion del vertice | vLlegada: vertice de llegada del Arco
    CVertice* ver = vertices->at(v);
    //Crear el objeto ARCO
    CArco* arc = new CArco(vLlegada);
    ver->ady->push_back(arc);
    return ver->ady->size() - 1;
  }

  int cantidadArcos(int v) {
    return (vertices->at(v))->ady->size();
  }

  T obtenerArco(int v, int apos) {
    CVertice* ver = vertices->at(v);
    return (ver->ady->at(apos))->info;
  }

  void modificarArco(int v, int apos, T info) {	//v: posicion del vertice | apos: posicion de la lista de adyacencia
    CVertice* ver = vertices->at(v);
    (ver->ady->at(apos))->info = info;
  }

  int obtenerVerticeLlegada(int v, int apos) {
    CVertice* ver = vertices->at(v);
    return (ver->ady->at(apos))->v; //indice del vertice de llegada
  }

  void dibujarGrafo(const string& nombreArchivo) {
        string digraph = "digraph G {\nrankdir=LR\nbgcolor = \"black\"\nnode[color=white fontcolor=white shape=circle width=.6]\nedge[color=white fontcolor=white]\n";

        for (int i = 0; i < cantidadVertices(); ++i) {
            digraph += to_string(i) + " [label=\"" + static_cast<char>(obtenerVertice(i)) + "\"];\n";

            for (int j = 0; j < cantidadArcos(i); ++j) {
                int vLlegada = obtenerVerticeLlegada(i, j);
                T peso = obtenerArco(i, j);
                digraph += to_string(i) + " -> " + to_string(vLlegada) + " [label=\"" + to_string(peso) + "\"];\n";
            }
        }

        digraph += "}\n";

        ofstream archivo(nombreArchivo + ".dot");
        if (!archivo.is_open()) {
            cerr << "Error al abrir el archivo para escribir el grafo." << endl;
            return;
        }
        archivo << digraph;
        archivo.close();

        string comando = "dot -Tpng " + nombreArchivo + ".dot -o " + nombreArchivo + ".png";
        system(comando.c_str());
        comando = "start " + nombreArchivo + ".png";
        system(comando.c_str());
    }
};


