#include <iostream>
#include "utils.hpp"

int main() {
    utils::saludar();

    int resultado = utils::suma(100, 200);

    std::cout << resultado << std::endl;
}

// 
// Librerías Estáticas
// 
// Uso (Compilación)
// 
// g++ -o main main.cpp lib<name>.a
// 
// Ejecutable
// 
// ./main
// 