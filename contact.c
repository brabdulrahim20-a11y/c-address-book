#include "contact.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Return 1 if the name is valid and unique, otherwise return 0. */
int validname(AddressBook *addressBook, char *name, int ignoredContact)
{
    int i;
    int j;

    /* Check for a duplicate name first. */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (i != ignoredContact &&
            strcasecmp(addressBook->contacts[i].name, name) == 0)
        {
            printf("A contact with this name already exists.\n");
            return 0;
        }
    }

    /* Allow letters and spaces only. */
    if (name[0] == '\0')
    {
        printf("Invalid name. Use letters and spaces.\n");
        return 0;
    }

    for (j = 0; name[j] != '\0'; j++)
    {
        if (!((name[j] >= 'a' && name[j] <= 'z') ||
              (name[j] >= 'A' && name[j] <= 'Z') ||
              name[j] == ' '))
        {
            printf("Invalid name. Use letters and spaces.\n");
            return 0;
        }
    }

    return 1;
}

/* Return 1 if the phone number is valid and unique, otherwise return 0. */
int validphone(AddressBook *addressBook, char *phone, int ignoredContact)
{
    int i;
    int j;

    /* Check for a duplicate phone number first. */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (i != ignoredContact &&
            strcasecmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("A contact with this phone number already exists.\n");
            return 0;
        }
    }

    /* Allow digits only. */
    if (phone[0] == '\0')
    {
        printf("Invalid phone number. Use digits only, with no spaces.\n");
        return 0;
    }

    for (j = 0; phone[j] != '\0'; j++)
    {
        if (phone[j] < '0' || phone[j] > '9')
        {
            printf("Invalid phone number. Use digits only, with no spaces.\n");
            return 0;
        }
    }

    return 1;
}

/* Return 1 if the email is valid and unique, otherwise return 0. */
int validemail(AddressBook *addressBook, char *email, int ignoredContact)
{
    int i;
    int j;
    int atCount = 0;
    int atPosition = -1;
    int hasDotAfterAt = 0;
    int emailLength;

    /* Check for a duplicate email first. */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (i != ignoredContact &&
            strcasecmp(addressBook->contacts[i].email, email) == 0)
        {
            printf("A contact with this email already exists.\n");
            return 0;
        }
    }

    emailLength = (int)strlen(email);

    if (emailLength == 0)
    {
        printf("Invalid email. Use lowercase letters and check @ and dot placement.\n");
        return 0;
    }

    /* Allow lowercase letters, digits, @, and dots. */
    for (j = 0; email[j] != '\0'; j++)
    {
        if (!((email[j] >= 'a' && email[j] <= 'z') ||
              (email[j] >= '0' && email[j] <= '9') ||
              email[j] == '@' || email[j] == '.'))
        {
            printf("Invalid email. Use lowercase letters and check @ and dot placement.\n");
            return 0;
        }

        if (email[j] == '@')
        {
            atCount++;
            atPosition = j;
        }

        if (email[j] == '.' && atCount == 1)
        {
            hasDotAfterAt = 1;
        }
    }

    if (atCount != 1 ||
        atPosition <= 0 ||
        atPosition >= emailLength - 1 ||
        !hasDotAfterAt)
    {
        printf("Invalid email. Use lowercase letters and check @ and dot placement.\n");
        return 0;
    }

    /* Do not allow a dot immediately before or after @. */
    if (email[atPosition - 1] == '.' || email[atPosition + 1] == '.')
    {
        printf("Invalid email. Use lowercase letters and check @ and dot placement.\n");
        return 0;
    }

    /* Require the email to end with a letter. */
    if (!(email[emailLength - 1] >= 'a' && email[emailLength - 1] <= 'z'))
    {
        printf("Invalid email. Use lowercase letters and check @ and dot placement.\n");
        return 0;
    }

    return 1;
}

/*
 * Search for contacts, display the matches, and return the selected
 * contact's array index. Return -1 if no contact is selected.
 */
