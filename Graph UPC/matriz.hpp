#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

// Función para seleccionar letras aleatorias del abecedario
std::vector<char> seleccionarLetras(int n) {
    std::vector<char> abecedario = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    std::random_shuffle(abecedario.begin(), abecedario.end());
    return std::vector<char>(abecedario.begin(), abecedario.begin() + n);
}

// Función para generar un número aleatorio con 0 teniendo 10 veces más probabilidad
int generarNumeroSesgado() {
    int randomNum = rand() % 31; // Rango de 0 a 30
    if (randomNum < 16) {
        return 0; 
    } else {
        return randomNum - 15; //[1, 15]
    }
}

// Función para obtener el ancho máximo de los elementos de la matriz
int obtenerAnchoMaximo(const std::vector<std::vector<int>>& matriz, const std::vector<char>& letras) {
    int maxWidth = 0;

    // Calcular el ancho de los números
    for (const auto& fila : matriz) {
        for (int num : fila) {
            int width = std::to_string(num).length();
            if (width > maxWidth) {
                maxWidth = width;
            }
        }
    }

    // Calcular el ancho de las letras
    for (char letra : letras) {
        if (1 > maxWidth) {
            maxWidth = 1;
        }
    }

    return maxWidth + 1;
}

// Función para generar la matriz
std::vector<std::vector<int>> generarMatriz(int n) {
    srand(static_cast<unsigned>(time(0)));

    // Seleccionar n letras aleatorias del abecedario
    std::vector<char> letras = seleccionarLetras(n);

    // Crear la matriz (n+1)x(n+1)
    int size = n + 1;
    std::vector<std::vector<int>> matriz(size, std::vector<int>(size));

    // Llenar la matriz con números aleatorios sesgados del 0 al 30
    for (int i = 1; i < size; ++i) {
        for (int j = 1; j < size; ++j) {
            matriz[i][j] = generarNumeroSesgado();
        }
    }

    // Colocar las letras en la primera fila y primera columna
    for (int i = 1; i < size; ++i) {
        matriz[0][i] = letras[i - 1];
        matriz[i][0] = letras[i - 1];
    }

    return matriz;
}

// Función para imprimir la matriz
void imprimirMatriz(const std::vector<std::vector<int>>& matriz, const std::vector<char>& letras) {
    int anchoMaximo = obtenerAnchoMaximo(matriz, letras);
    int n = matriz.size();

    // Mostrar la matriz resultante
    std::cout << "Matriz resultante:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 0) {
                std::cout << std::setw(anchoMaximo) << " ";
            } else if (i == 0 || j == 0) {
                std::cout << std::setw(anchoMaximo) << static_cast<char>(matriz[i][j]);
            } else {
                std::cout << std::setw(anchoMaximo) << matriz[i][j];
            }
        }
        std::cout << std::endl;
    }
}