/*Name : ESWARAMOORTHY P
    Date : 10-08-2025
    Descripton : 
        Address Book is an  console application written in C. It can work on all platforms which have a C compiler or cross-compiler.
    The application keeps track of contact names and telephone/mobile numbers and e-mail addresses. It is a console application
    which uses standard C I/O for adding names, phone numbers and e-mail addresses, searching names and associated numbers and
    email addresses, updating numbers and email addresses, and deleting contacts.
*/
#include <stdio.h>
#include<unistd.h>
#include "contact.h"


int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        
        printf("\n\033[1;32m---->Address Book Menu\n");
        printf("\033[1;33m---->1. Create contact\n");
        printf("\033[1;33m---->2. Search contact\n");
        printf("\033[1;33m---->3. Edit contact\n");
        printf("\033[1;33m---->4. Delete contact\n");
        printf("\033[1;33m---->5. List all contacts\n");
        printf("\033[1;33m---->6. Exit\n");
        printf("\033[0mEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
            
                printf("\033[1;33mSelect sort criteria:\n");
                printf("\033[0m1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("\033[0;33mEnter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);

                listContacts(&addressBook, sortChoice);
                break;
            case 6:
            sleep(1);
            
           printf("\033[0;33m");
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
            printf("\033[0;33m");
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}
