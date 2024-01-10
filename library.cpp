#include <iostream>
#include <string>
#include <locale>
#include <vector>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <sstream>

using namespace std;
using namespace filesystem;

//Our maximum number of members allowed in our library
int MAX_MEMBERS = 200;
//Each time we add a member we increment this counter (we check against this counter every time we add to make sure membercount is < MAX_MEMBERS)
int memberCount = 1;

//Classes
class Book; // Forward declaration to break cyclic dependancy for member class
class Date{
public:
  int day;
  int month;
  int year;

public:
  Date() {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    day = localTime->tm_mday;
    month = localTime->tm_mon + 1;  // tm_mon is zero-based
    year = localTime->tm_year + 1900;  // tm_year is years since 1900
  }

  
  Date(int d, int m, int y) : day(d), month(m), year(y) {}

  
  int getDay(){
    return day;
  }

  int getMonth(){
    return month;
  }

  int getYear(){
    return year;
  }

  void setDay(int newday) {
    day = newday;
  }

  void setMonth(int newmonth) {
    month = newmonth;
  }

  void setYear(int newyear) {
    year = newyear;
  }

  void displayDate(){
    cout << day << "/" << month << "/" << year;
  }
};
  
class Person{ //Here we have our Person superclass from which our librarians and member classes will inherit from as they are both persons with the corresponding attributes
public:
  string name;
  string address;
  string email;

  string getName(){
    return name;
  }
    
  void setName(string newname){
    name = newname;
  }

  string getAddress(){
    return address;
  }

  void setAddress(string newaddress){
    address = newaddress;
  }

  string getEmail(){
    return email;
  }

  void setEmail(string newemail){
    email = newemail;
  }
};

class Member : public Person
{
public:
  int memberID;
  vector<Book> booksLoaned; //vector of book IDs which are the names of each book object

  friend class Book;
  Member(int newmemberID): memberID(newmemberID){}

  int getMemberID(){
    return memberID;
  }

  vector<Book> getBooksBorrowed(){
    return booksLoaned;
  }

  void setBooksBorrowed(){
  }
};

class Book{
public:
  int bookPages;
  int bookID;
  string bookName;
  string authorFirstName;
  string authorLastName;
  string bookType;
  Date dueDate;
  Member borrower();

  Book(int bID, string bName, string authFirstName, string authLastName): bookID(bID), bookName(bName), authorFirstName(authFirstName), authorLastName(authLastName){}

  int getBookID(){
    return bookID;
  }

  string getBookName(){
    return bookName;
  }

  string getAuthorFirstName(){
    return authorFirstName;
  }

  string getAuthorLastName(){
    return authorLastName;
  }

  Date getDueDate(){
    return dueDate;
  }

  void setDueDate(Date date){
    dueDate = date;
  }

  void returnBook(){
  }

  void borrowBook(Member borrower, Date dueDate){
  }
};

class  Librarian : public Person{
private:
  int staffID;
  int salary;
public:

  Librarian(int newstaffID, int newsalary): staffID(newstaffID), salary(newsalary){}
  void addMember(){
  }

  void issueBook(int memberID, int bookID){	
  }

  void returnBook(int memberID, int bookID){
  }

  void displayBorrowedBooks(int memberID){
  }

  void calcFine(int memberID){	
  }

  int getStaffID(){
    return staffID;
  }

  void setStaffID(int newstaffID){
    staffID = newstaffID;
  }

  int getSalary(){
    return salary;
  }

  void setSalary(int newsalary){
    salary = newsalary;
  }
};

int main(){
  vector<Book> allbooks;
  //We declare the extension we are looking for as we will not hardcode the name of data file
  string datafileext = ".csv";
  //
  for(auto i : directory_iterator(current_path())){ //iterating over each file in the directory
    if(i.path().extension() == datafileext){ // if that file has a csv extension we open that file (our limitation is that only one csv file can be in the directory for the program to work
      ifstream bookDataFile(i.path());
      if (bookDataFile.is_open()){
	string line;
	getline(bookDataFile,line); //Skip the header line with table titles
	int bID, bPageCount;
	string idStr, bName, pageStr , bAuthFName, bAuthLName, bType;
        while(getline(bookDataFile,line)){
	  string trash; //Just a variable to hold double quote or any spaces that are left behind
	  stringstream ss(line);
	  getline(ss, idStr, ','); // Reading in id for book
	  if(line.at(idStr.length() + 1) == '"'){ //If the name of the book starts with 
	    bID = stoi(idStr); //Read in id as string then converted to int
	    getline(ss, trash, '"'); //We remove the first double quote
	    getline(ss, bName, '"'); //Extract the name from the previous double quote to the next one
	    getline(ss, trash, ','); //remove the gap between the last double quote and the next comma
	    getline(ss, pageStr, ',');
	    bPageCount = stoi(pageStr);
	    getline(ss, bAuthFName, ',');
	    getline(ss, bAuthLName, ',');
	    getline(ss, bType, ',');
	  }else{
	    bID = stoi(idStr); //Read in id as string then converted to int
	    getline(ss, bName, ',');//Reading in the name
	    getline(ss, pageStr, ',');//Reading in the string of the amount of pages
	    bPageCount = stoi(pageStr);//converting that string into an int
	    getline(ss, bAuthFName, ',');//Reading the author first name
	    getline(ss, bAuthLName, ',');//Reading the author last name
	    getline(ss, bType, ',');//Reading in the book type
	  }
	  //Here we take each book attribute and make a Book object with it
	  Book newBook(bID, bName, bAuthFName, bAuthLName);
	  newBook.bookPages = bPageCount;
	  newBook.bookType = bType;
	  allbooks.emplace_back(newBook);
	}
	bookDataFile.close();
	cout << "SUCCESS";
      }else{
	cout << "Could not open file : " << i.path();
	return 0;
      }
    }
  }
  
  string staffName;
  string staffAddress;
  string staffEmail;
  int baseSalary = 25000;
  int id;
  cout << "Welcome fellow librarian to the Kamariddin library! \n";
  cout << "Please enter your name to create a staff account. \n";
  getline(cin,staffName);
  cout << "Please enter your address. \n";
  getline(cin,staffAddress);
  cout << "Please enter your email. \n";
  getline(cin,staffEmail);
  id = (rand() * 9000) + 1000;
  Librarian main(id, baseSalary);
  main.name = staffName;
  main.address =  staffAddress;
  main.email = staffEmail;
  main.setSalary(baseSalary);
  cout <<  "Welcome to the Library management program " << main.getName() << "#" << main.getStaffID() << ". \n";
  cout << "Your details are as follows - \n" << "Address: " << main.getAddress() << endl << "Email: " << main.getEmail() << endl << "Base salary: " << main.getSalary() << endl;
  // ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  cout<< endl << "What action would you like to request:
  return 0;
}



