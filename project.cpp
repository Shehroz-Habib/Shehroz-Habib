 #include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <cctype>
#include <limits>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;

// Class Person
class Person
{
public:
  int id;
  string name, Fathername;
  string cnic, address, contact, designation, Shift, attendence;
  string Salary;
  int age;

  // Constructor with default values for Person class data members
  Person()
  {
    id = 0;
    name = "";
    Fathername = "";
    cnic = "";
    address = "";
    contact = "";
    designation = "";
    Shift = "";
    attendence = "";
    Salary = "";
    age = 0;
  }
};
// Class Employee
class Employee : public Person
{
public:
  string reson, date;
  double fine;
  int days;
  string previousJob;
  string behavior;

  // Constructor with default values for Employee class data members
  Employee()
  {
    reson = "";
    date = "";
    fine = 0.0;
    days = 0;
    previousJob = "";
    behavior = "";
  }
};

// Currunt Date
bool isCurrentDate(const string &dateStr)
{
  // Get the current time
  time_t now = time(0);
  tm *ltm = localtime(&now);
  int currentYear = 1900 + ltm->tm_year;
  int currentMonth = 1 + ltm->tm_mon;
  int currentDay = ltm->tm_mday;

  // Parse the date from the CSV file
  stringstream dateStream(dateStr);
  int year, month, day;
  char delimiter;
  dateStream >> year >> delimiter >> month >> delimiter >> day;

  // Check if the date matches the current date
  return (year == currentYear && month == currentMonth && day == currentDay);
}

// for validate id
int getIntegerInput(const string &prompt)
{
  int input;

  while (true)
  {
    cout << prompt << ": ";
    cin >> input;

    // Check if input failed or was not an integer
    if (cin.fail())
    {
      cout << "Invalid input. Please enter an integer." << endl;
      cin.clear();                                         // Clear the error state from cin
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    }
    else
    {
      break; // Break out of the loop if a valid integer is entered
    }
  }
  return input;
}

// for validate of Date
bool validateDATE(const string &date)
{
  // Regular expression to match valid DATE format (XX-XX-XXXX)
  regex pattern("^[0-9]{2}-[0-9]{2}-[0-9]{4}$");
  return regex_match(date, pattern);
}

// for validate cnic
bool validateCNIC(const string &cnic)
{
  // Regular expression to match valid CNIC format (XXXXX-XXXXXXX-X)
  regex pattern("^[0-9]{5}-[0-9]{7}-[0-9]{1}$");
  return regex_match(cnic, pattern);
}

// Function to write employee data to a file in CSV format
void writeEmployeeData(Employee emp, string filename)
{
  ofstream file(filename, ios::app);
  if (!file.is_open())
  {
    cout << "Error opening file!" << endl;
    return;
  }

  // Write data in CSV format
  file << emp.id << "," << emp.name << "," << emp.Fathername << ","
       << emp.cnic << "," << emp.address << "," << emp.contact << ","
       << emp.designation << "," << emp.age << "," << emp.previousJob << ","
       << emp.Shift << "," << emp.behavior << "," << emp.Salary << endl;

  file.close();
  cout << "Employee data saved successfully!" << endl;
}

// Function to count peon
int countPeonsInCSV(const string &filename)
{
  ifstream file(filename);
  if (!file.is_open())
  {
    cerr << "Error opening file: " << filename << endl;
    return -1; // Indicate error
  }

  int countPeons = 0;
  string line;

  // Skip the header line (optional)
  getline(file, line); // Uncomment this line if your CSV file has a header

  while (getline(file, line))
  {
    stringstream ss(line);
    string designation;

    // Extract designation field (modify if different)
    Employee emp;
    getline(ss, line, ',');
    emp.id = stoi(line);
    getline(ss, emp.name, ',');
    getline(ss, emp.Fathername, ',');
    getline(ss, emp.cnic, ',');
    getline(ss, emp.address, ',');
    getline(ss, emp.contact, ',');
    getline(ss, emp.designation, ',');

    if (emp.designation == "Peon")
    {
      countPeons++;
    }
  }

  file.close();
  return countPeons;
}

