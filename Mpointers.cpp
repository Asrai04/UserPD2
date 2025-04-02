#include "MPointers.h"
#include <winsock2.h>
#include <iostream>

template <typename T>
MPointers<T>::MPointers(int puerto) : port(puerto), value(T()) {}

template <typename T>
MPointers<T> MPointers<T>::New(int puerto) {
    return MPointers<T>(puerto);
}

template <typename T>
T& MPointers<T>::operator*() {
    std::cout << "Valor enviedo:" << value << std::endl;
    return value;  // Devuelve la referencia al valor (getter)
}

template <typename T>
void MPointers<T>::operator*(const T& newValue) {
    value = newValue;  // Asignamos el nuevo valor (setter)
    sendToServer(value);  // Enviamos el valor al servidor
    std::cout << "Valor enviado:" << value << std::endl;
}

template <typename T>
void MPointers<T>::sendToServer(const T& value) {
    // Inicializar Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup falló" << std::endl;
        return;
    }

    // Crear el socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket" << std::endl;
        WSACleanup();
        return;
    }

    // Configurar la dirección del servidor
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);  // Puerto
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Dirección localhost

    // Conectar al servidor
    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Conexión fallida" << std::endl;
        closesocket(sock);
        WSACleanup();
        return;
    }

    // Enviar el valor (en este caso, un valor de tipo T)
    if (send(sock, reinterpret_cast<const char*>(&value), sizeof(value), 0) == SOCKET_ERROR) {
        std::cerr << "Error al enviar datos" << std::endl;
    } else {
        std::cout << "Valor enviado: " << value << std::endl;
    }

    // Cerrar el socket
    closesocket(sock);

    // Limpiar Winsock
    WSACleanup();
}

// Instanciación explícita para el tipo int
template class MPointers<int>;
template class MPointers<float>;
template class MPointers<double>;
