/*** Angelo segura Ibarra
    A01711723
    Fecha:18/09/2024
***/
#include <iostream>  
#include <string> 
#include "cancion.h"
#include "sorts.h" 
#include <vector>
#include <sstream>
#include <limits>
#include <fstream>

int main() {

    Sorts sorter;

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

        // Leer y separar los valores para seleccionar nuestrosa atributos 
        std::getline(ss, nombre, ',');
        std::getline(ss, artista, ',');
        std::getline(ss, genero, ',');
        ss >> vistas; ss.ignore(1);  // Leer vistas y saltar la coma
        ss >> lanzamiento; ss.ignore(1);  
        ss >> duracion;  

        // Crear un objeto Cancion usando el constructor 
        Cancion cancion(nombre, artista, genero, vistas, lanzamiento, duracion);
        sorter.agregar_cancion(cancion);  // Agregamos todo al vevtor
    }

    archivo.close();  
    }
    else{
        std::cerr << "Error al abrir el archivo" << std::endl; 
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
        std::cout << "3. Ordenar inventario. " << std::endl;
        std::cout << "4. Buscar cancion. " << std::endl;
        std::cout << "5. Salir del programa" << std:: endl;
        std::cout << "Elija una opcion : " ;

        std::cin >> option;

        if (option == 1)
        {
            std::cout << "Listado de canciones de tu dispositivo: " << std::endl;
            sorter.mostrar_lista();
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
            sorter.agregar_cancion(Cancion(nombre,artista,genero,duracion,
            vistas,lanzamiento));
            std::cout << "Cancion agregada." << std::endl; 
            std::cout << "Deseas seguir agregando peliculas? (si=1 / no=0): ";
            std::cin >> fin;
            }
        }

        else if (option == 3)
        {
            int opcion=1;
            int option;
            while (opcion == 1 )
            {
            std::cout << "Como quieres ordenar el inventario: " << std::endl;
            std::cout << "1. Por orden alfabetico." << std::endl;
            std::cout << "2. Por artista" << std::endl;
            std::cout << "3. Por genero musical." << std::endl;
            std::cout << "4. Por duracion de la cancion(min). " << std::endl;
            std::cout << "5. Por popularidad " << std::endl;
            std::cout << "6. Por fecha de lanzamiento" << std::endl;
            std::cout << "Elija una opcion : " ;

            std::cin >> option;

            if(option==1){
                sorter.ordena_nombre();
                sorter.mostrar_lista();
            }
            else if(option==2){
                sorter.ordena_artista();
                sorter.mostrar_lista();
            }
            else if(option==3){
                sorter.ordena_genero();
                sorter.mostrar_lista();
            }
            else if(option==4){
                sorter.ordena_duracion();
                sorter.mostrar_lista();
            }
            else if(option==5){
                sorter.ordena_vistas();
                sorter.mostrar_lista();
            }
            else if(option==6){
                sorter.ordena_lanzamiento();
                sorter.mostrar_lista();
            }
            else{
                std::cout << "Opcion invalida...." << std::endl;
                std::cout << "Intenta nuevamente." << std::endl;
            }

            std::cout << "Deseas seguir ordenando? (si=1 / no=0): ";
            std::cin >> opcion;
            }
        }
        
        else if (option == 4)
        {
            int opcion = 1;

            while (opcion == 1)
            {
                std::string nom_buscado;

                std::cout << "BUSCAR CANCION" << std::endl;
                std::cout << "Introduce el nombre de la cancion: ";

                std::cin.ignore(std::numeric_limits
                <std::streamsize>::max(), '\n');
          
                
                std::getline(std::cin, nom_buscado); 
                // Buscar usando búsqueda binaria
                Cancion* encontrada = sorter.buscarPorNombre(nom_buscado);

                // Comprobar si se encontró la película
                if (encontrada != nullptr) 
                {
                    std::cout << "Cancion encontrada:" << std::endl;
                    encontrada->print();
                }
                
                else
                {
                    std::cout << "No se encontro la pelicula: " 
                    << nom_buscado << std::endl;
                }
                
                std::cout << "Deseas seguir buscando? (si=1 / no=0): ";
                std::cin >> opcion;
            }
        }
        else if (option == 5)
        {
            menu=0;
        }
    }





    //sorter.ordena_nombre();
    //sorter.mostrar_lista();


    return 0;
};
