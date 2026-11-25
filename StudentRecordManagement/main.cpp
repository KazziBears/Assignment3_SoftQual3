#include "StudentManager.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

namespace {
void displayStudent(const StudentRecord& student) {
    std::cout << std::left << std::setw(8) << student.getId()
              << std::setw(18) << student.getFirstName()
              << std::setw(18) << student.getLastName()
              << std::fixed << std::setprecision(1)
              << student.getGrade() << '\n';
}

void displayAllStudents(const StudentManager& manager) {
    if (manager.getAllStudents().empty()) {
        std::cout << "No student records found.\n";
        return;
    }

    std::cout << std::left << std::setw(8) << "ID"
              << std::setw(18) << "First name"
              << std::setw(18) << "Last name" << "Grade\n";
    std::cout << "--------------------------------------------------\n";

    for (const StudentRecord& student : manager.getAllStudents()) {
        displayStudent(student);
    }
}

int readInteger(const std::string& prompt) {
    int value = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Please enter a valid whole number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double readGrade() {
    double grade = 0.0;
    while (true) {
        std::cout << "Grade (0-100): ";
        if (std::cin >> grade && grade >= 0.0 && grade <= 100.0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return grade;
        }

        std::cout << "Please enter a grade between 0 and 100.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string readName(const std::string& prompt) {
    std::string name;
    do {
        std::cout << prompt;
        std::getline(std::cin, name);
        if (name.empty()) {
            std::cout << "Name cannot be empty.\n";
        }
    } while (name.empty());
    return name;
}

void addStudent(StudentManager& manager) {
    const int id = readInteger("Student ID: ");
    const std::string firstName = readName("First name: ");
    const std::string lastName = readName("Last name: ");
    const double grade = readGrade();

    try {
        if (manager.addStudent(StudentRecord(id, firstName, lastName, grade))) {
            std::cout << "Student added successfully.\n";
        } else {
            std::cout << "A student with that ID already exists.\n";
        }
    } catch (const std::invalid_argument& error) {
        std::cout << "Could not add student: " << error.what() << '\n';
    }
}

void searchStudent(const StudentManager& manager) {
    const int id = readInteger("Enter student ID to search: ");
    const StudentRecord* student = manager.findStudentById(id);

    if (student == nullptr) {
        std::cout << "Student not found.\n";
    } else {
        displayStudent(*student);
    }
}

void updateStudent(StudentManager& manager) {
    const int id = readInteger("Enter student ID to update: ");
    if (manager.findStudentById(id) == nullptr) {
        std::cout << "Student not found.\n";
        return;
    }

    const std::string firstName = readName("New first name: ");
    const std::string lastName = readName("New last name: ");
    const double grade = readGrade();

    if (manager.updateStudent(id, firstName, lastName, grade)) {
        std::cout << "Student updated successfully.\n";
    } else {
        std::cout << "Update failed. Check the supplied information.\n";
    }
}

void removeStudent(StudentManager& manager) {
    const int id = readInteger("Enter student ID to delete: ");
    if (manager.removeStudent(id)) {
        std::cout << "Student deleted successfully.\n";
    } else {
        std::cout << "Student not found.\n";
    }
}
} // namespace

int main() {
    StudentManager manager;
    bool running = true;

    while (running) {
        std::cout << "\n=== Student Record Management System ===\n"
                  << "1. Add student\n"
                  << "2. View all students\n"
                  << "3. Search for student\n"
                  << "4. Update student\n"
                  << "5. Delete student\n"
                  << "0. Exit\n";

        const int choice = readInteger("Select an option: ");
        switch (choice) {
        case 1:
            addStudent(manager);
            break;
        case 2:
            displayAllStudents(manager);
            break;
        case 3:
            searchStudent(manager);
            break;
        case 4:
            updateStudent(manager);
            break;
        case 5:
            removeStudent(manager);
            break;
        case 0:
            running = false;
            std::cout << "Goodbye.\n";
            break;
        default:
            std::cout << "Invalid menu option.\n";
            break;
        }
    }

    return 0;
}