// Function to count Gatekeeper
int countGatekeeperInCSV(const string &filename)
{
  ifstream file(filename);
  if (!file.is_open())
  {
    cerr << "Error opening file: " << filename << endl;
    return -1; // Indicate error
  }

  int countGatekeeper = 0;
  string line;

  // Skip the header line (optional)
  getline(file, line); // Uncomment this line if your CSV file has a header

  while (getline(file, line))
  {
    stringstream ss(line);
    string designation;

    // Extract designation field (modify if different)
    Employee emp;
    getline(ss, line, ',');
    emp.id = stoi(line);
    getline(ss, emp.name, ',');
    getline(ss, emp.Fathername, ',');
    getline(ss, emp.cnic, ',');
    getline(ss, emp.address, ',');
    getline(ss, emp.contact, ',');
    getline(ss, emp.designation, ',');

    if (emp.designation == "Gatekeeper")
    {
      countGatekeeper++;
    }
  }

  file.close();
  return countGatekeeper;
}
// function to count Pecuniary
int countPecuniaryInCSV(const string &filename)
{
  ifstream file(filename);
  if (!file.is_open())
  {
    cerr << "Error opening file: " << filename << endl;
    return -1; // Indicate error
  }

  int countPecuniary = 0;
  string line;

  // Skip the header line (optional)
  getline(file, line); // Uncomment this line if your CSV file has a header

  while (getline(file, line))
  {
    stringstream ss(line);
    string designation;

    // Extract designation field (modify if different)
    Employee emp;
    getline(ss, line, ',');
    emp.id = stoi(line);
    getline(ss, emp.name, ',');
    getline(ss, emp.Fathername, ',');
    getline(ss, emp.cnic, ',');
    getline(ss, emp.address, ',');
    getline(ss, emp.contact, ',');
    getline(ss, emp.designation, ',');

    if (emp.designation == "Pecuniary")
    {
      countPecuniary++;
    }
  }

  file.close();
  return countPecuniary;
}

// Function to search for employee data by ID
void searchEmployeeData(int id, string filename)
{
  ifstream file(filename);
  if (!file.is_open())
  {
    cout << "Error opening file!" << endl;
    return;
  }

  int searchId;
  string line;
  Employee emp;

  while (getline(file, line))
  {
    stringstream ss(line);

    // Extract employee ID from the first field
    getline(ss, line, ',');
    searchId = stoi(line);

    if (searchId == id)
    {
      // Read remaining data fields
      emp.id = id;
      getline(ss, emp.name, ',');
      getline(ss, emp.Fathername, ',');
      getline(ss, emp.cnic, ',');
      getline(ss, emp.address, ',');
      getline(ss, emp.contact, ',');
      getline(ss, emp.designation, ',');
      getline(ss, line, ',');
      emp.age = stoi(line);
      getline(ss, emp.previousJob, ',');
      getline(ss, emp.Shift, ',');
      getline(ss, emp.behavior, ',');
      getline(ss, line, ',');
      emp.Salary = stoi(line);

      cout << "Employee ID: " << emp.id << endl;

      cout << "Employee Name: " << emp.name << endl;

      cout << "Employee Father Name: " << emp.Fathername << endl;

      cout << "Employee CNIC: " << emp.cnic << endl;

      cout << "Employee Address: " << emp.address << endl;

      cout << "Employee Contact: " << emp.contact << endl;

      cout << "Employee Designation: " << emp.designation << endl;

      cout << "Employee Age: " << emp.age << endl;

      cout << "Previous Job: " << emp.previousJob << endl;

      cout << "Shift: " << emp.Shift << endl;

      cout << "Behavior: " << emp.behavior << endl;

      cout << "Salary: " << emp.Salary << endl;
      return;
    }
  }

  cout << "Employee with ID " << id << " not found!" << endl;
  file.close();
}
void searchEmployeefine(int id, string Fine)
{
  ifstream file(Fine);
  if (!file.is_open())
  {
    cout << "Error opening file!" << endl;
    return;
  }

  int searchId;
  string line;
  Employee emp;

  while (getline(file, line))
  {
    stringstream ss(line);

    // Extract employee ID from the first field
    getline(ss, line, ',');
    searchId = stoi(line);

    if (searchId == id)
    {
      // Read remaining data fields
      emp.id = id;
         getline(ss, line, ',');
      emp.fine = stoi(line);
      getline(ss, emp.reson, ',');
      
      cout << "Employee id:" << emp.id << endl;
      cout << "Employee Fine:" << emp.fine << endl ;
      cout << "Reson for fine:" << emp.reson << endl ;
      return;
    }
  }

  cout << "Employee with ID " << id << " not found!" << endl;
  file.close();
}

