#include <iostream>
#include "Grafo.hpp"
#include "matriz.hpp"
using namespace std;

void imprGrafo(CGrafo<int>* G){
  for (int i = 0; i < G->cantidadVertices(); ++i) {
    cout << "Vertice[" << i << "]: " << static_cast<char>(G->obtenerVertice(i)) << endl;

    for (int j = 0; j < G->cantidadArcos(i); j++){
      int aux = G->obtenerVerticeLlegada(i, j);
      cout << "Arco[" << j << "] -(" << G->obtenerArco(i, j) << ")-> "<< static_cast<char>(G->obtenerVertice(aux)) << ", ";
    }

    cout << endl<<endl;
  }
}
int main() {
  //Crear el grafo
  CGrafo<int>* G = new CGrafo<int>();


  int n;
  std::cout << "Introduce el número de letras (entre 4 y 12): ";
  std::cin >> n;
  if (n < 4 || n > 12) {
      std::cout << "El número debe estar entre 4 y 12." << std::endl;
      return 1;
  }

  //Generar la matriz
  std::vector<std::vector<int>> matriz = generarMatriz(n);
  std::vector<char> letras = seleccionarLetras(n);
  imprimirMatriz(matriz, letras);

  //Crear el grafo a partir de la matriz de adyacencia
   for (int i = 1; i <= n; ++i) 
      G->adicionarVertice(matriz[0][i]);

  for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
          if (matriz[i][j] != 0) { // No agregar arcos con valor 0
              int v = i - 1;
              int vLlegada = j - 1;
              G->adicionarArco(v, vLlegada);
              G->modificarArco(v, G->cantidadArcos(v) - 1, matriz[i][j]);
          }
      }
  } 
  imprGrafo(G);  
  G->dibujarGrafo("grafo");
  //Agregar Vértices
  /* G->adicionarVertice(2); //indice=0
  G->adicionarVertice(15); //indice=1
  G->adicionarVertice(30); //indice=2
  G->adicionarVertice(7); //indice=3

  //Agregar los arcos
  G->adicionarArco(0, 1); //indice=0 del vector de indices
  G->modificarArco(0, 0, 10);
  G->adicionarArco(0, 3);	//indice=0 del vector de indices
  G->modificarArco(0, 1, 20);
  G->adicionarArco(1, 2);	//indice=1 del vector de indices
  G->modificarArco(1, 0, 30);
  G->adicionarArco(2, 0);	//indice=2 del vector de indices
  G->modificarArco(2, 0, 40);

  //Imprimir los vértices con sus arcos
  imprGrafo(G); */


  cin.get();
  return 0;
}