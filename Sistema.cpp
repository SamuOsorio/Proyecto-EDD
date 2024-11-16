/*
Proyecto Estructura de Datos 24-3
Samuel Osorio R, Gabriel Camacho
Tomas Ospina e Ivan Cortés
*/

#include "Sistema.h"
#include "Objeto.h"
#include "GestorObjetos.h"
#include "Comando.h"
#include "ArbolKD.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>
#include <queue>
#include <unordered_map>

// Constructor
Sistema::Sistema()
{
    cargarComandos("comandos.txt");
}

// Método para cargar comando -- lee los comandos desde el archivo y almacenarlos en un vector
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

// Método para procesar comando -- Procesa un comando introducido por consolo por el usuario
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
            std::cerr << "\nError: Faltan las coordenadas (px, py, pz) para el vertice más cercano.\n" << std::endl;
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

// Método para mostrar ayuda de los comandos -- Muestra lista de comandos disponibles y su descripción
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
    std::cout << "  1. Si se ingresa con las coordenadas <px> <py> <pz> y el nombre del objeto <nombre_objeto>, identifica el vertice más cercano de ese objeto especifico al punto dado" << std::endl;
    std::cout << "  2. Si se ingresa solo con las coordenadas `<px> <py> <pz>`, identifica el vertice mas cercano entre todos los objetos cargados en memoria al punto dado.\n" << std::endl;
}

// Método para listar comandos -- Lista los nombres de los comandos disponibles
void Sistema::listarComandos()
{
    std::cout << "\nLista de comandos disponibles: \n" << std::endl;
    for (const auto& comando : comandos)
    {
        std::cout << comando.getNombre() << std::endl;
    }
}


// Método para cargar archivo -- Carga objeto 3D desde un archivo de texto con todas sus caracteristicas
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

        nuevoObjeto.agregarVertice(x,y,z);

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
                std::cout << "Error al leer los índices de una cara en el archivo " << nombreArchivo << "." << std::endl;
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

    ArbolKD* nuevoArbol = new ArbolKD(nuevoObjeto.getVertices());
    arbolesKD[nuevoObjeto.getNombreMalla()] = nuevoArbol;
}

// Método para listar objetos -- Muestra los objetos y su informacion cargados en memoria
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

// Método para generar el envolvente de un objeto -- Crea el envolvente de un objeto
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

    //Obtener los vértices del objeto
    std::vector<Vertice> vertices = objeto->getVertices();
    if (vertices.empty())
    {
        std::cout << "El objeto " << nombreObjeto << " no tiene vértices." << std::endl;
        return;
    }

    //Inicializar los puntos mínimos y máximos con el primer vértice
    Vertice pmin = vertices[0];
    Vertice pmax = vertices[0];

    //Iteraa sobre los vértices para encontrar los límites de la caja envolvente
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

    //Agregar los puntos mínimos y máximos como vértices de la envolvente
    envolvente.agregarVertice(pmin.getX(), pmin.getY(), pmin.getZ());
    envolvente.agregarVertice(pmax.getX(), pmax.getY(), pmax.getZ());
    envolvente.agregarPuntosObjeto(puntos);

    //Agregar la envolvente al gestor
    gestor.agregarObjeto(envolvente);
    std::cout << "La caja envolvente del objeto " << nombreObjeto << " se ha generado con el nombre " << nombreEnvolvente << " y se ha agregado a los objetos en memoria.\n" << std::endl;

    //Verificación de los puntos máximos y minimos
    //envolvente.leerVertices();
}

// Método para generar el envolvente de todos los objetos -- Crea el envolvente que incluye todos los objetos en memoria
void Sistema::generarEnvolventeGlobal()
{
    int puntos=2;
    //Verifica que haya al menos un objeto en memoria
    if (gestor.estaVacio())
    {
        std::cout << "Ningun objeto ha sido cargado en memoria." << std::endl;
        return;
    }

    //Obtiene todos los vértices de todos los objetos en memoria
    std::vector<Vertice> vertices = gestor.obtenerTodosLosVertices();

    //Inicializar los puntos mínimos y máximos con el primer vértice
    Vertice pmin = vertices[0];
    Vertice pmax = vertices[0];

    //Itera sobre los vértices para encontrar los límites de la caja envolvente global
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

    //Agregar los puntos mínimos y máximos como vértices de la envolvente global
    envolvente.agregarVertice(pmin.getX(), pmin.getY(), pmin.getZ());
    envolvente.agregarVertice(pmax.getX(), pmax.getY(), pmax.getZ());
    envolvente.agregarPuntosObjeto(puntos);

    //Agregar la envolvente global al gestor
    gestor.agregarObjeto(envolvente);
    std::cout << "\nLa caja envolvente de los objetos en memoria se ha generado con el nombre "  << nombreEnvolvente <<" y se ha agregado a los objetos en memoria." << std::endl;
}