void checkEmployeeData(int id, string filename)
{
  ifstream file(filename);
  if (!file.is_open())
  {
    cout << "Error opening file!" << endl;
    return;
  }

  int searchId;
  string line;
  Employee emp;
  int c=0;

  while (getline(file, line))
  {
    stringstream ss(line);

    // Extract employee ID from the first field
    getline(ss, line, ',');
    searchId = stoi(line);
do{
 if (searchId == id)
    {
     cout << "This id already exiest. Please! Enter a new id."<< endl;
     cin >> id;
     c=0;
    }else{
      emp.id=id;
     c=1;
    }
 
}while(c==0);
    }
  file.close();
}

// Function to Update Employee Record
void UpdateEmployeeRecord(int id, string filename)
{
  // Find the employee record with the given ID
  bool foundEmployee = false;
  ifstream inputFile(filename);
  if (inputFile.is_open())
  {
    string line;
    Employee tempEmp;
    while (getline(inputFile, line))
    {
      string idstring = line; // Creat a copy of the line for id extraction
      stringstream ss(line);
      getline(ss, idstring, ','); // Extract ID
      int searchId = stoi(idstring);

      if (searchId == id)
      {
        // Read remaining data fields
        getline(ss, tempEmp.name, ',');
        getline(ss, tempEmp.Fathername, ',');
        getline(ss, tempEmp.cnic, ',');
        getline(ss, tempEmp.address, ',');
        getline(ss, tempEmp.contact, ',');
        getline(ss, tempEmp.designation, ',');
        getline(ss, line, ','); // Skip age
        tempEmp.age = stoi(line);
        getline(ss, tempEmp.previousJob, ',');
        getline(ss, tempEmp.Shift, ',');
        getline(ss, tempEmp.behavior, ',');
        getline(ss, line, ','); // Skip existing salary
        tempEmp.Salary = stod(line);
        foundEmployee = true;
        break;
      }
    }
    inputFile.close(); // close the orignal file

    if (foundEmployee)
    {
      // Prompt for new shift
      cout << "Current Shift: " << tempEmp.Shift << endl;
      bool isAlphabetic;
      do
      {
        isAlphabetic = true;
        cout << "Enter Employee Shift: ";
        cin >> tempEmp.Shift;

        if (cin.fail())
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input. Please enter a valid string." << endl;
        }
        else
        {
          for (char c : tempEmp.Shift)
          {
            if (!isalpha(c))
            {
              isAlphabetic = false;
              break;
            }
          }

          if (!isAlphabetic)
          {
            cout << "Invalid input. Please enter a string containing only alphabetic characters." << endl;
          }
        }

      } while (tempEmp.Shift.empty() || !isAlphabetic);

      // Prompt for new Behaviour
      cout << "Current Behavior: " << tempEmp.behavior << endl;
      do
      {
        cout << "Enter New Behavior: ";
        cin >> tempEmp.behavior;

        if (cin.fail())
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input. Please enter a valid string." << std::endl;
        }

      } while (tempEmp.behavior.empty());

      // Prompt for new salary
      cout << "Current Salary: " << tempEmp.Salary << endl;
      do
      {
        cout << "Enter new Salary: ";
        cin >> tempEmp.Salary;

        // Check for input failure (e.g., entering non-numeric characters)
        if (cin.fail())
        {
          cout << "Invalid input. Please enter a valid number for salary." << endl;
          cin.clear();                                         // Clear the error state from the input stream
          cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
      } while (cin.fail());

      // Update the employee record in a temporary file
      ofstream tempFile("temp_data.csv");
      if (tempFile.is_open())
      {
        inputFile.open(filename);
        if (inputFile.is_open())
        {
          while (getline(inputFile, line))
          {
            string idstring = line;
            stringstream ss(line);
            getline(ss, idstring, ','); // Extract ID
            idstring.erase(0, idstring.find_first_not_of("\t\n"));
            int searchId = stoi(idstring);

            if (searchId == id)
            {
              // Write updated data for the employee
              tempFile << searchId << "," << tempEmp.name << "," << tempEmp.Fathername << ","
                       << tempEmp.cnic << "," << tempEmp.address << "," << tempEmp.contact << ","
                       << tempEmp.designation << "," << tempEmp.age << "," << tempEmp.previousJob << ","
                       << tempEmp.Shift << "," << tempEmp.behavior << "," << tempEmp.Salary << endl;
            }
            else
            {
              // Write original data for other employees
              tempFile << line << endl;
            }
          }
        }
        inputFile.close();
        tempFile.close();

        // Remove the original file and rename the temporary file
        remove(filename.c_str());
        rename("temp_data.csv", filename.c_str());

        cout << "Employee data updated successfully!" << endl;
      }
      else
      {
        cout << "Error creating temporary file!" << endl;
      }
    }
    else
    {
      cout << "Employee with ID " << id << " not found!" << endl;
    }
  }
  else
  {
    cout << "Error opening file!" << endl;
  }
}

