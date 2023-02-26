// GPA.cpp
// Anthony Thompson CISP 400
// 12/19/2023

#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

// Specification B4 - Highlight Failing Grades
class FancyText { // colors.cpp -- color text demo
  int ANSIcode = 0;

public:
  void setColor(int c) { ANSIcode = c; } // setter
  string CPrint(string s) {              // getter
    string sout;
    sout += "\033[0;";
    sout += to_string(ANSIcode);
    sout += "m";
    sout += s;
    sout += "\033[0m\n";
    return sout;
  }
};
// Specification A1 - Date class
class Date {
private:
  int mo, day, yr;

public:
  void setDate(int, int, int);
  void Print();
  string getDate();
  void componentTest();
};
void Date::setDate(int m, int d, int y) {
  mo = m;
  day = d;
  yr = y;
}
void Date::Print() { cout << mo << "/" << day << "/" << yr << endl; }
string Date::getDate() {
  return to_string(mo) + "/" + to_string(day) + "/" + to_string(yr);
}
// Specification A3 - Component Test Method in Date
void Date::componentTest() {
  Date test;
  test.setDate(2, 19, 2023);
  if (test.getDate() == "2/19/2023")
    cout << "Component test passed" << endl;
  else
    cout << "Component test failed" << endl;
}

class Student {
private:
  double *stuGrades;
  int gradeInt;

public:
  Student();
  void addGradeMethod(double grade);
  void gradeDisplayMethod();
  void
  Grade2Lttr(); // Rename from GradeLetterMethod to Grade2Lttr before handing in
};

// constructor initializing stuGrades
Student::Student() : stuGrades(nullptr), gradeInt(0) {}

// Specification B1 - Dynamic Array
// Specification B2 - Add Element
void Student::addGradeMethod(double grade) {
  double *temp = new double[gradeInt + 1];
  if (stuGrades != nullptr) {
    for (int i = 0; i < gradeInt; i++) {
      temp[i] = stuGrades[i];
    }
    delete[] stuGrades; // throw away existing stuGrades array (clean up?)
  }
  // insert grade to the end of temp
  temp[gradeInt] = grade;
  // set temp to stuGrades for later use
  stuGrades = temp;
  gradeInt++; // increment gradeInt
}

// Specification C2 - Print Scores
void Student::gradeDisplayMethod() {
  // initializing the FancyText variables so I can use it in my output
  const int red = 31;
  FancyText cout_red;
  cout_red.setColor(red);
  if (gradeInt == 0) {
    cout << "Please enter a grade before trying to display stuGrades." << endl;
  } else {
    cout << "Grades Entered: " << endl;
    // Specification C3 - Letter Grades
    for (int i = 0; i < gradeInt; i++) {
      cout << stuGrades[i] << " - ";
      if (stuGrades[i] >= 90)
        cout << "A" << endl;
      else if (stuGrades[i] >= 80 && stuGrades[i] < 90)
        cout << "B" << endl;
      else if (stuGrades[i] >= 70 && stuGrades[i] < 80)
        cout << "C" << endl;
      else if (stuGrades[i] >= 60 && stuGrades[i] < 70)
        cout << "D" << endl;
      else if (stuGrades[i] < 60)
        cout << cout_red.CPrint("F");
    }
  }
}

// Specification C4 - Compute GPA
void Student::Grade2Lttr() {
  if (gradeInt == 0)
    cout << "No grade entered yet, that's option [1]." << endl;
  else {
    double totalGrade = 0;
    // loop to add all scores into one grade/get data
    for (int i = 0; i < gradeInt; i++)
      totalGrade += stuGrades[i];

    // gpa is the number of stuGrades divided by the total scores
    double gpa = totalGrade / gradeInt;

    cout << "Grade Average: " << fixed << setprecision(2) << gpa << endl
         << "Letter Grades: ";
    if (gpa >= 90)
      cout << "A" << endl;
    else if (gpa >= 80)
      cout << "B" << endl;
    else if (gpa >= 70)
      cout << "C" << endl;
    else if (gpa >= 60)
      cout << "D" << endl;
    else
      cout << "F" << endl;
  }
}
void ProgramGreeting();
void currentTime();
void UnitTest();
void MainMenu();

