# C Address Book

This is my first C project: a menu-driven program for managing contacts.

## Features

- Add, search, edit, delete, and list contacts.
- Validate names, phone numbers, and email addresses.
- Check for duplicate contact details.
- Load and save contacts in a text file.

## Project files

- `main.c` — displays the menu and calls the selected operation.
- `contact.c` — contains the contact operations and validation functions.
- `contact.h` — defines the contact structures and function declarations.
- `contact.txt` — sample contacts in `name,phone,email` format.
- `documentation.txt` — explains the program functions and input rules.

## Build and run

Use GCC in Linux or WSL:

```bash
gcc main.c contact.c -o addressbook
./addressbook
```

The current code uses `strcasestr` and `strcasecmp` for case-insensitive searching and duplicate checks. These are GNU/POSIX functions rather than ISO C functions.

## Sample contact format

```text
Alex Example,0000000001,alex@example.com
Jordan Example,0000000002,jordan@example.com
```

The repository's sample contacts use placeholder data. Choose **Save contact to files** in the menu to write the current contact list to `contact.txt`.