// Método para eliminar un objeto de sistema -- Elimina un objeto dado su nombre de memoria
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

// Método para guardar un objeto en un archivo .txt -- Crea un archivo.txt y guarda el objeto con su información
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

// Método para obtener el vertice más cercano
void Sistema::verticeMasCercano(float px, float py, float pz, const std::string& nombreObjeto)
{
    Objeto* objeto = gestor.obtenerObjeto(nombreObjeto);
    if (objeto == nullptr)
    {
        std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
        return;
    }

    // Verificar si existe el árbol KD asociado al objeto
    auto it = arbolesKD.find(nombreObjeto);
    if (it == arbolesKD.end()) {
        std::cerr << "El árbol KD para el objeto " << nombreObjeto << " no existe." << std::endl;
        return;
    }

    // Crear el punto de búsqueda
    Vertice punto(px, py, pz);

    // Obtener el árbol KD y buscar el vértice más cercano
    ArbolKD* arbol = it->second;
    Vertice* verticeCercano = arbol->VerticeMasCercano(punto, nombreObjeto);

    if (verticeCercano != nullptr) {
        // Obtener la distancia
        float distancia = arbol->distanciaEuclidiana(punto, *verticeCercano);

        // Verificar si el vértice se encuentra en los datos del objeto
        Objeto* objeto = gestor.obtenerObjeto(nombreObjeto);
        if (objeto == nullptr) {
            std::cerr << "El objeto " << nombreObjeto << " no existe en memoria." << std::endl;
            return;
        }

        // Encontrar el índice del vértice en el vector de vértices del objeto
        const std::vector<Vertice>& vertices = objeto->getVertices();
        auto itVertice = std::find_if(vertices.begin(), vertices.end(), [&](const Vertice& v) {
            return v.getX() == verticeCercano->getX() &&
                   v.getY() == verticeCercano->getY() &&
                   v.getZ() == verticeCercano->getZ();
        });

        if (itVertice != vertices.end()) {
            int indice = std::distance(vertices.begin(), itVertice);
            // Mostrar el mensaje correcto
            std::cout << "El vertice " << indice
                      << " (" << verticeCercano->getX() << ", " << verticeCercano->getY() << ", " << verticeCercano->getZ()
                      << ") del objeto " << nombreObjeto << " es el mas cercano al punto ("
                      << px << ", " << py << ", " << pz
                      << "), a una distancia de " << distancia << "." << std::endl;
        } else {
            std::cerr << "No se encontró el índice del vértice más cercano en el objeto " << nombreObjeto << "." << std::endl;
        }
    } else {
        std::cerr << "No se encontró un vértice cercano en el objeto " << nombreObjeto << "." << std::endl;
    }
}

