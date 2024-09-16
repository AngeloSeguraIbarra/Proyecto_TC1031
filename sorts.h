#ifndef SORTS_H
#define SORTS_H
#include "cancion.h"
#include <vector>

template <class T>
class Sorts {
public:
    void swap(std::vector<T> &v, int i, int j);
    void copyarray(std::vector<T>& A, std::vector<T>& B, int low, int high);
    void ordena_nombre(std::vector<T>& source);
    void ordena_artista(std::vector<T>& source);
    void ordena_genero(std::vector<T>& source);

    void mergearray_lanzamiento(std::vector<T>& A, std::vector<T>& B, int low, int mid, int high);
    void ordena_lanzamiento(std::vector<T>& source);
    void mergesplit_lanzamiento(std::vector<T>& A, std::vector<T>& B, int low, int high);

    void mergearray_vistas(std::vector<T>& A, std::vector<T>& B, int low, int mid, int high);
    void ordena_vistas(std::vector<T>& source);
    void mergesplit_vistas(std::vector<T>& A, std::vector<T>& B, int low, int high);

    void mergearray_duracion(std::vector<T>& A, std::vector<T>& B, int low, int mid, int high);
    void ordena_duracion(std::vector<T>& source);
    void mergesplit_duracion(std::vector<T>& A, std::vector<T>& B, int low, int high);
};

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j)
{
            Cancion aux = v[i];
	        v[i] = v[j];
	        v[j] = aux;
}

template <class T>
void Sorts<T>::ordena_nombre(std::vector<T>& source) {
    int n = source.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (source[i].get_nombre() > source[j].get_nombre()) {
                swap(source, i, j);
            }
        }
    }
}

template <class T>
void Sorts<T>::ordena_genero(std::vector<T>& source) {
    int n = source.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (source[i].get_nombre() > source[j].get_nombre()) {
                swap(source, i, j);
            }
        }
    }
}

template <class T>
void Sorts<T>::ordena_artista(std::vector<T>& source) {
    int n = source.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (source[i].get_nombre() > source[j].get_nombre()) {
                swap(source, i, j);
            }
        }
    }
}

template <class T>
void Sorts<T>::copyarray(std::vector<T>& A, std::vector<T>& B, int low, int high) {
    for (int i = low; i <= high; i++) {
        A[i] = B[i];
    }
}

template <class T>
void Sorts<T>::mergearray_duracion(std::vector<T>& A, std::vector<T>& B, int low, int mid, int high) {
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

template <class T>
void Sorts<T>::mergearray_lanzamiento(std::vector<T>& A, std::vector<T>& B, int low, int mid, int high) {
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

template <class T>
void Sorts<T>::mergearray_vistas(std::vector<T>& A, std::vector<T>& B, int low, int mid, int high) {
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

template <class T>
void Sorts<T>::mergesplit_vistas(std::vector<T>& A, std::vector<T>& B, int low, int high) {
    if (low < high) {
        int mitad = (high + low) / 2;
        mergesplit_vistas(A, B, low, mitad);
        mergesplit_vistas(A, B, mitad + 1, high);
        mergearray_vistas(A, B, low, mitad, high);
    }
}

template <class T>
void Sorts<T>::mergesplit_duracion(std::vector<T>& A, std::vector<T>& B, int low, int high) {
    if (low < high) {
        int mitad = (high + low) / 2;
        mergesplit_duracion(A, B, low, mitad);
        mergesplit_duracion(A, B, mitad + 1, high);
        mergearray_duracion(A, B, low, mitad, high);
    }
}

template <class T>
void Sorts<T>::mergesplit_lanzamiento(std::vector<T>& A, std::vector<T>& B, int low, int high) {
    if (low < high) {
        int mitad = (high + low) / 2;
        mergesplit_lanzamiento(A, B, low, mitad);
        mergesplit_lanzamiento(A, B, mitad + 1, high);
        mergearray_lanzamiento(A, B, low, mitad, high);
    }
}

template <class T>
void Sorts<T>::ordena_vistas(std::vector<T>& source)
{
    std::vector<T> tmp(source.size());
    mergesplit_vistas(source, tmp, 0, source.size() - 1);
}

template <class T>
void Sorts<T>::ordena_duracion(std::vector<T>& source)
{
    std::vector<T> tmp(source.size());
    mergesplit_duracion(source, tmp, 0, source.size() - 1);
}

template <class T>
void Sorts<T>::ordena_lanzamiento(std::vector<T>& source)
{
    std::vector<T> tmp(source.size());
    mergesplit_lanzamiento(source, tmp, 0, source.size() - 1);
}

#endif // SORTS_H
