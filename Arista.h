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
    Arista(int V1index, int V2Index);
    int getIndiceV1() const;
    int getIndiceV2() const;
    void mostrarArista() const;

private:
    Vertice* v1;
    Vertice* v2;
    int indiceV1;
    int indiceV2;
};

#endif // ARISTA_H