// Método para obtener el vertice mas cercano global
void Sistema::verticeMasCercanoGlobal(float px, float py, float pz)
{
    if (gestor.estaVacio())
    {
        std::cout << "Ningun objeto ha sido cargado en memoria." << std::endl;
    }

    if (arbolesKD.empty())
    {
        std::cout << "No hay árboles KD cargados." << std::endl;
        return;
    }

    Vertice punto(px, py, pz);
    Vertice* mejorVertice = nullptr;
    float mejorDistancia = std::numeric_limits<float>::max();
    std::string nombreObjetoCercano;
    int indiceVertice = -1;

    for (auto& par : arbolesKD)
    {
        ArbolKD* arbol = par.second;
        Vertice* verticeCercano = arbol->VerticeMasCercano(punto, par.first);
        if (verticeCercano != nullptr)
        {
            float distancia = arbol->distanciaEuclidiana(punto, *verticeCercano);
            if (distancia < mejorDistancia)
            {
                mejorDistancia = distancia;
                mejorVertice = verticeCercano;
                nombreObjetoCercano = par.first;
                indiceVertice = verticeCercano->getIndex();
            }
        }
    }

    if (mejorVertice != nullptr)
    {
        std::cout << "El vertice " << indiceVertice
                  << " (" << mejorVertice->getX() << ", " << mejorVertice->getY() << ", "
                  << mejorVertice->getZ() << ") del objeto " << nombreObjetoCercano
                  << " es el mas cercano al punto (" << px << ", " << py << ", " << pz
                  << "), a una distancia de " << mejorDistancia << "." << std::endl;
    }
    else
    {
        std::cout << "No se encontraron vértices cercanos." << std::endl;
    }
}

// Método para obtener el vertice mas cercano de la caja
void Sistema::verticesCercanosCaja(const std::string& nombreObjeto)
{
    // Obtener el objeto desde el gestor usando su nombre
    Objeto* objeto = gestor.obtenerObjeto(nombreObjeto);
    if (objeto == nullptr)
    {
        std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
        return;
    }

    // Obtener los vértices del objeto
    std::vector<Vertice> vertices = objeto->getVertices();
    if (vertices.empty())
    {
        std::cout << "El objeto " << nombreObjeto << " no tiene vertices." << std::endl;
        return;
    }

    // Inicializar los puntos mínimos y máximos con el primer vértice
    Vertice pmin = vertices[0];
    Vertice pmax = vertices[0];

    // Iterar sobre los vértices para encontrar los límites de la caja envolvente
    for (const auto& vertice : vertices)
    {
        if (vertice.getX() < pmin.getX()) pmin.setX(vertice.getX());
        if (vertice.getY() < pmin.getY()) pmin.setY(vertice.getY());
        if (vertice.getZ() < pmin.getZ()) pmin.setZ(vertice.getZ());

        if (vertice.getX() > pmax.getX()) pmax.setX(vertice.getX());
        if (vertice.getY() > pmax.getY()) pmax.setY(vertice.getY());
        if (vertice.getZ() > pmax.getZ()) pmax.setZ(vertice.getZ());
    }

    // Crear un nuevo objeto para la caja envolvente
    std::string nombreEnvolvente = "env_" + nombreObjeto;
    Objeto envolvente(nombreEnvolvente);

    // Agregar los puntos mínimos y máximos como vértices de la envolvente
    envolvente.agregarVertice(pmin.getX(), pmin.getY(), pmin.getZ());
    envolvente.agregarVertice(pmax.getX(), pmax.getY(), pmax.getZ());

    // Agregar la envolvente al gestor
    gestor.agregarObjeto(envolvente);
    std::cout << "La caja envolvente del objeto " << nombreObjeto << " se ha generado con el nombre " << nombreEnvolvente << " y se ha agregado a los objetos en memoria.\n" << std::endl;

    // Obtener los vértices de la envolvente
    std::vector<Vertice> verticesEnvolvente = envolvente.getVertices();
    if (verticesEnvolvente.empty())
    {
        std::cout << "La envolvente no tiene vértices." << std::endl;
        return;
    }

    std::cout << "Los vertices del objeto " << nombreObjeto << " mas cercanos a las esquinas de su caja envolvente son:\n";
    std::cout << "Esquina         Vertice        Distancia\n";

    // Iterar sobre los vértices del objeto original para encontrar el vértice más cercano en la envolvente
    int contadorEsquina = 0;
    for (const auto& vertice : vertices)
    {
        Vertice* verticeCercano = nullptr;
        float distanciaMinima = std::numeric_limits<float>::max();
        int indiceCercano = -1;

        for (int i = 0; i < verticesEnvolvente.size(); i++)
        {
            float dx = vertice.getX() - verticesEnvolvente[i].getX();
            float dy = vertice.getY() - verticesEnvolvente[i].getY();
            float dz = vertice.getZ() - verticesEnvolvente[i].getZ();
            float distancia = sqrt((dx * dx) + (dy * dy) + (dz * dz));


            if (distancia < distanciaMinima)
            {
                distanciaMinima = distancia;
                verticeCercano = &verticesEnvolvente[i];
                indiceCercano = i;
            }
        }

        if (verticeCercano != nullptr)
        {
            std::cout << contadorEsquina + 1 << " (" << verticeCercano->getX() << ", " << verticeCercano->getY()<< ", " << verticeCercano->getZ()
                      << ")     " << indiceCercano << " (" << vertice.getX() << ", " << vertice.getY()
                      << ", " << vertice.getZ()<< ")     " << distanciaMinima << "\n";

            //delete verticeCercano; // Liberar memoria
        }
        contadorEsquina++;
    }
}