// Function to delete employee data by ID (improved efficiency)
void deleteEmployeeData(int id, string filename)
{
  ifstream inputFile(filename);
  if (!inputFile.is_open())
  {
    cout << "Error opening file!" << endl;
    return;
  }

  ofstream outputFile("temp_data.csv"); // Create a temporary file
  if (!outputFile.is_open())
  {
    cout << "Error creating temporary file!" << endl;
    inputFile.close();
    return;
  }

  string line;
  int searchId;

  while (getline(inputFile, line))
  {
    stringstream ss(line);
    getline(ss, line, ',');
    searchId = stoi(line);

    if (searchId != id)
    {
      outputFile << line << endl; // Write all lines except the one with the target ID
    }
  }

  inputFile.close();
  outputFile.close();

  // Remove the original file and rename the temporary file
  remove(filename.c_str());
  rename("temp_data.csv", filename.c_str());

  cout << "Employee with ID " << id << " deleted successfully!" << endl;
}
// Function to delete employee Leave by ID (improved efficiency)
void deleteEmployeeData(string Leave, int id)
{
  ifstream inputFile(Leave);
  if (!inputFile.is_open())
  {
    cout << "Error opening file!" << endl;
    return;
  }

  ofstream outputFile("temp_data.csv"); // Create a temporary file
  if (!outputFile.is_open())
  {
    cout << "Error creating temporary file!" << endl;
    inputFile.close();
    return;
  }

  string line;
  int searchId;

  while (getline(inputFile, line))
  {
    stringstream ss(line);
    getline(ss, line, ',');
    searchId = stoi(line);

    if (searchId != id)
    {
      outputFile << line << endl; // Write all lines except the one with the target ID
    }
  }

  inputFile.close();
  outputFile.close();

  // Remove the original file and rename the temporary file
  remove(Leave.c_str());
  rename("temp_data.csv", Leave.c_str());

  cout << "Employee Leave with ID " << id << " deleted successfully!" << endl;
}
// Function to delete employee Fine by ID (improved efficiency)
void deleteEmployeeFine(int id, string Fine)
{
  ifstream inputFile(Fine);
  if (!inputFile.is_open())
  {
    cout << "Error opening file!" << endl;
    return;
  }

  ofstream outputFile("temp_data.csv"); // Create a temporary file
  if (!outputFile.is_open())
  {
    cout << "Error creating temporary file!" << endl;
    inputFile.close();
    return;
  }

  string line;
  int searchId;

  while (getline(inputFile, line))
  {
    stringstream ss(line);
    getline(ss, line, ',');
    searchId = stoi(line);

    if (searchId != id)
    {
      outputFile << line << endl; // Write all lines except the one with the target ID
    }
  }

  inputFile.close();
  outputFile.close();

  // Remove the original file and rename the temporary file
  remove(Fine.c_str());
  rename("temp_data.csv", Fine.c_str());

  cout << "Employee Fine with ID " << id << " deleted successfully!" << endl;
}

