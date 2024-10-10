/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#include "GestorObjetos.h"
#include <iostream>

// Método para agregar un objeto al vector
void GestorObjetos::agregarObjeto(const Objeto& objeto) {
    objetos.push_back(objeto);
}

// Método mostrar información de todos los objetos
void GestorObjetos::mostrarObjetos() const {
    for (const auto& objeto : objetos) {
        std::cout << objeto.getNombreMalla() << " contiene " << objeto.getCantidadVertices() << " vertices, ";
        std::cout << objeto.getCantidadAristas() << " aristas y " << objeto.getCantidadCaras() <<" caras" <<std::endl;
        std::cout<<std::endl;
    }
}

// Método para verificar la exisistencia de un objeto
bool GestorObjetos::verificarObjeto(const std::string& mesh){
    bool bandera = false;
    for (const auto& objeto : objetos) {
        if(mesh == objeto.getNombreMalla()){
            bandera = true;
        }
    }
    return bandera;
}

// Método para obtener un objeto por su nombre
Objeto* GestorObjetos::obtenerObjeto(const std::string& nombre) {
    for (auto& objeto : objetos) {
        if (objeto.getNombreMalla() == nombre) {
            return &objeto;
        }
    }
    return nullptr;
}

// Método para obtener todos los objetos cargados en memoria
std::vector<Objeto>& GestorObjetos::obtenerObjetos() {
    return objetos; // Retorna una referencia al vector de objetos
}

// Método para implementar la función obtenerTodosLosVertices
std::vector<Vertice> GestorObjetos::obtenerTodosLosVertices() const {
    std::vector<Vertice> todosLosVertices;  // Vector que almacena todos los vértices

    // Recorrer todos los objetos en memoria
    for (const auto& objeto : objetos) {
        // Obtener los vértices de cada objeto
        const std::vector<Vertice>& verticesDelObjeto = objeto.getVertices();

        // Añadir esos vértices al vector global
        todosLosVertices.insert(todosLosVertices.end(), verticesDelObjeto.begin(), verticesDelObjeto.end());
    }

    return todosLosVertices;  // Retornar todos los vértices en un solo vector
}

// Método para verificar si la lista de objetos está vacía
bool GestorObjetos::estaVacio() const {
    return objetos.empty();
}

// Método para eliminar un objeto del vector y de la memoria
bool GestorObjetos::descargarObjeto(const std::string& nombre) {
    for (auto it = objetos.begin(); it != objetos.end(); ++it) {
        if (it->getNombreMalla() == nombre) {
            objetos.erase(it);
            return true;
        }
    }
    std::cout << "El objeto " << nombre << " no ha sido cargado en memoria." << std::endl;
    return false;
}


