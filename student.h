#pragma once
#include <string>

class Student
{
private:
    std::string studentKey;
    void setKey();

public:
    std::string name;
    int grade;
    std::string className;
    std::string studentNumber;

    Student(
        std::string name,
        int grade,
        std::string className,
        std::string studentNumber
    );

    std::string getKey() const;
    bool updateInfo(Student& student);
};