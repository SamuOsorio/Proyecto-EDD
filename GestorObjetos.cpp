/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cort�s
*/

#include "GestorObjetos.h"
#include <iostream>

// M�todo para agregar un objeto al vector
void GestorObjetos::agregarObjeto(const Objeto& objeto) {
    objetos.push_back(objeto);
}

// M�todo mostrar informaci�n de todos los objetos
void GestorObjetos::mostrarObjetos() const {
    for (const auto& objeto : objetos) {
        std::cout << objeto.getNombreMalla() << " contiene " << objeto.getCantidadVertices() << " vertices, ";
        std::cout << objeto.getCantidadAristas() << " aristas y " << objeto.getCantidadCaras() <<" caras" <<std::endl;
        std::cout<<std::endl;
    }
}

// M�todo para verificar la exisistencia de un objeto
bool GestorObjetos::verificarObjeto(const std::string& mesh){
    bool bandera = false;
    for (const auto& objeto : objetos) {
        if(mesh == objeto.getNombreMalla()){
            bandera = true;
        }
    }
    return bandera;
}

// M�todo para obtener un objeto por su nombre
Objeto* GestorObjetos::obtenerObjeto(const std::string& nombre) {
    for (auto& objeto : objetos) {
        if (objeto.getNombreMalla() == nombre) {
            return &objeto;
        }
    }
    return nullptr;
}

// M�todo para obtener todos los objetos cargados en memoria
std::vector<Objeto>& GestorObjetos::obtenerObjetos() {
    return objetos; // Retorna una referencia al vector de objetos
}

// M�todo para implementar la funci�n obtenerTodosLosVertices
std::vector<Vertice> GestorObjetos::obtenerTodosLosVertices() const {
    std::vector<Vertice> todosLosVertices;  // Vector que almacena todos los v�rtices

    // Recorrer todos los objetos en memoria
    for (const auto& objeto : objetos) {
        // Obtener los v�rtices de cada objeto
        const std::vector<Vertice>& verticesDelObjeto = objeto.getVertices();

        // A�adir esos v�rtices al vector global
        todosLosVertices.insert(todosLosVertices.end(), verticesDelObjeto.begin(), verticesDelObjeto.end());
    }

    return todosLosVertices;  // Retornar todos los v�rtices en un solo vector
}

// M�todo para verificar si la lista de objetos est� vac�a
bool GestorObjetos::estaVacio() const {
    return objetos.empty();
}

// M�todo para eliminar un objeto del vector y de la memoria
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


