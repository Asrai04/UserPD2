#include <iostream>
#include <winsock2.h>  // Incluye Winsock

#pragma comment(lib, "ws2_32.lib")  // Enlaza con la librería Winsock

#define PORT 8080  // Puerto del servidor

int main() {
    // Inicializar Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return -1;
    }

    // Crear un socket para el cliente
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation error\n";
        WSACleanup();
        return -1;
    }

    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir la dirección IP del servidor de texto a binario usando inet_addr
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Dirección IP del servidor

    if (serv_addr.sin_addr.s_addr == INADDR_NONE) {
        std::cerr << "Invalid address or address not supported\n";
        WSACleanup();
        return -1;
    }

    // Conectar al servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed\n";
        WSACleanup();
        return -1;
    }

    // Recibir mensaje del servidor
    char buffer[1024] = {0};
    recv(sock, buffer, sizeof(buffer), 0);
    std::cout << "Mensaje recibido del servidor: " << buffer << std::endl;

    // Enviar mensaje al servidor
    const char *message = "Hola desde el cliente";
    send(sock, message, strlen(message), 0);
    std::cout << "Mensaje enviado al servidor: " << message << std::endl;

    // Cerrar el socket
    closesocket(sock);

    // Limpiar Winsock
    WSACleanup();

    return 0;
}
