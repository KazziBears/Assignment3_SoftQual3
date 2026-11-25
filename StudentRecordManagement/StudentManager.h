#pragma once

#include "StudentRecord.h"

#include <cstddef>
#include <vector>

class StudentManager {
public:
    bool addStudent(const StudentRecord& student);
    const StudentRecord* findStudentById(int id) const;
    bool updateStudent(int id, const std::string& firstName,
                       const std::string& lastName, double grade);
    bool removeStudent(int id);

    const std::vector<StudentRecord>& getAllStudents() const;
    std::size_t getStudentCount() const;

private:
    std::vector<StudentRecord> students_;
};
