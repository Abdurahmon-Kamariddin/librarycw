#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
//We list our members in a vector that we only allow upto 200 members
vector<Member> members;
//Our maximum number of members allowed in our library
int MAX_MEMBERS = 200;
//Each time we add a member we increment this counter (we check against this counter every time we add to make sure membercount is < MAX_MEMBERS)
int memberCount = 0;
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
public:
  friend class Book;
  int memberID;
  vector<Book> booksLoaned; //vector of book IDs which are the names of each book object

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
  friend class Member;
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

  void setDueDate(Date dueDate){
    dueDate = dueDate;
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
  string name;
  string address;
  string email;
  
  cout << "Welcome fellow librarian to the Kamariddin library! \n";
  cout << "Please enter your name to create a staff account. \n";
  cin << ;
  Librarian * main = new Librarian(196, 20000);
  abdurahmon->name = "Abdurahmon";
  abdurahmon->address =  "Gatliff Road";
  abdurahmon->email = "ak2527@live.mdx.ac.uk";
  cout <<  abdurahmon->getName();
  for(int i=0; i<MAX_MEMBERS; i++){
    members[i] = (new Member(i));
  }
  
  return 0;
}


