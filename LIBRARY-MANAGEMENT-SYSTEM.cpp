#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool isAvailable;
};

struct Borrower {
    string name;
    string borrowedBookISBN;
    time_t borrowDate;
    bool hasOverdueBook;
};

// Vector to store the library's book collection
vector<Book> libraryBooks;

// Vector to store borrowers' data
vector<Borrower> borrowers;

// Function to add a book to the library
void addBook(const string& title, const string& author, const string& ISBN) {
    libraryBooks.push_back({title, author, ISBN, true});
    cout << "Book added: " << title << " by " << author << endl;
}

// Function to search for a book by title, author, or ISBN
void searchBook() {
    string query;
    cout << "Enter title, author, or ISBN to search: ";
    cin.ignore();
    getline(cin, query);

    bool found = false;
    for (const auto& book : libraryBooks) {
        if (book.title == query || book.author == query || book.ISBN == query) {
            cout << "Book Found - Title: " << book.title << ", Author: " << book.author
                 << ", ISBN: " << book.ISBN << ", Available: " << (book.isAvailable ? "Yes" : "No") << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No matching books found.\n";
    }
}

// Function to check out a book to a borrower
void checkoutBook() {
    string borrowerName, bookISBN;
    cout << "Enter borrower's name: ";
    cin.ignore();
    getline(cin, borrowerName);
    cout << "Enter ISBN of the book to check out: ";
    getline(cin, bookISBN);

    for (auto& book : libraryBooks) {
        if (book.ISBN == bookISBN && book.isAvailable) {
            book.isAvailable = false;
            time_t now = time(0);

            borrowers.push_back({borrowerName, bookISBN, now, false});
            cout << "Book checked out to " << borrowerName << ".\n";
            return;
        }
    }

    cout << "Book not available or not found.\n";
}

// Function to return a book
void returnBook() {
    string bookISBN;
    cout << "Enter ISBN of the book to return: ";
    cin.ignore();
    getline(cin, bookISBN);

    for (auto& book : libraryBooks) {
        if (book.ISBN == bookISBN && !book.isAvailable) {
            book.isAvailable = true;
            cout << "Book returned successfully.\n";

            // Check borrower data and update fine status if necessary
            for (auto& borrower : borrowers) {
                if (borrower.borrowedBookISBN == bookISBN) {
                    time_t now = time(0);
                    double days = difftime(now, borrower.borrowDate) / (60 * 60 * 24);  // Calculate days between borrow and return

                    if (days > 14) {
                        borrower.hasOverdueBook = true;
                        cout << "Book returned late! A fine will be applied.\n";
                    } else {
                        borrower.hasOverdueBook = false;
                        cout << "Book returned on time. No fine.\n";
                    }
                    return;
                }
            }
        }
    }

    cout << "Book not found or already returned.\n";
}

// Function to calculate and display fines
void calculateFines() {
    for (const auto& borrower : borrowers) {
        if (borrower.hasOverdueBook) {
            cout << "Borrower: " << borrower.name << " has overdue books. A fine of Rs. 50 will be applied.\n";
        }
    }
}

// Main function and user interface
int main() {
    bool exit = false;
    int choice;

    // Adding books to the library (Programming, Cybersecurity, AI, Meditation, etc.)
    
    // C++ Books
    addBook("The C++ Programming Language", "Bjarne Stroustrup", "9780321563842");
    addBook("Effective C++", "Scott Meyers", "9780321334879");
    addBook("C++ Primer", "Stanley B. Lippman", "9780321714114");
    addBook("Programming: Principles and Practice Using C++", "Bjarne Stroustrup", "9780321992789");
    addBook("Accelerated C++", "Andrew Koenig", "9780201703535");
    addBook("More Effective C++", "Scott Meyers", "9780201633719");
    addBook("C++ Concurrency in Action", "Anthony Williams", "9781933988771");
    addBook("C++ Templates", "David Vandevoorde", "9780321714121");
    addBook("The Design and Evolution of C++", "Bjarne Stroustrup", "9780201543308");
    addBook("C++ Standard Library", "Nicolai M. Josuttis", "9780321623218");

    // Java Books
    addBook("Effective Java", "Joshua Bloch", "9780134685991");
    addBook("Java: The Complete Reference", "Herbert Schildt", "9781260440232");
    addBook("Head First Java", "Kathy Sierra", "9780596009205");
    addBook("Java Concurrency in Practice", "Brian Goetz", "9780321349606");
    addBook("Java Performance", "Charlie Hunt", "9780137142521");
    addBook("Java Network Programming", "Elliotte Rusty Harold", "9781449357672");
    addBook("Java Puzzlers", "Joshua Bloch", "9780321336781");
    addBook("Core Java Volume I", "Cay Horstmann", "9780135166307");
    addBook("The Well-Grounded Java Developer", "Benjamin Evans", "9781617290060");
    addBook("Java 8 in Action", "Raoul-Gabriel Urma", "9781617291999");

    // Python Books
    addBook("Python Crash Course", "Eric Matthes", "9781593279288");
    addBook("Automate the Boring Stuff with Python", "Al Sweigart", "9781593279929");
    addBook("Fluent Python", "Luciano Ramalho", "9781491946008");
    addBook("Learning Python", "Mark Lutz", "9781449355739");
    addBook("Python for Data Analysis", "Wes McKinney", "9781491957660");
    addBook("Python Cookbook", "David Beazley", "9781449340377");
    addBook("Effective Python", "Brett Slatkin", "9780134034287");
    addBook("Django for Beginners", "William S. Vincent", "9781735467207");
    addBook("Introduction to Machine Learning with Python", "Andreas Müller", "9781449369415");
    addBook("Python Tricks", "Dan Bader", "9781775093305");

    // Cybersecurity Books
    addBook("The Web Application Hacker's Handbook", "Dafydd Stuttard", "9781118026472");
    addBook("Hacking: The Art of Exploitation", "Jon Erickson", "9781593271442");
    addBook("Metasploit: The Penetration Tester’s Guide", "David Kennedy", "9781593272883");
    addBook("Practical Malware Analysis", "Michael Sikorski", "9781593272906");
    addBook("Network Security Essentials", "William Stallings", "9780134527338");
    addBook("The Hacker Playbook 3", "Peter Kim", "9781980901754");
    addBook("Advanced Penetration Testing", "Wil Allsopp", "9781119367680");
    addBook("The Tangled Web", "Michal Zalewski", "9781593273880");
    addBook("Ghost in the Wires", "Kevin Mitnick", "9780316037723");
    addBook("The Basics of Hacking and Penetration Testing", "Patrick Engebretson", "9780124116443");

    // AI and Generative AI Books
    addBook("Artificial Intelligence: A Modern Approach", "Stuart Russell", "9780136042594");
    addBook("Deep Learning", "Ian Goodfellow", "9780262035613");
    addBook("Superintelligence", "Nick Bostrom", "9780198739838");
    addBook("Human Compatible", "Stuart Russell", "9780525558613");
    addBook("Generative Deep Learning", "David Foster", "9781492041948");
    addBook("Artificial Intelligence Engines", "James V. Stone", "9781788360237");
    addBook("Machine Learning Yearning", "Andrew Ng", "No ISBN");
    addBook("Generative Adversarial Networks Cookbook", "Josh Kalin", "9781789139900");
    addBook("The Master Algorithm", "Pedro Domingos", "9780465065707");
    addBook("Hands-On Machine Learning with Scikit-Learn and TensorFlow", "Aurélien Géron", "9781492032649");

    // Meditation and Mindfulness Books
    addBook("The Miracle of Mindfulness", "Thich Nhat Hanh", "9780807012390");
    addBook("Wherever You Go, There You Are", "Jon Kabat-Zinn", "9781401307783");
    addBook("The Power of Now", "Eckhart Tolle", "9781577314806");
    addBook("Radical Acceptance", "Tara Brach", "9780553380996");
    addBook("The Untethered Soul", "Michael A. Singer", "9781572245372");
    addBook("Mindfulness in Plain English", "Bhante Henepola Gunaratana", "9780861719068");
    addBook("The Headspace Guide to Meditation and Mindfulness", "Andy Puddicombe", "9781250104908");
    addBook("10% Happier", "Dan Harris", "9780062415473");
    addBook("Waking Up", "Sam Harris", "9781451636024");
    addBook("The Art of Living", "Thich Nhat Hanh", "9780062435334");

    // Business, Motivation, and Attitude Books
    addBook("The Lean Startup", "Eric Ries", "9780307887894");
    addBook("Zero to One", "Peter Thiel", "9780804139298");
    addBook("Good to Great", "Jim Collins", "9780066620996");
    addBook("The Innovator’s Dilemma", "Clayton M. Christensen", "9781633691780");
    addBook("Start with Why", "Simon Sinek", "9781591846444");
    addBook("The Hard Thing About Hard Things", "Ben Horowitz", "9780062273208");
    addBook("The 4-Hour Workweek", "Tim Ferriss", "9780307465351");
    addBook("The 7 Habits of Highly Effective People", "Stephen Covey", "9780743269513");
    addBook("Atomic Habits", "James Clear", "9780735211292");
    addBook("Man’s Search for Meaning", "Viktor Frankl", "9780807014271");

    // Literature and Poetry Books
    addBook("The Odyssey", "Homer", "9780140268867");
    addBook("The Iliad", "Homer", "9780140275360");
    addBook("Leaves of Grass", "Walt Whitman", "9781420954111");
    addBook("The Divine Comedy", "Dante Alighieri", "9780140448955");
    addBook("The Waste Land", "T.S. Eliot", "9780156948777");
    addBook("Paradise Lost", "John Milton", "9780140424393");
    addBook("Shakespeare’s Sonnets", "William Shakespeare", "9780486268729");
    addBook("The Road Not Taken", "Robert Frost", "9780805069860");
    addBook("The Collected Poems of W.B. Yeats", "W.B. Yeats", "9780684807317");
    addBook("Ariel", "Sylvia Plath", "9780060732608");

    while (!exit) {
        cout << "\nLibrary Management System Menu:\n";
        cout << "1. Search for a Book\n";
        cout << "2. Check Out a Book\n";
        cout << "3. Return a Book\n";
        cout << "4. Calculate Fines\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                searchBook();
                break;
            case 2:
                checkoutBook();
                break;
            case 3:
                returnBook();
                break;
            case 4:
                calculateFines();
                break;
            case 5:
                exit = true;
                cout << "Exiting Library Management System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
