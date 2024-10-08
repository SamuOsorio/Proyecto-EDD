/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cort�s
*/

#include "ArbolKD.h"
#include <cmath>
#include <algorithm>
#include <iostream>

// Constructor
ArbolKD::ArbolKD(const std::vector<Vertice*>& vertices){
    raiz = construirArbol(const_cast<std::vector<Vertice*>&>(vertices), 0);
}

ArbolKD::~ArbolKD(){
    destruirArbol(raiz);
}

void ArbolKD::destruirArbol(NodoKD* nodo){
    if(nodo != nullptr){
        destruirArbol(nodo->getHijoIzquierdo());
        destruirArbol(nodo->getHijoDerecho());
        delete nodo;
    }
}

NodoKD* ArbolKD::construirArbol(std::vector<Vertice*>& vertices, int profundidad){
    if(vertices.empty()) return nullptr;

    int eje = profundidad % 3;
    std::sort(vertices.begin(), vertices.end(), [eje](const Vertice* v1, const Vertice* v2){
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

void ArbolKD::preOrden() const {
    std::cout << "Recorrido Preorden del Arbol KD:" << std::endl;
    preOrdenRecursivo(raiz);  // Llama al m�todo recursivo desde la ra�z
}

// M�todo recursivo para realizar el recorrido en preorden
void ArbolKD::preOrdenRecursivo(NodoKD* nodo) const {
    if (nodo == nullptr) {
        return;  // Caso base: si el nodo es nulo, se termina la recursi�n
    }

    // Imprime la informaci�n del v�rtice del nodo actual
    Vertice* v = nodo->getVertice();
    std::cout << "V�rtice: (" << v->getX() << ", " << v->getY() << ", " << v->getZ() << ")" << std::endl;

    // Recursivamente recorrer el sub�rbol izquierdo
    preOrdenRecursivo(nodo->getHijoIzquierdo());

    // Recursivamente recorrer el sub�rbol derecho
    preOrdenRecursivo(nodo->getHijoDerecho());
}
/*
// M�todo para obtener el vertice 1
Vertice* Arista::getV1() const
{
    return v1;
}

// M�todo para obtener el vertice 2
Vertice* Arista::getV2() const
{
    return v2;
}

// M�todo para leer y mostrar todos las aristas
void Arista::mostrarArista() const
{
    std::cout << "Arista: ";
    v1->mostrarVertices();
    std::cout << " a ";
    v2->mostrarVertices();
    std::cout << std::endl;
}
*/
