/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <vector>
#include "Objeto.h"
#include "Comando.h"
#include "GestorObjetos.h"

//Definición de atributos y métodos de Sistema
class Sistema {
public:
    Sistema();
    void mostrarAyuda();
    void borrarPantalla();
    void cargarArchivo(const std::string& nombreArchivo);
    void listarObjetos();
    void generarEnvolvente(const std::string& nombreObjeto);
    void generarEnvolventeGlobal();
    void descargarObjeto(const std::string& nombreObjeto);
    void guardarObjeto(const std::string& nombreObjeto, const std::string& nombreArchivo);
    void verticeMasCercano(float px, float py, float pz, const std::string& nombreObjeto);
    void verticeMasCercanoGlobal(float px, float py, float pz);
    void verticesCercanosCaja(const std::string& nombreObjeto);
    void rutaCorta(int i1, int i2, const std::string& nombreObjeto);
    void rutaCortaCentro(int i1, const std::string& nombreObjeto);

    void procesarComando(const std::string& comando);
    void cargarComandos(const std::string& nombreArchivo);
    void listarComandos();

private:
    void agregarComando(const std::string& nombre, const std::string& parametros, const std::string& descripcion);
    std::vector<Comando> comandos;
    std::vector<std::string> nombresObjetos;
    GestorObjetos gestor;

};

#endif
