/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#include "Objeto.h"
#include <iostream>
#include <algorithm>


// Constructor
Objeto::Objeto(const std::string& nombre) : nombreMalla(nombre) {}

// Método para reservar memoria a los vertices
void Objeto::agregarPuntos(int cantidadVertices)
{
    vertices.reserve(cantidadVertices);
}

// Método para reservar memoria a las caras
void Objeto::agregarCarasObjeto(int cantidadCaras)
{
    caras.reserve(cantidadCaras);
}

// Método para agregar un vértice
void Objeto::agregarVertice(float x, float y, float z)
{
    vertices.emplace_back(x, y, z);
}

// Método sobrecargado para agregar un vértice como objeto Vertice
void Objeto::agregarVertice(const Vertice& vertice)
{
    vertices.push_back(vertice);
}

// Metodo para agregar la cantidad de puntos del objeto
void Objeto::agregarPuntosObjeto(int puntos)
{
    cantidadPuntos = puntos;
}

// Método para agregar una cara
void Objeto::agregarCara(const Cara& cara)
{
    caras.push_back(cara);
}

// Método para obetener el nombre del objeto
std::string Objeto::getNombreMalla() const
{
    return nombreMalla;
}

// Métodos para obtener la cantidad de puntos
int Objeto::getCantidadPuntos() const
{
    return cantidadPuntos;
}

// Método para obtener la cantidad de vértices
int Objeto::getCantidadVertices() const
{
    return vertices.size();
}

// Método para obtener la cantidad de caras
int Objeto::getCantidadCaras() const
{
    return caras.size();
}

//Método para obtener la cantidad de aristas
int Objeto::getCantidadAristas() const
{
    return aristas.size();
}

// Método para implementar la función getVertices
const std::vector<Vertice>& Objeto::getVertices() const
{
    return vertices;
}

//Método para implementar la función getCaras
const std::vector<Cara>& Objeto::getCaras() const
{
    return caras;
}

// Método para leer y mostrar todos los vértices
void Objeto::leerVertices() const
{
    std::cout << "Vertices del objeto \"" << nombreMalla << "\":" << std::endl;
    for (int i = 0; i < vertices.size(); ++i)
    {
        const auto& v = vertices[i];
        std::cout << "Vertice " << i + 1 << ": "
                  << v.getX() << ", " << v.getY() << ", " << v.getZ() << std::endl;
        std::cout << std::endl;
    }
}

std::vector<Vertice*> Objeto::getVerticePtr()
{
    std::vector<Vertice*> verticesPtr;
    for (Vertice& vertice : vertices)
    {
        verticesPtr.push_back(&vertice);
    }
    return verticesPtr;
}

//Método para calcular las aristas de un objeto
void Objeto::calcularAristas()
{
    // Recorrer las caras del objeto
    for (const auto& cara : caras)
    {
        const auto& verticesCara = cara.getVertices();
        int numVerticesCara = verticesCara.size();

        for (int i = 0; i < numVerticesCara; ++i)
        {
            // Obtener los índices de los vértices
            int v1Index = verticesCara[i];
            int v2Index = verticesCara[(i + 1) % numVerticesCara];

            // Obtener las referencias de los vértices
            Vertice* v1 = &vertices[v1Index];
            Vertice* v2 = &vertices[v2Index];

            // Crear una nueva arista
            Arista nuevaArista(v1, v2);

            // Verificar si la arista ya existe
            if (std::find_if(aristas.begin(), aristas.end(),
                [&nuevaArista](const Arista& a) {
                    return (a.getV1() == nuevaArista.getV1() && a.getV2() == nuevaArista.getV2());
                }) == aristas.end()) {
                aristas.push_back(nuevaArista);
            }
        }
    }
}
