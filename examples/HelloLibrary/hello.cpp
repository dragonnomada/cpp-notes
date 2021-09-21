// 
// HelloLibrary - hello.cpp
// 
// Impementa la librería `hello.h | HELLO_H`
// 
// Autor: Alan Badillo Salas [Dragón Nómada](dragonnomada123@gmail.com)
// Versión: Septiembre 2021 v1.0.0
// Github: https://github.com/dragonnomada/cpp-notes/tree/main/examples/HelloLibrary
// 

// Implementamos la librería "hello.h"
#include "hello.h"

// Implementamos la función sayHello (void) -> void
// * Nota: No es necesario incluir nuevamente la librería <iostream>
void sayHello() {
    std::cout << "Hello world" << std::endl;
}