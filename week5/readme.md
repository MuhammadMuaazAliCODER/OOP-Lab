# Student Record System — C++

A simple digital student record system built in C++ for a college registrar's office.  
It replaces a paper-based process by storing and managing student profiles in memory using Object-Oriented Programming concepts.

---

## Features

| Feature | How it works |
|---|---|
| Getters & Setters | Controlled access to `name`, `rollNumber`, `gpa` |
| `const` members | `rollNumber` and `admissionYear` can never change after creation |
| Static counter | `totalStudents` tracks how many students are registered at any time |
| Utility methods | `calculateGrade()`, `isHonor()`, `displayInfo()` |
| Const reference | Free function `printStudentSummary()` receives objects safely |
| Input validation | Setters reject invalid GPA (outside 0–4) and empty names |

---

## Files

```
student_record.cpp   ← entire program (single file)
README.md            ← this file
```

---

## How to Compile & Run

You need a C++ compiler (g++ recommended).

```bash
# Compile
g++ -o student_record student_record.cpp

# Run
./student_record
```

On Windows (with MinGW):
```bash
g++ -o student_record.exe student_record.cpp
student_record.exe
```

---

## Concepts Used — Plain English Explanation

### 1. Class & Object
A **class** is a blueprint. An **object** is a real thing made from that blueprint.

```cpp
class Student { ... };      // blueprint

Student s1(1001, 2022, "Alice", 3.9);  // real student object
```

---

### 2. Getters and Setters (Accessor Functions)
Instead of making data public (anyone can change it), we keep it `private` and provide controlled access.

- **Getter** → reads the value (safe, no side effects)
- **Setter** → writes the value (can validate before accepting)

```cpp
// Getter
string getName() const { return name; }

// Setter with validation
void setGpa(double newGpa) {
    if (newGpa >= 0.0 && newGpa <= 4.0)
        gpa = newGpa;
    else
        cout << "Error: GPA must be between 0.0 and 4.0.\n";
}
```

`rollNumber` has **no setter** — it's protected from ever being changed.

---

### 3. `const` Members (Set Once, Never Change)
`rollNumber` and `admissionYear` are declared as `const`.  
This means they **must** be set in the constructor and can never be modified later.

```cpp
const int rollNumber;      // declared const
const int admissionYear;

// Must be initialized in the constructor initializer list:
Student(int roll, int year, ...)
    : rollNumber(roll), admissionYear(year)  // set here, locked forever
```

If you try to write `s1.rollNumber = 999;` anywhere, the compiler will give an error.

---

### 4. Static Member — `totalStudents`
A `static` member belongs to the **class itself**, not to any individual object.  
All objects share the same copy.

```cpp
static int totalStudents;   // declared inside class
int Student::totalStudents = 0;  // defined outside class (required)
```

- Constructor does `totalStudents++` → count goes up when a student is created.
- Destructor does `totalStudents--` → count goes down when a student is destroyed.
- You can check it any time with `Student::getTotalStudents()` — no object needed.

---

### 5. Utility Methods

#### `calculateGrade()`
Converts the numeric GPA into a letter grade (A, B, C, D, F).

```
GPA >= 3.7  →  A
GPA >= 3.3  →  A-
GPA >= 3.0  →  B+
GPA >= 2.7  →  B
GPA >= 2.3  →  B-
GPA >= 2.0  →  C
GPA >= 1.0  →  D
below 1.0   →  F
```

#### `isHonor()`
Returns `true` if GPA is 3.5 or above (qualifies for the Honor Roll).

```cpp
bool isHonor() const { return gpa >= 3.5; }
```

#### `displayInfo()`
Prints all student details in a neat formatted block.

---

### 6. `const` Reference Parameters
When passing an object to a function, using `const Student& s` means:
- **No copy is made** (efficient).
- **The original object cannot be modified** inside the function (safe).

```cpp
void printStudentSummary(const Student& s) {
    cout << s.getName() << ...;
    // s.setName("X");  ← compile error! const reference is read-only
}
```

---

## Sample Output

```
========== College Student Record System ==========

Total students registered: 4

=== Full Student Records ===
-------------------------------------
  Name          : Alice Johnson
  Roll Number   : 1001
  Admission Year: 2022
  GPA           : 3.9
  Grade         : A
  Honor Roll    : Yes
-------------------------------------
-------------------------------------
  Name          : Bob Smith
  Roll Number   : 1002
  Admission Year: 2023
  GPA           : 2.8
  Grade         : B
  Honor Roll    : No
-------------------------------------
...

=== Updating Bob's record ===
  Name          : Robert Smith
  GPA           : 3.6
  Grade         : A-
  Honor Roll    : Yes

=== Testing invalid inputs ===
Error: GPA must be between 0.0 and 4.0.
Error: Name cannot be empty.
```

---

## Class Structure at a Glance

```
Student
│
├── Private Data
│   ├── const int rollNumber       ← never changes
│   ├── const int admissionYear    ← never changes
│   ├── string name
│   ├── double gpa
│   └── static int totalStudents   ← shared by all objects
│
├── Constructor  →  sets const members, increments totalStudents
├── Destructor   →  decrements totalStudents
│
├── Getters:  getRollNumber(), getAdmissionYear(), getName(), getGpa()
├── Setters:  setName(), setGpa()  (with validation; no setter for roll/year)
│
├── Utility Methods
│   ├── calculateGrade()  →  returns letter grade string
│   ├── isHonor()         →  returns true/false
│   └── displayInfo()     →  prints full profile
│
└── Static Method
    └── getTotalStudents()  →  returns current student count
```