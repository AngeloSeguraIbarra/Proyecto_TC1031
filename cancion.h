#ifndef CANCION_H
#define CANCION_H

#include <string>
#include <iostream>

class Cancion {
private: 
    std::string nombre;
    std::string artista;
    std::string genero;
    float vistas;       // en miles
    int lanzamiento;    // año de lanzamiento
    float duracion;     // en minutos

public:
    // Constructor
    Cancion(std::string _nombre, std::string _artista, std::string _genero, float _vistas, int _lanzamiento, float _duracion) 
        : nombre(_nombre), artista(_artista), genero(_genero), vistas(_vistas), lanzamiento(_lanzamiento), duracion(_duracion) {}

    // Getters
    std::string get_nombre() const { return nombre; }
    std::string get_artista() const { return artista; }
    std::string get_genero() const { return genero; }
    float get_vistas() const { return vistas; }
    int get_lanzamiento() const { return lanzamiento; }
    float get_duracion() const { return duracion; }

    // Operador < para comparar canciones por nombre
    bool operator<(const Cancion& other) const {
        return this->nombre < other.nombre;
    }

    // Operador == para comparar canciones por nombre
    bool operator==(const Cancion& other) const {
        return this->nombre == other.nombre;
    }

    // Impresión de la canción
    void print() const {
        std::cout << "Titulo: " << nombre << std::endl;
        std::cout << "Artista: " << artista << std::endl;
        std::cout << "Genero: " << genero << std::endl;
        std::cout << "Numero de vistas (miles): " << vistas << std::endl;
        std::cout << "Año de lanzamiento: " << lanzamiento << std::endl;
        std::cout << "Duracion: " << duracion << " minutos" << std::endl;
    }
};

#endif // CANCION_H
