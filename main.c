#include <stdio.h>
#include "contact.h"

int main()
{
    int choice;
    int ch;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    while(1)
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save contact to files\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            if (ch == EOF)
            {
                break;
            }

            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        
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
                listContacts(&addressBook);
                break;
            case 6:
                printf("contact saving to files\n");
                saveContactsToFile(&addressBook);
                break;
            case 7:
                printf("Exiting...\n");
                saveAndExit(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
       return 0;
}