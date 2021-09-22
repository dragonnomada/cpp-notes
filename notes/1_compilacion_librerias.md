# Compilación y Librerías

Autor: Alan Badillo Salas [Dragón Nómada](mailto:dragonnomada123@gmail.com)

## Compilación

El proceso de compilación consiste en generar código máquina a partir del código fuente.

El compilador `g++` tomará el código fuente y creará *archivos objeto* con extensión `*.o` al usar el comando de compilación `g++ -c <source>.cpp -o <target>.o`, creando así para un archivo `hello.cpp` el archivo `hello.o`.

> Ejemplo de un código fuente

```cpp
#include <iostream>

int main() {
    std::cout << "Hello world!" << std::endl;
}
```

> Ejemplo de compilación a código máquina

```bash
g++ -c main.cpp

--- ls *.o ---
main.o
```

### Compilación de Ejecutables

Los *archivo objeto* pueden ser utilizados para generar aplicaciones ejecutables mediante el comando `g++ -o <exec> <target>.o` o directamente con `g++ -o <exec> <source>.cpp`.

> Ejemplo de compilación a un ejecutable

```bash
g++ -o main main.o

--- ls --
main main.cpp main.o
```

> Ejemplo de lanzar el ejecutable

```bash
./main

--- salida ---
Hello world!
```

> Ejemplo de compilación directa sin generar código máquina

```bash
g++ -o main main.cpp

--- ls --
main main.cpp
```

* **Nota:** El crear el código máquina permitirá crear un objeto compilado que podrá ser utilizado para compilar posteriores programas, utilice esta opción si su intención es crear librerías estáticas o dinámicas o reutilizar su código compilado.

## Librerías Estáticas

Las librerías estáticas son piezas de código que se pueden reutilizar en varios proyectos. Estas librerías **son incluídas dentro de los ejecutables compilados** de otros proyectos haciendo que el código máquina generado por la librería sea **portable de forma estática**, lo que significa, que los ejecutables **incluirán la librería** dentro de él y **no habrá necesidad que la librería esté en la máquina del usuario**.

    La librería estática es un archivo `lib<name>.a` que puede ser usada para compilar otros proyectos que hagan uso de la la declaración `<name>.h`.

Las librerías se componen de dos archivos.

* **Archivo Cabecera | `header.h`** - Este archivo declara todas las piezas de la librería disponibles en otros códigos. Generalmente no incluyen la implementación, sólo las definiciones. Se puede imaginar esta cabecera como la declaración de la librería (el código compartido).
* **Archivo Código | `code.cpp`** - Este archivo implementa las piezas incluídas en la librería. Una librería puede tener uno o varios archivos de código de implementación. Se puede imaginar este archivo como la implementación de la librería (el código oculto).

Las librerías generalmente no exponen su código, sólo sus definiciones. Por ejemplo, las funciones disponibles, clases, nombres de espacios, etc.

> Ejemplo de la librería `hello.h`

```cpp
// Comprobamos que la librería no esté definida aún
#ifndef HELLO_H

// Definimos la librería y reservamos el nombre HELLO_H
#define HELLO_H

// Declaramos los miembros de la librería

// Incluímos librerías utilizadas en la implementación
#include <iostream>

// Declaramos la función sayHello (void) -> void
void sayHello();

// Finalizamos las declaraciones
#endif
```

[Ver archivo hello.h](../examples/HelloLibrary/hello.h)

> Ejemplo de la implementación `hello.cpp`

```cpp
// Implementamos la librería "hello.h"
#include "hello.h"

// Implementamos la función sayHello (void) -> void
// * Nota: No es necesario incluir nuevamente la librería <iostream>
void sayHello() {
    std::cout << "Hello world" << std::endl;
}
```
[Ver archivo hello.cpp](../examples/HelloLibrary/hello.cpp)

### Compilación de una librería estática

Para compilar la librería estática (archivo `*.a`), debemos usar el *archivo objeto* y usar el comando `ar rvs lib<name>.a <name>.o`. El archivador `ar` genera los archivos de librería (formalmente bibliotecas) y permite actualizar y enlazarlos.

> Ejemplo de la compilación de la librería `hello.h`

```bash
# Genera el <archivo objeto>
g++ -c hello.cpp -o hello.o

# Compila la librería estática
ar rvs libhello.a hello.o

--- ls --
hello.cpp hello.o libhello.a
```

### Uso de la librería estática

Ahora podemos distribuir el archivo `lib<name>.a` y `<name>.h` para usar la librería en otros proyectos. Al compilar el proyecto debemos incluir el archivo `lib<name>.a` cómo si tratara de `<name>.o`. 

