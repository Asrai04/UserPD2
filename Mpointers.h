#ifndef MPointer_H
#define MPointer_H

#include <iostream>
#include <winsock2.h>  // Incluir la librería de Winsock para trabajar con sockets en Windows

template <typename T>
class MPointers {
private:
    int port;  // El puerto donde se enviará el valor
    T value;   // El valor que se desea enviar

public:
    // Constructor para configurar el puerto
    MPointers(int puerto);

    // Método estático para crear una nueva instancia de MPointer
    static MPointers<T> New(int puerto);

    // Sobrecargar el operador * para devolver una referencia al valor
    T& operator*();

    // Sobrecargar el operador = para asignar un valor y enviarlo
    void operator*(const T& newValue);

private:
    // Función para enviar el valor al servidor mediante un socket
    void sendToServer(const T& value);
};

#endif
