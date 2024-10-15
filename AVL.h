/*
Angelo Segura Ibarra
14/10/2024
*/
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

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), level(0), balance(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, int lev, int bal)
    : value(val), left(le), right(ri), level(lev), balance(bal) {}

// Modificado para usar el atributo 'nombre' de Cancion
template <class T>
void Node<T>::agregar_cancion(T val) {
    if (val.get_nombre() < value.get_nombre()) {  // Comparar nombres de las canciones
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
        return left->encontrar_cancion(nombre);  // Buscar en el subárbol izquierdo
    } else if (nombre > value.get_nombre() && right != 0) {
        return right->encontrar_cancion(nombre);  // Buscar en el subárbol derecho
    }
    // Si no se encuentra la canción
    return "La canción no fue encontrada.";
}


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
        // Caso 1: Nodo sin hijos
        if (left == 0 && right == 0) {
            delete this;
            return nullptr;
        }
        // Caso 2: Nodo con un solo hijo
        else if (left == 0) {
            Node<T> *temp = right;
            delete this;
            return temp;
        } else if (right == 0) {
            Node<T> *temp = left;
            delete this;
            return temp;
        }
        // Caso 3: Nodo con dos hijos
        else {
            Node<T> *succ = right;
            while (succ->left != 0) {
                succ = succ->left;
            }
            value = succ->value;  // Reemplazar con el valor del sucesor
            right = right->eliminar_cancion(succ->value.get_nombre());  // Eliminar sucesor
        }
    }
    return this;
}

template <class T>
Node<T>* Node<T>::predecesor() {
    Node<T> *le, *ri;
    le = left;
    ri = right;

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

    Node<T> *parent, *child;
    parent = left;
    child = left->right;
    while (child->right != 0) {
        parent = child;
        child = child->right;
    }
    parent->right = child->left;
    child->left = 0;
    return child;
}

// Métodos adicionales que usas como remove, balance_tree y otros
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

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
    if (left != 0) {
        left->inorder(aux);
    }
    aux << "\nNombre: " << value.get_nombre()<< "\nArtista: " << value.get_artista()<< "\ngenero: " << value.get_genero()<< "\nvistas: " << value.get_vistas()<< "\nDuracion: " << value.get_duracion() << endl;
    if (right != 0) {
        right->inorder(aux);
    }
}

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

template <class T>
AVL<T>::AVL() : root(0) {}

template <class T>
bool AVL<T>::empty() const {
    return (root == 0);
}

template <class T>
void AVL<T>::agregar_cancion(T val) {
    if (root != 0) {
        root->agregar_cancion(val);
    } else {
        root = new Node<T>(val);
    }
}

template <class T>
void AVL<T>::eliminar_cancion(const std::string& nombre) {
    if (root != 0) {
        root = root->eliminar_cancion(nombre);
    }
}

template <class T>
AVL<T>::~AVL() {
	removeAll();
}

template <class T>
void AVL<T>::removeAll() {
    if (root != 0) {
        root->removeChilds();
        delete root;
        root = 0;
    }
}


template <class T>
std::string AVL<T>::encontrar_cancion(const std::string& nombre) const {
    if (root != 0) {
        return root->encontrar_cancion(nombre);
    }
    return "La canción no fue encontrada.";
}

template <class T>
std::string AVL<T>::inorder() const {
    std::stringstream aux;
    if (root != 0) {
        root->inorder(aux);
    }
    return aux.str();
}

#endif // AVL_H_
