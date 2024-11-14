/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#include "Comando.h"

// Constructor
Comando::Comando(const std::string& nombre, const std::string& parametros, const std::string& descripcion)
    : nombre(nombre), parametros(parametros), descripcion(descripcion) {}

// Método para obtener nombre
std::string Comando::getNombre() const {
    return nombre;
}

// Método para obtener parametro
std::string Comando::getParametros() const {
    return parametros;
}

// Método para obtener descripción
std::string Comando::getDescripcion() const {
    return descripcion;
}