La diferencia es que la librería estática no será tratada como un *archivo objeto* (código máquina), sino que incluirá un **static linking** (enlazado estático) o **early binding** (enlazado tardío). Esto permitirá manipular un único objeto llamado librería (`*.a`) en lugar de múltiples *archivo objeto* (`*.o`).

> Ejemplo del archivo `main.cpp` que usa la librería `hello.h`

```cpp
// Incluímos las cabeceras
#include "hello.h"

// Definimos la función de entrada
int main() {

    // Cosumimos la librería
    sayHello();
    
}
```

[Ver archivo main.cpp](../examples/HelloStaticApp/main.cpp)

> Ejemplo de la compilación de un archivo `main.cpp` que usa la librería estática `hello.h` compilada en `libhello.a`

```bash
g++ -o main main.cpp libhello.a

--- ls --
main.cpp main hello.h libhello.a
```

* **Nota:** El archivo `libhello.a` junto a su cabecera `hello.h` son distribuibles para cualquier proyecto que los quiera incorporar.

## Librerías Dinámicas

Las librerías dinámicas son piezas de código que se pueden reutilizar en varios proyectos. Estas librerías **no son incluídas dentro de los ejecutables compilados** de otros proyectos haciendo que el código máquina generado por la librería sea **portable de forma dinámica**, lo que significa, que los ejecutables **no incluirán la librería** dentro de él, sino que llamarán de forma dinámica a librería y **habrá necesidad que la librería esté en la máquina del usuario** en la carpeta `/lib`, `/usr/lib`, `/usr/local/lib` o junto al ejecutable.

    La librería dinámica es un archivo `lib<name>.so` (o `lib<name>.dll` en windows) que puede ser usada para compilar otros proyectos que hagan uso de la la declaración `<name>.h`.

Las librerías se componen de dos archivos.

La diferencia entre las librerías dinámicas y estáticas está en el proceso de compilación, los archivos `<header>.h` y `<code>.cpp` serán los mismos.

Por ejemplo, el archivo [hello.h](../examples/HelloLibrary/hello.h) y [hello.cpp](../examples/HelloLibrary/hello.cpp)

### Compilación de una librería dinámica

Para compilar la librería dinámica (archivo `*.so`), debemos usar el *archivo objeto* marcado con la bandera `-fPIC`, usando el comando `g++ -c -fPIC <name>.cpp -o lib<name>.o` y usar el comando `g++ --shared --fPIC -o lib<name>.so lib<name>.o`. El compilador `g++` entenderá que se quiere generar una librería dinámica compartida y hacer que los ejecutables busquen la librería `lib<name>.so` en las carpetas `/lib`, `/usr/lib`, `/usr/local/lib` o junto al ejecutable.

> Ejemplo de la compilación de la librería `hello.h`

```bash
# Genera el <archivo objeto>
g++ -c -fPIC hello.cpp -o libhello.o

# Compila la librería estática
g++ --shared --fPIC -o libhello.so libhello.o

--- ls --
hello.cpp libhello.o libhello.so
```

### Uso de la librería estática

Ahora podemos distribuir el archivo `lib<name>.so` y `<name>.h` para usar la librería en otros proyectos. Al compilar el proyecto debemos incluir el archivo `lib<name>.so` cómo si tratara de `<name>.o`. 

La diferencia es que la librería dinámica no será tratada como un *archivo objeto* (código máquina), sino que incluirá un **dynamic linking** (enlazado dinámico). Esto permitirá manipular un único objeto llamado librería (`*.so`) en lugar de múltiples *archivo objeto* (`*.o`).

> Ejemplo del archivo `main.cpp` que usa la librería `hello.h`

```cpp
// Incluímos las cabeceras
#include "hello.h"

// Definimos la función de entrada
int main() {

    // Cosumimos la librería
    sayHello();
    
}
```

[Ver archivo main.cpp](../examples/HelloDynamicApp/main.cpp)

> Ejemplo de la compilación de un archivo `main.cpp` que usa la librería dinámica `hello.h` compilada en `libhello.so`

```bash
g++ -o main main.cpp libhello.so

--- ls --
main.cpp main hello.h libhello.so
```

* **Nota:** El archivo `libhello.so` junto a su cabecera `hello.h` son distribuibles para cualquier proyecto que los quiera incorporar.

* **Advertencia:** Al ejecutar el archivo compilado `main` deberá estar la librería `libhello.so` junto al ejecutable o en la carpeta `/lib`, `/usr/lib` o `/usr/local/lib`.

## Referencias

> [1] https://www.bogotobogo.com/cplusplus/libraries.php

> [2] http://www.fdi.ucm.es/profesor/luis/fp/devtools/MinGWUso.html

> [3] https://www.geeksforgeeks.org/compiling-with-g-plus-plus/