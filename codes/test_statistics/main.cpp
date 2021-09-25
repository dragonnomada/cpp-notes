#include <iostream>
#include <vector>
#include "statistics.hpp"

int main() {
    std::vector<double> edades;

    edades.push_back(18);
    edades.push_back(25);
    edades.push_back(13);
    edades.push_back(35);
    edades.push_back(22);

    double edades_suma = statis::sum(edades);
    double edad_promedio = statis::average(edades);

    std::cout << "Suma edades: " << edades_suma << " Edad promedio: " << edad_promedio << std::endl;
}

// 
// Librerías Dinámicas
// 
// Uso (Compilación)
// 
// g++ -o main main.cpp lib<name>.so
// 
// Ejecutable
// 
// ./main
// 