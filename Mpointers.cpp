#include <iostream>
#include <string>
#include <winsock2.h>  // Biblioteca de Winsock para trabajar con sockets en Windows

#pragma comment(lib, "ws2_32.lib")  // Vincula la biblioteca Winsock

template <typename T>
class Mpointers {
private:
    int puerto;
    T value;
    int id_Memory_Block = 1;
    std::string Tipo = getTypeName<T>();

    explicit Mpointers(int puerto) : value(T()), puerto(puerto) {
        sendServer("Create (" + getTypeName<T>() + ")");
    }

public:
    static Mpointers<T> New(int puerto) {
        return Mpointers<T>(puerto);
    }

    // Operador de desreferenciación
    T operator*() {
        std::string valueAsString = "get(" + std::to_string(id_Memory_Block) + ")";
        T respuesta = str_to_T(valueAsString);
        return respuesta;
    }

    void operator=(const T& val) {
        this->value = val;
        std::string valueAsString = "Set (" + std::to_string(id_Memory_Block)+ ", " + std::to_string(val) + ")";
        sendServer(valueAsString);
    }

    // Operador de asignación para otra instancia de Mpointers del mismo tipo
    void operator=(const Mpointers<T>& other) {
        int new_id = other.id_Memory_Block;
        this->id_Memory_Block = new_id;
    }

    std::string sendServer(const std::string& Mensaje) {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "Error al inicializar Winsock. Código de error: " << result << std::endl;
        return "ERROR: Failed to initialize Winsock";
    }

    // Crear un socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket. Código de error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return "ERROR: Failed to create socket";
    }

    // Dirección del servidor (localhost)
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(puerto);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Conectar al servidor
    result = connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR) {
        std::cerr << "No se pudo conectar al servidor. Código de error: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return "ERROR: Failed to connect to server";
    }

    // Enviar el mensaje al servidor
    result = send(clientSocket, Mensaje.c_str(), Mensaje.size(), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "Error al enviar el mensaje. Código de error: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return "ERROR: Failed to send message";
    }

    std::cout << "Mensaje enviado: " << Mensaje << std::endl;

    // Recibir la respuesta del servidor
    char buffer[4096];
    result = recv(clientSocket, buffer, sizeof(buffer), 0);
    std::string respuesta;

    if (result > 0) {
        buffer[result] = '\0'; // Null-terminate the string
        respuesta = std::string(buffer);
        std::cout << "Respuesta del servidor: " << respuesta << std::endl;
    }
    else if (result == 0) {
        respuesta = "ERROR: Connection closed by server";
        std::cout << respuesta << std::endl;
    }
    else {
        respuesta = "ERROR: Failed to receive data";
        std::cerr << respuesta << ". Código de error: " << WSAGetLastError() << std::endl;
    }

    // Cerrar el socket
    closesocket(clientSocket);
    WSACleanup();

    return respuesta;
    }

    int getPuerto() {
        return puerto;
    }
    int getId_Memory_Block() {
        return id_Memory_Block;
    }

    T str_to_T(const std::string& str) {

        if (Tipo == "int") {
            try {
                return std::stoi(str);
            } catch (const std::invalid_argument&) {
                std::cerr << "Error: Valor no numérico (int): " << str << std::endl;
                return 0;
            } catch (const std::out_of_range&) {
                std::cerr << "Error: Número fuera de rango (int): " << str << std::endl;
                return 0;
            }
        }
        else if (Tipo == "float") {
            try {
                return std::stof(str);
            } catch (const std::invalid_argument&) {
                std::cerr << "Error: Valor no numérico (float): " << str << std::endl;
                return 0.0f;
            } catch (const std::out_of_range&) {
                std::cerr << "Error: Número fuera de rango (float): " << str << std::endl;
                return 0.0f;
            }
        }
        else if (Tipo == "double") {
            try {
                return std::stod(str);
            } catch (const std::invalid_argument&) {
                std::cerr << "Error: Valor no numérico (double): " << str << std::endl;
                return 0.0;
            } catch (const std::out_of_range&) {
                std::cerr << "Error: Número fuera de rango (double): " << str << std::endl;
                return 0.0;
            }
        }
        else {
            return T(); // Devuelve valor por defecto para tipos no implementados
        }

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
