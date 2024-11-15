/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#include "Arista.h"
#include <iostream>
#include <algorithm>

// Constructor
Arista::Arista(int v1Index, int v2Index) : indiceV1(v1Index), indiceV2(v2Index) {
    if (v1Index < 0 || v2Index < 0) {
        std::cerr << "Error: se ha intentado crear una arista con índices negativos." << std::endl;
    }
}


// Método para obtener el vertice 1
int Arista::getIndiceV1() const {
    return indiceV1;
}

int Arista::getIndiceV2() const {
    return indiceV2;
}

// Método para leer y mostrar todos las aristas
void Arista::mostrarArista() const {
    std::cout << "Arista: Vértice " << indiceV1 << " a Vértice " << indiceV2 << std::endl;
}
