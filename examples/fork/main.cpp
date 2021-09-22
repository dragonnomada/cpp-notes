// 
// fork - main.cpp
// 
// Muestra el manejo de ramificaciones con fork()
// 
// Autor: Alan Badillo Salas [Dragón Nómada](dragonnomada123@gmail.com)
// Versión: Septiembre 2021 v1.0.0
// Github: https://github.com/dragonnomada/cpp-notes/tree/main/examples/thread
// 

// Librerías estándar
// <iostream> std::cout
// <sys/wait.h> wait
// <unistd> usleep fork pid_t
// <ctime> time_t time difftime
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

// Define una constante con el número de ramas que haremos
#define FORK_SIZE 4

// Define una estructura para almacenar los datos de cada rama
struct ChildData {
    std::string label;
};

// Define la función de entrada
int main() {
    // Sólo se imprime en la rama principal
    std::cout << "<<<-------------- INICIO --------------" << std::endl;

    // Datos de todas las ramas
    ChildData children_data[FORK_SIZE] {
        { "Data 1" }, // Datos para la rama 1
        { "Data 2" }, // Datos para la rama 2
        { "Data 3" }, // Datos para la rama 3
        { "Data 4" }  // Datos para la rama 4
    };

    // Suponemos que la rama principal es la rama padre
    bool isParent = true;

    // No debería tener ningún índice de rama positivo
    int child_id = -1;

    // Proceso de ramificación
    // Creamos una rama en cada iteración
    for (int i = 0; i < FORK_SIZE; i++) {
        // Solicita la rama nueva
        // Aquí el `pid` podría ser positivo, indicando que ya hay una rama previa
        pid_t pid = fork();

        // Si la rama no pudo ser creada abortamos
        if (pid == -1) {
            std::cout << "ERROR: No se pudo ramificar el hijo " << i << std::endl;
            exit(EXIT_FAILURE);
        }

        // Si la rama pudo ser creada su `pid` será 0
        if (pid == 0) {
            // Retenemos el número de iteración como el id de la rama
            child_id = i + 1;
            std::cout << "Hijo " << child_id << " Ramificado" << std::endl;
            // Determinamos que la rama no es la principal
            isParent = false;
            // Rompemos el ciclo para no generar más ramas a partir de aquí
            break;
        }

        // Hacemos un retraso de 100 ms para evitar imprimir al mismo tiempo
        usleep(100);

    }

    // Hacemos otro retraso para la última rama
    usleep(100);

    // Si después de ramificar todas las ramas todos los `pid` fueron positivos
    // significa que esta es la rama principal (rama padre)
    if (isParent) {
        std::cout << "--------- PROCESOS LANZADOS ----------" << std::endl;

        std::cout << "[+] Proceso Padre: " << child_id << " " << getpid() << std::endl;

        // TODO: Aquí coloca el código previo a esperar a que finalicen las ramas

        std::cout << "------- PROCESOS EJECUTÁNDOSE -------" << std::endl;

        for (int i = 0; i < FORK_SIZE; i++) {
            pid_t pid = wait(NULL);

            if (pid >= 0) {
    			std::cout << "[~] Proceso " << pid << " terminado" << std::endl;
    		}
        }

        std::cout << "------- PROCESOS FINALIZADOS --------" << std::endl;

        // TODO: Aquí coloca el código posterior a esperar a que finalicen las ramas
        // Todas las ramas han finalizado
    } else {
        // Si la rama no es la principal, significa que es una nueva rama
        // Obtenemos el índice de la rama para extraer los datos de la rama
        int index = child_id - 1;
        // Obtenemos los datos de la rama
        ChildData data = children_data[index];

        std::cout << "* [" << child_id << "] Procesando Datos: " << " " << data.label << std::endl;

        sleep(FORK_SIZE - child_id);
        
        // TODO: Aquí coloca el código de la rama y todo lo que tenga que procesar según sus datos

        std::cout << "* [" << child_id << "] Procesado Finalizado: " << getpid() << " " << data.label << std::endl;

        // Notifica al sistema operativo que la rama ha concluído exitósamente
        exit(EXIT_SUCCESS);
    }

    std::cout << "[-] Proceso Padre: " << child_id << " " << getpid() << std::endl;

    // TODO: Aquí coloca el código posterior a esperar a que finalicen las ramas
    // Finaliza la rama principal (rama padre)

    // Sólo se imprime en la rama principal
    std::cout << ">>>--------------- FIN ----------------" << std::endl;
}


// Compilación:
// g++ -o main main.cpp -lpthread
// 
// Ejecución:
// ./main

// * NOTAS:
// ! Podría ser necesario compilar con `g++ -std=c++11 -o main main.cpp -lpthread`

// REFERENCIAS
// 
// [1] https://www.delftstack.com/es/howto/cpp/cpp-fork/
// [2] https://www.section.io/engineering-education/fork-in-c-programming-language/
// [3] https://gist.github.com/dgacitua/64ff00e90d5e21f9c3f7
// 