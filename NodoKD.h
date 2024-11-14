/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cort�s
*/

#ifndef NODOKD_H
#define NODOKD_H

#include <vector>
#include <string>
#include "Vertice.h"

//Definici�n de atributos y m�todos de NodoKD
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
