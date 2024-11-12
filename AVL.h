#ifndef AVL_H_
#define AVL_H_

#include <string> 
#include <sstream>
#include <iostream>

using namespace std; 

template <class T> class AVL;

template <class T>
class Node {
private:
    T value;  // Este será un objeto de tipo Cancion
    Node *left, *right;
    int level, balance;
    Node<T>* predecesor();

public:
    Node(T);
    Node(T, Node<T>*, Node<T>*, int, int);  
    void agregar_cancion(T);
    std::string encontrar_cancion(const std::string&) const;
    Node<T>* eliminar_cancion(const std::string& nombre);
    void removeChilds();
    void inorder(std::stringstream&) const;

    int max_depth();
    Node<T>* check_tree(T *check_val, Node<T> *parent, bool *checked);
    Node<T>* balance_tree();
    Node<T>* rot_left(Node<T>*);
    Node<T>* rot_right(Node<T>*);
    Node<T>* rot_left_right(Node<T>*);
    Node<T>* rot_right_left(Node<T>*);
    friend class AVL<T>;
};

/*
 * Node<T>::Node(T val) - Constructor de nodo
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Inicializa un nodo con el valor val, sin hijos y con balance y nivel en 0. La complejidad es constante porque solo inicializa variables.
 */
template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), level(0), balance(0) {}

/*
 * Node<T>::Node(T val, Node<T>* le, Node<T>* ri, int lev, int bal) - Constructor completo de nodo
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Inicializa un nodo con el valor y los punteros a hijos especificados. La complejidad es constante debido a la inicialización simple de variables.
 */
template <class T>
Node<T>::Node(T val, Node<T>* le, Node<T>* ri, int lev, int bal)
    : value(val), left(le), right(ri), level(lev), balance(bal) {}

/*
 * Node<T>::agregar_cancion() - Inserta una canción en el árbol AVL.
 * Complejidad temporal:
 * - Mejor caso: O(1) (inserción en un nodo hoja inmediato)
 * - Caso promedio: O(log N) (inserción en árbol balanceado)
 * - Peor caso: O(N) (en un árbol completamente desbalanceado similar a una lista)
 * Descripción: Inserta un nodo en el árbol balanceado. En el caso balanceado, la complejidad es logarítmica. En el peor caso, el árbol se convierte en una lista enlazada.
 */
template <class T>
void Node<T>::agregar_cancion(T val) {
    if (val.get_nombre() < value.get_nombre()) {
        if (left != 0) {
            left->agregar_cancion(val);
        } else {
            left = new Node<T>(val);
        }
    } else {
        if (right != 0) {
            right->agregar_cancion(val);
        } else {
            right = new Node<T>(val);
        }
    }
}

/*
 * Node<T>::encontrar_cancion() - Busca una canción por nombre en el árbol.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el elemento buscado está en la raíz)
 * - Caso promedio: O(log N) (en un árbol balanceado)
 * - Peor caso: O(N) (en un árbol completamente desbalanceado)
 * Descripción: La búsqueda es O(1) si la canción está en la raíz. En promedio es logarítmica si el árbol está balanceado, y en el peor caso es lineal.
 */
template <class T>
std::string Node<T>::encontrar_cancion(const std::string& nombre) const {
    if (nombre == value.get_nombre()) {
        std::stringstream ss;
        ss << "\nNombre: " << value.get_nombre()
           << "\nArtista: " << value.get_artista()
           << "\ngenero: " << value.get_genero()
           << "\nvistas: " << value.get_vistas()
           << "\nDuracion: " << value.get_duracion() << " minutos\n";
        return ss.str();
    } else if (nombre < value.get_nombre() && left != 0) {
        return left->encontrar_cancion(nombre);
    } else if (nombre > value.get_nombre() && right != 0) {
        return right->encontrar_cancion(nombre);
    }
    return "La canción no fue encontrada.";
}

