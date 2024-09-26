/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cort�s
*/

#include "Sistema.h"
#include "Objeto.h"
#include "GestorObjetos.h"
#include "Comando.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>

// Constructor
Sistema::Sistema()
{
    cargarComandos("comandos.txt");
}

// M�todo para cargar comando -- lee los comandos desde el archivo y almacenarlos en un vector
void Sistema::cargarComandos(const std::string& nombreArchivo)
{
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        std::cerr << "No se pudo abrir el archivo de comandos: " << nombreArchivo << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea))
    {
        std::istringstream iss(linea);
        std::string nombre, parametros, descripcion;

        if (std::getline(iss, nombre, '|') &&
                std::getline(iss, parametros, '|') &&
                std::getline(iss, descripcion, '|'))
        {
            Comando comando(nombre, parametros, descripcion);

            comandos.push_back(comando);
        }
    }

    archivo.close();
}

// M�todo para procesar comando -- Procesa un comando introducido por consolo por el usuario
void Sistema::procesarComando(const std::string& comando)
{
    std::istringstream iss(comando);
    std::string nombre;
    iss >> nombre;

    if (nombre == "ayuda")
    {
        mostrarAyuda();
    }
    else if (nombre == "cargar")
    {
        std::string nombreArchivo;
        if (iss >> nombreArchivo)
        {
            cargarArchivo(nombreArchivo);
        }
        else
        {
            std::cerr << "\nError: Falta el nombre del archivo para cargar.\n" << std::endl;
        }
    }
    else if (nombre == "listado")
    {
        listarObjetos();
    }
    else if (nombre == "envolvente")
    {
        std::string nombreObjeto;
        if (iss >> nombreObjeto)
        {
            generarEnvolvente(nombreObjeto);
        }
        else
        {
            std::cout << "\nConfirmacion: No se ha ingresado un nombre de objeto. Se asume que esta llamando a envolventeGlobal." << std::endl;
            generarEnvolventeGlobal();
        }
    }
    else if (nombre == "descargar")
    {
        std::string nombreObjeto;
        if (iss >> nombreObjeto)
        {
            descargarObjeto(nombreObjeto);
        }
        else
        {
            std::cerr << "\nError: Falta el nombre del objeto para descargar.\n" << std::endl;
        }
    }
    else if (nombre == "guardar")
    {
        std::string nombreObjeto, nombreArchivo;
        if (iss >> nombreObjeto >> nombreArchivo)
        {
            guardarObjeto(nombreObjeto, nombreArchivo);
        }
        else
        {
            std::cerr << "\nError: Faltan el nombre del objeto o el nombre del archivo para guardar.\n" << std::endl;
        }
    }
    else if (nombre == "v_cercano")
    {
        float px, py, pz;
        if (iss >> px >> py >> pz)
        {
            std::string nombreObjeto;
            if (iss >> nombreObjeto)
            {
                verticeMasCercano(px, py, pz, nombreObjeto);
            }
            else
            {
                std::cout << "\nConfirmacion: Se ha ingresado 3 coordenadas. Se asume que ests llamando a verticeCercanoGlobal." << std::endl;
                verticeMasCercanoGlobal(px, py, pz);
            }
        }
        else
        {
            std::cerr << "\nError: Faltan las coordenadas (px, py, pz) para el vertice m�s cercano.\n" << std::endl;
        }
    }
    else if (nombre == "v_cercanos_caja")
    {
        std::string nombreObjeto;
        if (iss >> nombreObjeto)
        {
            verticesCercanosCaja(nombreObjeto);
        }
        else
        {
            std::cerr << "\nError: Falta el nombre del objeto para vertices cercanos a la caja.\n" << std::endl;
        }
    }
    else if (nombre == "ruta_corta")
    {
        int i1, i2;
        std::string nombreObjeto;
        if (iss >> i1 >> i2 >> nombreObjeto)
        {
            rutaCorta(i1, i2, nombreObjeto);
        }
        else
        {
            std::cerr << "\nError: Faltan los indices (i1, i2) o el nombre del objeto para la ruta mas corta.\n" << std::endl;
        }
    }
    else if (nombre == "ruta_corta_centro")
    {
        int i1;
        std::string nombreObjeto;
        if (iss >> i1 >> nombreObjeto)
        {
            rutaCortaCentro(i1, nombreObjeto);
        }
        else
        {
            std::cerr << "\nError: Faltan el indice (i1) o el nombre del objeto para la ruta mas corta al centro.\n" << std::endl;
        }
    }
    else if(nombre=="clear")
    {
        borrarPantalla();
    }
    else
    {
        std::cout << "\nComando no reconocido: " << comando << "\n" << std::endl;
    }
}

