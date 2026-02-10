This system is a C++ library management application designed for use by a librarian to manage books and members in a small library. It reads book data from a CSV file (provided for testing, but configurable to accept any valid file) and uses a predefined UML class diagram that must be followed exactly.

The system keeps track of library books and registered members, allowing the librarian to manage borrowing and returning of books. Each book has an ID, title, author, genre, and page count, and members may borrow books for a fixed period of three days.

Key functionality includes:

Creating and displaying new library members

Issuing books to members with an automatically calculated due date

Returning borrowed books

Displaying all books currently borrowed by a specific member

Calculating overdue fines at a rate of £1 per day when books are returned late

The program includes input validation and helpful error messages to ensure correct usage and an intuitive user experience. It does not handle payments or customer-facing features and is intended solely for librarian use.

This project was designed and coded to adhere to specific system and class design as shown in the UML provided in the repo 
