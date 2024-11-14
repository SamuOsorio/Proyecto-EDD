/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cort�s
*/

#ifndef ARISTA_H
#define ARISTA_H

#include <vector>
#include <string>
#include "Vertice.h"

//Definici�n de atributos y m�todos de Arista
class Arista
{
public:
    Arista(Vertice* v1, Vertice* v2);
    Vertice* getV1() const;
    Vertice* getV2() const;
    void mostrarArista() const;

private:
    Vertice* v1;
    Vertice* v2;
};

#endif // ARISTA_H
