#ifndef CANCION_H
#define CANCION_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Cancion
{
    private:
        std:: string nombre;
        std:: string artista;
        std:: string genero;
        float vistas;
        int lanzamiento;
        float duracion;
    public:
        // cosntructor por defecto
        Cancion(): nombre(""), artista(""), genero(""), vistas(0), lanzamiento(0), duracion(0) {}
        // cosntructor 
        Cancion(std:: string name, std::string artist,std:: string type_m, float views, int year, float time):
        nombre(name), artista(artist), genero(type_m), vistas(views), lanzamiento(year), duracion(time){}
        std::string get_nombre(void);
        std::string get_artista(void);
        std::string get_genero(void);
        float get_vistas(void);
        float get_duracion(void);
        int get_lanzamiento(void);
        void print(void);
        std::vector<Cancion> leerCancionesDesdeArchivo(const std::string& nombreArchivo);

};

std::vector<Cancion> Cancion:: leerCancionesDesdeArchivo(const std::string& nombreArchivo) 
{
    std::vector<Cancion> canciones;  // Aquí almacenaremos las canciones
    std::ifstream archivo(nombreArchivo);  // Abrimos el archivo
    std::string linea;

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return canciones;  // Retorna el vector vacío si hay un error
    }

    // Saltar la primera línea de encabezado
    std::getline(archivo, linea);

    // Leer cada línea del archivo
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string nombre, artista, genero;
        float vistas, duracion;
        int lanzamiento;

        // Leer y separar los valores por comas
        std::getline(ss, nombre, ',');
        std::getline(ss, artista, ',');
        std::getline(ss, genero, ',');
        ss >> vistas; ss.ignore(1);  // Leer vistas y saltar la coma
        ss >> lanzamiento; ss.ignore(1);  // Leer lanzamiento y saltar la coma
        ss >> duracion;  // Leer duración

        // Crear un objeto Cancion usando el constructor parametrizado
        Cancion cancion(nombre, artista, genero, vistas, lanzamiento, duracion);
        canciones.push_back(cancion);  // Agregarlo al vector
    }

    archivo.close();  // Cerrar el archivo
    return canciones;  // Retornar el vector con las canciones leídas
}

std::string Cancion::get_artista(void){return artista;}
std::string Cancion::get_nombre(void){return nombre;}
std::string Cancion::get_genero(void){return genero;}
float Cancion::get_vistas(void){return vistas;}
float Cancion::get_duracion(void){return duracion;}
int Cancion::get_lanzamiento(void){return lanzamiento;}


void Cancion::print(void){
            std::cout << "Titulo: " << nombre << std::endl;
            std::cout << "Artista: " << artista << std::endl;
            std::cout << "Genero: " << genero << std::endl;
            std::cout << "Fecha de lanzamiento: " << lanzamiento << std::endl;
            std::cout << "Numero de vistas(miles): " << vistas << std::endl;
            std::cout << "Duracion: " << duracion << "minutos" << std::endl;
}


#endif //cancion_h