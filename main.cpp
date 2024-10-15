/*
Angelo Segura Ibarra
14/10/2024
*/


#include <iostream>  
#include <string> 
#include "cancion.h"
#include "AVL.h" 
#include <sstream>
#include <limits>
#include <fstream>

int main() { 

    AVL<Cancion> arbol;

    std::ifstream archivo("Lista_canciones.txt");  // Abrimos el archivo a leer   
    if(archivo.is_open()){
        std::string linea;
        // Saltar la primera línea de encabezado
        std::getline(archivo, linea);

        // Leer cada línea del archivo
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string nombre, artista, genero;
            float vistas, duracion;
            int lanzamiento;

            // Leer y separar los valores para seleccionar nuestros atributos 
            std::getline(ss, nombre, ',');
            std::getline(ss, artista, ',');
            std::getline(ss, genero, ',');
            ss >> vistas; ss.ignore(1);  // Leer vistas y saltar la coma
            ss >> lanzamiento; ss.ignore(1);  
            ss >> duracion;  

            // Crear un objeto Cancion usando el constructor 
            Cancion cancion(nombre, artista, genero, vistas, lanzamiento, duracion);
            arbol.agregar_cancion(cancion); 
        }

        archivo.close();  
    }
    else {
        std::cout << "Error al abrir el archivo" << std::endl; 
        // en caso de no poder abrir el archivo
        return 1; 
    }

    int option=0;
    int menu=1;
    while(menu==1)
    {
        std::cout << " " << std::endl;
        std::cout << "Registro de canciones" << std::endl;
        std::cout << "Menu: " << std::endl;
        std::cout << "1. Mostrar listado de canciones." << std::endl;
        std::cout << "2. Agregar cancion." << std::endl;
        std::cout << "3. Buscar cancion. " << std::endl;
        std::cout << "5. Salir del programa" << std:: endl;
        std::cout << "Elija una opcion : " ;

        std::cin >> option;

        if (option == 1)
        {
            std::cout << "Listado de canciones de tu dispositivo: " << std::endl;
            std::cout<< arbol.inorder() << endl;
        }

        else if (option == 2)
        {
            std::string nombre,artista,genero;
            float duracion,vistas;
            int lanzamiento;
            int fin=1;

            while ( fin == 1 )
            {
            std::cout << "Artista, autor de la cancion: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, artista);
            std::cout << "Nombre de la cancion: " << std::endl;
            std::getline(std::cin, nombre); 
            std::cout << "Genero musical de la cancion: " << std::endl;
            std::getline(std::cin, genero);
            std::cout << "Duracion de la cancion (min): " << std::endl;
            std::cin >> duracion;
            std::cout << "Numero de vistas de la cancion: " << std::endl;
            std::cin >> vistas;
            std::cout << "Fecha de lanzamiento de la cancion: " << std::endl;
            std::cin >> lanzamiento;
            arbol.agregar_cancion(Cancion(nombre,artista,genero,duracion,
            vistas,lanzamiento));
            std::cout << "Cancion agregada." << std::endl; 
            std::cout << "Deseas seguir agregando peliculas? (si=1 / no=0): ";
            std::cin >> fin;
            }
        }
        else if (option == 3) {
            // Buscar una canción por nombre
            int opcion = 1;

            while (opcion == 1) {
                std::string nom_buscado;

                std::cout << "BUSCAR CANCION" << std::endl;
                std::cout << "Introduce el nombre de la cancion: ";

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignorar entrada previa
                std::getline(std::cin, nom_buscado); 
                
                std::string resultado = arbol.encontrar_cancion(nom_buscado);
                std::cout << resultado << std::endl;  // Se imprime el resultado de la búsqueda

                std::cout << "Deseas seguir buscando? (si=1 / no=0): ";
                while (!(std::cin >> opcion) || (opcion != 0 && opcion != 1)) {
                    std::cin.clear();  // Limpiar el estado de error de cin
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Limpiar el buffer
                    std::cout << "Opción no válida, intenta nuevamente (si=1 / no=0): ";
                }
            }
        }
        else if (option == 5)
        {
            menu=0;
        }
    }


    return 0;
};
