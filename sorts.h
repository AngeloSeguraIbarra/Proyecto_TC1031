#ifndef SORTS_H
#define SORTS_H
#include "cancion.h"
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <limits>
#include <fstream>


std::string limpiarEspacios(const std::string& str) {
    std::string resultado = str;
    resultado.erase(0, resultado.find_first_not_of(" \t\n\r\f\v"));
    resultado.erase(resultado.find_last_not_of(" \t\n\r\f\v") + 1);
    return resultado;
}


class Sorts 
{
    private:
        std::vector<Cancion> canciones;
public:
    void swap(std::vector<Cancion> &v, int i, int j);
    void agregar_cancion(const Cancion& cancion);
    void copyarray(std::vector<Cancion>& A, std::vector<Cancion>& B,
     int low, int high);

    void ordena_nombre();
    void ordena_artista();
    void ordena_genero();

    Cancion* buscarPorNombre(const std::string& nombreBuscado);
    void mostrar_lista() const;

    
    void mergearray_lanzamiento(std::vector<Cancion>& A,
     std::vector<Cancion>& B, int low, int mid, int high);
    void ordena_lanzamiento();
    void mergesplit_lanzamiento(std::vector<Cancion>& A,
     std::vector<Cancion>& B, int low, int high);

    void mergearray_vistas(std::vector<Cancion>& A, std::vector<Cancion>& B,
     int low, int mid, int high);
    void ordena_vistas();
    void mergesplit_vistas(std::vector<Cancion>& A, std::vector<Cancion>& B,
     int low, int high);

    void mergearray_duracion(std::vector<Cancion>& A, std::vector<Cancion>& B,
     int low, int mid, int high);
    void ordena_duracion();
    void mergesplit_duracion(std::vector<Cancion>& A, std::vector<Cancion>& B,
     int low, int high);
};

void Sorts::agregar_cancion(const Cancion& cancion) {
    canciones.push_back(cancion);
}

void Sorts::mostrar_lista() const
        {
            for (const auto& cancion : canciones)
            {
                cancion.print();
                std::cout << "- - - - - - - - - - - - -" << std::endl;
            }
        }

Cancion* Sorts::buscarPorNombre(const std::string& nombreBuscado) 
{
    
    std::sort(canciones.begin(), canciones.end(), [](const Cancion& a,
     const Cancion& b) {
        std::string tituloA = limpiarEspacios(a.get_nombre());
        std::string tituloB = limpiarEspacios(b.get_nombre());

        // Convertir los títulos a minúsculas para ordenamiento 
        std::transform(tituloA.begin(), tituloA.end(), tituloA.begin(),
         ::tolower);
        std::transform(tituloB.begin(), tituloB.end(), tituloB.begin(),
         ::tolower);

        return tituloA < tituloB;  // Comparación para ordenar alfabéticamente
    });

    int izquierda = 0;
    int derecha = canciones.size() - 1;

    // Limpiar espacios y convertir a minúsculas el título buscado
    std::string tituloLimpio = limpiarEspacios(nombreBuscado);
    std::transform(tituloLimpio.begin(), tituloLimpio.end(),
     tituloLimpio.begin(), ::tolower);

    std::cout << "Buscando por: '" << tituloLimpio << "' (longitud: " <<
     tituloLimpio.length() << ")" << std::endl;

    // Convertir el nombre buscado a minúsculas
    std::string nombreLimpio = nombreBuscado;
    std::transform(nombreLimpio.begin(), nombreLimpio.end(),
     nombreLimpio.begin(), ::tolower);

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        // Limpiar espacios y convertir a minúsculas el título de la película
        // en la posición medio
        std::string tituloMedio = limpiarEspacios(canciones[medio].get_nombre());
        std::transform(tituloMedio.begin(), tituloMedio.end(),
         tituloMedio.begin(), ::tolower);
        if (tituloMedio == tituloLimpio)
        {
            return &canciones[medio]; // se encontro la cancion 
        }
        else if (tituloMedio < tituloLimpio)
        {
            izquierda = medio + 1; // Continuar búsqueda a la derecha
        }
        else
        {
            derecha = medio - 1; // Continuar búsqueda a la izquierda
        }
    }
    return nullptr;
}





void Sorts::swap(std::vector<Cancion> &v, int i, int j)
{
            Cancion aux = v[i];
	        v[i] = v[j];
	        v[j] = aux;
}


void Sorts::ordena_nombre() {
    int n = canciones.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (canciones[i].get_nombre() > canciones[j].get_nombre()) {
                swap(canciones, i, j);
            }
        }
    }
}


void Sorts::ordena_genero() {
    int n = canciones.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (canciones[i].get_genero() > canciones[j].get_genero()) {
                swap(canciones, i, j);
            }
        }
    }
}


