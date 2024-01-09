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

  
  int getDay() const {
    return day;
  }

  int getMonth() const {
    return month;
  }

  int getYear() const {
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

  void displayDate() const {
    std::cout << day << "/" << month << "/" << year;
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
private:
  int memberID;
  vector<Book> booksLoaned; //vector of book IDs which are the names of each book object
public:

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
  Member borrower;

  Book(int bookID, string bookName, string authorFirstName, string authorLastName);

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
	vector<Book> allbooks;
        while(getline(bookDataFile,line)){
	  string trash; //Just a variable to hold double quote or any spaces that are left behind
	  stringstream ss(line);
	  getline(ss, idStr, ','); // Reading in id for book
	  if(line.at(idStr.length() + 1) == '"'){
	    cout << "1idStr passed into stoi is: " << idStr << endl;
	    bID = stoi(idStr); //Read in id as string then converted to int
	    getline(ss, trash, '"'); 
	    getline(ss, bName, '"');
	    getline(ss, trash, ',');
	    getline(ss, pageStr, ',');
	    cout << "1pageStr passed into stoi is: " << pageStr << endl;
	    bPageCount = stoi(pageStr);
	    getline(ss, bAuthFName, ',');
	    getline(ss, bAuthLName, ',');
	    getline(ss, bType, ',');
	  }else{
	    cout << "2idStr passed into stoi is: " << idStr << endl;
	    bID = stoi(idStr); //Read in id as string then converted to int
	    getline(ss, bName, ',');//Reading in the name
	    getline(ss, pageStr, ',');
	    cout << "2pageStr passed into stoi is: " << pageStr << endl;
	    bPageCount = stoi(pageStr);
	    getline(ss, bAuthFName, ',');
	    getline(ss, bAuthLName, ',');
	    getline(ss, bType, ',');
	  }
	  cout << bID << " , " << bName << " , " << bPageCount << " , " << bAuthFName << " , " << bAuthLName << " , " << bType << endl;
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
  Librarian * main = new Librarian(id, baseSalary);
  main->name = staffName;
  main->address =  staffAddress;
  main->email = staffEmail;
  main->setSalary(baseSalary);
  cout <<  "Welcome to the Library management program " << main->getName() << "#" << main->getStaffID() << ". \n";
  cout << "Your details are as follows - \n" << "Address: " << main->getAddress() << endl << "Email: " << main->getEmail() << endl << "Base salary: " << main->getSalary() << endl;
  
  return 0;
}


