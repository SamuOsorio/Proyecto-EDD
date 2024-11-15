/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#ifndef OBJETO_H
#define OBJETO_H

#include "Vertice.h"
#include "Arista.h"
#include "Cara.h"
#include <vector>
#include <string>

//Definición de atributos y métodos de Objeto
class Objeto
{
public:
    Objeto(const std::string& nombre);
    void agregarArista(const Arista& arista);
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
    void eliminarVertice(int indice);
    void eliminarArista(const Arista& arista);
    void leerVertices() const;
    const std::vector<Vertice>& getVertices() const;
    const std::vector<Cara>& getCaras() const;
    const std::vector<Arista>& getAristas() const;
    void calcularAristas();
    std::vector<Vertice*> getVerticePtr();
    static float distanciaEuclidiana(const Vertice& v1, const Vertice& v2);
    Vertice calcularCentroide() const;
    int encontrarVerticeMasCercano(const Vertice& punto) const;


private:
    std::string nombreMalla;
    std::vector<Vertice> vertices;
    std::vector<Cara> caras;
    std::vector<Arista> aristas;
    int cantidadPuntos=0;
};

#endif // OBJETO_H
