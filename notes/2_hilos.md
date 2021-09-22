# Manejo de Hilos

Autor: Alan Badillo Salas [Dragón Nómada](mailto:dragonnomada123@gmail.com)

## Hilos en C/C++ y POSIX

En versiones previas a C++11 el manejo de hilos se hacía a través del sistema operativo y la librería `<pthread.h>`.

En el siguiente tutorial puede encontrar información al respecto si desea manejar hilos de esta forma. Sin embargo, no hay estandarización entre sistemas operativos y lo más probable es que el código sólo funcione para sistemas operativos UNIX.

[Tutorials Point - C++ Multithreading](https://www.tutorialspoint.com/cplusplus/cpp_multithreading.htm)

## Hilos en C++11

Para manejar hilos en C++11 debemos incluir la librería `<thread>` para acceder a la clase `std::thread`, la cuál creará un nuevo hilo basado en una función.

La función asociada al hilo deber ser de la forma `void <name>(void)` si no recibe parámetros o de la forma `void <name>(<decay type>)` si recibe algún parámetro. Consulta la referencia al [Tipo Decay](https://www.cplusplus.com/reference/type_traits/decay/).

Un hilo es un proceso que se ejecuta de forma independiente al proceso principal del programa, realizando operaciones sin interferir o bloquear el hilo principal. Por ejemplo, piense en descargar una imágen desde internet, mientras al mismo tiempo se desea leer un archivo de audio. Estas son dos tareas independientes que se podrían procesar al mismo tiempo, sin tener que esperar a que una termine para comenzar la otra. De esta forma, se puede conseguir lo que se conoce como **Multithreading** (programación concurrente o multi-hilos). 

Así entonces, para lograr ejecutar tareas independientes al mismo tiempo, podemos definir funciones que reciban o no un argumento y lanzarlas en hilos de procesamiento independientes.

Cuándo un hilo es creado, este es ejecutado inmediatamente y mediante `<thread>.join()` podemos hacer que el programa espere hasta que el hilo finalice, si el hilo ya está finalizado en ese momento, el programa continuará, sino hará la espera.

### Paso 1 - Define la función objetivo

Primero debemos establecer la función que será ejecutada en el hilo.

> Ejemplo de una función objetivo sin argumento

```c++
void printHello() {
    std::cout << "Hello" << std::endl;
}
```

> Ejemplo de una función objetivo con argumento simple

```c++
void printId(int id) {
    std::cout << "ID: " << id << std::endl;
}
```

> Ejemplo de una función con argumento complejo

```c++
struct Product {
    int id;
    std::string name;
    double price;
}

void printProduct(Product product) {
    std::cout << "Product [" << product.id << "]: " << product.name << "(" << product.price << ")" << std::endl;
}
```

* **Nota:** El argumento complejo también podría ser una clase, puntero o cualquier [Tipo Decay](https://www.cplusplus.com/reference/type_traits/decay/).

### Paso 2 - Construir el hilo (lanzarlo/iniciarlo)

Una vez definida la función que será ejecutada, debemos crear el hilo, que reciba en su contructor la función objetivo y el argumento en caso necesario.

> Ejemplo de un hilo sin argumento

```c++
std::thread t1(printHello);
```

> Ejemplo de un hilo con argumento simple

```c++
int id = 5;

std::thread t2(printId, id);
```

* **Nota:** En corto `std::thread t2(printId, 5);`.

> Ejemplo de un hilo con argumento complejo

```c++
Product product = {123, "Coca Cola", 18.5};

std::thread t3(printProduct, product);
```

* **Nota:** En corto `std::thread t3(printProduct, (Product) {123, "Coca Cola", 18.5});`.

### Paso 3 - Esperar a que finalice el hilo (juntarlo/completarlo)

Al crear un hilo, estos se invocan automáticamente y ejecutan la función objetivo con el argumento dado. Sin embargo, si el programa finaliza antes de haber esperado a que el hilo finalice se devolverá una señal de error. Para evitar esto, es necesario juntar el hilo al proceso principal. Este juntado es conocido como el `join` y consiste en pegar el hilo al proceso principal.

Imagina que el hilo se está ejecutando y esperando a que finalice su operación, por ejemplo, que la base de datos inserte un registro. Entonces, en algún momento el hilo finalizará, pero no se sabe determinísisticamente cuánto tiempo pasará. Así que el hilo se mantendrá en ejecución desde que fue creado.

La función `<thread>.join()` nos permitirá retener el proceso hasta que el hilo finalice, a esto se le conoce como *JUNTADO*, ya que el proceso principal está esperando a que el hilo se junte y continue el proceso principal.

Finalmente, cuándo tenemos varios hilos, podemos hacer que se peguen al proceso principal, para determinar que los hilos ya finalizaron. Podríamos de forma avanzada crear funciones dedicadas a esperar conjuntos de hilos, a este proceso se le conoce como *batching*, ya que una *batería* de hilos estarían siendo esperados a completarse antes de la siguiente. Por ejemplo, ejecutar 5 hilos que descargue una imagen en cada uno, luego esperar a que finalicen los 5 hilos para el siguiente *batch* de imágenes, es decir, estaríamos descargando imágenes de 5 en 5.

> Ejemplo de la espera de una serie de hilos

```c++
t1.join() // Tiempo transcurrido: 0 | Tiempo del hilo para finalizar 5s
t2.join() // Tiempo transcurrido: 5 | Tiempo del hilo para finalizar 2s (* Ya había finalizado, se pega inmediatamente)
t3.join() // Tiempo transcurrido: 5 | Tiempo del hilo para finalizar 6s (* Espera un segundo más para finalizar)
// Tiempo transcurrido: 6
```

Como se puede observar en el ejemplo, los hilos que tardan más bloquean el proceso principal hasta acabar, y los que ya habían finalizado no aumentan tiempo al proceso principal. Es decir, los hilos bloquean el proceso principal hasta acabar.

> Ejemplo de la espera de una serie de hilos en batches

```c++
vector<thread> threads;

// Inicializamos una lista de hilos
// Los hilos comienzan a ejecutarse mientras se agregan otros en cada iteración
for (int i = 0; i < BATCH_SIZE; i++) {
    thread t(task, data); // Lanza un hilo `t`
    threads.push_back(t); // Guarda el hilo `t` en la lista de hilos
}

// Los hilos se están ejecutando

// Recorremos cada hilo en la lista para esperar a que acaben
// No se pasará a la siguiente iteración hasta que el hilo haya acabado
// Si el hilo ya había acabado continua al siguiente hilo
// Uno tras otro los hilos se van juntando
for (auto it = threads.begin(); it != threads.end(); it++) {
    thread t = *it; // Recuperamos el hilo de la lista
    t.join(); // Esperamos a que el hilo finalice
}

// En este punto todos los hilos de la lista ya finalizaron
// Podemos decir que el *batch* está completado
```

[Revisar el ejemplo completo sobre Hilos](../examples/thread/main.cpp)