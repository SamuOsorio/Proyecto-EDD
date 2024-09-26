/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#ifndef GESTOROBJETOS_H
#define GESTOROBJETOS_H

#include <vector>
#include "Objeto.h"

//Definición de atributos y métodos de GestorObjetos
class GestorObjetos {
public:
    GestorObjetos() = default;
    void agregarObjeto(const Objeto& objeto);
    void mostrarObjetos() const;
    bool verificarObjeto(const std::string& mesh);
    Objeto* obtenerObjeto(const std::string& nombre);
    std::vector<Vertice> obtenerTodosLosVertices() const;
    bool estaVacio() const;
    bool descargarObjeto(const std::string& nombre);

private:
    std::vector<Objeto> objetos;
    std::vector<std::vector<float>> verticesTotales;

};

#endif // GESTOROBJETOS_H
