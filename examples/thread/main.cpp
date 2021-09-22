// 
// thread - main.cpp
// 
// Muestra el manejo de hilos con std::thread
// NOTA: Requiere C++11 o superior y la librería pthread.h
// 
// Autor: Alan Badillo Salas [Dragón Nómada](dragonnomada123@gmail.com)
// Versión: Septiembre 2021 v1.0.0
// Github: https://github.com/dragonnomada/cpp-notes/tree/main/examples/thread
// 

// Librerías estándar
// <iostream> std::cout
// <thread> std::thread
// <unistd> sleep
// <ctime> time_t time difftime
#include <iostream>
#include <thread>
#include <unistd.h>
#include <ctime>

// Definimos una estructura para enviar datos al hilo
struct TaskData {
    int id; // ID del hilo
    std::string label; // Mensaje asociado
    int value; // Segundos a esperar
};

// Definimos la Función a ejecutar en el hilo
// TaskData data - datos asociados al hilo cuándo es lanzado
void task(TaskData data) {
    // Imprime el ID del hilo y los segundos a esperar
    std::cout << "Task ID [" << data.id << "] " << " esperando " << data.value << " segundos..." << std::endl;
    // Espera tantos segundos como se hayan especificado
    sleep((unsigned int) data.value); // sleep(seconds) duerme al hilo tantos segundos
    // Imprime el mensaje asociado al hilo
    std::cout << "Task ID [" << data.id << "] " << data.label << " listo." << std::endl;
}

// Función de entrada
int main() {

    // Guardamos la hora actual (hora de inicio)
    time_t start = time(0);

    // Creamos un hilo basado en la función `task` y un `TaskData` asociado
    std::thread t1(task, (TaskData) { 1, "L", 4 });

    // Creamos un hilo basado en la función `task` y un `TaskData` asociado
    std::thread t2(task, (TaskData) { 2, "H", 2 });

    // Creamos un hilo basado en la función `task` y un `TaskData` asociado
    std::thread t3(task, (TaskData) { 3, "A", 5 });

    // Creamos un hilo basado en la función `task` y un `TaskData` asociado
    std::thread t4(task, (TaskData) { 4, "O", 3 });

    // Esperamos a que termine el hilo 1 (4 segundos)
    t1.join();
    std::cout << "T1 JOINED" << std::endl;
    // Esperamos a que termine el hilo 2 (2 segundos)
    // * NOTA: El hilo 2 ya terminó porque ya han pasado 4 segundos
    t2.join();
    std::cout << "T2 JOINED" << std::endl;
    // Esperamos a que termine el hilo 3 (5 segundos)
    // * NOTA: Hasta aquí ya han pasado 4 segundos, por lo que esperará 1 segundo más
    t3.join();
    std::cout << "T3 JOINED" << std::endl;
    // Esperamos a que termine el hilo 4 (3 segundos)
    // * NOTA: El hilo 4 ya terminó ya que hasta aquí han pasado 5 segundos
    t4.join();
    std::cout << "T4 JOINED" << std::endl;

    // Indicamos que todos los hilos han finalizado y el tiempo transcurrido
    std::cout << "Hilos finalizados en " << difftime(time(0), start) << " segundos" << std::endl;
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
// [1] https://www.geeksforgeeks.org/multithreading-in-cpp/
// 