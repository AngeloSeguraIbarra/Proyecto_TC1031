#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include "inventario.h"
#include "cancion.h"
#include "AVL.h"

// Función para guardar el inventario de canciones en un archivo
void guardarEnArchivo(const Inventario& inventario, const std::string& nombreArchivo) {
    std::ofstream archivo_salida(nombreArchivo);
    if (!archivo_salida.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir el inventario." << std::endl;
        return;
    }

    // Escribir encabezado
    archivo_salida << "Titulo,Artista,Genero,Vistas,Lanzamiento,Duracion\n";

    // Recorrer todas las canciones y escribir cada una en el archivo
    for (const auto& cancion : inventario.getCanciones()) { 
        archivo_salida << cancion.get_nombre() << ","
                       << cancion.get_artista() << ","
                       << cancion.get_genero() << ","
                       << cancion.get_vistas() << ","
                       << cancion.get_lanzamiento() << ","
                       << cancion.get_duracion() << "\n";
    }

    archivo_salida.close();
    std::cout << "Inventario guardado en el archivo con exito." << std::endl;
}

int main() {
    Inventario inventario;
    AVL<Cancion> arbolCanciones;  // Árbol AVL de canciones
    int opcion;
    bool continuar = true;

    // Leer canciones desde archivo al inicio y agregar al inventario y AVL
    std::ifstream archivo_entrada("Lista_canciones.txt");
    if (archivo_entrada.is_open()) {
        std::string linea;
        std::getline(archivo_entrada, linea); // Saltar encabezado

        while (std::getline(archivo_entrada, linea)) {
            std::stringstream ss(linea);
            std::string nombre, artista, genero;
            float vistas, duracion;
            int lanzamiento;

            std::getline(ss, nombre, ',');
            std::getline(ss, artista, ',');
            std::getline(ss, genero, ',');
            ss >> vistas; ss.ignore(1);
            ss >> lanzamiento; ss.ignore(1);
            ss >> duracion;

            Cancion cancion(nombre, artista, genero, vistas, lanzamiento, duracion);
            inventario.agregarCancion(cancion);
            arbolCanciones.agregar_cancion(cancion);
        }

        archivo_entrada.close();
        std::cout << "Canciones cargadas desde archivo." << std::endl;
    } else {
        std::cout << "No se pudo abrir el archivo de canciones." << std::endl;
    }

    // Menú principal
    while (continuar) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Agregar cancion.\n";
        std::cout << "2. Mostrar inventario de canciones.\n";
        std::cout << "3. Buscar cancion.\n";
        std::cout << "4. Guardar inventario en archivo.\n";
        std::cout << "5. Salir.\n";
        std::cout << "Elija una opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            std::string nombre, artista, genero;
            float vistas, duracion;
            int lanzamiento;

            std::cout << "Introduce el nombre de la cancion: ";
            std::cin.ignore();
            std::getline(std::cin, nombre);

            std::cout << "Introduce el artista de la cancion: ";
            std::getline(std::cin, artista);

            std::cout << "Introduce el genero de la cancion: ";
            std::getline(std::cin, genero);

            std::cout << "Introduce el numero de vistas (en miles): ";
            std::cin >> vistas;

            std::cout << "Introduce el año de lanzamiento: ";
            std::cin >> lanzamiento;

            std::cout << "Introduce la duracion en minutos: ";
            std::cin >> duracion;

            Cancion nuevaCancion(nombre, artista, genero, vistas, lanzamiento, duracion);
            inventario.agregarCancion(nuevaCancion);
            arbolCanciones.agregar_cancion(nuevaCancion);  // Agregar al AVL también
            std::cout << "Cancion agregada exitosamente." << std::endl;
        }
        else if (opcion == 2) {
            std::cout << "Inventario de canciones:" << std::endl;
            inventario.mostrarCanciones();
        }
        else if (opcion == 3) {
            std::string nombre;
            std::cout << "Introduce el nombre de la cancion a buscar: ";
            std::cin.ignore();
            std::getline(std::cin, nombre);

            // Buscar en el AVL
            std::string resultado = arbolCanciones.encontrar_cancion(nombre);
            std::cout << resultado << std::endl;
        }
        else if (opcion == 4) {
            guardarEnArchivo(inventario, "Lista_canciones.txt");
        }
        else if (opcion == 5) {
            continuar = false;
        }
        else {
            std::cout << "Opcion invalida, intenta nuevamente." << std::endl;
        }
    }

    return 0;
}