// M�todo para mostrar ayuda de los comandos -- Muestra lista de comandos disponibles y su descripci�n
void Sistema::mostrarAyuda()
{
    std::cout << std::left
              << std::setw(20) << "\nComando"
              << std::setw(35) << "Parametros"
              << "Descripcion" << std::endl;
    std::cout << std::string(120, '-') << std::endl;

    for (const auto& comando : comandos)
    {
        std::cout << std::left
                  << std::setw(20) << comando.getNombre()
                  << std::setw(35) << comando.getParametros()
                  << comando.getDescripcion() << std::endl;
    }

    std::cout << "\n**Aclaraciones:**" << std::endl;
    std::cout << "\n- El comando 'envolvente' puede comportarse de dos maneras: " << std::endl;
    std::cout << "  1. Si se ingresa con un parametro <nombre_objeto>, calcula la caja envolvente para el objeto especificado y agrega esta caja como un nuevo objeto en memoria con el nombre 'env_nombre_objeto'." << std::endl;
    std::cout << "  2. Si se ingresa sin parametros, calcula la caja envolvente que incluye a todos los objetos cargados en memoria y agrega esta caja como un nuevo objeto en memoria con el nombre 'env_global'." << std::endl;
    std::cout << "\n- El comando 'v_cercano' puede comportarse de dos maneras: " << std::endl;
    std::cout << "  1. Si se ingresa con las coordenadas <px> <py> <pz> y el nombre del objeto <nombre_objeto>, identifica el vertice m�s cercano de ese objeto especifico al punto dado" << std::endl;
    std::cout << "  2. Si se ingresa solo con las coordenadas `<px> <py> <pz>`, identifica el vertice mas cercano entre todos los objetos cargados en memoria al punto dado.\n" << std::endl;
}

// M�todo para listar comandos -- Lista los nombres de los comandos disponibles
void Sistema::listarComandos()
{
    std::cout << "\nLista de comandos disponibles: \n" << std::endl;
    for (const auto& comando : comandos)
    {
        std::cout << comando.getNombre() << std::endl;
    }
}


// M�todo para cargar archivo -- Carga objeto 3D desde un archivo de texto con todas sus caracteristicas
void Sistema::cargarArchivo(const std::string& nombreArchivo)
{

    std::ifstream archivo(nombreArchivo);
    if(!archivo.is_open())
    {
        std::cout<<"El archivo "<< nombreArchivo<<" no existe o es ilegible." << std::endl;
        return;
    }
    std::string meshName;
    int numVertice, tamCaras = 0, numIndices;
    archivo >> meshName;

    if (!archivo)
    {
        std::cout << "Error al leer el archivo " << nombreArchivo << "." << std::endl;
        return;
    }

    // Verifica exisitencia del objeto
    if (gestor.verificarObjeto(meshName))
    {
        std::cerr << "El objeto " << meshName << " ya ha sido cargado en memoria." << std::endl;
        return;
    }

    archivo >> numVertice;
    if (!archivo)
    {
        std::cout << "Error al leer el archivo " << nombreArchivo << " en el numero de vertices." << std::endl;
        return;
    }
    if(numVertice <= 0)
    {
        std::cout << "El archivo " << nombreArchivo << " no contiene un objeto 3D valido (cantidad de puntos no valida, tiene que ser > 0)." << std::endl;
        return;
    }

    // Crea la instancia de un nuevo Objeto
    Objeto nuevoObjeto(meshName);

    //Agrega los vertices del objeto
    for(int i=0; i< numVertice; i++)
    {
        float x,y,z;
        archivo >> x >> y >> z;
        if (!archivo)
        {
            std::cout << "Error al leer el archivo " << nombreArchivo << " en las coordenadas." << std::endl;
            return;
        }
        Vertice nuevoVertice(x,y,z);
        nuevoObjeto.agregarVertice(nuevoVertice);
    }

    //Agrega las caras del objeto y sus indices
    while(true)
    {
        archivo >> tamCaras;
        if(tamCaras == -1)
        {
            break;
        }
        if (!archivo)
        {
            std::cout << "Error al leer el archivo " << nombreArchivo << " en el numero de caras." << std::endl;
            return;
        }

        Cara nuevaCara;
        for(int i=0; i < tamCaras; i++)
        {
            int indiceVertice;
            archivo >> indiceVertice;
            if (!archivo)
            {
                std::cout << "Error al leer los �ndices de una cara en el archivo " << nombreArchivo << "." << std::endl;
                return;
            }
            nuevaCara.agregarVertice(indiceVertice);
        }

        nuevoObjeto.agregarCara(nuevaCara);
    }

    if(tamCaras == -1)
    {
        std::cout << "Lectura Exitosa del archivo " << nombreArchivo << std::endl;
    }

    //Calcula las aristas del objeto
    nuevoObjeto.calcularAristas();
    //Agrega el objeto a memoria
    gestor.agregarObjeto(nuevoObjeto);
    if(gestor.verificarObjeto(meshName))
    {
        std::cout << "El objeto " << meshName << " fue cargado exitosamente." << std::endl;
    }
    else
    {
        std::cerr << "Error: El objeto " << meshName << " no se pudo cargar. "<< std::endl;
    }
}

