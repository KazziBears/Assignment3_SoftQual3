#include "CppUnitTest.h"
#include "../StudentRecordManagement/StudentManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StudentRecordTests {

TEST_CLASS(StudentRecordUnitTests) {
public:
    TEST_METHOD(ConstructorStoresStudentDetails) {
        StudentRecord student(1001, "John", "Smith", 85.5);

        Assert::AreEqual(1001, student.getId());
        Assert::AreEqual(std::string("John"), student.getFirstName());
        Assert::AreEqual(std::string("Smith"), student.getLastName());
        Assert::AreEqual(85.5, student.getGrade(), 0.001);
    }

    TEST_METHOD(ConstructorRejectsNonPositiveId) {
        bool threw = false;
        try {
            StudentRecord student(0, "John", "Smith", 85.0);
        } catch (const std::invalid_argument&) {
            threw = true;
        }
        Assert::IsTrue(threw);
    }

    TEST_METHOD(ConstructorRejectsEmptyName) {
        bool threw = false;
        try {
            StudentRecord student(1001, "", "Smith", 85.0);
        } catch (const std::invalid_argument&) {
            threw = true;
        }
        Assert::IsTrue(threw);
    }

    TEST_METHOD(ConstructorRejectsOutOfRangeGrade) {
        bool threw = false;
        try {
            StudentRecord student(1001, "John", "Smith", 105.0);
        } catch (const std::invalid_argument&) {
            threw = true;
        }
        Assert::IsTrue(threw);
    }

    TEST_METHOD(SettersAcceptValidValues) {
        StudentRecord student(1001, "John", "Smith", 70.0);

        Assert::IsTrue(student.setFirstName("Jane"));
        Assert::IsTrue(student.setLastName("Brown"));
        Assert::IsTrue(student.setGrade(92.0));
        Assert::AreEqual(std::string("Jane"), student.getFirstName());
        Assert::AreEqual(std::string("Brown"), student.getLastName());
        Assert::AreEqual(92.0, student.getGrade(), 0.001);
    }

    TEST_METHOD(SettersRejectInvalidValues) {
        StudentRecord student(1001, "John", "Smith", 70.0);

        Assert::IsFalse(student.setFirstName(""));
        Assert::IsFalse(student.setLastName(""));
        Assert::IsFalse(student.setGrade(101.0));
        Assert::AreEqual(70.0, student.getGrade(), 0.001);
    }

    TEST_METHOD(AddStudentIncreasesCount) {
        StudentManager manager;

        Assert::IsTrue(manager.addStudent(StudentRecord(1001, "John", "Smith", 85.0)));
        Assert::AreEqual(1, static_cast<int>(manager.getStudentCount()));
    }

    TEST_METHOD(AddStudentRejectsDuplicateId) {
        StudentManager manager;
        manager.addStudent(StudentRecord(1001, "John", "Smith", 85.0));

        Assert::IsFalse(manager.addStudent(StudentRecord(1001, "Jane", "Brown", 90.0)));
        Assert::AreEqual(1, static_cast<int>(manager.getStudentCount()));
    }

    TEST_METHOD(FindStudentReturnsMatchingStudent) {
        StudentManager manager;
        manager.addStudent(StudentRecord(1001, "John", "Smith", 85.0));

        const StudentRecord* result = manager.findStudentById(1001);

        Assert::IsNotNull(result);
        Assert::AreEqual(std::string("John"), result->getFirstName());
    }

    TEST_METHOD(FindStudentReturnsNullForUnknownId) {
        StudentManager manager;

        Assert::IsNull(manager.findStudentById(9999));
    }

    TEST_METHOD(UpdateStudentChangesDetails) {
        StudentManager manager;
        manager.addStudent(StudentRecord(1001, "John", "Smith", 70.0));

        Assert::IsTrue(manager.updateStudent(1001, "Jane", "Brown", 95.0));
        const StudentRecord* result = manager.findStudentById(1001);

        Assert::IsNotNull(result);
        Assert::AreEqual(std::string("Jane"), result->getFirstName());
        Assert::AreEqual(95.0, result->getGrade(), 0.001);
    }

    TEST_METHOD(UpdateStudentReturnsFalseForUnknownId) {
        StudentManager manager;

        Assert::IsFalse(manager.updateStudent(9999, "Jane", "Brown", 95.0));
    }

    TEST_METHOD(RemoveStudentDeletesRecord) {
        StudentManager manager;
        manager.addStudent(StudentRecord(1001, "John", "Smith", 85.0));

        Assert::IsTrue(manager.removeStudent(1001));
        Assert::AreEqual(0, static_cast<int>(manager.getStudentCount()));
        Assert::IsNull(manager.findStudentById(1001));
    }

    TEST_METHOD(RemoveStudentReturnsFalseForUnknownId) {
        StudentManager manager;

        Assert::IsFalse(manager.removeStudent(9999));
    }

    TEST_METHOD(GetAllStudentsReturnsEveryRecord) {
        StudentManager manager;
        manager.addStudent(StudentRecord(1001, "John", "Smith", 85.0));
        manager.addStudent(StudentRecord(1002, "Jane", "Brown", 92.0));

        Assert::AreEqual(2, static_cast<int>(manager.getAllStudents().size()));
    }
};

} // namespace StudentRecordTests
