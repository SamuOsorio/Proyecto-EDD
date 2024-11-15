/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#ifndef ARBOLKD_H
#define ARBOLKD_H

#include "NodoKD.h"
#include "Vertice.h"
#include <vector>

//Definición de atributos y métodos de ArbolKD
class ArbolKD
{
public:
    ArbolKD(const std::vector<Vertice>& vertices);
    ~ArbolKD();
    Vertice* VerticeMasCercano(const Vertice& punto,const std::string& nombreObjeto);
	float distanciaEuclidiana(const Vertice& v1, const Vertice& v2);
    void preOrden() const;

private:
    NodoKD* raiz;
    NodoKD* construirArbol(std::vector<Vertice*>& vertices, int profundidad);
    void preOrdenRecursivo(NodoKD* nodo) const;
    void destruirArbol(NodoKD* nodo);
    void buscarVerticeMasCercano(NodoKD* nodo, const Vertice& punto, int profundidad, Vertice*& mejorVertice, float& mejorDistancia);

};

#endif
