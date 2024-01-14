#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;
using namespace filesystem;
//Methods that help with formatting in terminal
void partition(){
  for(int i=0; i<100; i++){
    cout << "-";
  }
  cout << endl;
}


//Each time we add a member we increment this counter
int memberCount = 1;

// Forward declarations to break cyclic dependancy for member class
class Book;
class Member;
class Librarian;
//Vectors that store our persons and books
vector<Book> allbooks;
vector<Member> allmembers;

//Classes
class Date{
public:
  int day;
  int month;
  int year;

public:
  Date() { // this constructor sets the date object to todays date
    time_t now = time(0);
    tm* localTime = localtime(&now);

    day = localTime->tm_mday;
    month = localTime->tm_mon + 1;  // tm_mon is zero-based (january = 0)
    year = localTime->tm_year + 1900;  // tm_year is years since 1900
  }

  //This one takes in values for day month and year
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
  int getDaysInMonth(int month){
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
      return 31;
    } else if (month == 4 || month == 6 ||month == 9 || month == 11){
      return 30;
    } else if (month == 2){
      return 28;
    } else
      return 31; // wont be necessary but just incase
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
  
  Member(int newmemberID): memberID(newmemberID){}

   Member(){ //overloaded constructor was needed to reset the borrower member in Book class as it was not compiling without
     memberID = 0;
     setName(" ");
     setAddress(" ");
     setEmail(" ");
   }

  int getMemberID(){
    return memberID;
  }

  
  vector<Book>& getBooksBorrowed(){ //we need to access those object attributes directly and not running functions using copied in values
    return booksLoaned;
  }

  void setBooksBorrowed(Book& book){
    booksLoaned.emplace_back(book);
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
    borrower = Member(0); //set the borrower member attribute as an empty member
  }

  void borrowBook(Member memBor, Date due){
    borrower = memBor;
    setDueDate(due);
  }
  
};

class  Librarian : public Person{
private:
  int staffID;
  int salary;
public:

  Librarian(int newstaffID, int newsalary): staffID(newstaffID), salary(newsalary){}
  void addMember(){
    string newMemName, newMemEmail, newMemAddress;
    cout << "Please enter the new members name - \n";
    getline(cin,newMemName);
    cout << "Please enter the new members email - \n";
    getline(cin,newMemEmail);
    cout << "Please enter the new members address - \n";
    getline(cin,newMemAddress);
    cout << endl << "WARNING! These details cannot be changed after the fact.\n" << "Please take time to review details of new member entry.\n";
    cout << "Name: " << newMemName << endl;
    cout << "Email: " << newMemEmail << endl;
    cout << "Address: " << newMemAddress << endl;
    cout << endl << "Do you wish to submit membership?\n";
    cout << "\t1 - Submit\n";
    cout << "\t2 - Cancel submission and return home\n";
    int choice;
    cin >> choice;
    while(!cin){
      cout << "Not a valid choice, plese input from the previous options\n";
      cin.clear(); //clear the error
      cin.ignore(); //ignore the non integer inputted
      cin >> choice;
    }
    while((choice < 1) || (choice > 2)){
      cout << "Not a valid choice, plese input from the previous options\n";
      cin.clear(); //clear the error
      cin.ignore();//ignore the non integer inputted
      cin >> choice;
    }
    Member newMem(memberCount);
    switch(choice){
    case 1:{
      newMem.name = newMemName;
      newMem.email = newMemEmail;
      newMem.address = newMemAddress;
      memberCount++;
      allmembers.emplace_back(newMem);
      cout << endl;
      partition();
      cout << endl;
      cout << endl << endl << "New member registered!\n";
      cout << "Member ID: " << newMem.getMemberID() << endl;
      cout << "Name: " << newMem.getName() << endl;
      cout << "Email: " << newMem.getEmail() << endl;
      cout << "Address: " << newMem.getAddress() << endl << endl;
    }break;
    case 2:{
      cout << "Member submission cancelled.\n";
    }break;
    }
  }

