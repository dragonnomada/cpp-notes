#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <ctime>
#include <unistd.h>

using std::cout;
using std::endl;
using std::thread;
using std::vector;
using std::ofstream;

void write_hello_file(int id) {
    ofstream fout;

    char buffer[100];

    sprintf(buffer, "output/hello_%d.txt", id);
    
    fout.open(buffer);

    for (int i = 0; i < 3000; i++) {
        fout << i << ". " << "Hola mundo" << endl;
    }

    fout.close();
}

int main() {
    time_t start = time(0);

    // write_hello_file(0);

    vector<thread> threads;

    for (int i = 1; i < 200; i++) {
        thread t(write_hello_file, i);
        threads.push_back(std::move(t));
    }

    for (thread& t : threads) {
        t.join();
    }

    // thread t1(write_hello_file, 1);
    // thread t2(write_hello_file, 2);
    // thread t3(write_hello_file, 3);
    // thread t4(write_hello_file, 4);

    // t1.join();
    // t2.join();
    // t3.join();
    // t4.join();

    time_t end = time(0);

    cout << "Finalizado " << difftime(end, start) << " segundos" << endl;
}