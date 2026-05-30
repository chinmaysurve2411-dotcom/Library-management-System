#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    int quantity;
    int available;

    Book(int i, string t, string a, int q) {
        id = i;
        title = t;
        author = a;
        quantity = q;
        available = q;
    }
};

class BorrowRecord {
public:
    string studentName;
    int bookId;
    string borrowDate;
    string returnDate;
    bool returned;
    int fine;

    BorrowRecord(string name, int id, string date) {
        studentName = name;
        bookId = id;
        borrowDate = date;
        returnDate = "";
        returned = false;
        fine = 0;
    }
};

vector<Book> books;
vector<BorrowRecord> records;

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void addBook() {
    int id, quantity;

    cout << "\nEnter Book ID: ";
    cin >> id;
    clearInput();

    for (auto &b : books) {
        if (b.id == id) {
            cout << "Book ID already exists.\n";
            return;
        }
    }

    string title, author;

    cout << "Enter Title: ";
    getline(cin, title);

    cout << "Enter Author: ";
    getline(cin, author);

    cout << "Enter Quantity: ";
    cin >> quantity;

    books.push_back(Book(id, title, author, quantity));

    cout << "\nBook added successfully.\n";
}

void viewBooks() {
    if (books.empty()) {
        cout << "\nNo books available.\n";
        return;
    }

    for (auto &b : books) {
        cout << "\nID: " << b.id << endl;
        cout << "Title: " << b.title << endl;
        cout << "Author: " << b.author << endl;
        cout << "Available: " << b.available
             << "/" << b.quantity << endl;
    }
}

void searchBook() {
    int id;

    cout << "\nEnter Book ID: ";
    cin >> id;

    for (auto &b : books) {
        if (b.id == id) {
            cout << "\nBook Found\n";
            cout << b.title << endl;
            cout << b.author << endl;
            return;
        }
    }

    cout << "Book not found.\n";
}

void issueBook() {
    int id;

    cout << "\nEnter Book ID: ";
    cin >> id;
    clearInput();

    string studentName;
    string borrowDate;

    cout << "Enter Student Name: ";
    getline(cin, studentName);

    cout << "Enter Borrow Date (DD/MM/YYYY): ";
    getline(cin, borrowDate);

    for (auto &b : books) {
        if (b.id == id) {
            if (b.available <= 0) {
                cout << "No copies available.\n";
                return;
            }

            b.available--;

            records.push_back(
                BorrowRecord(studentName, id, borrowDate)
            );

            cout << "\nBook issued successfully.\n";
            return;
        }
    }

    cout << "Book not found.\n";
}

void returnBook() {
    int id;
    cin.ignore();

    cout << "\nEnter Book ID: ";
    cin >> id;
    clearInput();

    string studentName;
    string returnDate;
    int daysKept;

    cout << "Enter Student Name: ";
    getline(cin, studentName);

    cout << "Enter Return Date: ";
    getline(cin, returnDate);

    cout << "Days Kept: ";
    cin >> daysKept;

    for (auto &r : records) {
        if (r.bookId == id &&
            r.studentName == studentName &&
            !r.returned) {

            r.returned = true;
            r.returnDate = returnDate;

            if (daysKept > 14) {
                r.fine = (daysKept - 14) * 5;
            }

            for (auto &b : books) {
                if (b.id == id) {
                    b.available++;
                }
            }

            cout << "\nReturned successfully.\n";
            cout << "Fine: ₹" << r.fine << endl;
            return;
        }
    }

    cout << "Record not found.\n";
}

void viewBorrowRecords() {
    if (records.empty()) {
        cout << "\nNo records found.\n";
        return;
    }

    for (auto &r : records) {
        cout << "\nStudent: " << r.studentName << endl;
        cout << "Book ID: " << r.bookId << endl;
        cout << "Borrow Date: " << r.borrowDate << endl;
        cout << "Return Date: " << r.returnDate << endl;
        cout << "Returned: "
             << (r.returned ? "Yes" : "No") << endl;
        cout << "Fine: ₹" << r.fine << endl;
    }
}

void deleteBook() {
    int id;

    cout << "\nEnter Book ID to delete: ";
    cin >> id;

    for (auto &r : records) {
        if (r.bookId == id && !r.returned) {
            cout << "Cannot delete. Book is currently issued.\n";
            return;
        }
    }

    for (int i = 0; i < books.size(); i++) {
        if (books[i].id == id) {
            books.erase(books.begin() + i);

            cout << "Book deleted.\n";
            return;
        }
    }

    cout << "Book not found.\n";
}

void showTerms() {
    cout << "\n===== TERMS =====\n";
    cout << "Borrow limit: 14 days\n";
    cout << "Fine: ₹5/day after 14 days\n";
    cout << "Lost books must be replaced\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== LIBRARY SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. View Borrow Records\n";
        cout << "7. Delete Book\n";
        cout << "8. Terms & Conditions\n";
        cout << "9. Exit\n";

        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: viewBorrowRecords(); break;
            case 7: deleteBook(); break;
            case 8: showTerms(); break;
            case 9: cout << "Goodbye\n"; break;
            default: cout << "Invalid choice\n";
        }

    } while (choice != 9);

    return 0;
}