/*
 * Node<T>::eliminar_cancion() - Elimina una canción por nombre del árbol.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el nodo a eliminar es una hoja sin hijos)
 * - Caso promedio: O(log N) (si el árbol está balanceado)
 * - Peor caso: O(N) (en un árbol completamente desbalanceado)
 * Descripción: Si el nodo a eliminar es una hoja, la eliminación es constante. Si el árbol está balanceado, es logarítmica. En el peor caso, el árbol se comporta como una lista enlazada.
 */
template <class T>
Node<T>* Node<T>::eliminar_cancion(const std::string& nombre) {
    if (nombre < value.get_nombre()) {
        if (left != 0) {
            left = left->eliminar_cancion(nombre);
        }
    } else if (nombre > value.get_nombre()) {
        if (right != 0) {
            right = right->eliminar_cancion(nombre);
        }
    } else {
        if (left == 0 && right == 0) {
            delete this;
            return nullptr;
        } else if (left == 0) {
            Node<T>* temp = right;
            delete this;
            return temp;
        } else if (right == 0) {
            Node<T>* temp = left;
            delete this;
            return temp;
        } else {
            Node<T>* succ = right;
            while (succ->left != 0) {
                succ = succ->left;
            }
            value = succ->value;
            right = right->eliminar_cancion(succ->value.get_nombre());
        }
    }
    return this;
}

/*
 * Node<T>::predecesor() - Encuentra el nodo predecesor.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el predecesor es el hijo izquierdo inmediato)
 * - Caso promedio: O(log N) (en un árbol balanceado)
 * - Peor caso: O(N) (en un árbol completamente desbalanceado)
 * Descripción: Se recorre el subárbol izquierdo para encontrar el predecesor, logarítmico en un árbol balanceado.
 */
template <class T>
Node<T>* Node<T>::predecesor() {
    Node<T>* le = left;
    Node<T>* ri = right;

    if (left == 0) {
        if (right != 0) {
            right = 0;
        }
        return ri;
    }

    if (left->right == 0) {
        left = left->left;
        le->left = 0;
        return le;
    }

    Node<T>* parent = left;
    Node<T>* child = left->right;
    while (child->right != 0) {
        parent = child;
        child = child->right;
    }
    parent->right = child->left;
    child->left = 0;
    return child;
}

/*
 * Node<T>::removeChilds() - Elimina todos los hijos del nodo.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si no tiene hijos)
 * - Caso promedio: O(N/2) ≈ O(N) (en un árbol balanceado con subárboles)
 * - Peor caso: O(N) (si el nodo es raíz de un árbol completamente desbalanceado)
 * Descripción: Elimina todos los nodos hijo, recorriendo todo el subárbol bajo este nodo.
 */
template <class T>
void Node<T>::removeChilds() {
    if (left != 0) {
        left->removeChilds();
        delete left;
        left = 0;
    }
    if (right != 0) {
        right->removeChilds();
        delete right;
        right = 0;
    }
}

/*
 * Node<T>::inorder() - Realiza un recorrido inorder del árbol.
 * Complejidad temporal:
 * - Mejor caso: O(N)
 * - Caso promedio: O(N)
 * - Peor caso: O(N)
 * Descripción: Recorre todos los nodos del árbol en orden, la complejidad es lineal al visitar cada nodo.
 */
template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
    if (left != 0) {
        left->inorder(aux);
    }
    aux << "\nNombre: " << value.get_nombre()
        << "\nArtista: " << value.get_artista()
        << "\ngenero: " << value.get_genero()
        << "\nvistas: " << value.get_vistas()
        << "\nDuracion: " << value.get_duracion()
        << "\nLanzamiento: " << value.get_lanzamiento() << endl;
    if (right != 0) {
        right->inorder(aux);
    }
}

/*
 * Node<T>::max_depth() - Calcula la profundidad máxima del árbol.
 * Complejidad temporal:
 * - Mejor caso: O(log N) (en un árbol completamente balanceado)
 * - Caso promedio: O(log N) (en un árbol balanceado)
 * - Peor caso: O(N) (en un árbol completamente desbalanceado)
 * Descripción: Calcula la profundidad máxima del árbol recorriendo todos los nodos.
 */