// Mark leave
void writeEmployeeData(string Leave, Employee emp)
{
  ofstream file(Leave, ios::app);
  if (!file.is_open())
  {
    cout << "Error opening file!" << endl;
    return;
  }

  file << emp.id << "," << emp.reson << "," << emp.days << "," << emp.date << endl;

  file.close();
  cout << "Leave is Send successfully!" << endl;
}

// New

// Mark attendence
void WriteEmployeeAttendence(Employee emp, string Attendence)
{
  ofstream file(Attendence, ios::app);
  if (!file.is_open())
  {
    cout << "Error opening file!" << endl;
    return;
  }

  // Get the current time
  auto now = chrono::system_clock::now();
  auto timeNow = chrono::system_clock::to_time_t(now);

  // Convert the current time to a string
  std::tm *currentLocalTime = localtime(&timeNow);
  std::stringstream ss;
  ss << std::put_time(currentLocalTime, "%Y-%m-%d");
  std::string currentDate = ss.str();

  emp.date = currentDate;

  file << emp.id << "," << emp.attendence << "," << emp.date << endl;

  file.close();
}

// Function to search for ID for mark attendence
void MarkEmployeeAttendence(int id, string filename, string Leave)
{
  ifstream file(filename);
  if (!file.is_open())
  {
    cout << "Error opening file!" << endl;
    return;
  }

  int searchId;
  string line;
  Employee emp;
  bool findId;

  while (getline(file, line))
  {
    stringstream ss(line);

    // Extract employee ID from the first field
    getline(ss, line, ',');
    searchId = stoi(line);

    // cout<<id<<endl;

    if (searchId == id)
    {
      ifstream file(Leave);
      if (!file.is_open())
      {
        cout << "Error opening file!" << endl;
        return;
      }

      int searchId;
      string line;
      Employee emp;
      emp.id = id;

      while (getline(file, line))
      {
        stringstream ss(line);

        // Extract employee ID from the first field
        getline(ss, line, ',');
        searchId = stoi(line);

        if (searchId == id)
        {
          getline(ss, line, ',');
          if (isCurrentDate(line))
          {
            // Read remaining data fields
            cout << "Employ on leave \n";
            getline(ss, emp.reson, ',');
            getline(ss, line, ',');
            emp.days = stoi(line);
            getline(ss, emp.date, ',');

            cout << "Employee ID: " << emp.id << endl;
            cout << "Leave Reson: " << emp.reson << endl;
            cout << "Leave Days: " << emp.days << endl;
            cout << "Leave Date: " << emp.date << endl;
            int x;
            cout << "1.Accept\n2.Reject" << endl;
            cin >> x;
            if (x == 1)
            {
              emp.attendence = "Leave";
              string Attendence = "Attendence.csv";
              WriteEmployeeAttendence(emp, Attendence);
            }
            else if (x == 2)
            {
              string Attendence = "Attendence.csv";
              int x = 0;
              while (x == 0)
              {
                cout << "Mark Attendence Present (P) and Absent (A) \n";
                string attendence;
                cin >> attendence;
                if (attendence == "P" || attendence == "A")
                {
                  emp.attendence = attendence;
                  WriteEmployeeAttendence(emp, Attendence);
                  x = 1;
                }
                else
                {
                  cout << "You use wrong sign. \n Please! Use Right Sign (P) for Present and (A) for Absent \n";
                }
              }
            }
          }
          else
          {
            string Attendence = "Attendence.csv";
            int x = 0;
            while (x == 0)
            {
              cout << "Mark Attendence Present (P) and Absent (A) \n";
              string attendence;
              cin >> attendence;
              if (attendence == "P" || attendence == "A")
              {
                emp.attendence = attendence;
                WriteEmployeeAttendence(emp, Attendence);
                x = 1;
                findId = true;
              }
              else
              {
                cout << "You use wrong sign. \n Please! Use Right Sign (P) for Present and (A) for Absent \n";
              }
            }
          }

          return;
        }
        else
        {
          string Attendence = "Attendence.csv";
          int x = 0;
          while (x == 0)
          {
            cout << "Mark Attendence Present (P) and Absent (A) \n";
            string attendence;
            cin >> attendence;
            if (attendence == "P" || attendence == "A")
            {
              emp.attendence = attendence;
              WriteEmployeeAttendence(emp, Attendence);
              x = 1;
              findId = true;
            }
            else
            {
              cout << "You use wrong sign. \n Please! Use Right Sign (P) for Present and (A) for Absent \n";
            }
          }
        }
      }
      file.close();
      findId = true;
    }
    else
    {
      // cout << "Employee with ID " << id << " not found!" << endl;
      findId = false;
    }
  }
  file.close();
  if (!findId)
  {
    cout << "Employee with ID " << id << " not found!" << endl;
  }
  else
  {
    cout << "Attendance Marked Successfully" << endl;
  }
}