int main() {
  ProgramGreeting();
  Student studentData;
  int menu_Choices;
  double grade;
  // Specification A2 - External date initialization
  Date d1;
  d1.setDate(2, 19, 2023);
  d1.Print();
  currentTime();

  // do while loop in main: as advised to do in my peer review
  /* do - inputs while the inputs are not equal to INT 4 */
  do {
    MainMenu();
    cin >> menu_Choices;
    // while choices are less that 1 and greater than 4, stay in loop until
    // giving a valid input.
    // Specification B3 - Menu Input Validation
    while (menu_Choices < 1 || menu_Choices > 4) {
      cout << "Validation failed, please enter the corresponding number to "
              "action. \n\n";

      cin >> menu_Choices;
    }

    if (menu_Choices == 1)
    // Menu Choice 1: Add Grade
    {
      cout << "Enter a grade: ";
      cin >> grade;
      studentData.addGradeMethod(grade);
    } else if (menu_Choices == 2)
    //  Menu Choice 2: Display All Grades
    {
      studentData.gradeDisplayMethod();
    } else if (menu_Choices == 3) {
      //  Menu Choice 3: Process All Grades (gpa average)
      studentData.Grade2Lttr();
    } else if (menu_Choices != 4) // No good data
      cout << "Please re-enter, thanks." << endl;
    cout << endl;
    // while choice is not 4, do XXXX. if 4: end.
  } while (menu_Choices != 4);
  // Menu Choice 4: Quit The Program
  {
    cout << "Huh. I'm surprised you didnt just [X] out of the program." << endl;
    cout << "Goodbyte!" << endl;
  }

  return 0;
}
// Specification C1 - Program Greeting Function
void ProgramGreeting() {
  cout << R"(
 _     _____ _     _     ____                  
/ \ /|/  __// \   / \   /  _ \                 
| |_|||  \  | |   | |   | / \|                 
| | |||  /_ | |_/\| |_/\| \_/|                 
\_/ \|\____\\____/\____/\____/                 
                                               
                                               
                                               
        _____   _____                          
        \____\  \____\                         
_____                   _____   _____          
\____\                  \____\  \____\         
                   _                           
                  /.\                          
                  \ _\_                        
                  /|/ /                        
                  \__/\                        
                                               
 _      _____ _     ____  ____  _      _____ _ 
/ \  /|/  __// \   /   _\/  _ \/ \__/|/  __// \
| |  |||  \  | |   |  /  | / \|| |\/|||  \  | |
| |/\|||  /_ | |_/\|  \_ | \_/|| |  |||  /_ \_/
\_/  \|\____\\____/\____/\____/\_/  \|\____\(_)  
  )" << '\n';

  cout << endl;
  cout << "Program by: Anthony Thompson" << endl;
  cout << "" << endl;
  UnitTest();
  cout << "" << endl;
  cout << "Due date: ";
}
void MainMenu() {
  cout << "Main Menu" << endl;
  cout << "=============\n\n";
  cout << "1. Add Grade \n" << endl;
  cout << "2. Display All Grades \n" << endl;
  cout << "3. Process All Grades \n" << endl;
  cout << "4. Quit The Program \n" << endl;
  cout << "=============\n\n";
  cout << "Enter a number that corresponds with the desired action: \n\n";
}
void FailedGrade() {
  const int red = 31;
  FancyText cout_red;
  cout_red.setColor(red);
  cout << cout_red.CPrint(" Failing grade") << endl;
  // cout << cout_red.CPrint(" Failing grade") << endl;
}
void currentTime() {
  cout << "Current time and date:" << endl;
  time_t result = time(0);
  cout << asctime(localtime(&result)) << endl;
  cout << "" << endl;
}
// Specification A4 - Unit Test
void UnitTest() {
  Date d1;
  d1.componentTest();
}

/*
~~~~~~~~~~~~~~~~~~~~||  Spec Test  ||~~~~~~~~~~~~~~~~~~~~~~~

c1:greeting (done) includes welcome ASCI message, name, due date via setDate
method [line 210]
c2:print scores (done) apart of Grade Display method [line
105]
c3: letter stuGrades (done) apart of the Grade Display method. [line 105]
c4: compute GPA (done) called method to display gpa- unsure if there was a
setprescion requirement....  [line 130]

b1: create dynamic array (done)- I used a method in the sudent class addGrade to
both create and add to grade when its called in main() [line 79]
b2: [line 80]
b3: menu input validation (done) something I didnt do last time, used textbook
to get best way to do it [line 161]
b4: highlight failing grade (done) I could
not highlight score so I did letter grade [line 6]

A1: Date class (done) heavily relied on class work
A2: External date initialization (done) d1.setDate has 3 integers that are used
inside main()
A3: compmonent test method date (done) I have 2 tests. They failed
for about 4 hours and I changed the format of my date and now they work. I do
not know why at all. [ line 264]
A4: Unit test (done) tests the input for the due date
*/