template <class T>
int Node<T>::max_depth() {
    int le = 0, ri = 0;
    if (left != 0) {
        le = left->max_depth() + 1;
    }
    if (right != 0) {
        ri = right->max_depth() + 1;
    }
    balance = le - ri;
    return (le > ri) ? le : ri;
}

/*
 * Node<T>::check_tree() - Verifica y ajusta el balance del árbol.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si no requiere balanceo)
 * - Caso promedio: O(log N) (en un árbol balanceado)
 * - Peor caso: O(N) (en un árbol completamente desbalanceado)
 * Descripción: Recorre y balancea el árbol, ajustando nodos desbalanceados.
 */
template <class T>
Node<T>* Node<T>::check_tree(T *check_val, Node<T> *parent, bool *checked) {
    cout << "node value " << value.get_nombre() << " " << level << " " << balance << endl;
    Node<T> *le = 0, *ri = 0, *a = 0;
    if (left != 0)
        le = left->check_tree(check_val, this, checked);
    if (right != 0)
        ri = right->check_tree(check_val, this, checked);
    if (*checked == false) {
        if (balance > 1) {
            a = balance_tree();
            *check_val = value;
            *checked = true;
            if (parent != 0) {
                cout << "parent  " << parent->value.get_nombre() << " parent->left " << parent->left->value.get_nombre() << endl;
                parent->left = a;
            }
        } else if (balance < -1) {
            a = balance_tree();
            *check_val = value;
            *checked = true;
            if (parent != 0) {
                cout << "parent  " << parent->value.get_nombre() << " parent->right " << parent->right->value.get_nombre() << endl;
                parent->right = a;
            }
        }
    }
    return a;
}

/*
 * Node<T>::balance_tree() - Realiza el balance del nodo actual.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el nodo ya está balanceado)
 * - Caso promedio: O(log N) (en un árbol balanceado)
 * - Peor caso: O(N) (si el árbol está completamente desbalanceado)
 * Descripción: Balancea el nodo actual, con una complejidad constante por rotación.
 */
template <class T>
Node<T>* Node<T>::balance_tree() {
    Node<T> *a = this, *le = left, *ri = right;
    cout << "Balancing node : " << a->value.get_nombre() << " " << endl;
    if (balance > 0) {
        if (le->balance > 0) {
            cout << "rot_right  " << a->balance << " left: " << le->balance << endl;
            a = rot_right(a);
        } else {
            cout << "rot_left_right " << a->balance << " left: " << le->balance << endl;
            a = rot_left_right(a);
        }
    } else {
        if (ri->balance < 0) {
            cout << "rot_left " << a->balance << " right: " << ri->balance << endl;
            a = rot_left(a);
        } else {
            cout << "rot_right_left " << a->balance << " right: " << ri->balance << endl;
            a = rot_right_left(a);
        }
    }
    cout << "New current node value is " << a->value.get_nombre() << endl;
    return a;
}

/*
 * Node<T>::rot_left(), rot_right(), rot_left_right(), rot_right_left() - Rotaciones para balancear el árbol.
 * Complejidad temporal:
 * - Complejidad: O(1)
 * Descripción: Cada rotación individual tiene una complejidad constante.
 */

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* a) {
    Node<T> *b, *temp = 0;
    if (a->right != 0) {
        b = a->right;
        if (b->left != 0)
            temp = b->left;
        b->left = a;
        if (temp != 0) {
            a->right = temp;
        } else {
            a->right = 0;
        }
    }
    return b;
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* a) {
    Node<T> *b, *temp = 0;
    if (a->left != 0) {
        b = a->left;
        if (b->right != 0)
            temp = b->right;
        b->right = a;
        if (temp != 0) {
            a->left = temp;
        } else {
            a->left = 0;
        }
    }
    return b;
}

template <class T>
Node<T>* Node<T>::rot_left_right(Node<T>* a) {
    a->left = rot_left(a->left);
    a = rot_right(a);
    return a;
}

