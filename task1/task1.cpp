#include <iostream>
#include <string>
using namespace std;

// ============================================================
//  Student Class
// ============================================================
class Student {
private:
    // --- const members: set once in constructor, never change ---
    const int    rollNumber;
    const int    admissionYear;

    // --- regular members ---
    string name;
    double gpa;

    // --- static member: shared across ALL Student objects ---
    static int totalStudents;

public:
    // --------------------------------------------------------
    //  Constructor
    // --------------------------------------------------------
    Student(int roll, int year, const string& studentName, double studentGpa)
        : rollNumber(roll), admissionYear(year)   // const members must be set here
    {
        name = studentName;
        gpa  = studentGpa;
        totalStudents++;   // increment count every time a student is created
    }

    // --------------------------------------------------------
    //  Destructor
    // --------------------------------------------------------
    ~Student() {
        totalStudents--;   // decrement count when a student object is destroyed
    }

    // --------------------------------------------------------
    //  Getters  (accessors)
    // --------------------------------------------------------
    int getRollNumber()    const { return rollNumber;    }
    int getAdmissionYear() const { return admissionYear; }
    string getName()       const { return name;          }
    double getGpa()        const { return gpa;           }

    // --------------------------------------------------------
    //  Setters  (mutators) — roll number & year have NO setter
    // --------------------------------------------------------
    void setName(const string& newName) {
        if (!newName.empty()) {
            name = newName;
        } else {
            cout << "Error: Name cannot be empty.\n";
        }
    }

    void setGpa(double newGpa) {
        if (newGpa >= 0.0 && newGpa <= 4.0) {
            gpa = newGpa;
        } else {
            cout << "Error: GPA must be between 0.0 and 4.0.\n";
        }
    }

    // --------------------------------------------------------
    //  Utility Method 1 — calculateGrade()
    //  Returns letter grade based on GPA
    // --------------------------------------------------------
    string calculateGrade() const {
        if      (gpa >= 3.7) return "A";
        else if (gpa >= 3.3) return "A-";
        else if (gpa >= 3.0) return "B+";
        else if (gpa >= 2.7) return "B";
        else if (gpa >= 2.3) return "B-";
        else if (gpa >= 2.0) return "C";
        else if (gpa >= 1.0) return "D";
        else                 return "F";
    }

    // --------------------------------------------------------
    //  Utility Method 2 — isHonor()
    //  Returns true if student qualifies for Honor Roll (GPA >= 3.5)
    // --------------------------------------------------------
    bool isHonor() const {
        return gpa >= 3.5;
    }

    // --------------------------------------------------------
    //  Utility Method 3 — displayInfo()
    //  Accepts a const reference so the original object is safe
    // --------------------------------------------------------
    void displayInfo() const {
        cout << "-------------------------------------\n";
        cout << "  Name          : " << name          << "\n";
        cout << "  Roll Number   : " << rollNumber    << "\n";
        cout << "  Admission Year: " << admissionYear << "\n";
        cout << "  GPA           : " << gpa           << "\n";
        cout << "  Grade         : " << calculateGrade() << "\n";
        cout << "  Honor Roll    : " << (isHonor() ? "Yes" : "No") << "\n";
        cout << "-------------------------------------\n";
    }

    // --------------------------------------------------------
    //  Static method — getTotalStudents()
    //  Can be called without any object
    // --------------------------------------------------------
    static int getTotalStudents() {
        return totalStudents;
    }
};

// ============================================================
//  Define static member OUTSIDE the class
// ============================================================
int Student::totalStudents = 0;

// ============================================================
//  Free function — printStudentSummary()
//  Demonstrates passing Student by const reference
// ============================================================
void printStudentSummary(const Student& s) {
    cout << "Summary -> " << s.getName()
         << "  |  Roll: " << s.getRollNumber()
         << "  |  GPA: "  << s.getGpa()
         << "  |  Grade: "<< s.calculateGrade()
         << "\n";
}

// ============================================================
//  main — Test the system
// ============================================================
int main() {
    cout << "========== College Student Record System ==========\n\n";

    // Create student objects
    Student s1(1001, 2022, "Alice Johnson",  3.9);
    Student s2(1002, 2023, "Bob Smith",      2.8);
    Student s3(1003, 2022, "Carol Martinez", 3.5);
    Student s4(1004, 2024, "David Lee",      1.6);

    cout << "Total students registered: " << Student::getTotalStudents() << "\n\n";

    // Display full info for each student
    cout << "=== Full Student Records ===\n";
    s1.displayInfo();
    s2.displayInfo();
    s3.displayInfo();
    s4.displayInfo();

    // Use the free function (passes by const reference)
    cout << "\n=== Quick Summaries ===\n";
    printStudentSummary(s1);
    printStudentSummary(s2);
    printStudentSummary(s3);
    printStudentSummary(s4);

    // Demonstrate setter — update name and GPA
    cout << "\n=== Updating Bob's record ===\n";
    s2.setName("Robert Smith");
    s2.setGpa(3.6);
    s2.displayInfo();

    // Demonstrate invalid setter calls
    cout << "=== Testing invalid inputs ===\n";
    s3.setGpa(5.0);   // invalid: above 4.0
    s3.setName("");   // invalid: empty name

    // Roll number cannot be changed — it's const (no setter exists)
    // s1.setRollNumber(9999);  <-- this line would cause a compile error

    cout << "\nFinal total students: " << Student::getTotalStudents() << "\n";
    cout << "\n====================================================\n";

    return 0;
}