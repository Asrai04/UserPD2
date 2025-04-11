#include <iostream>
#include "Mpointers.h"  // Incluir el archivo con la implementación de la clase Mpointers
#include "ListaEnlazada.cpp"
int main() {
    std::cout << "Inicio del programa" << std::endl;
    LinkedList<int> list;

    auto ptr1 = Mpointers<int>::New(8080);
    auto ptr2 = Mpointers<int>::New(8080);

    ptr1 = 100;
    ptr2 = 200;

    list.append(ptr1);
    list.prepend(ptr2);

    std::cout << "Lista completa:" << std::endl;
    list.print();

    // Buscar un elemento
    auto found = list.findById(ptr1.getId_Memory_Block());
    if (found) {
        std::cout << "\nEncontrado: " << **found << std::endl;
    }
    // No hay forma de eliminar elementos individualmente
    // La memoria se libera automáticamente al salir del ámbito
    return 0;
}
