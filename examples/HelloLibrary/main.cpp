// 
// HelloLibrary - main.cpp
// 
// Muestra el uso de la librería local `hello.h`
// 
// Autor: Alan Badillo Salas [Dragón Nómada](dragonnomada123@gmail.com)
// Versión: Septiembre 2021 v1.0.0
// Github: https://github.com/dragonnomada/cpp-notes/tree/main/examples/HelloLibrary
// 

// Incluímos la librería que hemos creado
#include "hello.h"

// Definimos la función de entrada
int main() {

    // Usamos la función expuesta en nuestra librería
    sayHello();

}

// LIBRERÍA OBJETO

// Compilación de la librería a un archivo de objeto (código máquina):
// g++ -c hello.cpp -o hello.o
// 
// Archivo Objeto:
// hello.o

// Compilación del ejecutable con el archivo objeto:
// g++ -o main main.cpp hello.o
// 
// Ejecutable:
// main

// LIBRERÍA ESTÁTICA

// Compilación de la librería estática
// ar rvs libhello.a hello.o
// 
// Librería estática:
// libhello.a

// Compilación del ejecutable con la librería estática:
// g++ -o main main.cpp libhello.a
// 
// Ejecutable:
// main

// LIBRERÍA DINÁMICA

// g++ -c -fPIC hello.cpp -o libhello.o
// g++ --shared --fPIC -o libhello.so libhello.o
// 
// Librería dinámica:
// libhello.so
// 
// * NOTAS:
// ~ Se agregó la bandera -fPIC en la compilación del archivo de objeto `libhello.o`
// ~ Esto permitirá compilar la librería `libhello.so`
// ! No funcionará `g++ --shared --fPIC -o libhello.so hello.o`
// ~ Ya que el archivo de objeto `hello.o` no fue marcardo como -fPIC

// Compilación del ejecutable con la librería dinámica:
// g++ -o main main.cpp ./libhello.so
// 
// Ejecutable:
// main

// REFERENCES
// 
// [1] https://www.bogotobogo.com/cplusplus/libraries.php
// 