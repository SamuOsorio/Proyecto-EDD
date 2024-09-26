/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cort�s
*/

#ifndef OBJETO_H
#define OBJETO_H

#include "Vertice.h"
#include "Arista.h"
#include "Cara.h"
#include <vector>
#include <string>

//Definici�n de atributos y m�todos de Objeto
class Objeto
{
public:
    Objeto(const std::string& nombre);
    void agregarVertice(float x, float y, float z);
    void agregarVertice(const Vertice& vertice);
    void agregarPuntosObjeto(int puntos);
    void agregarCara(const Cara& cara);
    void agregarPuntos(int cantidadVertices);
    void agregarCarasObjeto(int cantidadCaras);
    std::string getNombreMalla() const;
    int getCantidadPuntos() const;
    int getCantidadVertices() const;
    int getCantidadCaras() const;
    int getCantidadAristas() const;
    void leerVertices() const;
    const std::vector<Vertice>& getVertices() const;
    const std::vector<Cara>& getCaras() const;
    void calcularAristas();

private:
    std::string nombreMalla;
    std::vector<Vertice> vertices;
    std::vector<Cara> caras;
    std::vector<Arista> aristas;
    int cantidadPuntos=0;
};

#endif // OBJETO_H
