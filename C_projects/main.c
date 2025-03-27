#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Define constants
#define FILENAME "library.dat"
#define NUM_CATEGORIES 6
#define BOOKS_PER_CATEGORY 20
#define SHELVES_PER_CATEGORY 2
#define COLUMNS_PER_SHELF 5
#define ROWS_PER_SHELF 2

// Define the Book structure
typedef struct {
    int id;
    char name[100];
    char author[50];
    float price;
    char category[20];
    int shelf;
    int aisle;
    int row;
    int availableCopies;
} Book;

// Function declarations
void initializeLibrary(void);
void addSampleBooks(void);
void searchBook(void);
void rentBookByTitleOrAuthor(void);
void rentBook(int bookID);
void checkLocation(int bookID);
void displayCategories(void);
void listBooksInCategory(const char *category);
void showBookInfo(int bookID);
void toLowerCase(char *str);

int main() {
    int choice;

    // Initialize the library and add sample books
    initializeLibrary();
    addSampleBooks();

    // Main menu loop
    while (1) {
        printf("_________________________________\n");
        printf("WELCOME TO LIPPSTADT CITY LIBRARY\n");
        printf("Press 1 to Rent a Book\n");
        printf("Press 2 to Search for a Book\n");
        printf("Press 3 to See Categories\n");
        printf("Press 4 to Exit\n");
        printf("_________________________________\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                rentBookByTitleOrAuthor();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                displayCategories();
                break;
            case 4:
                exit(0);
            default:
                printf("!!!Invalid Choice!!!\n");
                printf("Please Try again.\n");
        }
    }

    return 0;
}

// Function to initialize the library file if it doesn't exist
void initializeLibrary(void) {
    FILE *file = fopen(FILENAME, "ab+");  // Open file in append binary mode
    if (!file) {
        printf("Error initializing database file!\n");
        exit(1);
    }
    fclose(file);
}

