#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include "inventario.h"
#include "cancion.h"
#include "AVL.h"

class NoSuchElement : public std::exception 
{
    public:
        const char* what() const noexcept override {
            return "Elemento no encontrado.";
        }
};

// Función para guardar el inventario de canciones en un archivo
void guardarEnArchivo(const Inventario& inventario,
 const std::string& nombreArchivo) {
    std::ofstream archivo_salida(nombreArchivo);
    if (!archivo_salida.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir el inventario."
         << std::endl;
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

            Cancion cancion(nombre, artista, genero, vistas, lanzamiento
            , duracion);
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
        std::cout << "5. Ordenar Inventario. " << std::endl;
        std::cout << "6. Eliminar cancion. " << std::endl;
        std::cout << "7. Salir.\n";
        std::cout << "Elija una opcion: (solo ingrese numeros)";
        std::cin >> opcion;

        if (opcion == 1) {
            std::string nombre, artista, genero;
            float vistas, duracion;
            int lanzamiento;

            std::cout<<"Una vez agregada la cancion guarda el inventario"<<endl;
            std::cout << "Introduce el nombre de la cancion(ej.: Sin ti ) : ";
            std::cin.ignore();
            std::getline(std::cin, nombre);

            std::cout << "Introduce el artista de la cancion(ej.: Fidel): ";
            std::getline(std::cin, artista);

            std::cout << "Introduce el genero de la cancion(ej.: regional): ";
            std::getline(std::cin, genero);

            std::cout << "Introduce el numero de vistas (en miles, eje.: 20):";
            std::cin >> vistas;

            std::cout << "Introduce el año de lanzamiento(eje.: 2025): ";
            std::cin >> lanzamiento;

            std::cout << "Introduce la duracion en minutos(eje,: 3): ";
            std::cin >> duracion;

            Cancion nuevaCancion(nombre, artista, genero, vistas, lanzamiento
            , duracion);
            inventario.agregarCancion(nuevaCancion);
            arbolCanciones.agregar_cancion(nuevaCancion);  // Agregar al AVL también
            std::cout << "Cancion agregada exitosamente." << std::endl;
        }
        else if (opcion == 2) {
            std::cout << "Inventario de canciones:" << std::endl;
            std::cout << arbolCanciones.inorder(); 
        }
        else if (opcion == 3) {
            std::string nombre;
            std::cout << 
            "Introduce el nombre de la cancion a buscar(ej.:Solo me dejaste):";
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
                int criterio;
                std::cout << "\nORDENAR Canciones\n";
                std::cout << 
                "Elige el criterio de ordenamiento: (ingresa solo el numero)" 
                << std::endl;
                std::cout << "1. Por nombre." << std::endl;
                std::cout << "2. Por duracion." << std::endl;
                std::cout << "3. Por ano de lanzamiento." << std::endl;
                std::cin >> criterio;

                if (criterio == 1)
                {
                    inventario.ordena_nombre();
                    std::cout << "Canciones ordenadas por nombre:"<< std::endl;
                    inventario.mostrarCanciones();
                }
                else if (criterio == 2)
                {
                    inventario.ordena_duracion();
                    std::cout << "Canciones ordenadas por Duracion:"<<std::endl;
                    inventario.mostrarCanciones();
                }
                else if (criterio == 3)
                {
                    inventario.ordena_lanzamiento();
                    std::cout<<"Canciones ordenadas por Lanzamiento:"<<std::endl;
                    inventario.mostrarCanciones();
                }
                else
                {
                    std::cout << "Criterio invalido." << std::endl;
                } 
        }
        else if (opcion == 6) {
            std::string eliminar;

            std::cout << "\nELIMINAR Cancion\n";
            std::cout << "\nRecuerda! Si eliminas una cancion,";
            std::cout <<"no se actulizará el archivo de inventario,";
            std::cout << "por lo tanto después de eliminar una cancion,";
            std::cout <<" ingresa la opción 4 en el menu.";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Introduce el nombre de la cancion a eliminar";
            std::cout <<"(ej.: solo me dejaste): ";
            std::getline(std::cin, eliminar);  

            if (eliminar.empty()) 
            {
                std::cout << "Error: No se ingreso ningun nombre.";
                std::cout << "Intentalo nuevamente." << std::endl;
            } 
            else 
            {
                std::cout << "\nEliminando la cancion \"" << eliminar << "\"..."
                 << std::endl;
                Cancion cancionaEliminar(eliminar, "", "", 0, 0, 0.0);

                try 
                {
                    arbolCanciones.remove(cancionaEliminar);
                    inventario.eliminarCancion(eliminar);
                    std::cout << "La cancion \"" << eliminar << "\" fue eliminada."
                    << std::endl;
                } 
                catch (NoSuchElement& e) 
                {
                    std::cout << "No se pudo eliminar la pelicula \"" << eliminar 
                    << "\" porque no se encontro." << std::endl;
                }
            }

        }
        else if (opcion == 7) {
            continuar = false;
        }
        else {
            std::cout << "Opcion invalida, intenta nuevamente." << std::endl;
        }
    }

    return 0;
}
