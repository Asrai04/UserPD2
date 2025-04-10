#ifndef M_POINTERS_H
#define M_POINTERS_H

#include <iostream>
#include <string>

template<typename T>

class Mpointers {
    private:
        int puerto;
        T value;
        int id_Memory_Block = -1;
    public:

    explicit Mpointers(int puerto) : value(T()), puerto(puerto) {
        sendServer("Create" );
    }

    T operator*() {
    }

    void operator=(T NewValue) {
    }

    static void sendServer(std::string Mensaje){}

    int getPuerto() {
    }

    int getId_Memory_Block() {
    }

    T getValue() {
    }



};

#endif // M_POINTERS_H
