#include "pch.h"
#include <string>
#include <sstream>
#include "Student.h"

int Student::studentIndex = 0;  // 정적 멤버 정의 및 초기화

Student::Student(
    std::string& name,
    std::string& grade,
    std::string& className,
    std::string& studentNumber
) : name(name), grade(grade), className(className), studentNumber(studentNumber)
{
    studentKey = ++studentIndex;  // 학생 생성 시 자동 증가 (AUTO_INCREMENT)
}

int Student::getKey() const { return studentKey; }

const std::string& Student::getName() const { return name; }
const std::string& Student::getGrade() const { return grade; }
const std::string& Student::getClassName() const { return className; }
const std::string& Student::getStudentNumber() const { return studentNumber; }

void Student::setName(const std::string& name) { this->name = name; }
void Student::setGrade(const std::string& grade) { this->grade = grade; }
void Student::setClassName(const std::string& className) { this->className = className; }
void Student::setStudentNumber(const std::string& studentNumber) { this->studentNumber = studentNumber; }

void Student::setStudent(const Student& updateStudent) {
    name = updateStudent.name;
    grade = updateStudent.grade;
    className = updateStudent.className;
    studentNumber = updateStudent.studentNumber;
}

std::string Student::getListKey() const {
    std::ostringstream oss;
    oss << grade << "-" << className << "-" << studentNumber;
    return oss.str();
}

bool Student::isSameStudentInfo(const Student& compareStudent) const
{
    return (this->grade == compareStudent.grade) &&
        (this->className == compareStudent.className) &&
		(this->studentNumber == compareStudent.studentNumber);
}