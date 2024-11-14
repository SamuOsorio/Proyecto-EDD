/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cort�s
*/

#ifndef CARA_H
#define CARA_H

#include <vector>
#include <string>

//Definici�n de atributos y m�todos de Caras
class Cara
{
public:
    void agregarVertice(int indice);
    const std::vector<int>& getVertices() const;

private:
    std::vector<int> vertices;
};

#endif // CARA_H
