#include <stdio.h>

typedef struct _book{
    int id;
    char title[100];
    char author[100];
    // TODO: agregar genero del libro
    int quantity;
}book_t;

typedef struct _member{
    int id;
    char name[100];
    int bookIssued;
} memeber_t;

int main()
{
    int choice = 0;

    do
    {
        printf("\nMenu de sisteamde manejo de biblioteca\n");
        printf("\t1. Agregar un libro\n");
        printf("\t2. Mostrar libros disponibles\n");
        printf("\t3. Agregar un miembro\n");
        printf("\t4. Prestar libro\n");
        printf("\t5. Salir.\n");
        printf("Indica tu opcion: ");
        scanf("%d", &choice);

        /*switch (choice)
        {
        case 1:
            addBook();
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            addMember();
            break;

        case 4:
            issueBook();
            break;
   
        default:
            printf("Esta no es una opcion valida!!!\n");
            break;
        }*/
    }while(choice != 5);
    
    return 0;
}