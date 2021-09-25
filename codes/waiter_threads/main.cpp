#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

struct Context {
    bool* stopped;
};

void task1(Context ctx) {
    while (!*ctx.stopped) {
        cout << "Realizando tarea TAREA_1 del hilo..." << endl;
        sleep(3);
    }
}

void task2(Context ctx) {
    while (!*ctx.stopped) {
        cout << "Realizando tarea TAREA_2 del hilo..." << endl;
        sleep(4);
    }
}

int main() {
    bool* stopped = new bool(false);

    Context ctx { stopped };

    thread t1(task1, ctx);
    thread t2(task2, ctx);

    int i = 0;

    while (!*ctx.stopped) {
        cout << "Realizando tarea GLOBAL..." << endl;
        sleep(10); // BLOQUEA EL HILO PRINCIPAL
        ++i;
        if (i == 2) {
            *ctx.stopped = true;
        }
    }

    t1.join();
    t2.join();
}