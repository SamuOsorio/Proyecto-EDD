/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#ifndef NODOKD_H
#define NODOKD_H

#include <vector>
#include <string>
#include "Vertice.h"

//Definición de atributos y métodos de NodoKD
class NodoKD
{
public:
    NodoKD(Vertice* vertice);
    Vertice* getVertice() const;
    NodoKD* getHijoIzquierdo() const;
    NodoKD* getHijoDerecho() const;
    void setHijoIzquierdo(NodoKD* nodo);
    void setHijoDerecho(NodoKD* nodo);
    ~NodoKD();

private:
    Vertice* vertice;
    NodoKD* hijoIzquierdo;
    NodoKD* hijoDerecho;
};

#endif
