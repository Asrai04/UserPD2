#include <iostream>
#include "Mpointers.h"  // Incluir el archivo con la implementación de la clase Mpointers
#include "ListaEnlazada.cpp"
int main() {
    std::cout << "Inicio del programa" << std::endl;
    LinkedList<int> list;

    Mpointers<int> ptr1 = Mpointers<int>::New(8000);
    Mpointers<int> ptr2 = Mpointers<int>::New(8000);
    Mpointers<int> ptr3 = Mpointers<int>::New(8000);
    Mpointers<int> ptr4 = Mpointers<int>::New(8000);

    Mpointers<double> ptr5 = Mpointers<double>::New(8000);

    ptr1 = 100;
    ptr2 = 200;
    ptr3 = 300;
    ptr4 = ptr1;

    int valor = *ptr1;

    std::cout <<  "Valor almacenado en ptr1: " << valor << std::endl;

    list.prepend(ptr1);
    list.prepend(ptr2);
    list.prepend(ptr3);
    list.prepend(ptr4);


    std::cout << "Lista completa:" << std::endl;
    list.print();

    list.removeByIdAndAdjust(&ptr2);

    list.print();

    // La memoria se libera automáticamente al salir del ámbito
    return 0;
}
