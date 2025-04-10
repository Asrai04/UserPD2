#include <iostream>
#include <string>
#include <winsock2.h>  // Biblioteca de Winsock para trabajar con sockets en Windows

#pragma comment(lib, "ws2_32.lib")  // Vincula la biblioteca Winsock

template <typename T>
class Mpointers {
private:
    int puerto;
    T value;
    int id_Memory_Block = -1;

public:
    // Marcar el constructor como 'explicit' para evitar conversiones implícitas
    explicit Mpointers(int puerto) : value(T()), puerto(puerto) {
        sendServer("Create " + getTypeName<T>());
    }

    // Operador de desreferenciación
    T operator*() {
        return value;
    }

    void operator=(const T& val) {
        this->value = val;
        std::string valueAsString = "Set " + std::to_string(val);
        sendServer(valueAsString);
    }

    // Operador de asignación para otra instancia de Mpointers del mismo tipo
    void operator=(const Mpointers<T>& other) {
        sendServer("Get id");

    }

    void sendServer(std::string Mensaje) {
        WSADATA wsaData;
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0) {
            std::cerr << "Error al inicializar Winsock. Código de error: " << result << std::endl;
            return;
        }

        // Crear un socket
        SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error al crear el socket. Código de error: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return;
        }

        // Dirección del servidor (localhost)
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(puerto);  // Puerto del servidor
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Dirección IP del servidor (localhost)

        // Conectar al servidor
        result = connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
        if (result == SOCKET_ERROR) {
            std::cerr << "No se pudo conectar al servidor. Código de error: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            WSACleanup();
            return;
        }

        // Enviar el mensaje al servidor
        result = send(clientSocket, Mensaje.c_str(), Mensaje.size(), 0);
        if (result == SOCKET_ERROR) {
            std::cerr << "Error al enviar el mensaje. Código de error: " << WSAGetLastError() << std::endl;
        } else {
            std::cout << "Mensaje enviado: " << Mensaje << std::endl;
        }

        // Cerrar el socket
        closesocket(clientSocket);

        // Limpiar Winsock
        WSACleanup();
    }
    int getPuerto() {
        return puerto;
    }
    int getId_Memory_Block() {
        return id_Memory_Block;
    }


private:
    // Función para obtener el nombre del tipo de instancia
    template <typename U>
    std::string getTypeName() {
        if (typeid(U) == typeid(int)) {
            return "int";
        } else if (typeid(U) == typeid(double)) {
            return "double";
        } else if (typeid(U) == typeid(float)) {
            return "float";
        } else {
            return "unknown";
        }
    }
};
