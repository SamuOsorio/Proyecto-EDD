/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#include "Vertice.h"
#include <iostream>

// Constructor
Vertice::Vertice(float x, float y, float z) : x(x), y(y), z(z){}

// Método para obtener eje x
float Vertice::getX() const
{
    return x;
}

// Método para obtener eje y
float Vertice::getY() const
{
    return y;
}

// Método para obtener eje z
float Vertice::getZ() const
{
    return z;
}

// Método para asignar eje x
void Vertice::setX(float nuevaX)
{
    x = nuevaX;
}

// Método para asignar eje y
void Vertice::setY(float nuevaY)
{
    y = nuevaY;
}

// Método para asignar eje z
void Vertice::setZ(float nuevaZ)
{
    z = nuevaZ;
}

// Método para leer y mostrar todos los vértices
void Vertice::mostrarVertices() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}


