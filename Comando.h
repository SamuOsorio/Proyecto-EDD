/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cort�s
*/

#ifndef COMANDO_H
#define COMANDO_H

#include <string>

//Definici�n de atributos y m�todos de Comando
class Comando {
public:
    Comando(const std::string& nombre, const std::string& parametros, const std::string& descripcion);
    std::string getNombre() const;
    std::string getParametros() const;
    std::string getDescripcion() const;

private:
    std::string nombre;
    std::string parametros;
    std::string descripcion;
};

#endif





