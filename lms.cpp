#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
class Item {
protected:
std::string title;
std::string author;
public:
Item(std::string title, std::string author) : title(title), author(author) {}
virtual std::string getTitle() const { return title; }
virtual std::string getAuthor() const { return author; }
virtual void display() const = 0;
};
class Book : public Item {
private:
int copies;
public:
Book(std::string title, std::string author, int copies)
: Item(title, author), copies(copies) {}
int getCopies() const { return copies; }
void setTitle(std::string newTitle) { title = newTitle; }
void setAuthor(std::string newAuthor) { author = newAuthor; }
void setCopies(int newCopies) { copies = newCopies; }
void display() const override {
std::cout << "Title: " << title
<< ", Author: " << author
<< ", Copies: " << copies << std::endl;
}
friend std::ostream& operator<<(std::ostream& os, const Book& book);
friend std::istream& operator>>(std::istream& is, Book& book);
};
std::ostream& operator<<(std::ostream& os, const Book& book) {
os << book.title << '\n' << book.author << '\n' << book.copies << '\n';
return os;
}
std::istream& operator>>(std::istream& is, Book& book) {
std::getline(is, book.title);
std::getline(is, book.author);
is >> book.copies;
is.ignore();
return is;
}
class librarymanagementsystem {
private:
std::vector<Book> books;
const std::string filename = "book_records.txt";
void loadFromFile() {
std::ifstream file(filename);
if (!file.is_open()) return;
books.clear();
Book temp("", "", 0);
while (file >> temp) {
books.push_back(temp);
}
file.close();
}
void saveToFile() {
std::ofstream file(filename);
for (const auto& book : books) {
file << book;
}
file.close();
}
public:
librarymanagementsystem() {
loadFromFile();
}
~librarymanagementsystem() {
saveToFile();
}
void addBookRecord() {
std::string title, author;
int copies;
std::cout << "Enter book title: ";
std::getline(std::cin, title);
std::cout << "Enter author name: ";
std::getline(std::cin, author);
std::cout << "Enter number of copies: ";
std::cin >> copies;
std::cin.ignore();
books.emplace_back(title, author, copies);
std::cout << "Book record added successfully!" << std::endl;
}
void showBookRecords() {
if (books.empty()) {
std::cout << "No book records available." << std::endl;
return;
}
std::cout << "Book Records:" << std::endl;
for (const auto& book : books) {
book.display();
}
}
void checkAvailability() {
std::string bookTitle;
std::cout << "Enter the book title to check availability: ";
std::getline(std::cin, bookTitle);
auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
return book.getTitle() == bookTitle;
});
if (it != books.end()) {
it->display();
} else {
std::cout << "Book not found in the system." << std::endl;
}
}
void modifyBookRecord() {
std::string bookTitle;
std::cout << "Enter the book title to modify: ";
std::getline(std::cin, bookTitle);
auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
return book.getTitle() == bookTitle;
});
if (it != books.end()) {
std::string newTitle, newAuthor;
int newCopies;
std::cout << "Enter new book title: ";
std::getline(std::cin, newTitle);
std::cout << "Enter new author name: ";
std::getline(std::cin, newAuthor);
std::cout << "Enter new number of copies: ";
std::cin >> newCopies;
std::cin.ignore();
it->setTitle(newTitle);
it->setAuthor(newAuthor);
it->setCopies(newCopies);
std::cout << "Book record modified successfully!" << std::endl;
} else {
std::cout << "Book not found in the system." << std::endl;
}
}
void deleteBookRecord() {
std::string bookTitle;
std::cout << "Enter the book title to delete: ";
std::getline(std::cin, bookTitle);
auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
return book.getTitle() == bookTitle;
});
if (it != books.end()) {
char confirmation;
std::cout << "Are you sure you want to delete the book record? (y/n) ";
std::cin >> confirmation;
std::cin.ignore();
if (confirmation == 'y') {
books.erase(it);
std::cout << "Book record deleted successfully!" << std::endl;
} else {
std::cout << "Book record deletion cancelled." << std::endl;
}
} else {
std::cout << "Book not found in the system." << std::endl;
}
}
};
int main() {
librarymanagementsystem system;
int choice;
while (true) {
std::cout << "\nLibrary Management System" << std::endl;
std::cout << "1. Add Book Record" << std::endl;
std::cout << "2. Show Book Records" << std::endl;
std::cout << "3. Check Availability" << std::endl;
std::cout << "4. Modify Book Record" << std::endl;
std::cout << "5. Delete Book Record" << std::endl;
std::cout << "6. Exit" << std::endl;
std::cout << "Enter your choice: ";
std::cin >> choice;
std::cin.ignore();
switch (choice) {
case 1:
system.addBookRecord();
break;
case 2:
system.showBookRecords();
break;
case 3:
system.checkAvailability();
break;
case 4:
system.modifyBookRecord();
break;
case 5:
system.deleteBookRecord();
break;
case 6:
std::cout << "Exiting Library Management System..." << std::endl;
return 0;
default:
std::cout << "Invalid choice. Please try again." << std::endl;
break;
}
}
}