  void issueBook(int memberID, int bookID){
    allmembers[memberID - 1].setBooksBorrowed(allbooks[bookID - 1]);
    Date today;
    Date dateDue;
    int dayToday = today.getDay(), monthToday = today.getMonth(), yearToday = today.getYear(), dayDue, monthDue, yearDue;
    int daysInTodayMonth = today.getDaysInMonth(monthToday);
    dayDue = dayToday + 3;
    if (dayDue > daysInTodayMonth) { //If due date is in the next month
      dayDue = daysInTodayMonth - dayDue; // find date due in the next month
      monthDue = monthToday + 1; //increment the month
      if (monthDue > 12) { // if in december then year is incremented and month is 1 again
	monthDue = 1;
	yearDue = yearToday + 1;
      } else { //if not just keep in the same year
	yearDue = yearToday;
      }
    } else {
      monthDue = monthToday;
      yearDue = yearToday;
    }
    dateDue.setDay(dayDue);
    dateDue.setMonth(monthDue);
    dateDue.setYear(yearDue);
    cout << endl << endl << "Today's date is ";
    today.displayDate();
    cout << ".\n";
    allbooks[bookID - 1].borrowBook(allmembers[memberID - 1], dateDue);
    cout << "Member " << allmembers[memberID - 1].getName() << "#" << allmembers[memberID - 1].getMemberID() << " has borrowed " << allbooks[bookID - 1].getBookName() << "#" << allbooks[bookID - 1].getBookID() << " and the book is due back on ";
    allbooks[bookID - 1].getDueDate().displayDate();
    cout << ".\n" << endl << endl;
  }

  void returnBook(int memberID, int bookID){
    if(allmembers[memberID - 1].getBooksBorrowed().size() == 1){ // 
      calcFine(memberID); //We calculate the fine and print the amount owed if any and print message inside
      allbooks[bookID - 1].returnBook(); //Set the borrower of the book to empty and the id to 0 as a flag
      allmembers[memberID - 1].getBooksBorrowed().pop_back(); //take the returned book out of the vector
    }else{
      vector<Book> tempVec = allmembers[memberID - 1].getBooksBorrowed(); //Create a temporary vector to hold all borrowed books
      int index1 = 0, index2 = 0; //We need to find the index of the book being returned once in the booksBorrowed vector to remove all books but the one being returned, and the second time to remove just the book thats been returned from the tempVec which we will use to refill the booksBorrowed vector after calculating fines
      for( index1=0; index1 < allmembers[memberID - 1].getBooksBorrowed().size(); index1++){
	if(allmembers[memberID - 1].getBooksBorrowed()[index1].getBookName() == allbooks[bookID - 1].getBookName()){ //finding the index of book being returned
	  break;
	}
      }
      swap(allmembers[memberID - 1].getBooksBorrowed()[index1] ,allmembers[memberID - 1].getBooksBorrowed().front() ); //Swap the book being returned with the first book in the vector of booksBorrowed()
      for(int i=0; i < (allmembers[memberID - 1].getBooksBorrowed().size() - 1); i++){ //Removing all books but the one being returned
	allmembers[memberID - 1].getBooksBorrowed().pop_back();
      }
      calcFine(memberID); //there should only be the book being returned in the vector as of now
      allmembers[memberID - 1].getBooksBorrowed() = tempVec; //Restore all borrowed books plus the one thats been returned
      for(index2=0; index2 < allmembers[memberID - 1].getBooksBorrowed().size(); index2++){
	if(allmembers[memberID - 1].getBooksBorrowed()[index2].getBookName() == allbooks[bookID - 1].getBookName()){ //finding the index of book being returned
	  break;
	}
      }
      swap(allmembers[memberID - 1].getBooksBorrowed()[index2] ,allmembers[memberID - 1].getBooksBorrowed().back() ); //Send the book thats just been returned to the back
      allmembers[memberID - 1].getBooksBorrowed().pop_back(); //Remove returned book
      allbooks[bookID - 1].returnBook(); //Set the borrower of the book to empty and the id to 0 as a flag
    }
    
  }

  void displayBorrowedBooks(int memberID){
    if (allmembers[memberID - 1].getBooksBorrowed().size() == 0){
      cout << "No books on loan.\n";
    } else {
      for (auto b : allmembers[memberID - 1].getBooksBorrowed()){
	cout << "\t\tID: " << b.getBookID() << endl <<
	  "\t\tName: " << b.getBookName() << endl <<
	  "\t\tAuthor: " << b.getAuthorFirstName() << " " << b.getAuthorLastName() << endl <<
	  "\t\tGenre/Type: " << b.bookType << endl;
      }
    }
  }

