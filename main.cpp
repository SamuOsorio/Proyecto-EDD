/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#include <iostream>
#include <string>
#include <sstream>
#include "Sistema.h"
#include "Objeto.h"
#include "GestorObjetos.h"

int main()
{
	// Creación de instancias
    Sistema sistema;
    GestorObjetos gestor;
	// Lista comandos disponibles
    sistema.listarComandos();
    
	// Ciclo para recibir y procesar comando
    while (true)
    {
        std::cout<<std::endl;
		// Lee el comando ingresado en consola
        std::string comando;
        std::cout << "\n$ ";
        std::getline(std::cin, comando);
        if (comando == "salir")
        {
            break;
        }
        // Procesa el comando del usuario
        sistema.procesarComando(comando);
    }

    return 0;
}

