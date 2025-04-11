#include <iostream>
#include "Mpointers.h"  // Incluir el archivo con la implementación de la clase Mpointers
#include "ListaEnlazada.cpp"
int main() {
    std::cout << "Inicio del programa" << std::endl;
    LinkedList<int> list;

    Mpointers<int> ptr1 = Mpointers<int>::New(8000);
    Mpointers<int> ptr2 = Mpointers<int>::New(8000);
    Mpointers<int> ptr3 = Mpointers<int>::New(8000);

    ptr1 = 100;
    ptr2 = 200;
    ptr3 = ptr1;

    int valor = *ptr1;

    std::cout <<  "Valor almacenado en ptr1: " << valor << std::endl;

    list.prepend(ptr1);
    list.prepend(ptr2);
    list.prepend(ptr3);


    std::cout << "Lista completa:" << std::endl;
    list.print();

    ptr2.Kill();
    // La memoria se libera automáticamente al salir del ámbito
    return 0;
}