// Function to add sample books to the library
void addSampleBooks(void) {
    const char *categories[NUM_CATEGORIES] = {
        "Academic", "Novel", "Biography", "Comic/Manga", "Politics", "Entertainment"
    };

    const char *books[NUM_CATEGORIES][BOOKS_PER_CATEGORY] = {
        // Academic books
        {"The Design of Everyday Things", "The Existential Pleasure of Engineering", "Engineering Mathematics",
         "Mathematics for Machine Learning",
         "The Pragmatic Programmer", "Refactoring", "Six Easy Pieces", "The Cartoon Guide to Physics",
         "Quantum Mechanics and Experience",
         "The Fabric of the Cosmos", "The Order of Time", "The Periodic Table", "Chemistry: The Central Science",
         "The Alchemy of Air", "H2O: A Biography of Water", "The Extended Phenotype", "Entangled Life", "Silent Spring",
         "The Insect Societies", "Basic Economics: A Citizen's Guide to the Economy"},
        // Novel books
        {"Gulliver's Travels", "The Call of the Wild", "Robinson Crusoe", "Tropic of Cancer", "Catch-22",
         "This Side of Paradise", "The Lord of the Rings", "Gone with the Wind", "Herzog", "Loving",
         "Harry Potter and the Prisoner of Azkaban", "A Death in the Family", "The Man Who Loved Children",
         "Money", "White Teeth", "The Blind Assassin", "All the King’s Men", "On the Road", "Atonement",
         "One Flew Over the Cuckoo's Nest"},
        // Biography books
        {"Steve Jobs", "Into the Wild", "Team of Rivals: The Political Genius of Abraham Lincoln", "Alexander Hamilton",
         "Unbroken: A World War II Story of Survival, Resilience and Redemption", "Wild Swans: Three Daughters of China",
         "The Rise of Theodore Roosevelt",
         "Oscar Wilde", "Mornings on Horseback", "Means of Ascent", "Tolstoy", "Zelda", "The Lost Girls", "Grant",
         "A Beautiful Mind", "The Twelve Caesars", "A House in the Sky", "A. Lincoln", "Leo Africanus",
         "Muhammad: His Life Based on the Earliest Sources"},
        // Comic/Manga books
        {"Batman: Year One", "Superman: American Alien", "Watchmen", "V for Vendetta", "From Hell", "Batman: The Killing Joke",
         "I Kill Giants", "Green Lantern", "Amazing Spider-Man: Kraven's Last Hunt", "One Piece", "Naruto", "Attack on Titan",
         "Dragon Ball", "Berserk", "Hunter x Hunter", "Akira", "Vinland Saga", "Monster", "Fullmetal Alchemist", "Tokyo Ghoul"},
        // Politics books
        {"The Communist Manifesto", "1984", "Why We're Polarized", "Common Sense", "Between The World and Me",
         "The Wretched of the Earth",
         "The Republic", "The Prince", "Leviathan", "Second Treatise of Government", "The Social Contract",
         "Democracy in America", "On Liberty",
         "The Origins of Totalitarianism", "Why Nations Fail", "The Road to Serfdom", "The Populist's Guide to 2020",
         "Politics On the Edge",
         "This is Europe: The Way We Live Now", "Les Aveuglés: Comment Berlin et Paris ont laissé la voie libre à la Russie"},
        // Entertainment books
        {"Ender's Game", "The Da Vinci Code", "A Game of Thrones", "Ready Player One", "The Martian",
         "The Hitchhiker's Guide To The Galaxy",
         "To Kill a Mockingbird", "Born Standing Up", "Dune", "The Alchemist", "Angels & Demons", "Brave New World", "Freakonomics",
         "The Glass Castle", "Animal Farm", "Amusing Ourselves to Death", "The Catcher in the Rye", "The Kite Runner",
         "Twilight", "White Fang"}
    };

    const char *authors[NUM_CATEGORIES][BOOKS_PER_CATEGORY] = {
        // Academic authors
        {"Don Norman", "Samuel C. Florman", "Dexter J. Booth", "Marc Peter", "David Hunt",
         "Martin Fowler", "Richard Feynman", "Larry Gonick", "David Albert", "Brian Greene",
         "Carlo Rovelli", "Primo Levi", "H. Eugene LeMay", "Thomas Hager", "Philip Ball",
         "Richard Dawkins", "Merlin Sheldrake", "Rachel Carson", "E. O. Wilson", "Thomas Sowell"},
        // Novel authors
        {"Jonathan Swift", "Jack London", "Daniel Defoe", "Henry Miller", "Joseph Heller",
         "F. Scott Fitzgerald", "J.R.R. Tolkien", "Margaret Mitchell", "Saul Bellow", "Henry Green",
         "J.K. Rowling", "James Agee", "Christina Stead", "Martin Amis", "Zadie Smith", "Margaret Atwood",
         "Robert Penn Warren", "Jack Kerouac", "Ian McEwan", "Ken Kesey"},
        // Biography authors
        {"Walter Isaacson", "Jon Krakauer", "Doris Kearns Goodwin", "Ron Chernow", "Laura Hillenbrand",
         "Jung Chang", "Edmund Morris", "Richard Ellmann", "David McCullough", "Robert A. Caro",
         "Henri Troyat", "Nancy Milford", "John Glatt", "Ron Chernow", "Sylvia Nasar",
         "Suetonius", "Amanda Lindhout", "Ronald C. White Jr.", "Amin Maalouf", "Martin Lings"},
        // Comic/Manga authors
        {"Frank Miller", "Max Landis", "Alan Moore", "Alan Moore", "Alan Moore", "Alan Moore", "Joe Kelly", "Peter Tomasi",
         "J. M. DeMatteis", "Eiichiro Oda", "Masashi Kishimoto", "Hajime Isayama", "Akira Toriyama", "Kentaro Miura",
         "Yoshihiro Togashi", "Katsuhiro Otomo", "Makoto Yukimura", "Naoki Urasawa", "Hiromu Arakawa", "Sui Ishida"},
        // Politics authors
        {"Karl Marx", "George Orwell", "Ezra Klein", "Thomas Paine", "Ta-Nehisi Coates", "Frantz Fanon", "Plato",
         "Niccolo Machiavelli",
         "Thomas Hobbes", "John Locke", "Jean-Jacques Rousseau", "Alexis de Tocqueville", "John Stuart Mill",
         "Hannah Arendt", "Daron Acemoglu",
         "Friedrich Hayek", "Krystal Ball", "Rory Stewart", "Ben Judah", "Sylvie Kauffmann"},
        // Entertainment authors
        {"Orson Scott Card", "Dan Brown", "George R. R. Martin", "Ernest Cline", "Andy Weir", "Douglas Adams", "Harper Lee",
         "Steve Martin", "Frank Herbert", "Paulo Coelho", "Dan Brown", "Aldous Huxley", "Stephen J. Levitt", "Jeannette Walls",
         "George Orwell", "Neil Postman", "J. D. Salinger", "Khaled Hosseini", "Stephenie Meyer", "Jack London"}
    };

    const float prices[BOOKS_PER_CATEGORY] = {1.99, 1.99, 2.59, 4.67, 15.99, 3.85, 5.58, 1.99, 1.99, 2.99, 3.99, 9.99,
                                              12.00, 16.99, 6.00, 8.20, 1.99, 1.99, 4.99, 8.00};

    // Initialize random number generator
    srand(time(NULL));

    // Open the file for writing binary data
    FILE *file = fopen(FILENAME, "wb");
    if (!file) {
        printf("Error opening database file for writing!\n");
        exit(1);
    }

    // Initialize and write sample books to the file
    static int id = 1;
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        for (int j = 0; j < BOOKS_PER_CATEGORY; j++) {
            Book book;
            book.id = id++;
            strcpy(book.name, books[i][j]);
            strcpy(book.author, authors[i][j]);
            book.price = prices[j];
            strcpy(book.category, categories[i]);
            book.shelf = (rand() % SHELVES_PER_CATEGORY) + 1;
            book.aisle = (rand() % COLUMNS_PER_SHELF) + 1;
            book.row = (rand() % ROWS_PER_SHELF) + 1;
            book.availableCopies = (rand() % 20) + 1; // Random number of available copies between 1 and 20
            fwrite(&book, sizeof(Book), 1, file);
        }
    }
    fclose(file);
}

