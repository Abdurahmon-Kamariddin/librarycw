#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Classes

class Person{ //Here we have our Person superclass from which our librarians and member classes will inherit from as they are both persons with the corresponding attributes
public:
  string name;
  string address;
  string email;

  string getName(){
    return this->name;
  }
    
  void setName(string newname){
    this->name = newname;
  }

  string getAddress(){
    return this->address;
  }

  void setAddress(string newaddress){
    this->address = newaddress;
  }

  string getEmail(){
    return this->email;
  }

  void setEmail(string newemail){
    this->email = newemail;
  }
};

class Member : public Person
{
private:
  int memberID;
  vector<Book> booksLoaned; //vector of book IDs which are the names of each book object
public:
  Member(int newmemberID, string newname, string newaddress, string newemail){
    this->memberID = newmemberID;
    this->name = newname;
    this->address = newaddress;
    this->email = newemail;
  }

  int getMemberID(){
    return this->memberID;
  }

  vector<Book> getBooksBorrowed(){
    return this->booksLoaned;
  }

  void setBooksBorrowed(){
  }};

class  Librarian : public Person{
private:
  int staffID;
  int salary;
public:

  Librarian(int newstaffID, int newname, string newaddress, string newemail, int newsalary){
    this->staffID = newstaffID;
    this->name = newname;
    this->address = newaddress;
    this->email = newemail;
    this->salary = newsalary;
  }

  void addMember(){
    string tempName;
    string tempAddress;
    string tempEmail;
    int tempMemberID;
    cout << "Please input name of new member. \n";
    cin >> tempName;
    cout << "Please enter the address of the new member. \n";
    cin >> tempAddress;
    cout << "Please input the email of the new member. \n";
    cin >> tempEmail;
    cout << "Please assign " << tempName << " a ID number. \n";
    cin >> tempMemberID;
    int submitChoice;
    cout << "You are about to create a new library member, please review the details below and verify the creation of the following member. \n" <<
      "Member name: " << tempName << endl <<
      "Member address: " << tempAddress << endl <<
      "Member email: " << tempEmail << endl <<
      "Member ID: " << tempMemberID << endl <<
      "Enter 2 to submit, 1 to re-enter details and 0 to go back to home screen. \n";    
    cin >> submitChoice;
    if((submitChoice != 2) ||(submitChoice != 1) || (submitChoice != 0)){
      cout << "Invalid choice, please enter 2 to submit, 1 to re-enter details and 0 to go back to home screen. \n";
      cin >> submitChoice;
    }
    switch(submitChoice){
    case 0:
	  
      break;
    case 1:
      this->addMember();
      break;
    case 2:
      Member* tempMemberID = new Member(tempMemberID, tempName, tempAddress, tempEmail);
      cout << (*tempMemberID).getName << "#" << (*tempMemberID).getMemberID << " is now a member. \n";
	  
      break;


      break;
    }
	
	    
	  
	
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
    return this->staffID;
  }

  void setStaffID(int newstaffID){
    this->staffID = newstaffID;
  }

  int getSalary(){
    return this->salary;
  }

  void setSalary(int newsalary){
    this->salary = newsalary;
  }
};

class Book{
  int bookID;
  string bookName;
  string authorFirstName;
  string authorLastName;
  string bookType;
  Date dueDate;
  Member borrower;

  Book(int bookID, string bookName, string authorFirstName, string authorLastName);

  int getBookID(){
    return this->bookID;
  }

  string getBookName(){
    return this->bookName;
  }

  string getAuthorFirstName(){
    return this->authorFirstName;
  }

  string getAuthorLastName(){
    return this->authorLastName;
  }

  Date getDueDate(){
    return this->dueDate;
  }

  void setDueDate(Date dueDate){
    this->dueDate = dueDate;
  }

  void returnBook(){

  }

  void borrowBook(Member borrower, Date dueDate){

  }
}
  

  int main(){
  Librarian 196 = new Librarian(196,"Abdurahmon", "Gatliff Road", "ak2527@live.mdx.ac.uk", 20000);
  196.addMember();
  return 0;
}


