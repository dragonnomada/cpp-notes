// Aplicación que usa la librería estática `libhello.a`

// Incluímos las cabeceras
#include "hello.h"

// Definimos la función de entrada
int main() {

    // Cosumimos la librería
    sayHello();
    
}

// Compilación:
// g++ -o main main.cpp libhello.a
// 
// Aplicación distribuible:
// main
// 
// * NOTAS:
// - Las aplicaciones compiladas usando librerías estáticas pesan más
// * Estas incluyen dentro del ejecutable las implementaciones de la librería
// + No dependen de la librería `*.a` para ejecutarse
// + Esto las vuelve portables y compartibles
// * Se pueden distribuir las librerías y colocarlas en `/lib`, `/usr/lib` o `/usr/local/lib`
// + Se pueden compilar múltiples proyectos con la misma librería compartida
// + Si la librería es borrada, el ejecutable seguirá funcionando 
// ? CASO DE USO: Aplicaciones distribuíbles sin dependencia de librerías
// ? CASO DE USO: Librerías para proyectos específicos (consumibles)
// ? CASO DE USO: El usuario sólo necesita el ejecutable para funcionar