  void calcFine(int memberID){ //Ive made it so that upon calling of calcFine() the member returning their book only has that book in their booksBorrowed vector at the time of calculating fine, of course if they had more books on loan that their booksborrowed vector will be reinstated without this book that they just returned
    Date today;
    Date dueDate = allmembers[memberID - 1].getBooksBorrowed().front().getDueDate();
    int amountOwed = 0;
    if((today.getYear() > dueDate.getYear()) || (today.getMonth() > dueDate.getMonth()) || (today.getDay() > dueDate.getDay())){
      //If we're past the due date for the book then we need to calculate the amount of days past and set that as the fine
      int todayTotalDays, todayDaysSoFar, dueDateTotalDays, dueDateDaysSoFar;
      amountOwed = amountOwed + ((today.getYear() - dueDate.getYear()) * 365);
      for (int i = 1; i<today.getMonth(); i++){ //calculate amount of days uptil todays month
	todayDaysSoFar = todayDaysSoFar + today.getDaysInMonth(i);
      }
      todayDaysSoFar = todayDaysSoFar + today.getDay(); // add current months passed days til today
      for (int i = 1; i<dueDate.getMonth(); i++){ //calculate amount of days uptil duedate month
	dueDateDaysSoFar = dueDateDaysSoFar + dueDate.getDaysInMonth(i);
      }
      dueDateDaysSoFar = dueDateDaysSoFar + dueDate.getDay(); //add due dates months passed days 
      amountOwed = todayDaysSoFar - dueDateDaysSoFar;
      cout << endl << "Member : " << allmembers[memberID -1].getName() << " owes £" << amountOwed << " as per the library rules stating that a member, should they return a book past its due date, will owe £1 for every day it overdue by\n";
      
    }else{ //If the book is returned on time then no fine incurred
      cout << endl << "Return successful!\n" << "Member " << allmembers[memberID - 1].getName() << "#" << allmembers[memberID -1].getMemberID() << " has returned their book named " << allmembers[memberID - 1].getBooksBorrowed().front().getBookName() <<  " on time and will incur no fines.";
      
    }
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

vector<Librarian> libvec;


//Home method that sends user back to home page after each action
void home(){
  partition();
  cout << "Kamariddin Library Management system Home page - Hello " << libvec[0].getName() << "#" << libvec[0].getStaffID() << "! \n";
  partition();
  cout << endl;
  cout << "What action would you like to request:\n" << endl;
  cout << "\t\t1 - View library members \n";
  cout << "\t\t2 - Add a member to library database \n";
  cout << "\t\t3 - Issue a book loan \n";
  cout << "\t\t4 - Return a book from loan \n";
  cout << "\t\t5 - View member details via search \n";
  cout << "\t\t6 - View library of books \n";
  cout << "\t\t7 - Manage staff details \n";
  cout << "\t\t0 - Quit program \n" << endl;
  cout << "Enter the corresponding number to your choice \n";
  int homeChoice;
  cin >> homeChoice;
  while(!cin){
    cout << "Not a valid choice, please input a choice from the previous options\n";
    cin.clear(); //clear the error
    cin.ignore();//ignore the non integer inputted
    cin >> homeChoice;
  }
  while((homeChoice < 0) || (homeChoice > 7)){
    cout << "Not a valid choice, please input a choice from the previous options\n";
    cin.clear(); //clear the error
    cin.ignore();//ignore the non integer inputted
    cin >> homeChoice;
  }
  switch(homeChoice){
  case 0:{ //Close program
    partition();
    cout << endl << "\t\tSigning off...\n" << endl;
    cout << endl << "\t\tGoodbye " << libvec[0].getName() << endl << endl;
    partition();
    exit(0);
  }break;//End of close program
    
  case 1:{ // View library members
    partition();
    cout << "View library members chosen.\n";
    if(allmembers.size() == 0){
      cout << endl << endl << "There are currently no registered Kamariddin library members.\n";
      cout << "Would you like to register and add a member to the library database?\n";
      cout << endl << endl << "\t\t1 - Yes\n";
      cout << "\t\t2 - No (return to home page)\n" << endl;
      cin >> homeChoice;
      while(!cin){
	cout << "Not a valid choice, please input a choice from the previous options\n";
	cin.clear(); //clear the error
	cin.ignore();//ignore the non integer inputted
	cin >> homeChoice;
      }
      while((homeChoice < 1) || (homeChoice > 2)){
	cout << "Not a valid choice, please input from the previous options\n";
	cin.clear(); //clear the error
	cin.ignore();//ignore the non integer inputted
	cin >> homeChoice;
      }
      switch(homeChoice){
      case 1:
	cout << endl;
	partition();
	cout << endl;
	cin.ignore(); // get line kept getting skipped due to a \n being fed in so we ignore all before calling addMember
	libvec[0].addMember();
	cout << endl << "Returning home..." << endl;
	home();
	break;
      case 2:
	partition();
	cout << endl << endl;
	home();
	break;
      }
    }else{
      partition();
      for(auto mbr : allmembers){
	cout << endl << "\tName#memberID - " << mbr.getName() << "#" << mbr.memberID << endl;
	cout << "\tAddress - " << mbr.getAddress() << endl;
	cout << "\tEmail - " << mbr.getEmail() << endl;
	cout << "\tCurrently borrowing - ";
	if (mbr.getBooksBorrowed().size() == 0){
	  cout << "No books on loan " << endl;
	}else{
	  for (auto b : mbr.getBooksBorrowed()){
	    cout << b.getBookName() << "#" << b.getBookID() << " , ";
	  }
	  cout << endl;
	}
	partition();
      }
      cout << endl;
      cout << "Returning to home page...\n";
      cout << endl;
      partition();
      home();
    }
  }break; //end of View library members
    
  case 2:{ // Add member to library database
    cin.ignore();
    libvec[0].addMember();
    cout << endl;
    partition();
    cout << "Returning to home page..." << endl;
    home();
  }break;// end of add member to library
    
  case 3:{ // Issue a book
    cout << "Issue a book loan chosen.\n";
    if(allmembers.size() == 0){
      cout << "Cannot issue a book loan as there are currently no members registered to the Kamariddin library.\n";
    }else{
      int memIDChoice, bIDChoice;
      cout << "Enter the member ID: \n";
      cin >> memIDChoice;
      while(!cin){
	cin.clear();
	cin.ignore();
	cout << "Invalid input, please enter a member ID.\n";
	cin >> memIDChoice;
      }
      bool mExists = false;
      for (auto m : allmembers) {
        if (m.getMemberID() == memIDChoice) {
	  mExists = true;
	  break;
        }
      }
      cout << "Enter the book ID: \n";
      cin >> bIDChoice;
      while(!cin){
	cin.clear();
	cin.ignore();
	cout << "Invalid input, please enter a book ID.\n";
	cin >> bIDChoice;
      }
      bool bExists = false;
      bool bBorrowed = false;
      for (auto b : allbooks) {
        if (b.getBookID() == bIDChoice) {
	  bExists = true;
	  if(b.borrower.getMemberID() != 0){
	    bBorrowed = true;
	  }
	  break;
        }
      }
      if (mExists == false) {
        cout << "Invalid member ID.\n";
      }
      if (bExists == false) {
        cout << "Invalid book ID.\n";
      }
      if (bBorrowed == true) {
	cout << "This book is already out on loan.\n";
      }
      
      //Successful member and book id input
      if (mExists == true && bExists == true && bBorrowed == false){
	libvec[0].issueBook(memIDChoice, bIDChoice);
      }
    }
    cout << "Returning to home page...\n" << endl;
    home();
  }break; //end of issue a book
    
  case 4:{ //Return a book
    cout << endl << endl;
    partition();
    int memIDChoice, bIDChoice;
    bool mExists = false, bExists = false;
    cout << "Return a book chosen.\n" << endl << "Please enter the ID of the member returning their book - \n";
    cin >> memIDChoice;
    while(!cin){
	cin.clear();
	cin.ignore();
	cout << "Invalid input, please enter a member ID.\n";
	cin >> memIDChoice;
      }
    for (auto m : allmembers) {
        if (m.getMemberID() == memIDChoice) {
	  mExists = true;
	  break;
        }
      }
    if(mExists == true){
    cout << endl << "Member " << allmembers[memIDChoice - 1].getName() << "#" << allmembers[memIDChoice - 1].getMemberID() << " has \n";
    if (allmembers[memIDChoice - 1].getBooksBorrowed().size() == 0){
	  cout << "No books on loan " << endl;
	  cout << endl << "This member cannot return a book as no books have been borrowed in the first place\n";
	  cout << "Returning home ...\n";
	  cout << endl;
	  home();
	}else{
	  for (auto b : allmembers[memIDChoice - 1].getBooksBorrowed()){
	    cout << b.getBookName() << "#" << b.getBookID() << ".\n ";
	  }
	  cout << endl << "From the previously listed, which book does " << allmembers[memIDChoice - 1].getName() << " want to return?\n" << "Please input the corresponding book ID.\n";
	  cin >> bIDChoice;
	  while(!cin){
	    cin.clear();
	    cin.ignore();
	    cout << "Invalid input, please enter a book ID.\n";
	    cin >> bIDChoice;
	  }
	  for(auto b : allmembers[memIDChoice - 1].getBooksBorrowed()){ //Accessing that members borrowed books
	    if (b.getBookID() == bIDChoice) {
	      bExists = true;
	      break;
	    }
	  }
	  if(bExists == true){
	    cout << "You have now started the process for member " << allmembers[memIDChoice - 1].getName() << "#" <<  allmembers[memIDChoice - 1].getMemberID() << " to return their book named " <<  allbooks[bIDChoice - 1].getBookName() << "#" << allbooks[bIDChoice - 1].getBookID() << ".\n";
	    libvec[0].returnBook(memIDChoice, bIDChoice);
	    cout << endl << "Returning home...\n" << endl;
	  }else{ // If the bookID given doesnt match any in the members borrowedbooks vector
	    cout << "That book ID is not recognised as being borrowed by " << allmembers[memIDChoice - 1].getName() << "#" << allmembers[memIDChoice - 1].getMemberID() << ".\n";
	    cout << "Please consult either the member or book database to see which book is being borrowed by which member.\n";
	    cout << endl << "Returning home...\n";
	  }
    }
    }else{ //If memberID isn't recognised or doesnt exist
      cout << "That member ID is not recognised.\n";
      cout << "Please consult the member database to see member details for all registered members in the Kamariddin library.\n";
      cout << endl << "Returning home...\n";
    }
    home();
  }break; //End of return a book
    
  case 5:{ //View member details via search
    cout << endl << endl;
    partition();
    int memIDChoice;
    bool mExists = false;
    cout << "View member details via search chosen.\n" << endl << "Please enter the ID of the member to view their details - \n";
    cin >> memIDChoice;
    while(!cin){
      cin.clear();
      cin.ignore();
      cout << "Invalid input, please enter a member ID.\n";
      cin >> memIDChoice;
    }
    for (auto m : allmembers) {
      if (m.getMemberID() == memIDChoice) {
	mExists = true;
	break;
      }
    }
    if(mExists == true){
      cout << "Member profile: \n" <<
	"ID: " << allmembers[memIDChoice - 1].getMemberID() << endl <<
	"Name: " << allmembers[memIDChoice - 1].getName() << endl <<
	"Email: " << allmembers[memIDChoice - 1].getEmail() << endl <<
	"Address: " << allmembers[memIDChoice - 1].getAddress() << endl <<
	"Books on loan: \n";
      libvec[0].displayBorrowedBooks(memIDChoice);
      cout << endl << endl << "Returning home... \n";
      
    }else{
      cout << endl << "Member ID not recognised. Does this member exist?\n" << endl << "Returning home..\n";
    }
    home();
  }break; // end of view member details via search
    
  case 6:{ //View library of books
    cout << endl << endl;
    cout << endl << "View book library chosen.\n" << endl;
    for(auto b : allbooks){
      cout << "Name # BookID : " << b.getBookName() << "#" << b.getBookID() << endl
	   << "Author : " << b.getAuthorFirstName() << " " << b.getAuthorLastName() << endl
	   << "Pages : " << b.bookPages << endl
	   << "Type : " << b.bookType << endl
	   << "Borrower : ";
      if(b.borrower.getMemberID() == 0){
	cout << " Not on loan.\n" << endl << endl;
      }else{
	cout << b.borrower.getName() << "#" << b.borrower.getMemberID() << endl << endl;
      }
    }

    
    home();
  }break; //end of View books
    
  case 7:{ //Manage staff details
    cout << endl << endl;
    partition();
    cout << endl << "Manage staff details chosen.\n";
    cout << endl << endl << "Librarian profile: \n" <<
      "ID : " << libvec[0].getStaffID() << endl <<
      "Name :" << libvec[0].getName() << endl <<
      "Email : " << libvec[0].getEmail() << endl <<
      "Address :" << libvec[0].getAddress() << endl <<
      "Salary :" << libvec[0].getSalary() << endl << endl;
    cout << "Do you wish to review your details?\n";
    cout << "\t\t1 - Yes\n";
    cout << "\t\t2 - No\n";
    int staffChoice;
    cin >> staffChoice;
    while(!cin){
      cout << "Not a valid choice, please input a choice from the previous options\n";
      cin.clear(); //clear the error
      cin.ignore();//ignore the non integer inputted
      cin >> staffChoice;
    }
    while((staffChoice < 1) || (staffChoice > 2)){
      
      cin.clear(); //clear the error
      cin.ignore();//ignore the non integer inputted
      cout << "Not a valid choice, please input a choice from the previous options\n";
      cin >> staffChoice;
    }
    switch (staffChoice){
    case 1:{
      string staffAddress;
      string staffEmail;
      int salary;
      cout << endl << endl << "Please enter your updated address. \n";
      cin.ignore();
      getline(cin,staffAddress);
      cout << "Please enter your updated email. \n";
      getline(cin,staffEmail);
      cout << "Please enter your updated salary. \n";
      cin >> salary;
      while(!cin){
	cout << "Not a valid number, please input a number to change your salary (number subject to review).\n";
      cin.clear(); //clear the error
      cin.ignore();//ignore the non integer inputted
      cin >> salary;
      }
      libvec[0].setEmail(staffEmail);
      libvec[0].setAddress(staffAddress);
      libvec[0].setSalary(salary);
      cout << endl << endl;
      cout << "Your details are as follows - \n" << "Name: " << libvec[0].getName() << endl << "Address: " << libvec[0].getAddress() << endl << "Email: " << libvec[0].getEmail() << endl << "Salary (subject to review) : " << libvec[0].getSalary() << endl;
      cout << endl << endl << "Returning home...\n" << endl;
      
    }break;
    case 2:{
      cout << "Choice confirmed! \n" << "Returning home...\n" << endl;
    }break;
    }
    home();
  }break; // end of manage staff details
  }
}

int main(){
  //We declare the extension we are looking for as we will not hardcode the name of data file
  string datafileext = ".csv";
  //Processing .csv file
  for(auto i : directory_iterator(current_path())){ //iterating over each file in the directory
    if(i.path().extension() == datafileext){ // if that file has a csv extension we open that file (our limitation is that only one csv file can be in the same directory as our cpp file for the program to work)
      ifstream bookDataFile(i.path());
      if (bookDataFile.is_open()){
	string line;
	getline(bookDataFile,line); //Skip the header line with table titles
	int bID, bPageCount;
	string idStr, bName, pageStr , bAuthFName, bAuthLName, bType;
        while(getline(bookDataFile,line)){ //Looping through each row and storing each cell in a string
	  string trash; //Just a variable to hold double quote or any spaces that are left behind from fields that have commas in them
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
	  newBook.returnBook();
	  allbooks.emplace_back(newBook); //feed into the back of the vector 
	}
	bookDataFile.close(); //Close our csv file as all info is now stored
      }else{
	cout << "Could not open file : " << i.path(); //error message for if the opening of our csv file is unsucessful
	return 0;
      }
    }
  }
  string staffName;
  string staffAddress;
  string staffEmail;
  int baseSalary = 25000;
  int id;
  partition();
  cout << "\t\tWelcome fellow librarian to the Kamariddin library!" << endl;
  partition();
  cout << "Please enter your name to create a staff account."   << endl;
  getline(cin,staffName);
  cout << "Please enter your address. \n";
  getline(cin,staffAddress);
  cout << "Please enter your email. \n";
  getline(cin,staffEmail);
  cout << endl << endl;
  partition();
  id = (rand() * 9000) + 1000; //randomise the librarians id
  Librarian main(id, baseSalary);
  main.name = staffName;
  main.address =  staffAddress;
  main.email = staffEmail;
  main.setSalary(baseSalary);
  libvec.emplace_back(main);
  cout << endl << endl;
  cout << "Welcome to the Kamariddin Library management system " << libvec[0].getName() << "#" << libvec[0].getStaffID() << ". \n";
  cout << "Your details are as follows - \n" << "Address: " << libvec[0].getAddress() << endl << "Email: " << libvec[0].getEmail() << endl << "Base salary: " << libvec[0].getSalary() << endl << "Should you wish to change your details please do so by choosing option 'Manage staff details' in the home screen.\n" <<  endl ;
  home();
  return 0;
}



