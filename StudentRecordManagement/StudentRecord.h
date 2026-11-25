#pragma once

#include <string>

class StudentRecord {
public:
    StudentRecord(int id, const std::string& firstName,
                  const std::string& lastName, double grade);

    int getId() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    double getGrade() const;

    bool setFirstName(const std::string& firstName);
    bool setLastName(const std::string& lastName);
    bool setGrade(double grade);

private:
    int id_;
    std::string firstName_;
    std::string lastName_;
    double grade_;

    static bool isValidName(const std::string& name);
    static bool isValidGrade(double grade);
};
