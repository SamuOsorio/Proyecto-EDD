/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cort�s
*/

#include "Comando.h"

// Constructor
Comando::Comando(const std::string& nombre, const std::string& parametros, const std::string& descripcion)
    : nombre(nombre), parametros(parametros), descripcion(descripcion) {}

// M�todo para obtener nombre
std::string Comando::getNombre() const {
    return nombre;
}

// M�todo para obtener parametro
std::string Comando::getParametros() const {
    return parametros;
}

// M�todo para obtener descripci�n
std::string Comando::getDescripcion() const {
    return descripcion;
}
