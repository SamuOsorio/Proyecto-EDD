/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#include "ArbolKD.h"
#include <cmath>
#include <algorithm>
#include <iostream>

// Constructor
ArbolKD::ArbolKD(const std::vector<Vertice*>& vertices)
{
    raiz = construirArbol(const_cast<std::vector<Vertice*>&>(vertices), 0);
}

ArbolKD::~ArbolKD()
{
    destruirArbol(raiz);
}

void ArbolKD::destruirArbol(NodoKD* nodo)
{
    if(nodo != nullptr)
    {
        destruirArbol(nodo->getHijoIzquierdo());
        destruirArbol(nodo->getHijoDerecho());
        delete nodo;
    }
}

NodoKD* ArbolKD::construirArbol(std::vector<Vertice*>& vertices, int profundidad)
{
    if(vertices.empty()) return nullptr;

    int eje = profundidad % 3;
    std::sort(vertices.begin(), vertices.end(), [eje](const Vertice* v1, const Vertice* v2)
    {
        if (eje == 0) return v1->getX() < v2->getX();  // Comparar X
        else if (eje == 1) return v1->getY() < v2->getY();  // Comparar Y
        else return v1->getZ() < v2->getZ();  // Comparar Z
    });

    int mediana = vertices.size() / 2;
    NodoKD* nodo = new NodoKD(vertices[mediana]);

    std::vector<Vertice*> izquierda(vertices.begin(), vertices.begin() + mediana);
    std::vector<Vertice*> derecha(vertices.begin() + mediana + 1, vertices.end());

    nodo->setHijoIzquierdo(construirArbol(izquierda, profundidad + 1));
    nodo->setHijoDerecho(construirArbol(derecha, profundidad + 1));

    return nodo;
}

void ArbolKD::preOrden() const
{
    std::cout << "Recorrido Preorden del Arbol KD:" << std::endl;
    preOrdenRecursivo(raiz);  // Llama al método recursivo desde la raíz
}

// Método recursivo para realizar el recorrido en preorden
void ArbolKD::preOrdenRecursivo(NodoKD* nodo) const
{
    if (nodo == nullptr)
    {
        return;  // Caso base: si el nodo es nulo, se termina la recursión
    }

    // Imprime la información del vértice del nodo actual
    Vertice* v = nodo->getVertice();
    std::cout << "Vertice: (" << v->getX() << ", " << v->getY() << ", " << v->getZ() << ")" << std::endl;

    // Recursivamente recorrer el subárbol izquierdo
    preOrdenRecursivo(nodo->getHijoIzquierdo());

    // Recursivamente recorrer el subárbol derecho
    preOrdenRecursivo(nodo->getHijoDerecho());
}

// Método público para encontrar el vértice más cercano
Vertice* ArbolKD::VerticeMasCercano(const Vertice& punto, const std::string& nombreObjeto)
{
    if (raiz == nullptr)
    {
        std::cout << "El arbol está vacío." << std::endl;
        return nullptr;
    }
    Vertice* mejorVertice = nullptr;
    float mejorDistancia = std::numeric_limits<float>::max();

    // Llama a la función de búsqueda
    buscarVerticeMasCercano(raiz, punto, 0, mejorVertice, mejorDistancia);
    return mejorVertice;
}

// Método auxiliar para buscar el vértice más cercano en el árbol
void ArbolKD::buscarVerticeMasCercano(NodoKD* nodo, const Vertice& punto, int profundidad, Vertice*& mejorVertice, float& mejorDistancia)
{
    if (nodo == nullptr)
    {
        return;
    }

    // Calcular la distancia actual
    float distanciaActual = distanciaEuclidiana(punto, *nodo->getVertice());
    if (distanciaActual < mejorDistancia)
    {
        mejorDistancia = distanciaActual;
        mejorVertice = nodo->getVertice(); // Asignar el puntero directamente
    }

    // Determinar si buscar en el subárbol izquierdo o derecho
    int eje = profundidad % 3;
    NodoKD* ladoCercano = (punto.getX() < nodo->getVertice()->getX()) ? nodo->getHijoIzquierdo() : nodo->getHijoDerecho();
    NodoKD* ladoLejano = (punto.getX() < nodo->getVertice()->getX()) ? nodo->getHijoDerecho() : nodo->getHijoIzquierdo();

    // Recursión en el subárbol cercano
    buscarVerticeMasCercano(ladoCercano, punto, profundidad + 1, mejorVertice, mejorDistancia);

    // Verificar si debemos explorar el lado lejano
    if (fabs(punto.getX() - nodo->getVertice()->getX()) < mejorDistancia)
    {
        buscarVerticeMasCercano(ladoLejano, punto, profundidad + 1, mejorVertice, mejorDistancia);
    }
}

float ArbolKD::distanciaEuclidiana(const Vertice& v1, const Vertice& v2)
{
    float dx = v1.getX() - v2.getX();
    float dy = v1.getY() - v2.getY();
    float dz = v1.getZ() - v2.getZ();
    return sqrt(dx * dx + dy * dy + dz * dz);
}
