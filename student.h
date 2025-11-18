#pragma once
#include <string>

class Student
{
private:
    int studentKey = 0;

public:
    static int studentIndex;

    std::string name;
    std::string grade;
    std::string className;
    std::string studentNumber;

    Student() = default;
    Student(
        std::string name,
        std::string grade,
        std::string className,
        std::string studentNumber
    );

    int getKey() const;
    void setName(const std::string& name);
    void setGrade(const std::string& grade);
    void setClassName(const std::string& className);
    void setStudentNumber(const std::string& studentNumber);

    void setStudent(
        const std::string& name,
        const std::string& grade,
        const std::string& className,
        const std::string& studentNumber
    );
    void Student::setStudent(const Student& updateStudent);
};