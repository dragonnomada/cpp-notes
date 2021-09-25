#ifndef UTILS

#define UTILS

#include <iostream>

namespace utils {

void saludar(void);

int suma(int, int);

}

// utils::saludar()
// utils::suma(int, int)

#endif

// 
// Librería Estática
// 
// Comparte un código compilado con extensión `lib<name>.a`
// * El código <name>.cpp será compilado al objeto `*.a` y podrá ser usado por otro códigos
// 
// Compilación
// 
// g++ -o utils.o -c utils.cpp
// ar rvs libutils.a utils.o
// 
// Distribución
// 
// utils.hpp libutils.a
// 