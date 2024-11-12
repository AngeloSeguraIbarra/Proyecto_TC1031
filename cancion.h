#ifndef CANCION_H
#define CANCION_H

#include <iostream>
#include <string>

class Cancion {
private:
    std::string nombre;
    std::string artista;
    std::string genero;
    float vistas;       // en miles
    int lanzamiento;    // año de lanzamiento
    float duracion;     // en minutos

public:
    // Constructor por defecto
    Cancion() : nombre(""), artista(""), genero(""), vistas(0), lanzamiento(0), duracion(0) {}

    // Constructor parametrizado
    Cancion(std::string _nombre, std::string _artista, std::string _genero, float _vistas, int _lanzamiento, float _duracion) 
        : nombre(_nombre), artista(_artista), genero(_genero), vistas(_vistas), lanzamiento(_lanzamiento), duracion(_duracion) {}

    // Getters
    std::string get_nombre() const { return nombre; }
    std::string get_artista() const { return artista; }
    std::string get_genero() const { return genero; }
    float get_vistas() const { return vistas; }
    int get_lanzamiento() const { return lanzamiento; }
    float get_duracion() const { return duracion; }

    // Función para mostrar la información de la canción
    void mostrarInformacion() const {
        std::cout << "Nombre: " << nombre << std::endl;
        std::cout << "Artista: " << artista << std::endl;
        std::cout << "Genero: " << genero << std::endl;
        std::cout << "Vistas: " << vistas << " miles" << std::endl;
        std::cout << "Lanzamiento: " << lanzamiento << std::endl;
        std::cout << "Duracion: " << duracion << " minutos" << std::endl;
    }

    // Función para obtener los datos de la canción en formato CSV
    std::string getCancion() const {
        return nombre + "," + artista + "," + genero + "," + std::to_string(vistas) + "," + 
               std::to_string(lanzamiento) + "," + std::to_string(duracion);
    }

    // Operador < para comparar canciones por nombre (útil para el AVL)
    bool operator<(const Cancion& other) const {
        return this->nombre < other.nombre;
    }

    // Operador == para comparar canciones por nombre
    bool operator==(const Cancion& other) const {
        return this->nombre == other.nombre;
    }
};

#endif // CANCION_H
