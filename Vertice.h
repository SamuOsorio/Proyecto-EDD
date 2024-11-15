/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cort�s
*/

#ifndef VERTICE_H
#define VERTICE_H

#include <vector>
#include <string>

//Definici�n de atributos y m�todos de Vertice
class Vertice
{
public:
    Vertice(float x, float y, float z);
    Vertice(float x, float y, float z, int index);
    float getX() const;
    float getY() const;
    float getZ() const;
    int getIndex() const;
    void setX(float nuevoX);
    void setY(float nuevoY);
    void setZ(float nuevoZ);
    void mostrarVertices() const;

private:
    float x,y,z;
    int index;
};

#endif // VERTICE_H
