/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#include "NodoKD.h"
#include <iostream>
#include <algorithm>

// Constructor del nodo
NodoKD::NodoKD(Vertice* v) : vertice(v), hijoIzquierdo(nullptr), hijoDerecho(nullptr) {}

//Metodo para obtener un vertice
Vertice* NodoKD::getVertice() const {
    return vertice;
}

//Metodo para obtener el hijo
NodoKD* NodoKD::getHijoIzquierdo() const {
    return hijoIzquierdo;
}

NodoKD* NodoKD::getHijoDerecho() const {
    return hijoDerecho;
}

void NodoKD::setHijoIzquierdo(NodoKD* nodo) {
    hijoIzquierdo = nodo;
}

void NodoKD::setHijoDerecho(NodoKD* nodo) {
    hijoDerecho = nodo;
}

NodoKD::~NodoKD() {
    delete vertice;
}
