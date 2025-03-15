+++
date = '2025-03-11'
draft = false
title = 'Practica 1: Elementos básicos de los lenguajes de programación'
+++

# Introducción
En esta práctica se exploran los elementos fundamentales de los lenguajes de programación mediante la implementación de un sistema de gestión de biblioteca en el lenguaje C. Los lenguajes de programación cuentan con diversos conceptos esenciales que permiten la creación y manipulación de estructuras de datos, la administración de memoria y el control del flujo de ejecución en los programas.

# Desarrollo
Identifica los elementos fundamentales de los lenguajes de programación: nombres, marcos de activación, bloques de alcance, administración de memoria, expresiones, comandos, control de secuencia como lo es; selección, iteración y recursión, subprogramas, y tipos de datos.
En este documento solo se veran algunas partes del codigo, el codigo completo se puede consultar [Aqui](https://github.com/Blu18/portafolio_paradigmas/blob/master/biblioteca/src/biblioteca.c "Codigo Biblioteca")

__Nombres__

Son identificadores que permiten referenciar variables, funciones, estructuras, constantes, objetos, etc.
```C 
// Varibles globales
static int static_var = 0; // Variable estatica (almacenada en el segmento de datos)
int bss_var; // Variable del segmento BSS (variable global no inicializada)

// Estrucutura y tipos definidos
book_t, member_t // Estructuras para representar libros y miembros
genre_t // Enumeración para clasificar géneros de libros

// Funciones
addBook(), displayBooks(), issueBook(), returnBook()

// Varibles locales
new_book // En addBook().
current // En displayBooksRecursive()
```

__Marcos de activación__

Un marco de activación es un bloque de memoria en la pila (stack) que se crea cuando se llama a una función y se destruye cuando la función termina. Ejemplo con addBook()
```C 
// Se llama la funcion en main()
case 1:
    addBook(&library, &bookCount); // Se crea un marco en el stack y se almacenan los parametros

    // Dentro de addBook()
    book_t *new_book = (book_t *)malloc(sizeof(book_t)); // Se reserva espacio

    // Se ejecuta logica del codigo
    if (!new_book) {
        printf("Error al asignar memoria para el nuevo libro.\n");
        return;
    }
    incrementHeapAllocations(new_book, sizeof(book_t));
    printf("Memoria asignada para un nuevo libro (ID: %d) en el heap\n", new_book->id);

    printf("\nIngresa ID del libro: ");
    scanf("%d", &new_book->id);

    printf("Ingresa titulo del libro: ");
    getchar();
    fgets(new_book->title, 100, stdin);
    new_book->title[strcspn(new_book->title, "\n")] = '\0';

    printf("Ingresa nombre del autor: ");
    fgets(new_book->author, 100, stdin);
    new_book->author[strcspn(new_book->author, "\n")] = '\0';

    printf("Ingresa el ano de publicacion: ");
    scanf("%d", &new_book->publication_year);

    printf("Ingresa el genero del libro (0: FICTION, 1: NON_FICTION, 2: SCIENCE, 3: HISTORY, 4: FANTASY, 5: BIOGRAPHY, 6: OTHER): ");
    int genre;
    scanf("%d", &genre);
    new_book->genre = (genre_t)genre;

    printf("Ingresa la cantidad de libros: ");
    scanf("%d", &new_book->quantity);

    new_book->next = *library;
    *library = new_book;
    (*count)++;

    printf("\nEl libro fue agregado exitosamente!\n");
    displayMemoryUsage();
    // Al finalizar, el marco de activación se destruye y la pila regresa al estado anterior.
```
Si una función es recursiva, como *displayBooksRecursive()*, se crean múltiples marcos de activación, uno por cada llamada recursiva. Esto es clave para entender el uso eficiente de la memoria y evitar desbordamientos de pila (stack overflow).

__Bloques de alcance__

En el caso de C son aquellos que estan delimitados por {} y se pueden encontrar en funciones o if, for, while, etc. En esta ocasion se analizara la funcion findBookById.
Las variables creadan tendran un alcance dentro de su mismo bloque, si se crea una variable en el bloque más interno, esta no se podra usar en un bloque externo.
```C 
int bss_var; // Varible global
// Esta variable se podar usar en todo el programa sin importar donde se utilice ya que esta en el nivel más externo

book_t* findBookById(book_t *library, int bookID) 
{ // Inicio de primer bloque que corresponde a la funcion
    book_t *current = library;
    while (current) 
    { // Inicio de segundo bloque, corresponde a ciclo while
        if (current->id == bookID) 
        { // Inicio de terceer bloque, corresponde a if
            return current;
        } // Fin de bloque if
        current = current->next;
    }// Fin de bloque while
    return NULL;
} // Fin de bloque de funcion
```
Algo que se puede observar en los bloques es que no puedes cerrar un bloque más externo antes de cerrar los mas internos, por ejemplo, no se puede cerrar el bloque while sin haber cerrado el bloque del if.

__Administración de memoria__

Para administrar memoria en este programa se utilizan funciones como malloc(), realloc(), y free()
```C 
// Dentro de addBook()
book_t *new_book = (book_t *)malloc(sizeof(book_t)); // malloc() permite reservar memoria del heap y en este caso regresa el apuntador del espacio de memoria reservado en caso de no poder reservar regresa NULL

// Funcion para liberar memoria de la lista que contiene los libros
void freeLibrary(book_t *library) {
    book_t *current = library;
    while (current) { // Mientras current no sea NULL el ciclo se ejecutara
        book_t *next = current->next; // Recorre la lista
        incrementHeapDeallocations(current);
        free(current); // Libera la memoria del nodo actual
        current = next;
    }
    displayMemoryUsage();
}

// Bloque denrto de3 la funcion issueBook()
if (bookFound && memberFound) {
        bookFound->quantity--;
        memberFound->issued_count++;
        memberFound->issued_books = realloc(memberFound->issued_books, memberFound->issued_count * sizeof(int)); // realloc() permite redimensionar la memoria previamente asignada con malloc ya sea para aumentar o diminuir su tamaño
        incrementHeapAllocations(memberFound->issued_books, memberFound->issued_count * sizeof(int));
        printf("Memoria reasignada para los libros prestados del miembro (ID: %d) en el heap\n", memberFound->id);
        memberFound->issued_books[memberFound->issued_count - 1] = bookID;
        printf("\nLibro prestado satisfactoriamente!\n");
} else {
        printf("\nLibro o miembro no encontrados.\n");
}
```

__Expresiones__

Son constructos sintácticos que da como resultado un valor. Ejemplos:
```C 
memberFound->issued_count++; // Expresion arimetica esto es igual a memberFound->issued_count = memberFound->issued_count + 1
if (current->id == bookID) // Produce un valor booleano True o False
```

__Control de secuencia__

Permite darle un flujo al programa para que este tenga sentido. Para esto tenemos estructuras de selección, iteración y recursividad
```C 
// Seleción
if (bookFound && memberFound) { // En caso se econtrar el libro y el miebro
    // Se realizan las operaciones para asignar el libro al miembro
        bookFound->quantity--;
        memberFound->issued_count++;
        memberFound->issued_books = realloc(memberFound->issued_books, memberFound->issued_count * sizeof(int));
        incrementHeapAllocations(memberFound->issued_books, memberFound->issued_count * sizeof(int));
        printf("Memoria reasignada para los libros prestados del miembro (ID: %d) en el heap\n", memberFound->id);
        memberFound->issued_books[memberFound->issued_count - 1] = bookID;
        printf("\nLibro prestado satisfactoriamente!\n");
    } else { // Si no se encontro el libro, el miembro o ambos el programa sigue esta secuencia
        printf("\nLibro o miembro no encontrados.\n");
    }

// Iteración
while (current_member) { // Mientras la condicion sea verdadera se seguira esta secuencia repetidamente
    if (current_member->id == memberID) { // si el ID del que se busca coincide con uno de la lista  entra al if
        memberFound = current_member; // almacena al miebro que se buscaba
        break;
    }
    current_member = current_member->next; // Permite recorrer la lista de miebros
}

// Recursividad
// En este programa se utiliza la recursividad para recorrer y mostrar la lista de libros
void displayBooksRecursive(book_t *library) {
    if (!library) { // Verifica que lista no apunte a NULL
        return; // En caso de ser NULL sale de la funcion y se termina la recursividad
    }
    printf("\nID libro: %d\nTitulo: %s\nAutor: %s\nAno de publicacion: %d\nGenero: %s\nCantidad: %d\n",
        library->id, library->title, library->author, library->publication_year, genreToString(library->genre), library->quantity); // Imprime datos del libro
    displayBooksRecursive(library->next); // Se vuel a llamar a si misma pero con el siguiente nodo
}
```

__Tipo de datos__

En C a diferencia de lenguajes como Python, es necesario espedificar el tipo de dato de una variable y el tipo de dato que regresa una funcion.
```C 
// Estrucutra para los miebros
typedef struct _member { // typedef permite crear tipos de datos
    int id; // Entero
    char name[100]; // Arreglo de caracteres para simular un string
    int issued_count; // Entero
    int *issued_books; // Apuntador entereo
    struct _member *next; // Apuntador de tipo strcut
} member_t; // Nombre del nuevo tipo de dato

void addBook(book_t **library, int* count); // Funcion que no regresa ningun valor
book_t* findBookById(book_t *library, int bookID); // Funcion que regesa un apuntador de tipo book_t
```

# Conclusión
Con esta práctica reforze los conocimientos sobre la sintaxis y estructura del lenguaje C, también comprendi la importancia de la administración de memoria, la organización del código. La correcta implementación de estos conceptos es clave para el desarrollo de programas robustos y eficientes en cualquier lenguaje de programación.

[Repositorio de GitHub](https://github.com/Blu18/portafolio_paradigmas)