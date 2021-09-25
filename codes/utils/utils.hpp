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
// * El código <name>.o será compilado al objeto `*.a` y podrá ser usado por otro códigos
// 
// Compilación
// 
// g++ -o <name>.o -c <name>.cpp
// ar rvs lib<name>.a <name>.o
// 
// Distribución
// 
// <name>.hpp lib<name>.a
// 

// 
// Notas
// 
// - Las librerías estáticas insertan todo el código compilado (toda la librería)
//   dentro de los proyectos que estemos compilando (aumentan el tamaño de los proyectos)
// + Las aplicaciones compiladas mediante librerías estáticas no requieren que el usuario
//   posea la librería (ya está incluída en el ejecutable). Esto hace que las aplicaciones
//   sean portables en un solo binario.
// 