// Fine box
void writeEmployeeFine(Employee emp, string Fine)
{
  ofstream file(Fine, ios::app);
  if (!file.is_open())
  {
    cout << "Error opening file!" << endl;
    return;
  }

  file << emp.id << "," << emp.fine << "," << emp.reson << endl;

  file.close();
  cout << "Employee data saved successfully!" << endl;
}

// MAIN

int main()
{
  string Fine = "fine_record.csv";
  string filename = "employee_data.csv";
  string Attendence = "Attendence.csv";
  string Leave = "Leave.csv";
  int choice, id, Des;
  bool hasLowercase;
  bool isAlphabetic;
  Employee emp;
  int z = 0;
  int x = 0;
  bool allCaps = false;
  bool isNumber = false;
  string start;
  cout << "Enter Start to start Program." << endl;
  while (x == 0)
  {
    cin >> start;
    if (start == "start")
    {
      cout << "\n \t \t Welcome to Employee Record System\n";
      x = 1;
    }
    else
    {
      cout<< "Please Enter start to start program."<< endl;
      x = 0;
    }
  }
  do
  {
    cout << "\n1. Add Employee             2. Delete Employee Record  3. Employee Attendence \n";
    cout << "4. Serch Employee Record    5. Letter Box              6. Fine Box \n";
    cout << "7. Update Shift and Salary  8. Exit \n ";
    cout << "\n Enter your choice: ";
    cin >> choice;

    switch (choice)
    {

    case 1:

      cout << "\t Enter Employee Details \n";
      do
      {
        // for input Designation
        cout << "Select one designation from list. \n 1.Peon \n 2.Gatekeeper \n 3.Pecuniary \n";
        cout << "Designation: ";
        cin >> Des;
        switch (Des)
        {
        case 1:
          emp.designation = "Peon";
          break;
        case 2:
          emp.designation = "Gatekeeper";
          break;
        case 3:
          emp.designation = "Pecuniary";
          break;
        default:
          cout << "Invalid choice!" << endl;
        }
      } while (Des >= 4);

      // for input employee ID

      id = getIntegerInput("Enter Employee ID");
      checkEmployeeData(id, filename);
      // for input name in casesenstive

      do
      {
        cout << "Enter Employee Name (in UPPERCASE): ";
        cin >> emp.name;

        allCaps = true;
        for (char c : emp.name)
        {
          if (!isupper(c))
          {
            allCaps = false;
            cout << "Please enter Employee Name in ALL CAPS." << std::endl;
            break;
          }
        }

      } while (!allCaps);

      // for input Fathername in casesenstive

      do
      {
        cout << "Enter Employee Father Name (in UPPERCASE): ";
        cin >> emp.Fathername;

        allCaps = true;
        for (char c : emp.Fathername)
        {
          if (!isupper(c))
          {
            allCaps = false;
            cout << "Please enter Employee Father Name in ALL CAPS." << std::endl;
            break;
          }
        }

      } while (!allCaps);

      // For input Cnic in valid format
      do
      {
        cout << "Enter your CNIC ID in the format XXXXX-XXXXXXX-X:";
        cin >> emp.cnic;
        if (!validateCNIC(emp.cnic))
        {
          cout << "Invalid CNIC format. Please try again." << endl;
        }
      } while (!validateCNIC(emp.cnic));
      // for input address
      cout << "Address: ";
      cin >> emp.address;

      // for input contact

      do
      {
        cout << "Enter your contact number: ";
        cin >> emp.contact;
        isNumber = true;
        for (char c : emp.contact)
        {
          if (!isdigit(c))
          {
            isNumber = false;
            cout << "Invalid input. Please enter only numeric digits." <<endl;
            break;
          }
        }

      } while (!isNumber);

      // for input age between 18 to 60 year.
      do
      {
        cout << "The Employee is eligible which have age Between 18 to 60 year. \n";
        cout << "Age:";
        cin >> emp.age;
      } while (!(emp.age > 18 && emp.age < 60));
      // for input previous job of employee

      do
      {
        isAlphabetic = true;
        cout << "Enter Employee previous job: ";
        cin >> emp.previousJob;

        if (cin.fail())
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input. Please enter a valid string." << endl;
        }
        else
        {
          for (char c : emp.previousJob)
          {
            if (!isalpha(c))
            {
              isAlphabetic = false;
              break;
            }
          }

          if (!isAlphabetic)
          {
            cout << "Invalid input. Please enter a string containing only alphabetic characters." << endl;
          }
        }

      } while (emp.previousJob.empty() || !isAlphabetic);

      // for input job shift of employee
      do
      {
        isAlphabetic = true;
        cout << "Enter Employee Shift: ";
        cin >> emp.Shift;

        if (cin.fail())
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input. Please enter a valid string." << endl;
        }
        else
        {
          for (char c : emp.Shift)
          {
            if (!isalpha(c))
            {
              isAlphabetic = false;
              break;
            }
          }

          if (!isAlphabetic)
          {
            cout << "Invalid input. Please enter a string containing only alphabetic characters." << endl;
          }
        }

      } while (emp.Shift.empty() || !isAlphabetic);

      // for selection of reject and accept
      z = 0;
      while (z == 0)
      {
        int y;
        cout << "Select one option \n 1.Ok \n 2.Cancel \n";
        cin >> y;
        if (y == 1)
        {
          cout << "Congratulations! Now this person is a Employee of our department. \n";
          // input employee behavior
          emp.behavior = "New Employee";
          // input employee salary
          do
          {
            cout << "Enter Employee Salary: ";
            cin >> emp.Salary;
            isNumber = true;
            for (char c : emp.Salary)
            {
              if (!isdigit(c))
              {
                isNumber = false;
                cout << "Invalid input. Please enter only numeric digits for Salary." << std::endl;
                break;
              }
            }

          } while (!isNumber);

          writeEmployeeData(emp, filename);
          z = 1;
        }
        else if (y == 2)
        {
          cout << "Sorry!";
          z = 1;
        }
        else
        {
          cout << "Selection is Wrong!";
        }
      }
      break;

    case 2:

      int c;
      cout << "Select one option \n 1.Delete Employee record \n 2.Delete Employee Leaves \n 3.Delete Employee Fine";
      cin >> c;
      id = getIntegerInput("Enter Employee ID to Delete Record");
      switch (c)
      {
      case 1:
        deleteEmployeeData(id, filename);
        deleteEmployeeFine(id, Fine);
        deleteEmployeeData(Leave, id);
        break;
      case 2:
        deleteEmployeeData(Leave, id);
        break;
      case 3:
        deleteEmployeeFine(id, Fine);
        break;
      }
      break;

    case 3:

      id = getIntegerInput("Enter Employee ID to Mark Attendence");
      MarkEmployeeAttendence(id, filename, Leave);
      break;

    case 4:

      int r;
      cout << "\n Select one option\n \n 1.Check Number of Peon. \t 2.Check Number of Gate Keeper. \n3.Check Number of Pecuniary. \t 4.Check Record of an Employee \n 5.Check Fine of an Employee. \t 6.Check Number of Total Employee's. \n";
      cout << "\n Enter your choice: ";
      cin >> r;
      if (r == 1)
      {
        int numPeons = countPeonsInCSV(filename);

        if (numPeons != -1)
        {
          cout << "Number of Peons in " << filename << ": " << numPeons << endl;
        }
        else
        {
          cerr << "Error counting peons." << endl;
        }
      }
      else if (r == 2)
      {

        int numGatekeeper = countGatekeeperInCSV(filename);

        if (numGatekeeper != -1)
        {
          cout << "Number of Gatekeeper in " << filename << ": " << numGatekeeper << endl;
        }
        else
        {
          cerr << "Error counting Gatekeeper." << endl;
        }
      }
      else if (r == 3)
      {

        int numPecuniary = countPecuniaryInCSV(filename);

        if (numPecuniary != -1)
        {
          cout << "Number of Pecuniary in " << filename << ": " << numPecuniary << endl;
        }
        else
        {
          cerr << "Error counting Pecuniary." << endl;
        }
      }
      else if (r == 4)
      {
        id = getIntegerInput("Enter Employee ID to Search Record");
        searchEmployeeData(id, filename);
      }else if(r==5){
        id = getIntegerInput("Enter Employee ID to Search Record");
        searchEmployeefine(id, Fine);
      }
      else if (r == 6)
      {

        int numPeons = countPeonsInCSV(filename);
        int numPecuniary = countPecuniaryInCSV(filename);
        int numGatekeeper = countGatekeeperInCSV(filename);
        int numEmployee = numPeons + numPecuniary + numGatekeeper;
        if (numEmployee != -1)
        {
          cout << "Number of Employee's in " << filename << ": " << numEmployee << endl;
        }
        else
        {
          cerr << "Error counting Employee's." << endl;
        }
      }
      break;

    case 5:

      cout << "\nEnter Detail For leave \n: ";
      id = getIntegerInput("Enter Employee ID For Leave");
      // fpr enter reson of leave
      do
      {
        cout << "Enter Employee Reson: ";
        cin >> emp.reson;

        if (cin.fail())
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input. Please enter a valid string." << std::endl;
        }

      } while (emp.reson.empty());
      // for enter the days of leave
      emp.days = getIntegerInput("Enter day's of Leave");
      // For input date in valid format
      do
      {
        cout << "Enter Date of Leave in the format DD-MM-YYYY \n D=Day M=Month Y=Year:";
        cin >> emp.date;
        if (!validateDATE(emp.date))
        {
          cout << "Invalid Date Format. Please try again." << endl;
        }
      } while (!validateDATE(emp.date));
      // call funtion to write data on leave file
      writeEmployeeData(Leave, emp);
      break;

    case 6:

      emp.id = getIntegerInput("Enter Employee ID For Fine");
      // for enter fine
      emp.fine = getIntegerInput("Enter Fine amount");
      // for enter reson for fine
      do
      {
        cout << "Enter Reson For Fine: ";
        cin >> emp.reson;
        if (cin.fail())
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input. Please enter a valid string." << std::endl;
        }
      } while (emp.reson.empty());
      // Call funtion to write data on fine file
      writeEmployeeFine(emp, Fine);
      break;

    case 7:

      id = getIntegerInput("Enter Employee ID to Update Shift, Salary and Behaviour");
      UpdateEmployeeRecord(id, filename);
      break;

    case 8:

      cout << "Exiting program..." << endl;
      break;
    default:
      cout << "Invalid choice!" << endl;
    }
  } while (choice != 8);

  return 0;
}