// M�todo para listar objetos -- Muestra los objetos y su informacion cargados en memoria
void Sistema::listarObjetos()
{
    if (gestor.estaVacio())
    {
        std::cout << "Ningun objeto ha sido cargado en memoria." << std::endl;
    }
    else
    {
        gestor.mostrarObjetos();
    }
}

// M�todo para generar el envolvente de un objeto -- Crea el envolvente de un objeto
void Sistema::generarEnvolvente(const std::string& nombreObjeto)
{
    int puntos=2;

    //Obtener el objeto desde el gestor usando su nombre
    Objeto* objeto = gestor.obtenerObjeto(nombreObjeto);
    if (objeto == nullptr)
    {
        std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
        return;
    }

    //Obtener los v�rtices del objeto
    std::vector<Vertice> vertices = objeto->getVertices();
    if (vertices.empty())
    {
        std::cout << "El objeto " << nombreObjeto << " no tiene v�rtices." << std::endl;
        return;
    }

    //Inicializar los puntos m�nimos y m�ximos con el primer v�rtice
    Vertice pmin = vertices[0];
    Vertice pmax = vertices[0];

    //Iteraa sobre los v�rtices para encontrar los l�mites de la caja envolvente
    for (const auto& vertice : vertices)
    {
        if (vertice.getX() < pmin.getX()) pmin.setX(vertice.getX());
        if (vertice.getY() < pmin.getY()) pmin.setY(vertice.getY());
        if (vertice.getZ() < pmin.getZ()) pmin.setZ(vertice.getZ());

        if (vertice.getX() > pmax.getX()) pmax.setX(vertice.getX());
        if (vertice.getY() > pmax.getY()) pmax.setY(vertice.getY());
        if (vertice.getZ() > pmax.getZ()) pmax.setZ(vertice.getZ());
    }

    //Crear un nuevo objeto para la caja envolvente
    std::string nombreEnvolvente = "env_" + nombreObjeto;
    Objeto envolvente(nombreEnvolvente);

    //Agregar los puntos m�nimos y m�ximos como v�rtices de la envolvente
    envolvente.agregarVertice(pmin.getX(), pmin.getY(), pmin.getZ());
    envolvente.agregarVertice(pmax.getX(), pmax.getY(), pmax.getZ());
    envolvente.agregarPuntosObjeto(puntos);

    //Agregar la envolvente al gestor
    gestor.agregarObjeto(envolvente);
    std::cout << "La caja envolvente del objeto " << nombreObjeto << " se ha generado con el nombre " << nombreEnvolvente << " y se ha agregado a los objetos en memoria.\n" << std::endl;

    //Verificaci�n de los puntos m�ximos y minimos
    //envolvente.leerVertices();
}

// M�todo para generar el envolvente de todos los objetos -- Crea el envolvente que incluye todos los objetos en memoria
void Sistema::generarEnvolventeGlobal()
{
    int puntos=2;
    //Verifica que haya al menos un objeto en memoria
    if (gestor.estaVacio())
    {
        std::cout << "Ningun objeto ha sido cargado en memoria." << std::endl;
        return;
    }

    //Obtiene todos los v�rtices de todos los objetos en memoria
    std::vector<Vertice> vertices = gestor.obtenerTodosLosVertices();

    //Inicializar los puntos m�nimos y m�ximos con el primer v�rtice
    Vertice pmin = vertices[0];
    Vertice pmax = vertices[0];

    //Itera sobre los v�rtices para encontrar los l�mites de la caja envolvente global
    for (const auto& vertice : vertices)
    {
        if (vertice.getX() < pmin.getX()) pmin.setX(vertice.getX());
        if (vertice.getY() < pmin.getY()) pmin.setY(vertice.getY());
        if (vertice.getZ() < pmin.getZ()) pmin.setZ(vertice.getZ());

        if (vertice.getX() > pmax.getX()) pmax.setX(vertice.getX());
        if (vertice.getY() > pmax.getY()) pmax.setY(vertice.getY());
        if (vertice.getZ() > pmax.getZ()) pmax.setZ(vertice.getZ());
    }

    //Crear un nuevo objeto para la caja envolvente global
    std::string nombreEnvolvente = "env_global";
    Objeto envolvente(nombreEnvolvente);

    //Agregar los puntos m�nimos y m�ximos como v�rtices de la envolvente global
    envolvente.agregarVertice(pmin.getX(), pmin.getY(), pmin.getZ());
    envolvente.agregarVertice(pmax.getX(), pmax.getY(), pmax.getZ());
    envolvente.agregarPuntosObjeto(puntos);

    //Agregar la envolvente global al gestor
    gestor.agregarObjeto(envolvente);
    std::cout << "\nLa caja envolvente de los objetos en memoria se ha generado con el nombre "  << nombreEnvolvente <<" y se ha agregado a los objetos en memoria." << std::endl;
}

