#include "pch.h"
#include <string>
#include <sstream>
#include <chrono>
#include "Student.h"

int Student::studentIndex = 0;  // 정적 멤버 정의 및 초기화

Student::Student(
    std::string name,
    std::string grade,
    std::string className,
    std::string studentNumber
) : name(name), grade(grade), className(className), studentNumber(studentNumber)
{
    studentKey = ++studentIndex;  // 학생 생성될 때 증가 (AUTO_INCREMENT)
}

int Student::getKey() const
{
    return studentKey;
}

void Student::setName(const std::string& name) {
    this->name = name;
}

void Student::setGrade(const std::string& grade) {
    this->grade = grade;
}

void Student::setClassName(const std::string& className) {
    this->className = className;
}

void Student::setStudentNumber(const std::string& studentNumber) {
    this->studentNumber = studentNumber;
}

void Student::setStudent(
    const std::string& name,
    const std::string& grade,
    const std::string& className,
    const std::string& studentNumber
) {
    setName(name);
    setGrade(grade);
    setClassName(className);
    setStudentNumber(studentNumber);
}

void Student::setStudent(const Student& updateStudent) {
    setStudent(
        updateStudent.name,
        updateStudent.grade,
        updateStudent.className,
        updateStudent.studentNumber
    ); 
}