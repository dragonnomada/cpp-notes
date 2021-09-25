#ifndef STATISTICS

#define STATISTICS

#include <iostream>
#include <string>
#include <vector>

namespace statis {

double sum(std::vector<double>);

double average(std::vector<double>);

}

#endif

// 
// Librerías Dinámicas
// 
// Comparte un código compilado con extensión `lib<name>.so`
// * El código <name>.o será compilado al objeto `*.so` y podrá ser usado por otro códigos
// 
// Compilación
// 
// g++ -c -fPIC <name>.cpp -o <name>.o
// g++ --shared -fPIC -o lib<name>.so <name>.o
// 
// Distribución
// 
// <name>.hpp lib<name>.so
// 

// 
// Notas
// 
// + Al compilar los proyectos que usan la librería dinámica, aumentarán el código del ejecutable
//   ya que el compilador no incluíra la librería
// - El usuario deberá disponer en todo momento de la librearía
// * El ejecutable buscará la librería en alguna de las siguiente rutas
//   <ruta del ejecutable>/ /usr/local/lib /usr/lib /lib
// ! Si el ejecutable no encuentra la librería provocará error 
// + La librería no es requerida hasta que el programa es ejecutado
// 