int findContactNumber(AddressBook *addressBook, char *action)
{
    int choice;
    int i;
    int matched;
    int matchCount = 0;
    int matches[MAX_CONTACTS];
    int number;
    char name[50];
    char phone[20];
    char email[50];

    printf("What do you want to search with?\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid input.\n");
        return -1;
    }

    if (choice == 1)
    {
        printf("Enter the name to search: ");

        if (scanf(" %49[^\n]", name) != 1)
        {
            printf("Could not read the name.\n");
            return -1;
        }
    }
    else if (choice == 2)
    {
        printf("Enter the phone to search: ");

        if (scanf(" %19[^\n]", phone) != 1)
        {
            printf("Could not read the phone number.\n");
            return -1;
        }
    }
    else if (choice == 3)
    {
        printf("Enter the email to search: ");

        if (scanf(" %49[^\n]", email) != 1)
        {
            printf("Could not read the email.\n");
            return -1;
        }
    }
    else
    {
        printf("Invalid choice.\n");
        return -1;
    }

    /* Save the actual array positions of the matching contacts. */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        matched = 0;

        if (choice == 1 &&
            strcasestr(addressBook->contacts[i].name, name) != NULL)
        {
            matched = 1;
        }
        else if (choice == 2 &&
                 strcasestr(addressBook->contacts[i].phone, phone) != NULL)
        {
            matched = 1;
        }
        else if (choice == 3 &&
                 strcasestr(addressBook->contacts[i].email, email) != NULL)
        {
            matched = 1;
        }

        if (matched)
        {
            matches[matchCount] = i;
            matchCount++;
        }
    }

    if (matchCount == 0)
    {
        printf("Contact not found.\n");
        return -1;
    }

    printf("%-5s %-25s %-15s %s\n", "No.", "Name", "Phone", "Email");
    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < matchCount; i++)
    {
        int contactIndex = matches[i];

        printf("%-5d %-25s %-15s %s\n",
               i + 1,
               addressBook->contacts[contactIndex].name,
               addressBook->contacts[contactIndex].phone,
               addressBook->contacts[contactIndex].email);
    }

    printf("Enter the number of the contact you want to %s: ", action);

    if (scanf("%d", &number) != 1 ||
        number < 1 ||
        number > matchCount)
    {
        printf("Invalid contact number.\n");
        return -1;
    }

    /* Convert the displayed number into the real array index. */
    return matches[number - 1];
}

void initialize(AddressBook *addressBook)
{
    FILE *file;

    addressBook->contactCount = 0;
    file = fopen("contact.txt", "r");

    if (file == NULL)
    {
        printf("Could not open contact.txt.\n");
        return;
    }

    while (addressBook->contactCount < MAX_CONTACTS &&
           fscanf(file, " %49[^,],%19[^,],%49[^\r\n]",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    fclose(file);
}

void listContacts(AddressBook *addressBook)
{
    int i;

    printf("%-25s %-15s %s\n", "Name", "Phone", "Email");
    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-25s %-15s %s\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}

void saveAndExit(AddressBook *addressBook)
{
    (void)addressBook;
    exit(0);
}

void searchContact(AddressBook *addressBook)
{
    int choice;
    int i;
    int ch;
    int found = 0;
    int count = 1;
    char name[50];
    char phone[20];
    char email[50];

    printf("What do you want to search with?\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1)
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }

        printf("Invalid input.\n");
        return;
    }

    switch (choice)
    {
        case 1:
            printf("Enter the name to search: ");

            if (scanf(" %49[^\n]", name) != 1)
            {
                printf("Could not read the name.\n");
                return;
            }

            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasestr(addressBook->contacts[i].name, name) != NULL)
                {
                    if (!found)
                    {
                        printf("%-5s %-25s %-15s %s\n", "No.", "Name", "Phone", "Email");
                        printf("--------------------------------------------------------------------------\n");
                    }

                    printf("%-5d %-25s %-15s %s\n",
                           count++,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                    found = 1;
                }
            }
            break;

        case 2:
            printf("Enter the phone to search: ");

            if (scanf(" %19[^\n]", phone) != 1)
            {
                printf("Could not read the phone number.\n");
                return;
            }

            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasestr(addressBook->contacts[i].phone, phone) != NULL)
                {
                    if (!found)
                    {
                        printf("%-5s %-25s %-15s %s\n", "No.", "Name", "Phone", "Email");
                        printf("--------------------------------------------------------------------------\n");
                    }

                    printf("%-5d %-25s %-15s %s\n",
                           count++,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                    found = 1;
                }
            }
            break;

        case 3:
            printf("Enter the email to search: ");

            if (scanf(" %49[^\n]", email) != 1)
            {
                printf("Could not read the email.\n");
                return;
            }

            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasestr(addressBook->contacts[i].email, email) != NULL)
                {
                    if (!found)
                    {
                        printf("%-5s %-25s %-15s %s\n", "No.", "Name", "Phone", "Email");
                        printf("--------------------------------------------------------------------------\n");
                    }

                    printf("%-5d %-25s %-15s %s\n",
                           count++,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                    found = 1;
                }
            }
            break;

        default:
            printf("Invalid choice.\n");
            return;
    }

    if (!found)
    {
        printf("Contact not found.\n");
    }
}

