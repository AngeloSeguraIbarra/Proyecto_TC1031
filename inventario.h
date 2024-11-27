#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <vector>
#include <algorithm>
#include "cancion.h"


std::string limpiarEspacios(const std::string& str) {
    std::string resultado = str;
    resultado.erase(0, resultado.find_first_not_of(" \t\n\r\f\v"));
    resultado.erase(resultado.find_last_not_of(" \t\n\r\f\v") + 1);
    return resultado;
}

class Inventario {
private:

    std::vector<Cancion> canciones;
    void copyarray(std::vector<Cancion>& A, std::vector<Cancion>& B,
     int low, int high);
        void mergearray_lanzamiento(std::vector<Cancion>& A,
     std::vector<Cancion>& B, int low, int mid, int high);
    void mergesplit_lanzamiento(std::vector<Cancion>& A,
     std::vector<Cancion>& B, int low, int high);
    void mergearray_nombre(std::vector<Cancion>& A, std::vector<Cancion>& B,
     int low, int mid, int high);
    void mergesplit_nombre(std::vector<Cancion>& A, std::vector<Cancion>& B,
     int low, int high);
    void mergearray_duracion(std::vector<Cancion>& A, std::vector<Cancion>& B,
     int low, int mid, int high);
    void mergesplit_duracion(std::vector<Cancion>& A, std::vector<Cancion>& B,
     int low, int high);

public:
    void agregarCancion(const Cancion& cancion) {
        canciones.push_back(cancion);
    }

    const std::vector<Cancion>& getCanciones() const {
        return canciones;
    }

    void ordena_duracion();
    void ordena_nombre();
    void ordena_lanzamiento();
    void eliminarCancion(const std::string& canci );

    // Método para mostrar todas las canciones
    void mostrarCanciones() const {
        for (const auto& cancion : canciones) {
            cancion.mostrarInformacion();
            std::cout << "--------------------------" << std::endl;
        }
    }
};


/*
 * copyArray() - Copia elementos de un vector a otro en un rango específico.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Copia los elementos desde el índice low hasta 
 * high de un vector a otro.
 * La complejidad es O(n) porque en el peor de los casos recorre
 *  n elementos dentro del rango especificado.
 */
void Inventario::copyarray(std::vector<Cancion>& A, std::vector<Cancion>& B,
 int low, int high) {
    for (int i = low; i <= high; i++) {
        A[i] = B[i];
    }
}

/*
 * mergeSplitLanzamiento() - Divide el vector para ordenar por lanzamiento 
 usando Merge Sort.
 * Complejidad temporal:
 * - Mejor caso: O(n log n)
 * - Caso promedio: O(n log n)
 * - Peor caso: O(n log n)
 * Descripción: Esta función implementa la parte de división de Merge Sort. 
 * Cada llamada recursiva divide el vector en dos mitades,
 * realizando log n divisiones y fusionando en O(n) 
 * para lograr una complejidad total de O(n log n).
 */
void Inventario::mergesplit_lanzamiento(std::vector<Cancion>& A,
 std::vector<Cancion>& B, int low, int high) {
    if (low < high) {
        int mitad = (high + low) / 2;
        mergesplit_lanzamiento(A, B, low, mitad);
        mergesplit_lanzamiento(A, B, mitad + 1, high);
        mergearray_lanzamiento(A, B, low, mitad, high);
    }
}

/*
 * mergeSplitDuracion() - Divide el vector para ordenar por duración 
 usando Merge Sort.
 * Complejidad temporal:
 * - Mejor caso: O(n log n)
 * - Caso promedio: O(n log n)
 * - Peor caso: O(n log n)
 * Descripción: Similar a mergeSplitLanzamiento, 
 * esta función divide el vector por duración y alcanza complejidad O(n log n) 
 * por las divisiones y fusiones.
 */
void Inventario::mergesplit_duracion(std::vector<Cancion>& A,
 std::vector<Cancion>& B, int low, int high) {
    if (low < high) {
        int mitad = (high + low) / 2;
        mergesplit_duracion(A, B, low, mitad);
        mergesplit_duracion(A, B, mitad + 1, high);
        mergearray_duracion(A, B, low, mitad, high);
    }
}
/*
 * mergeSplitcanci() - Divide el vector para ordenar por título usando Merge Sort.
 * Complejidad temporal:
 * - Mejor caso: O(n log n)
 * - Caso promedio: O(n log n)
 * - Peor caso: O(n log n)
 * Descripción: Realiza divisiones para ordenar por título en tiempo O(n log n), 
 * dividiendo en log n niveles y fusionando en cada nivel en O(n).
 */
void Inventario::mergesplit_nombre(std::vector<Cancion>& A,
 std::vector<Cancion>& B,int low, int high) {
    if (low < high) {
        int mitad = (high + low) / 2;
        mergesplit_nombre(A, B, low, mitad);
        mergesplit_nombre(A, B, mitad + 1, high);
        mergearray_nombre(A, B, low, mitad, high);
    }
}
/*
 * mergeArrayLanzamiento() - Fusiona dos mitades ordenadas por año de lanzamiento.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Fusiona dos mitades ordenadas de A en B.
 *  La complejidad es O(n) porque recorre todos los elementos 
 * en el rango de fusión una sola vez.
 */
void Inventario::mergearray_lanzamiento(std::vector<Cancion>& A,
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


/*
 * mergeArrayDuracion() - Fusiona dos mitades ordenadas por duración.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Fusiona dos mitades ordenadas de A en B por duración. 
 * La complejidad es O(n),
 *  ya que el algoritmo recorre cada elemento una sola vez.
 */
void Inventario::mergearray_duracion(std::vector<Cancion>& A,
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


/*
 * mergeArraycanci() - Fusiona dos mitades ordenadas por título.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Fusiona dos mitades ordenadas por título de A en B. 
 * La operación tiene complejidad O(n) debido a la comparación y copia secuencial.
 */
void Inventario::mergearray_nombre(std::vector<Cancion>& A,
 std::vector<Cancion>& B, int low, int mid, int high) {
    int i_ordenado = low;
    int i = low;
    int j = mid + 1;

    while (i <= mid && j <= high) {
        // Comparar los elementos usando el criterio de ordenamiento
        if (A[i].get_nombre() <= A[j].get_nombre()) {
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

// Ordenar por nombre usando Merge Sort.
void Inventario::ordena_nombre()
{
    std::vector<Cancion> tmp(canciones.size());
    mergesplit_nombre(canciones, tmp, 0, canciones.size() - 1);
}

// Ordenar por duración usando Merge Sort.
void Inventario::ordena_duracion()
{
    std::vector<Cancion> tmp(canciones.size());
    mergesplit_duracion(canciones, tmp, 0, canciones.size() - 1);
}

// Ordenar por año de lanzamiento usando Merge Sort.
void Inventario::ordena_lanzamiento()
{
    std::vector<Cancion> tmp(canciones.size());
    mergesplit_lanzamiento(canciones, tmp, 0, canciones.size() - 1);
}

void Inventario::eliminarCancion(const std::string& canci) 
{
    canciones.erase(std::remove_if(canciones.begin(), canciones.end(),
                                   [&canci](const Cancion& p) 
                                   {
                                       return p.get_nombre() == canci;
                                   }),
                    canciones.end());
}

#endif // INVENTARIO_H