// Convert string to lowercase to facilitate case-insensitive search
void toLowerCase(char *str) {
    for (; *str; ++str) *str = tolower(*str);
}

// Search for a book by name or author
void searchBook(void) {
    char keyword[100];
    char lowerName[100];
    char lowerAuthor[50];
    int found = 0;
    Book book;
    FILE *file = fopen(FILENAME, "rb");

    if (!file) {
        printf("Error opening database file for reading!\n");
        return;
    }

    // Prompt user for search keyword
    printf("Enter book name or author's name to search: ");
    fgets(keyword, sizeof(keyword), stdin);
    strtok(keyword, "\n"); // remove trailing newline
    toLowerCase(keyword);

    // Read through the file and search for the book
    while (fread(&book, sizeof(Book), 1, file)) {
        strcpy(lowerName, book.name);
        strcpy(lowerAuthor, book.author);
        toLowerCase(lowerName);
        toLowerCase(lowerAuthor);

        if (strstr(lowerName, keyword) || strstr(lowerAuthor, keyword)) {
            found = 1;
            printf("_________________________________\n");
            printf("Book ID:      \t%d\n", book.id);
            printf("Book Name:    \t%s\n", book.name);
            printf("Author:       \t%s\n", book.author);
            printf("Price:        \t%.2f Euro\n", book.price);
            printf("Category:     \t%s\n", book.category);
            printf("Available Copies: \t%d\n", book.availableCopies);
            printf("_________________________________\n");

            int actionChoice;
            printf("Do you want to (1) Rent the book or (0) Go back to main menu? Enter 1 or 0: ");
            scanf("%d", &actionChoice);
            getchar();

            if (actionChoice == 1) {
                rentBook(book.id);
            } else if (actionChoice == 0) {
                printf("Returning to main menu.\n");
            } else {
                printf("Invalid choice! Returning to main menu.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Book is not available.\n");
    }

    fclose(file);
}

// Rent a book by searching for its title or author
void rentBookByTitleOrAuthor(void) {
    char keyword[100];
    char lowerName[100];
    char lowerAuthor[50];
    int found = 0;
    Book book;
    FILE *file = fopen(FILENAME, "rb");

    if (!file) {
        printf("Error opening database file for reading!\n");
        return;
    }

    // Prompt user for search keyword to rent
    printf("Enter book name or author's name to rent: ");
    fgets(keyword, sizeof(keyword), stdin);
    strtok(keyword, "\n");
    toLowerCase(keyword);

    // Read through the file and search for the book to rent
    while (fread(&book, sizeof(Book), 1, file)) {
        strcpy(lowerName, book.name);
        strcpy(lowerAuthor, book.author);
        toLowerCase(lowerName);
        toLowerCase(lowerAuthor);

        if (strstr(lowerName, keyword) || strstr(lowerAuthor, keyword)) {
            found = 1;
            rentBook(book.id);
            break;
        }
    }

    if (!found) {
        printf("Book is not available for rent.\n");
    }

    fclose(file);
}

// Rent a book by its ID
void rentBook(int bookID) {
    Book book;
    int found = 0;
    FILE *file = fopen(FILENAME, "r+b");

    if (!file) {
        printf("Error opening database file for reading!\n");
        return;
    }

    // Read through the file and search for the book by ID
    while (fread(&book, sizeof(Book), 1, file)) {
        if (book.id == bookID) {
            found = 1;
            if (book.availableCopies > 0) {
                printf("_________________________________\n");
                printf("You have selected:\n");
                printf("Book Name:    \t%s\n", book.name);
                printf("Author:       \t%s\n", book.author);
                printf("Price:        \t%.2f Euro\n", book.price);
                printf("You can rent this book for:\n");
                printf("1.            \t1 week for 1 Euro\n");
                printf("2.            \t1 month for 3 Euros\n");
                printf("Available Copies: \t%d\n", book.availableCopies);
                printf("_________________________________\n");
                int rentChoice;
                printf("Enter your choice: ");
                scanf("%d", &rentChoice);
                getchar();

                if (rentChoice == 1) {
                    printf("You have chosen to rent the book for 1 week for 1 Euro.\n");
                } else if (rentChoice == 2) {
                    printf("You have chosen to rent the book for 1 month for 3 Euros.\n");
                } else {
                    printf("Invalid choice! Returning to main menu.\n");
                    return;
                }
                printf("_________________________________\n");
                printf("Location of the book:\n");
                printf("Shelf:        \t%d\n", book.shelf);
                printf("Aisle:        \t%d\n", book.aisle);
                printf("Row:          \t%d\n", book.row);
                printf("Please proceed to the shelf to find the book and then go to the librarian for further processing.\n");

                book.availableCopies--;

                fseek(file, -sizeof(Book), SEEK_CUR);

                fwrite(&book, sizeof(Book), 1, file);
            } else {
                printf("Sorry, this book is currently out of stock.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Book ID not found.\n");
    }

    fclose(file);
}

// Check the location of a book by its ID
void checkLocation(int bookID) {
    Book book;
    int found = 0;
    FILE *file = fopen(FILENAME, "rb");

    if (!file) {
        printf("Error opening database file for reading!\n");
        return;
    }

    // Read through the file and search for the book by ID
    while (fread(&book, sizeof(Book), 1, file)) {
        if (book.id == bookID) {
            found = 1;
            printf("_________________________________\n");
            printf("Location of the book:\n");
            printf("Shelf:        \t%d\n", book.shelf);
            printf("Aisle:        \t%d\n", book.aisle);
            printf("Row:          \t%d\n", book.row);
            printf("Please proceed to the shelf to find the book.\n");
            break;
        }
    }

    if (!found) {
        printf("Book ID not found.\n");
    }

    fclose(file);
}

// Display the categories of books available in the library
void displayCategories(void) {
    while (1) {
        const char *categories[NUM_CATEGORIES] = {
            "Academic", "Novel", "Biography", "Comic/Manga", "Politics", "Entertainment"
        };

        printf("Available Categories:\n");
        for (int i = 0; i < NUM_CATEGORIES; i++) {
            printf("%d.\t%s\n", i + 1, categories[i]);
        }

        int categoryChoice;
        printf("Enter category number to list books or 0 to go back: ");
        scanf("%d", &categoryChoice);
        getchar(); // to consume the newline character

        if (categoryChoice == 0) {
            return;
        } else if (categoryChoice < 1 || categoryChoice > NUM_CATEGORIES) {
            printf("Invalid category choice.\n");
        } else {
            const char *selectedCategory = categories[categoryChoice - 1];
            listBooksInCategory(selectedCategory);
        }
    }
}

// List all books in a given category
void listBooksInCategory(const char *category) {
    Book book;
    FILE *file = fopen(FILENAME, "rb");

    if (!file) {
        printf("Error opening database file for reading!\n");
        return;
    }

    int found = 0;
    int bookCounter = 1;
    printf("Books in category: %s\n", category);
    while (fread(&book, sizeof(Book), 1, file)) {
        if (strcmp(book.category, category) == 0) {
            found = 1;
            printf("%d. %s\n", bookCounter++, book.name);
        }
    }

    if (!found) {
        printf("No books found in this category.\n");
    }

    fclose(file);

    if (found) {
        int bookChoice;
        printf("Enter the number of the book to see more information or 0 to go back: ");
        scanf("%d", &bookChoice);
        getchar();

        if (bookChoice == 0) {
            return;
        } else if (bookChoice > 0 && bookChoice < bookCounter) {
            int bookIndex = 1;
            file = fopen(FILENAME, "rb");
            while (fread(&book, sizeof(Book), 1, file)) {
                if (strcmp(book.category, category) == 0) {
                    if (bookIndex == bookChoice) {
                        showBookInfo(book.id);
                        break;
                    }
                    bookIndex++;
                }
            }
            fclose(file);
        } else {
            printf("Invalid choice! Returning to main menu.\n");
        }
    }
}

// Show detailed information about a book by its ID
void showBookInfo(int bookID) {
    Book book;
    FILE *file = fopen(FILENAME, "rb");

    if (!file) {
        printf("Error opening database file for reading!\n");
        return;
    }

    int found = 0;
    while (fread(&book, sizeof(Book), 1, file)) {
        if (book.id == bookID) {
            found = 1;
            printf("_________________________________\n");
            printf("Book ID:      \t%d\n", book.id);
            printf("Book Name:    \t%s\n", book.name);
            printf("Author:       \t%s\n", book.author);
            printf("Price:        \t%.2f Euro\n", book.price);
            printf("Category:     \t%s\n", book.category);
            printf("Shelf:        \t%d\n", book.shelf);
            printf("Aisle:        \t%d\n", book.aisle);
            printf("Row:          \t%d\n", book.row);
            printf("Available Copies: \t%d\n", book.availableCopies);
            printf("_________________________________\n");
            int actionChoice;
            printf("Do you want to (1) Rent the book or (0) Go back to category menu? Enter 1 or 0: ");
            scanf("%d", &actionChoice);
            getchar();

            if (actionChoice == 1) {
                rentBook(book.id);
            } else if (actionChoice == 0) {
                printf("Returning to category menu.\n");
            } else {
                printf("Invalid choice! Returning to category menu.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Book is not available.\n");
    }

    fclose(file);
}