// M�todo para eliminar un objeto de sistema -- Elimina un objeto dado su nombre de memoria
void Sistema::descargarObjeto(const std::string& nombreObjeto)
{
    //Obtener el objeto desde el gestor usando su nombre
       Objeto* objeto = gestor.obtenerObjeto(nombreObjeto);
       if (objeto == nullptr)
       {
           std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
           return;
       }

    //Elimina el objeto dado su nombre
       bool bandera = gestor.descargarObjeto(nombreObjeto);
       if(bandera == true)
       {
           std::cout << "El objeto " << nombreObjeto << " ha sido eliminado de la memoria de trabajo." << std::endl;
       }
       else
       {
           std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
       }
}

// M�todo para guardar un objeto en un archivo .txt -- Crea un archivo.txt y guarda el objeto con su informaci�n
void Sistema::guardarObjeto(const std::string& nombreObjeto, const std::string& nombreArchivo)
{
    //Obtener el objeto desde el gestor usando su nombre
       Objeto* objeto = gestor.obtenerObjeto(nombreObjeto);
       if (objeto == nullptr)
       {
           std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
           return;
       }

       std::ofstream archivo(nombreArchivo);
       if (!archivo)
       {
           std::cerr << "Error al abrir el archivo " << nombreArchivo << " para escritura." << std::endl;
           return;
       }

    //Agrega la informacion al archivo
       archivo << nombreObjeto << std::endl;
       archivo << objeto->getCantidadVertices()<<std::endl;
	   std::vector<Vertice> vertices = objeto->getVertices();
       for (int i = 0; i < objeto->getCantidadVertices(); i++)
       {
           archivo << vertices[i].getX() << " " << vertices[i].getY() << " " << vertices[i].getZ() << std::endl;
       }
       for (const auto& cara : objeto->getCaras())
       {
           archivo << cara.getVertices().size()<< " ";
           for (const auto& indice : cara.getVertices())
           {
               archivo << indice << " ";
           }
           archivo << std::endl;
       }
       archivo << "-1" << std::endl;
       archivo.close();
       std::cout << "La informacion del objeto " << nombreObjeto << " ha sido guardada exitosamente en el archivo " << nombreArchivo << "." << std::endl;
}

// M�todo para obtener el vertice m�s cercano
void Sistema::verticeMasCercano(float px, float py, float pz, const std::string& nombreObjeto)
{
    /*
       Objeto* objeto = gestor.obtenerObjeto(nombreObjeto);
       if (objeto == nullptr)
       {
           std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
           return;
       }*/
}

// M�todo para obtener el vertice mas cercano global
void Sistema::verticeMasCercanoGlobal(float px, float py, float pz)
{
    if (gestor.estaVacio())
    {
        std::cout << "Ning�n objeto ha sido cargado en memoria." << std::endl;
    }
}

// M�todo para obtener el vertice mas cercano de la caja
void Sistema::verticesCercanosCaja(const std::string& nombreObjeto)
{
    Objeto* objeto = gestor.obtenerObjeto(nombreObjeto);
    if (objeto == nullptr)
    {
        std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
        return;
    }
}

// M�todo para encontrar la ruta corta de un objeto
void Sistema::rutaCorta(int i1, int i2, const std::string& nombreObjeto)
{
    Objeto* objeto = gestor.obtenerObjeto(nombreObjeto);
    if (objeto == nullptr)
    {
        std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
        return;
    }
}

// M�todo para encontrar la ruta corta al cento del objeto
void Sistema::rutaCortaCentro(int i1, const std::string& nombreObjeto)
{
    Objeto* objeto = gestor.obtenerObjeto(nombreObjeto);
    if (objeto == nullptr)
    {
        std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
        return;
    }
}

// M�todo para borrar pantalla
void Sistema::borrarPantalla()
{

    system("cls");
}

