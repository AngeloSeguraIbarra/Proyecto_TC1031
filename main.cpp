#include <iostream>  
#include <string> 
#include "cancion.h"
#include "sorts.h"
#include <vector>

int main() {
    // Crear un objeto de la clase Cancion
    Cancion cancion;

    // Leer las canciones desde un archivo (suponiendo que el archivo es "canciones.txt")
    std::vector<Cancion> canciones = cancion.leerCancionesDesdeArchivo("Lista_canciones.txt");

    Sorts<Cancion> sorter;
    sorter.ordena_duracion(canciones);

    // Imprimir las canciones ordenadas
    std::cout << "Canciones ordenadas por duración:" << std::endl;
    for (auto& c : canciones) {
        c.print();
        std::cout << "-------------------" << std::endl;    
    }

        sorter.ordena_lanzamiento(canciones);

    // Imprimir las canciones ordenadas
    std::cout << "Canciones ordenadas por lanzamiento:" << std::endl;
    for (auto& c : canciones) {
        c.print();
        std::cout << "-------------------" << std::endl;    
    }

        sorter.ordena_vistas(canciones);

    // Imprimir las canciones ordenadas
    std::cout << "Canciones ordenadas por popularidad:" << std::endl;
    for (auto& c : canciones) {
        c.print();
        std::cout << "-------------------" << std::endl;    
    }
        sorter.ordena_nombre(canciones);

    // Imprimir las canciones ordenadas
    std::cout << "Canciones ordenadas por nombre:" << std::endl;
    for (auto& c : canciones) {
        c.print();
        std::cout << "-------------------" << std::endl;    
    }


    return 0;
};
