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
    protected:
        std:: string nombre;
        std:: string artista;
        std:: string genero;
        float vistas;
        int lanzamiento;
        float duracion;
    public:
        // constructor por defecto
        Cancion(): nombre(""), artista(""), genero(""), vistas(0),
         lanzamiento(0), duracion(0) {}
        // constructor
        Cancion(std:: string name, std::string artist,std:: string type_m,
         float views, int year, float time):
        nombre(name), artista(artist), genero(type_m), vistas(views),
         lanzamiento(year), duracion(time){}
        // getters
        std::string get_nombre(void) const;
        std::string get_artista(void) const;
        std::string get_genero(void) const;
        float get_vistas(void) const;
        float get_duracion(void) const;
        int get_lanzamiento(void) const;
        // impresion de las listas
        void print()const;

};


std::string Cancion::get_artista(void)const{return artista;}
std::string Cancion::get_nombre(void)const{return nombre;}
std::string Cancion::get_genero(void)const{return genero;}
float Cancion::get_vistas(void)const{return vistas;}
float Cancion::get_duracion(void)const{return duracion;}
int Cancion::get_lanzamiento(void)const{return lanzamiento;}


void Cancion::print() const{
            std::cout << "Titulo: " << nombre << std::endl;
            std::cout << "Artista: " << artista << std::endl;
            std::cout << "Genero: " << genero << std::endl;
            std::cout << "Fecha de lanzamiento: " << lanzamiento << std::endl;
            std::cout << "Numero de vistas(miles): " << vistas << std::endl;
            std::cout << "Duracion: " << duracion << "minutos" << std::endl;
}


#endif //cancion_h
