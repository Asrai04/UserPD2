#include "Mpointers.h"  // Incluir el archivo con la implementación de la clase Mpointers

template <typename T>
class LinkedList {
private:
    // Estructura del nodo básico
    struct Node {
        Mpointers<T> data;
        Node* next;

        Node(const Mpointers<T>& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    // Constructor
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Destructor (importante para liberar memoria)
    ~LinkedList() {
    }

    // Método para limpiar toda la lista
    void clear() {
        while (head) {
            Node* toDelete = head;
            head = head->next;
            toDelete->data.Kill(); // Liberar el Mpointer
            delete toDelete;
        }
        tail = nullptr;
        size = 0;
    }

    // Método para agregar elementos al final
    void append(const Mpointers<T>& value) {
        Node* newNode = new Node(value);
        
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Método para agregar elementos al inicio
    void prepend(const Mpointers<T>& value) {
        Node* newNode = new Node(value);
        
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    // Método para buscar por ID
    Mpointers<T>* findById(int id) {
        Node* current = head;
        while (current) {
            if (current->data.getId_Memory_Block() == id) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    // Método para obtener el tamaño
    size_t getSize() const {
        return size;
    }

    // Método para imprimir la lista
    void print() const {
        Node* current = head;
        while (current) {
            std::cout << "ID: " << &current->data
                      << ", Value: " << *current->data <<
                          std::endl;
            current = current->next;
        }
    }
    bool removeByIdAndAdjust(int id) {
        Node* current = head;
        Node* prev = nullptr;
        bool found = false;

        // Primero buscamos y eliminamos el nodo con el ID especificado
        while (current) {
            if (&current->data == id) {
                found = true;

                // Eliminar el nodo encontrado
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }

                if (current == tail) {
                    tail = prev;
                }

                current->data.Kill(); // Liberar el Mpointer
                delete current;
                size--;
                break;
            }
            prev = current;
            current = current->next;
        }

        // Si encontramos y eliminamos el nodo, ajustamos los IDs mayores
        if (found) {
            current = head;
            while (current) {
                if (&current->data > id) {
                    // Restamos 1 al ID de los nodos con ID mayor
                    current->data.Update_Id(1);
                }
                current = current->next;
            }
        }

        return found;
    }

    // Eliminar operaciones de copia por seguridad
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;
};