void Sorts::ordena_artista() {
    int n = canciones.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (canciones[i].get_artista() > canciones[j].get_artista()) {
                swap(canciones, i, j);
            }
        }
    }
}


void Sorts::copyarray(std::vector<Cancion>& A, std::vector<Cancion>& B,
 int low, int high) {
    for (int i = low; i <= high; i++) {
        A[i] = B[i];
    }
}


void Sorts::mergearray_duracion(std::vector<Cancion>& A,
 std::vector<Cancion>& B,int low, int mid, int high) {
    int i_ordenado = low;
    int i = low;
    int j = mid + 1;

    while (i <= mid && j <= high) {
        // Comparar los elementos usando el criterio de ordenamiento
        if (A[i].get_duracion() <= A[j].get_duracion()) {
            B[i_ordenado] = A[i];
            i++;
        } else {
            B[i_ordenado] = A[j];
            j++;
        }
        i_ordenado++;
    }

    while (i <= mid) {
        B[i_ordenado] = A[i];
        i++;
        i_ordenado++;
    }

    while (j <= high) {
        B[i_ordenado] = A[j];
        j++;
        i_ordenado++;
    }

    copyarray(A, B, low, high);
}


void Sorts::mergearray_lanzamiento(std::vector<Cancion>& A,
 std::vector<Cancion>& B, int low, int mid, int high) {
    int i_ordenado = low;
    int i = low;
    int j = mid + 1;

    while (i <= mid && j <= high) {
        // Comparar los elementos usando el criterio de ordenamiento
        if (A[i].get_lanzamiento() <= A[j].get_lanzamiento()) {
            B[i_ordenado] = A[i];
            i++;
        } else {
            B[i_ordenado] = A[j];
            j++;
        }
        i_ordenado++;
    }

    while (i <= mid) {
        B[i_ordenado] = A[i];
        i++;
        i_ordenado++;
    }

    while (j <= high) {
        B[i_ordenado] = A[j];
        j++;
        i_ordenado++;
    }

    copyarray(A, B, low, high);
}


void Sorts::mergearray_vistas(std::vector<Cancion>& A, std::vector<Cancion>& B,
 int low, int mid, int high) {
    int i_ordenado = low;
    int i = low;
    int j = mid + 1;

    while (i <= mid && j <= high) {
        // Comparar los elementos usando el criterio de ordenamiento
        if (A[i].get_vistas() <= A[j].get_vistas()) {
            B[i_ordenado] = A[i];
            i++;
        } else {
            B[i_ordenado] = A[j];
            j++;
        }
        i_ordenado++;
    }

    while (i <= mid) {
        B[i_ordenado] = A[i];
        i++;
        i_ordenado++;
    }

    while (j <= high) {
        B[i_ordenado] = A[j];
        j++;
        i_ordenado++;
    }

    copyarray(A, B, low, high);
}


void Sorts::mergesplit_vistas(std::vector<Cancion>& A, std::vector<Cancion>& B,
 int low, int high) {
    if (low < high) {
        int mitad = (high + low) / 2;
        mergesplit_vistas(A, B, low, mitad);
        mergesplit_vistas(A, B, mitad + 1, high);
        mergearray_vistas(A, B, low, mitad, high);
    }
}


void Sorts::mergesplit_duracion(std::vector<Cancion>& A, std::vector<Cancion>& B,
 int low, int high) {
    if (low < high) {
        int mitad = (high + low) / 2;
        mergesplit_duracion(A, B, low, mitad);
        mergesplit_duracion(A, B, mitad + 1, high);
        mergearray_duracion(A, B, low, mitad, high);
    }
}


void Sorts::mergesplit_lanzamiento(std::vector<Cancion>& A,
 std::vector<Cancion>& B, int low, int high) {
    if (low < high) {
        int mitad = (high + low) / 2;
        mergesplit_lanzamiento(A, B, low, mitad);
        mergesplit_lanzamiento(A, B, mitad + 1, high);
        mergearray_lanzamiento(A, B, low, mitad, high);
    }
}


void Sorts::ordena_vistas()
{
    std::vector<Cancion> tmp(canciones.size());
    mergesplit_vistas(canciones, tmp, 0, canciones.size() - 1);
}


void Sorts::ordena_duracion()
{
    std::vector<Cancion> tmp(canciones.size());
    mergesplit_duracion(canciones, tmp, 0, canciones.size() - 1);
}


void Sorts::ordena_lanzamiento()
{
    std::vector<Cancion> tmp(canciones.size());
    mergesplit_lanzamiento(canciones, tmp, 0, canciones.size() - 1);
}

#endif // SORTS_H
