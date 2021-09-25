#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>

#define FORK_SIZE 5

struct ForkData {
    std::string language;
    std::string message;
};

int main() {
    std::cout << "<<<-------------- INICIO --------------" << std::endl;

    ForkData forks_data[FORK_SIZE] {
        { "es", "Hola mundo" },
        { "en", "Hello world" },
        { "it", "Ciao mondo" },
        { "fr", "Salut monde" },
        { "al", "Hallo welt" }
    };

    bool isParent = true;

    int fork_id = -1;

    for (int i = 0; i < FORK_SIZE; i++) {
        pid_t pid = fork();

        // pid > 0 - Padre/Raíz
        // pid = 0 - Hijo/Rama
        // pid = -1 - ERROR

        if (pid == -1) {
            std::cout << "ERROR: No se pudo ramificar el programa " << i << std::endl;
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            fork_id = i + 1;
            std::cout << "Hijo " << fork_id << " Ramificado" << std::endl;
            isParent = false;
            break;
        }

        usleep(100);

    }

    usleep(100);

    if (isParent) {
        std::cout << "--------- PROCESOS LANZADOS ----------" << std::endl;

        std::cout << "[+] Proceso Padre: " << fork_id << " " << getpid() << std::endl;

        std::cout << "------- PROCESOS EJECUTÁNDOSE -------" << std::endl;

        for (int i = 0; i < FORK_SIZE; i++) {
            pid_t pid = wait(NULL); // ~ JOIN

            if (pid >= 0) {
    			std::cout << "[~] Proceso " << pid << " terminado" << std::endl;
    		}
        }

        std::cout << "------- PROCESOS FINALIZADOS --------" << std::endl;

        // TODO: YA TERMINARON TODOS LOS PROCESOS RAMIFICADOS
        std::ofstream fout("output/saludos.txt");
        
        for (int i = 0; i < FORK_SIZE; i++) {

            ForkData data = forks_data[i];
            
            std::ostringstream filename;

            filename << "output/" << data.language << ".txt";

            std::ifstream fin(filename.str());

            char line[256];

            fin.getline(line, 256);

            fout << "Saludo: " << data.language << std::endl;
            fout << line << std::endl;
            fout << "Fin del saludo: " << data.language << std::endl;

            fin.close();
        }

        fout.close();
    } else {
        int index = fork_id - 1; // Rama k-ésima => Índice de la i-rama

        ForkData data = forks_data[index]; // 
        
        std::cout << "* [" << fork_id << "] Procesando Datos: " << " " << data.language << std::endl;

        // TODO: PROCESAR LA RAMA
        std::ostringstream filename;
        filename << "output/" << data.language << ".txt";
        std::ofstream fout(filename.str());
        fout << data.message << std::endl;
        fout.close();
        
        std::cout << "* [" << fork_id << "] Procesado Finalizado: " << getpid() << " " << data.language << std::endl;
        exit(EXIT_SUCCESS);
    }

    std::cout << "[-] Proceso Padre: " << fork_id << " " << getpid() << std::endl;

    std::cout << ">>>--------------- FIN ----------------" << std::endl;
}
