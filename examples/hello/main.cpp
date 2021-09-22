// 
// hello - main.cpp
// 
// Muestra el uso de un programa de C++
// 
// Autor: Alan Badillo Salas [Dragón Nómada](dragonnomada123@gmail.com)
// Versión: Septiembre 2021 v1.0.0
// Github: https://github.com/dragonnomada/cpp-notes/tree/main/examples/hello
// 

// Se incluyen las definiciones de la librería estándar <iostream>
#include <iostream>

// Se define la función de entrada
int main() {
    // Imprime en pantalla `Hello world!` y salto de línea
    std::cout << "Hello world!" << std::endl;
}

// Compilación del archivo objeto (código máquina):
// 
// g++ -c main.cpp -o main.o
// 
// Archivo Objeto:
// main.o
// 

// Compilación del archivo ejecutable a través del archivo objeto:
// 
// g++ -o main main.o
// 
// Archivo ejecutable:
// main
// 

// Compilación del archivo ejecutable a través del archivo código:
// 
// g++ -o main main.cpp
// 
// Archivo ejecutable:
// main
// 

// * NOTAS:
// * Crear el archivo objeto no es necesario más que para construir librerías
// * El archivo objeto es una especie de precompilado (código máquina)
// * Se puede compilar directamente el código fuente