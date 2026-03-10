#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    const int    rollNumber;
    const int    admissionYear;
    string name;
    double gpa;
    static int totalStudents;

public:
    
    Student(int roll, int year, const string& studentName, double studentGpa)
        : rollNumber(roll), admissionYear(year)   
    {
        name = studentName;
        gpa  = studentGpa;
        totalStudents++;  
    }

    
    ~Student() {
        totalStudents--;   
    }

   
    int getRollNumber()    const { return rollNumber;    }
    int getAdmissionYear() const { return admissionYear; }
    string getName()       const { return name;          }
    double getGpa()        const { return gpa;           }

    
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

    bool isHonor() const {
        return gpa >= 3.5;
    }
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

 
    static int getTotalStudents() {
        return totalStudents;
    }
};

int Student::totalStudents = 0;

void printStudentSummary(const Student& s) {
    cout << "Summary -> " << s.getName()
         << "  |  Roll: " << s.getRollNumber()
         << "  |  GPA: "  << s.getGpa()
         << "  |  Grade: "<< s.calculateGrade()
         << "\n";
}


int main() {
    cout << "========== College Student Record System ==========\n\n";

   
    Student s1(1001, 2022, "Alice Johnson",  3.9);
    Student s2(1002, 2023, "Bob Smith",      2.8);
    Student s3(1003, 2022, "Carol Martinez", 3.5);
    Student s4(1004, 2024, "David Lee",      1.6);

    cout << "Total students registered: " << Student::getTotalStudents() << "\n\n";

    
    cout << "=== Full Student Records ===\n";
    s1.displayInfo();
    s2.displayInfo();
    s3.displayInfo();
    s4.displayInfo();

    
    cout << "\n=== Quick Summaries ===\n";
    printStudentSummary(s1);
    printStudentSummary(s2);
    printStudentSummary(s3);
    printStudentSummary(s4);

   
    cout << "\n=== Updating Bob's record ===\n";
    s2.setName("Robert Smith");
    s2.setGpa(3.6);
    s2.displayInfo();

    
    // cout << "=== Testing invalid inputs ===\n";
    // s3.setGpa(5.0);  
    // s3.setName("");  


    cout << "\nFinal total students: " << Student::getTotalStudents() << "\n";
    cout << "\n====================================================\n";

    return 0;
}