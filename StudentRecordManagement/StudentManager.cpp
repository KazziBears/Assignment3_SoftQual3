#include "StudentManager.h"

bool StudentManager::addStudent(const StudentRecord& student) {
    if (findStudentById(student.getId()) != nullptr) {
        return false;
    }

    students_.push_back(student);
    return true;
}

const StudentRecord* StudentManager::findStudentById(int id) const {
    for (const StudentRecord& student : students_) {
        if (student.getId() == id) {
            return &student;
        }
    }
    return nullptr;
}

bool StudentManager::updateStudent(int id, const std::string& firstName,
                                   const std::string& lastName, double grade) {
    for (StudentRecord& student : students_) {
        if (student.getId() == id) {
            return student.setFirstName(firstName) &&
                   student.setLastName(lastName) &&
                   student.setGrade(grade);
        }
    }
    return false;
}

bool StudentManager::removeStudent(int id) {
    for (auto it = students_.begin(); it != students_.end(); ++it) {
        if (it->getId() == id) {
            students_.erase(it);
            return true;
        }
    }
    return false;
}

const std::vector<StudentRecord>& StudentManager::getAllStudents() const {
    return students_;
}

std::size_t StudentManager::getStudentCount() const {
    return students_.size();
}
