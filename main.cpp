#include <iostream>
#include "Mpointers.h"  // Asegúrate de que este archivo esté en el mismo directorio o correctamente referenciado

int main() {
    // Crear un objeto MPointers para un puerto específico (por ejemplo, puerto 8000)
    int puerto = 8000;
    MPointers<int> ptr = MPointers<int>::New(puerto);

    // Asignar un valor al objeto
    *ptr = 42;  // Esto debería disparar el envío del valor al servidor

    // Obtener el valor almacenado mediante el operador *
    int valor = *ptr;  // Esto te dará el valor almacenado en 'ptr'
    std::cout << "Valor almacenado: " << valor << std::endl;

    return 0;
}