// Método para encontrar la ruta corta de un objeto
void Sistema::rutaCorta(int i1, int i2, const std::string& nombreObjeto)
{
    Objeto* objeto = gestor.obtenerObjeto(nombreObjeto);
    if (objeto == nullptr)
    {
        std::cout << "El objeto " << nombreObjeto
                  << " no ha sido cargado en memoria." << std::endl;
        return;
    }

    int numVertices = objeto->getCantidadVertices();

    // Validaciones iniciales
    if (i1 == i2)
    {
        std::cout << "Los indices de los vertices dados son iguales."
                  << std::endl;
        return;
    }

    if (i1 < 0 || i1 >= numVertices || i2 < 0 || i2 >= numVertices)
    {
        std::cout << "Algunos de los indices de vertices estan fuera de rango para el objeto "
                  << nombreObjeto << "." << std::endl;
        return;
    }

    // Estructuras para Dijkstra
    std::vector<float> distancias(numVertices, std::numeric_limits<float>::max());
    std::vector<int> predecesor(numVertices, -1);
    std::vector<bool> visitado(numVertices, false);
    distancias[i1] = 0;

    // Cola de prioridad
    using Nodo = std::pair<float, int>;
    std::priority_queue<Nodo, std::vector<Nodo>, std::greater<Nodo>> cola;
    cola.push({0, i1});

    const std::vector<Arista>& aristas = objeto->getAristas();

    // Algoritmo de Dijkstra
    while (!cola.empty())
    {
        int u = cola.top().second;
        cola.pop();

        if (visitado[u]) continue;
        visitado[u] = true;

        if (u == i2) break;

        for (const auto& arista : aristas)
        {
            int v1_index = arista.getIndiceV1();
            int v2_index = arista.getIndiceV2();

            // Validar índices
            if (v1_index < 0 || v1_index >= numVertices ||
                    v2_index < 0 || v2_index >= numVertices)
            {
                continue;
            }

            // Determinar el vértice destino
            int v = -1;
            if (v1_index == u) v = v2_index;
            else if (v2_index == u) v = v1_index;
            else continue;

            if (visitado[v]) continue;

            const Vertice& v1 = objeto->getVertices()[v1_index];
            const Vertice& v2 = objeto->getVertices()[v2_index];
            float distanciaUV = Objeto::distanciaEuclidiana(v1, v2);
            float nuevaDistancia = distancias[u] + distanciaUV;

            if (nuevaDistancia < distancias[v])
            {
                distancias[v] = nuevaDistancia;
                predecesor[v] = u;
                cola.push({distancias[v], v});
            }
        }
    }

    // Verificar si se encontró una ruta
    if (distancias[i2] == std::numeric_limits<float>::max())
    {
        std::cout << "No se encontro una ruta entre los vertices "
                  << i1 << " y " << i2 << " en el objeto " << nombreObjeto
                  << "." << std::endl;
        return;
    }

    // Reconstruir la ruta
    std::vector<int> ruta;
    for (int v = i2; v != -1; v = predecesor[v])
    {
        ruta.push_back(v);
    }
    std::reverse(ruta.begin(), ruta.end());

    // Mostrar resultado
    std::cout << "La ruta mas corta que conecta los vertices "
              << i1 << " y " << i2 << " del objeto " << nombreObjeto << " pasa por: ";
    for (size_t i = 0; i < ruta.size(); ++i)
    {
        std::cout << ruta[i];
        if (i != ruta.size() - 1) std::cout << " , ";
    }
    std::cout << "; con una longitud de " << std::fixed << std::setprecision(2)
              << distancias[i2] << "." << std::endl;
}

