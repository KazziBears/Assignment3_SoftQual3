#include "StudentRecord.h"

#include <cmath>
#include <stdexcept>

StudentRecord::StudentRecord(int id, const std::string& firstName,
                             const std::string& lastName, double grade)
    : id_(id), firstName_(firstName), lastName_(lastName), grade_(grade) {
    if (id <= 0 || !isValidName(firstName) || !isValidName(lastName) ||
        !isValidGrade(grade)) {
        throw std::invalid_argument("Invalid student record data.");
    }
}

int StudentRecord::getId() const {
    return id_;
}

const std::string& StudentRecord::getFirstName() const {
    return firstName_;
}

const std::string& StudentRecord::getLastName() const {
    return lastName_;
}

double StudentRecord::getGrade() const {
    return grade_;
}

bool StudentRecord::setFirstName(const std::string& firstName) {
    if (!isValidName(firstName)) {
        return false;
    }
    firstName_ = firstName;
    return true;
}

bool StudentRecord::setLastName(const std::string& lastName) {
    if (!isValidName(lastName)) {
        return false;
    }
    lastName_ = lastName;
    return true;
}

bool StudentRecord::setGrade(double grade) {
    if (!isValidGrade(grade)) {
        return false;
    }
    grade_ = grade;
    return true;
}

bool StudentRecord::isValidName(const std::string& name) {
    return !name.empty();
}

bool StudentRecord::isValidGrade(double grade) {
    return std::isfinite(grade) && grade >= 0.0 && grade <= 100.0;
}