template <class T>
Node<T>* Node<T>::rot_right_left(Node<T>* a) {
    a->right = rot_right(a->right);
    a = rot_left(a);
    return a;
}

// Clase AVL para manipular el árbol de nodos
template <class T>
class AVL {
private:
    Node<T> *root;

public:
    AVL();
    ~AVL();
    bool empty() const;
    void agregar_cancion(T);
    void eliminar_cancion(const std::string&);
    void removeAll();
    std::string encontrar_cancion(const std::string& nombre) const;
    std::string inorder() const;
};

/*
 * AVL<T>::AVL() - Constructor de AVL
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Inicializa un árbol AVL vacío.
 */
template <class T>
AVL<T>::AVL() : root(0) {}

/*
 * AVL<T>::empty() - Verifica si el árbol está vacío.
 * Complejidad temporal: O(1)
 * Descripción: Devuelve true si el árbol está vacío.
 */
template <class T>
bool AVL<T>::empty() const {
    return (root == 0);
}

/*
 * AVL<T>::agregar_cancion() - Inserta una canción en el árbol AVL.
 * Complejidad temporal:
 * - Mejor caso: O(1) (inserción directa en la raíz)
 * - Caso promedio: O(log N) (en un árbol balanceado)
 * - Peor caso: O(N) (en un árbol completamente desbalanceado)
 * Descripción: Inserta un nodo en el árbol balanceado.
 */
template <class T>
void AVL<T>::agregar_cancion(T val) {
    if (root != 0) root->agregar_cancion(val);
    else root = new Node<T>(val);
}

/*
 * AVL<T>::eliminar_cancion() - Elimina una canción por nombre en el árbol.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el nodo a eliminar es una hoja o la raíz)
 * - Caso promedio: O(log N) (si el árbol está balanceado)
 * - Peor caso: O(N) (en un árbol completamente desbalanceado)
 * Descripción: Busca y elimina un nodo en el árbol balanceado.
 */
template <class T>
void AVL<T>::eliminar_cancion(const std::string& nombre) {
    if (root != 0) root = root->eliminar_cancion(nombre);
}

/*
 * AVL<T>::~AVL() - Destructor de AVL
 * Complejidad temporal:
 * - Mejor caso: O(N)
 * - Caso promedio: O(N)
 * - Peor caso: O(N)
 * Descripción: Elimina todos los nodos del árbol.
 */
template <class T>
AVL<T>::~AVL() {
	removeAll();
}

/*
 * AVL<T>::removeAll() - Elimina todos los nodos del árbol.
 * Complejidad temporal:
 * - Mejor caso: O(N)
 * - Caso promedio: O(N)
 * - Peor caso: O(N)
 * Descripción: Recorre y elimina todos los nodos del árbol.
 */

template <class T>
void AVL<T>::removeAll() {
    if (root != 0) {
        root->removeChilds();
        delete root;
        root = 0;
    }
}

/*
 * AVL<T>::encontrar_cancion() - Busca una canción por nombre.
 * Complejidad temporal:
 * - Mejor caso: O(1) (si está en la raíz)
 * - Caso promedio: O(log N) (en árbol balanceado)
 * - Peor caso: O(N) (en árbol desbalanceado)
 * Descripción: Busca un nodo en el árbol.
 */

template <class T>
std::string AVL<T>::encontrar_cancion(const std::string& nombre) const {
    if (root != 0) {
        return root->encontrar_cancion(nombre);
    }
    return "La canción no fue encontrada.";
}

/*
 * AVL<T>::inorder() - Realiza un recorrido inorder del árbol.
 * Complejidad temporal:
 * - Mejor caso: O(N)
 * - Caso promedio: O(N)
 * - Peor caso: O(N)
 * Descripción: Recorre todos los nodos del árbol en orden.
 */

template <class T>
std::string AVL<T>::inorder() const {
    std::stringstream aux;
    if (root != 0) {
        root->inorder(aux);
    }
    return aux.str();
}

#endif // AVL_H_
