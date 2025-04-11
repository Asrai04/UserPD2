cmake_minimum_required(VERSION 3.10)

project(untitled5)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled5 main.cpp
        Mpointers.h
        ListaEnlazada.cpp
        ListaEnlazada.h)

# Vincula la librería ws2_32 que contiene las funciones de Winsock
target_link_libraries(untitled5 PRIVATE ws2_32)