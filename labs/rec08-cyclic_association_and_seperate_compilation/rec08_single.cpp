/*
  rec08_start.cpp
  Starter Code for required functionality

  Yes, of course, you may add other methods.

  And no, this won't compile. You have to fix the cyclic association
  and implement the methods.

 */

#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Course;
class Student;
class Registrar;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
    friend ostream& operator<<(ostream& os, const Registrar& rhs);

public:
    // Course methods needed by Registrar
    explicit Course(const string& courseName);

    const string& getName() const {
        return name;
    }

    bool addStudent(Student* new_student) {
        students.push_back(new_student);
        return true;
    }

    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse(Student* student) {
        for (size_t i = 0; i < students.size(); i++) {
            if (student == students[i]) {
                students[i]->removedFromCourse(this);
                students[i] = nullptr;
                students.erase(students.begin() + i);

            }
        }
    }

private:
    string name;
    vector<Student*> students;
}; // Course

class Student {
    friend ostream& operator<<(ostream& os, const Course& rhs);
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
    friend ostream& operator<<(ostream& os, const Student& rhs) {
        os << rhs.name;
        return os;
    }

public:
    // Student methods needed by Registrar
    explicit Student(const string& name);

    const string& getName() const {
        return name;
    }

    const vector<Course*>& getCourse() const {
        return courses;
    }

    bool addCourse(Course* new_course) {
        courses.push_back(new_course);
        return true;
    }

    // Student method needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course* course) {
        for (size_t i = 0; i < courses.size(); i++) {
            courses[i] = nullptr;
            courses.erase(courses.begin() + i);
        }
    }

private:
    string name;
    vector<Course*> courses;
}; // Student

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);

public:
    Registrar() = default;

    // Creates a new course, if none with that name
    bool addCourse(const string& course_name) {
        courses.push_back(new Course(course_name));
        return true;
    }

    // Creates a new student, if none with that name
    bool addStudent(const string& student_name) {
        students.push_back(new Student(student_name));
        return true;
    }

    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName) const {
        size_t course_index = -1;
        size_t student_index = -1;

        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i]->getName() == courseName) {
                course_index = i;
            }
            else {
                cerr << "could not find course " << courseName << "in registrar" << endl;
                return false;
            }
        }

        for (size_t j = 0; j < students.size(); j++) {
            if (students[j]->getName() == studentName) {
                student_index = j;
            }
            else {
                cerr << "could not find student " << studentName << "in registrar" << endl;
                return false;
            }
        }

        if (course_index != -1 && student_index != -1) {
            courses[course_index]->addStudent(students[student_index]);
            students[student_index]->addCourse(courses[course_index]);
            return true;
        }

        cerr << "fail to enroll student in registrar due to indexing failure" << endl;
        return false;
    }

    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string& courseName) {
        size_t course_index = -1;
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i]->getName() == courseName) {

                delete courses[i];
                courses[i] = nullptr;
                courses.erase(courses.begin() + i);
            }
        }

        for (size_t i = 0; i < students.size(); i++) {
            if (students[i]->getCourse() == courseName) {}
        }

        cerr << "failure to cancel course" << endl;
        return false;
    }

    // Get rid of everything!!!
    void purge() {
        for (Course* course : courses) {

        }
    }

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
}; // Registrar

ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Courses: " << endl;
    for (const Course* course : rhs.courses) {
        os << *course << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, const Course& rhs) {
    os << rhs.name << ": ";
    if (rhs.students.empty()) {
        os << "no students" << endl;
    }

    for (const Student* student : rhs.students) {
        os << student << " ";
    }
    return os;
}

int main() {
    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
} // main
