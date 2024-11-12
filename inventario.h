#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <vector>
#include "cancion.h"

class Inventario {
private:
    std::vector<Cancion> canciones;

public:
    void agregarCancion(const Cancion& cancion) {
        canciones.push_back(cancion);
    }

    const std::vector<Cancion>& getCanciones() const {
        return canciones;
    }

    // Método para mostrar todas las canciones
    void mostrarCanciones() const {
        for (const auto& cancion : canciones) {
            cancion.mostrarInformacion();
            std::cout << "--------------------------" << std::endl;
        }
    }
};

#endif // INVENTARIO_H