// Método para encontrar la ruta corta al cento del objeto
void Sistema::rutaCortaCentro(int i1, const std::string& nombreObjeto)
{
    // Verificar existencia del objeto
    Objeto* objeto = gestor.obtenerObjeto(nombreObjeto);
    if (objeto == nullptr)
    {
        std::cout << "El objeto " << nombreObjeto
                  << " no ha sido cargado en memoria." << std::endl;
        return;
    }

    int numVertices = objeto->getCantidadVertices();

    // Validar índice de entrada
    if (i1 < 0 || i1 >= numVertices)
    {
        std::cout << "El indice de vertice esta fuera de rango para el objeto "
                  << nombreObjeto << "." << std::endl;
        return;
    }

    try
    {
        // Calcular el centroide
        Vertice centroide = objeto->calcularCentroide();

        // Encontrar el vértice más cercano al centroide
        int indiceCercano = objeto->encontrarVerticeMasCercano(centroide);

        // Agregar temporalmente el centroide como un nuevo vértice
        int indiceCentroide = objeto->getCantidadVertices();
        objeto->agregarVertice(centroide.getX(), centroide.getY(), centroide.getZ());

        // Crear una arista temporal entre el centroide y el vértice más cercano
        Arista aristaTemporal(indiceCercano, indiceCentroide);
        objeto->agregarArista(aristaTemporal);

        // Estructuras para Dijkstra
        std::vector<float> distancias(numVertices + 1, std::numeric_limits<float>::max());
        std::vector<int> predecesor(numVertices + 1, -1);
        std::vector<bool> visitado(numVertices + 1, false);
        distancias[i1] = 0;

        // Cola de prioridad
        using Nodo = std::pair<float, int>;
        std::priority_queue<Nodo, std::vector<Nodo>, std::greater<Nodo>> cola;
        cola.push({0, i1});

        // Ejecutar Dijkstra
        while (!cola.empty())
        {
            int u = cola.top().second;
            cola.pop();

            if (visitado[u]) continue;
            visitado[u] = true;

            if (u == indiceCentroide) break;

            for (const auto& arista : objeto->getAristas())
            {
                int v1_index = arista.getIndiceV1();
                int v2_index = arista.getIndiceV2();

                int v = (v1_index == u) ? v2_index : (v2_index == u ? v1_index : -1);
                if (v == -1 || visitado[v]) continue;

                float distanciaUV = Objeto::distanciaEuclidiana(
                                        objeto->getVertices()[v1_index],
                                        objeto->getVertices()[v2_index]
                                    );
                float nuevaDistancia = distancias[u] + distanciaUV;

                if (nuevaDistancia < distancias[v])
                {
                    distancias[v] = nuevaDistancia;
                    predecesor[v] = u;
                    cola.push({distancias[v], v});
                }
            }
        }

        // Reconstruir la ruta
        std::vector<int> ruta;
        for (int v = indiceCentroide; v != -1; v = predecesor[v])
        {
            ruta.push_back(v);
        }
        std::reverse(ruta.begin(), ruta.end());

        // Mostrar resultado
        std::cout << "La ruta mas corta que conecta el vertice "
                  << i1 << " con el centro del objeto " << nombreObjeto
                  << ", ubicado en ct (" << centroide.getX() << ", "
                  << centroide.getY() << ", " << centroide.getZ() << "), pasa por: ";

        for (size_t i = 0; i < ruta.size(); ++i)
        {
            if (ruta[i] == indiceCentroide)
            {
                std::cout << "ct";
            }
            else
            {
                std::cout << ruta[i];
            }
            if (i != ruta.size() - 1) std::cout << " , ";
        }

        std::cout << "; con una longitud de " << std::fixed << std::setprecision(2)
                  << distancias[indiceCentroide] << "." << std::endl;

        // Eliminar el vértice y arista temporal
        objeto->eliminarVertice(indiceCentroide);
        objeto->eliminarArista(aristaTemporal);

    }
    catch (const std::exception& e)
    {
        std::cerr << "Error al calcular la ruta: " << e.what() << std::endl;
    }
}

// Método para borrar pantalla
void Sistema::borrarPantalla()
{

    system("cls");
}
