// Aplicación que usa la librería dinámica `libhello.so`

// Incluímos las cabeceras
#include "hello.h"

// Definimos la función de entrada
int main() {

    // Cosumimos la librería
    sayHello();
    
}

// Compilación:
// g++ -o main main.cpp ./libhello.so
// 
// Aplicación distribuible:
// main libhello.so
// 
// * NOTAS:
// + Las aplicaciones compiladas usando librerías dinámicas pesan menos
// + Estas no incluyen dentro del ejecutable las implementaciones de la librería
// - Sin embargo, dependen de la librería `*.so` para ejecutarse
// + Esto las vuelve portables y compartibles
// * Se pueden distribuir las librerías y colocarlas en `/lib`, `/usr/lib` o `/usr/local/lib`
// + Se pueden compilar múltiples proyectos con la misma librería compartida
// - Si la librería es borrada, el ejecutable quedará inservible 
// ? CASO DE USO: Aplicaciones distribuíbles con dependencia de librerías
// ? CASO DE USO: Librerías para proyectos compartidos (utilería)
// ? CASO DE USO: El usuario necesita instalar la librería para usar el ejecutable