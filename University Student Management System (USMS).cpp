#include <iostream>
#include <string>
#include <exception>
#include <vector>
using namespace std;
class studentException : public exception {
public:
    virtual const char* what() const noexcept {
        return "Student Exception";
    }
};
class negativefeesException : public studentException {
public:
    const char* what() const noexcept override {
        return "Error: Fees cannot be negative";
    }
};
class invalidrollnoException : public studentException {
public:
    const char* what() const noexcept override {
        return "Error: Invalid Roll Number";
    }
};
class University {
protected:
    string universityname;
    string location;
    static int totalstudent;
public:
    University(string un, string l) {
        universityname = un;
        location = l;
        cout << "University Information Added: "
             << universityname << endl;
    }
    ~University() {
        cout << "University Information Destroyed: "
             << universityname << endl;
    }
    string getuniversityname() {
        return universityname;
    }
    string getlocation() {
        return location;
    }
    static void increasecount() {
        totalstudent++;
    }
    static int gettotalstudent() {
        return totalstudent;
    }
};
int University::totalstudent = 0;
class Student : public University {
private:
    string studentname;
    int rollno;
    double fees;
public:
    Student(string un, string l, string sn, int rn, double f): University(un, l) {
        studentname = sn;
        setrollno(rn);
        setfees(f);

        University::increasecount();

        cout << "Student Information Added: "
             << studentname << endl;
    }
    ~Student() {
        cout << "Student Information Removed: "
             << studentname << endl;
    }
    string getstudentname() {
        return studentname;
    }
    void setrollno(int r) {
        if (r <= 0) {
            throw invalidrollnoException();
        }
        rollno = r;
    }
    int getrollno() {
        return rollno;
    }
    void setfees(double f) {
        if (f < 0) {
            throw negativefeesException();
        }
        fees = f;
    }
    double getfees() {
        return fees;
    }
    void displaystudent();
};
void Student::displaystudent() {
    cout << "\nUniversity Name: "<<getuniversityname() << endl;
    cout << "University Location: "<<getlocation() << endl;
    cout << "Student Name: "<<getstudentname() << endl;
    cout << "Student Roll No: "<<getrollno() << endl;
    cout << "Student Fees: "<<getfees() << endl;
}
int main() {
    vector<Student> s;
    string un, l, sn;
    int rn;
    double f;
    for (int i = 0; i < 3; i++) {
        cout << "\nEnter University Name: ";
        getline(cin, un);
        cout << "Enter Location: ";
        getline(cin, l);
        cout << "Enter Student Name: ";
        getline(cin, sn);
        cout << "Enter Roll Number: ";
        cin >> rn;
        cout << "Enter Fees: ";
        cin >> f;
        cin.ignore();
        try {
            s.emplace_back(un, l, sn, rn, f);
            cout << "Student Added Successfully!" << endl;
        }
        catch (studentException& e) {
            cout << e.what() << endl;
        }
    }
    cout << "\n========== STUDENT RECORDS ==========\n";
    for (int i = 0; i < s.size(); i++) {
        s[i].displaystudent();
    }
    cout << "\nTotal Students: "
         << University::gettotalstudent() << endl;
    return 0;
}

