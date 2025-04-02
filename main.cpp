#include <iostream>
#include "Mpointers.cpp"  // Incluir el archivo con la implementación de la clase Mpointers

int main() {
    // Crear un objeto de la clase Mpointers con el puerto 8000
    Mpointers<double> cliente(8000);

    // Usar el operador *= para asignar un valor a 'value' y enviarlo al servidor
    cliente *= 99.9742;  // Enviar el valor convertido a string (en este caso "42")

    // Usar el operador * para obtener el valor almacenado y asignarlo a una variable
    double valor = *cliente;  // Esto obtiene el valor almacenado en 'cliente'

    // Verificar que el valor se guardó correctamente
    std::cout << "Valor almacenado en cliente: " << valor << std::endl;  // Imprimir el valor

    return 0;
}
