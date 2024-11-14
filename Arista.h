/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#ifndef ARISTA_H
#define ARISTA_H

#include <vector>
#include <string>
#include "Vertice.h"

//Definición de atributos y métodos de Arista
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