void createContact(AddressBook *addressBook)
{
    int attemptsLeft;
    int nameAccepted = 0;
    int phoneAccepted = 0;
    int emailAccepted = 0;
    int i;
    char name[50];
    char phone[20];
    char email[50];

    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address book is full. Cannot add more contacts.\n");
        return;
    }

    attemptsLeft = 3;

    while (attemptsLeft > 0 && !nameAccepted)
    {
        printf("Enter name: ");

        if (scanf(" %49[^\n]", name) != 1)
        {
            printf("Could not read the name.\n");
            return;
        }

        nameAccepted = validname(addressBook, name, -1);

        if (!nameAccepted)
        {
            attemptsLeft--;

            if (attemptsLeft > 0)
            {
                printf("You have %d name attempts left.\n", attemptsLeft);
            }
        }
    }

    if (!nameAccepted)
    {
        printf("Contact was not added because the name was not accepted.\n");
        return;
    }

    attemptsLeft = 3;

    while (attemptsLeft > 0 && !phoneAccepted)
    {
        printf("Enter phone (digits only, no spaces): ");

        if (scanf(" %19[^\n]", phone) != 1)
        {
            printf("Could not read the phone number.\n");
            return;
        }

        phoneAccepted = validphone(addressBook, phone, -1);

        if (!phoneAccepted)
        {
            attemptsLeft--;

            if (attemptsLeft > 0)
            {
                printf("You have %d phone attempts left.\n", attemptsLeft);
            }
        }
    }

    if (!phoneAccepted)
    {
        printf("Contact was not added because the phone was not accepted.\n");
        return;
    }

    attemptsLeft = 3;

    while (attemptsLeft > 0 && !emailAccepted)
    {
        printf("Enter email: ");

        if (scanf(" %49[^\n]", email) != 1)
        {
            printf("Could not read the email.\n");
            return;
        }

        emailAccepted = validemail(addressBook, email, -1);

        if (!emailAccepted)
        {
            attemptsLeft--;

            if (attemptsLeft > 0)
            {
                printf("You have %d email attempts left.\n", attemptsLeft);
            }
        }
    }

    if (!emailAccepted)
    {
        printf("Contact was not added because the email was not accepted.\n");
        return;
    }

    i = addressBook->contactCount;
    strcpy(addressBook->contacts[i].name, name);
    strcpy(addressBook->contacts[i].phone, phone);
    strcpy(addressBook->contacts[i].email, email);
    addressBook->contactCount++;

    printf("Contact added successfully.\n");
}

