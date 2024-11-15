/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cort�s
*/

#include "Objeto.h"
#include <iostream>
#include <algorithm>
#include <cmath>


// Constructor
Objeto::Objeto(const std::string& nombre) : nombreMalla(nombre) {}

void Objeto::agregarArista(const Arista& arista)
{

    aristas.push_back(arista);
}

// M�todo para reservar memoria a los vertices
void Objeto::agregarPuntos(int cantidadVertices)
{
    vertices.reserve(cantidadVertices);
}

// M�todo para reservar memoria a las caras
void Objeto::agregarCarasObjeto(int cantidadCaras)
{
    caras.reserve(cantidadCaras);
}

// M�todo para agregar un v�rtice
void Objeto::agregarVertice(float x, float y, float z)
{
    int index = vertices.size();
    vertices.emplace_back(x, y, z, index);
}

// M�todo sobrecargado para agregar un v�rtice como objeto Vertice
void Objeto::agregarVertice(const Vertice& vertice)
{
    vertices.push_back(vertice);
}

// Metodo para agregar la cantidad de puntos del objeto
void Objeto::agregarPuntosObjeto(int puntos)
{
    cantidadPuntos = puntos;
}

// M�todo para agregar una cara
void Objeto::agregarCara(const Cara& cara)
{
    caras.push_back(cara);
}

// M�todo para obetener el nombre del objeto
std::string Objeto::getNombreMalla() const
{
    return nombreMalla;
}

// M�todos para obtener la cantidad de puntos
int Objeto::getCantidadPuntos() const
{
    return cantidadPuntos;
}

// M�todo para obtener la cantidad de v�rtices
int Objeto::getCantidadVertices() const
{
    return vertices.size();
}

// M�todo para obtener la cantidad de caras
int Objeto::getCantidadCaras() const
{
    return caras.size();
}

//M�todo para obtener la cantidad de aristas
int Objeto::getCantidadAristas() const
{
    return aristas.size();
}

// M�todo para implementar la funci�n getVertices
const std::vector<Vertice>& Objeto::getVertices() const
{
    return vertices;
}

//M�todo para implementar la funci�n getCaras
const std::vector<Cara>& Objeto::getCaras() const
{
    return caras;
}

//Metodo para obtener las aristas del objeto
const std::vector<Arista>& Objeto::getAristas() const
{
    return aristas;
}

void Objeto::eliminarVertice(int indice)
{
    if (indice >= 0 && indice < vertices.size())
    {
        vertices.erase(vertices.begin() + indice);
    }
}

void Objeto::eliminarArista(const Arista& arista)
{
    auto it = std::remove_if(aristas.begin(), aristas.end(),
                             [&arista](const Arista& a)
    {
        return (a.getIndiceV1() == arista.getIndiceV1() &&
                a.getIndiceV2() == arista.getIndiceV2()) ||
               (a.getIndiceV1() == arista.getIndiceV2() &&
                a.getIndiceV2() == arista.getIndiceV1());
    });
    aristas.erase(it, aristas.end());
}

// M�todo para leer y mostrar todos los v�rtices
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

//Metodo para obtener una lista de punteros de vertices
std::vector<Vertice*> Objeto::getVerticePtr()
{
    std::vector<Vertice*> verticesPtr;
    for (Vertice& vertice : vertices)
    {
        verticesPtr.push_back(&vertice);
    }
    return verticesPtr;
}

//M�todo para calcular las aristas de un objeto
void Objeto::calcularAristas()
{
// Recorrer las caras del objeto
    aristas.clear();
    for (const auto& cara : caras)
    {
        const auto& verticesCara = cara.getVertices();
        int numVerticesCara = verticesCara.size();

        for (int i = 0; i < numVerticesCara; ++i)
        {
            int v1Index = verticesCara[i];
            int v2Index = verticesCara[(i + 1) % numVerticesCara];  // Conectar el �ltimo v�rtice con el primero

            // Validar que los �ndices est�n dentro de rango
            if (v1Index < 0 || v1Index >= vertices.size() ||
                    v2Index < 0 || v2Index >= vertices.size())
            {
                std::cerr << "Error: �ndices fuera de rango al crear arista entre "
                          << v1Index << " y " << v2Index << std::endl;
                continue;
            }

            // Crear una nueva arista entre v1 y v2
            Arista nuevaArista(v1Index, v2Index);

            // Verificar duplicados usando �ndices
            bool aristaExiste = false;
            for (const auto& arista : aristas)
            {
                if ((arista.getIndiceV1() == v1Index && arista.getIndiceV2() == v2Index) ||
                        (arista.getIndiceV1() == v2Index && arista.getIndiceV2() == v1Index))
                {
                    aristaExiste = true;
                    break;
                }
            }

            if (!aristaExiste)
            {
                aristas.push_back(nuevaArista);
            }
        }
    }
}

// Implementaci�n del m�todo est�tico para calcular la distancia euclidiana
float Objeto::distanciaEuclidiana(const Vertice& v1, const Vertice& v2)
{
    float dx = v1.getX() - v2.getX();
    float dy = v1.getY() - v2.getY();
    float dz = v1.getZ() - v2.getZ();
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

Vertice Objeto::calcularCentroide() const
{
    if (vertices.empty())
    {
        throw std::runtime_error("No hay v�rtices para calcular el centroide");
    }

    float sumX = 0, sumY = 0, sumZ = 0;
    for (const auto& vertice : vertices)
    {
        sumX += vertice.getX();
        sumY += vertice.getY();
        sumZ += vertice.getZ();
    }

    float numVertices = static_cast<float>(vertices.size());
    return Vertice(sumX/numVertices, sumY/numVertices, sumZ/numVertices);
}

int Objeto::encontrarVerticeMasCercano(const Vertice& punto) const
{
    if (vertices.empty())
    {
        throw std::runtime_error("No hay v�rtices para comparar");
    }

    int indiceMasCercano = 0;
    float distanciaMinima = distanciaEuclidiana(vertices[0], punto);

    for (size_t i = 1; i < vertices.size(); ++i)
    {
        float distancia = distanciaEuclidiana(vertices[i], punto);
        if (distancia < distanciaMinima)
        {
            distanciaMinima = distancia;
            indiceMasCercano = i;
        }
    }

    return indiceMasCercano;
}