void editContact(AddressBook *addressBook)
{
    int contactNumber;
    int fieldChoice;
    int attemptsLeft;
    int nameAccepted;
    int phoneAccepted;
    int emailAccepted;
    char name[50];
    char phone[20];
    char email[50];

    contactNumber = findContactNumber(addressBook, "edit");

    if (contactNumber == -1)
    {
        return;
    }

    printf("Choose which field to edit:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. All\n");
    printf("Enter your choice: ");

    if (scanf("%d", &fieldChoice) != 1)
    {
        printf("Invalid input.\n");
        return;
    }

    switch (fieldChoice)
    {
        case 1:
            attemptsLeft = 3;
            nameAccepted = 0;

            while (attemptsLeft > 0 && !nameAccepted)
            {
                printf("Enter new name: ");

                if (scanf(" %49[^\n]", name) != 1)
                {
                    printf("Could not read the name.\n");
                    return;
                }

                nameAccepted = validname(addressBook, name, contactNumber);

                if (!nameAccepted)
                {
                    attemptsLeft--;

                    if (attemptsLeft > 0)
                    {
                        printf("You have %d name attempts left.\n", attemptsLeft);
                    }
                }
            }

            if (!nameAccepted)
            {
                printf("Contact was not edited.\n");
                return;
            }

            strcpy(addressBook->contacts[contactNumber].name, name);
            break;

        case 2:
            attemptsLeft = 3;
            phoneAccepted = 0;

            while (attemptsLeft > 0 && !phoneAccepted)
            {
                printf("Enter new phone (digits only, no spaces): ");

                if (scanf(" %19[^\n]", phone) != 1)
                {
                    printf("Could not read the phone number.\n");
                    return;
                }

                phoneAccepted = validphone(addressBook, phone, contactNumber);

                if (!phoneAccepted)
                {
                    attemptsLeft--;

                    if (attemptsLeft > 0)
                    {
                        printf("You have %d phone attempts left.\n", attemptsLeft);
                    }
                }
            }

            if (!phoneAccepted)
            {
                printf("Contact was not edited.\n");
                return;
            }

            strcpy(addressBook->contacts[contactNumber].phone, phone);
            break;

        case 3:
            attemptsLeft = 3;
            emailAccepted = 0;

            while (attemptsLeft > 0 && !emailAccepted)
            {
                printf("Enter new email: ");

                if (scanf(" %49[^\n]", email) != 1)
                {
                    printf("Could not read the email.\n");
                    return;
                }

                emailAccepted = validemail(addressBook, email, contactNumber);

                if (!emailAccepted)
                {
                    attemptsLeft--;

                    if (attemptsLeft > 0)
                    {
                        printf("You have %d email attempts left.\n", attemptsLeft);
                    }
                }
            }

            if (!emailAccepted)
            {
                printf("Contact was not edited.\n");
                return;
            }

            strcpy(addressBook->contacts[contactNumber].email, email);
            break;

        case 4:
            attemptsLeft = 3;
            nameAccepted = 0;

            while (attemptsLeft > 0 && !nameAccepted)
            {
                printf("Enter new name: ");

                if (scanf(" %49[^\n]", name) != 1)
                {
                    printf("Could not read the name.\n");
                    return;
                }

                nameAccepted = validname(addressBook, name, contactNumber);

                if (!nameAccepted)
                {
                    attemptsLeft--;

                    if (attemptsLeft > 0)
                    {
                        printf("You have %d name attempts left.\n", attemptsLeft);
                    }
                }
            }

            if (!nameAccepted)
            {
                printf("Contact was not edited.\n");
                return;
            }

            attemptsLeft = 3;
            phoneAccepted = 0;

            while (attemptsLeft > 0 && !phoneAccepted)
            {
                printf("Enter new phone (digits only, no spaces): ");

                if (scanf(" %19[^\n]", phone) != 1)
                {
                    printf("Could not read the phone number.\n");
                    return;
                }

                phoneAccepted = validphone(addressBook, phone, contactNumber);

                if (!phoneAccepted)
                {
                    attemptsLeft--;

                    if (attemptsLeft > 0)
                    {
                        printf("You have %d phone attempts left.\n", attemptsLeft);
                    }
                }
            }

            if (!phoneAccepted)
            {
                printf("Contact was not edited.\n");
                return;
            }

            attemptsLeft = 3;
            emailAccepted = 0;

            while (attemptsLeft > 0 && !emailAccepted)
            {
                printf("Enter new email: ");

                if (scanf(" %49[^\n]", email) != 1)
                {
                    printf("Could not read the email.\n");
                    return;
                }

                emailAccepted = validemail(addressBook, email, contactNumber);

                if (!emailAccepted)
                {
                    attemptsLeft--;

                    if (attemptsLeft > 0)
                    {
                        printf("You have %d email attempts left.\n", attemptsLeft);
                    }
                }
            }

            if (!emailAccepted)
            {
                printf("Contact was not edited.\n");
                return;
            }

            strcpy(addressBook->contacts[contactNumber].name, name);
            strcpy(addressBook->contacts[contactNumber].phone, phone);
            strcpy(addressBook->contacts[contactNumber].email, email);
            break;

        default:
            printf("Invalid choice.\n");
            return;
    }

    printf("Contact updated successfully.\n");
}

void deleteContact(AddressBook *addressBook)
{
    int contactNumber;
    int confirm;
    int i;

    contactNumber = findContactNumber(addressBook, "delete");

    if (contactNumber == -1)
    {
        return;
    }

    printf("Selected contact:\n");
    printf("%-25s %-15s %s\n",
           addressBook->contacts[contactNumber].name,
           addressBook->contacts[contactNumber].phone,
           addressBook->contacts[contactNumber].email);

    printf("Are you sure you want to delete this contact?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter your choice: ");

    if (scanf("%d", &confirm) != 1)
    {
        printf("Invalid input. Contact was not deleted.\n");
        return;
    }

    if (confirm == 2)
    {
        printf("Deletion cancelled.\n");
        return;
    }

    if (confirm != 1)
    {
        printf("Invalid choice. Contact was not deleted.\n");
        return;
    }

    for (i = contactNumber; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully.\n");
}

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *file;
    int i;

    file = fopen("contact.txt", "w");

    if (file == NULL)
    {
        printf("Could not save contact.txt.\n");
        return;
    }

    for (i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(file);
    printf("Contacts saved.\n");
}