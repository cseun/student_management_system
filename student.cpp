#include "pch.h"
#include <string>
#include <sstream>
#include "StudentListKey.h"
#include "Student.h"

int Student::studentIndex = 0;  // 정적 멤버 정의 및 초기화

Student::Student(
    std::string& name,
    int grade,
    int classNumber,
    int studentNumber
) : name(name), grade(grade), classNumber(classNumber), studentNumber(studentNumber)
{
    studentKey = ++studentIndex;  // 학생 생성 시 자동 증가 (AUTO_INCREMENT)
}

int Student::getKey() const { return studentKey; }

const std::string& Student::getName() const { return name; }
const int Student::getGrade() const { return grade; }
const int Student::getClassNumber() const { return classNumber; }
const int Student::getStudentNumber() const { return studentNumber; }

void Student::setName(const std::string& name) { this->name = name; }
void Student::setGrade(const int grade) { this->grade = grade; }
void Student::setClassNumber(const int classNumber) { this->classNumber = classNumber; }
void Student::setStudentNumber(const int studentNumber) { this->studentNumber = studentNumber; }

void Student::setStudent(const Student& updateStudent) {
    name = updateStudent.name;
    grade = updateStudent.grade;
    classNumber = updateStudent.classNumber;
    studentNumber = updateStudent.studentNumber;
}

StudentListKey Student::getListKey() const {
    return StudentListKey{
        grade,
        classNumber,
        studentNumber
	};
}

bool Student::isSameStudentInfo(const Student& compareStudent) const
{
    return (this->grade == compareStudent.grade) &&
        (this->classNumber == compareStudent.classNumber) &&
		(this->studentNumber == compareStudent.studentNumber);
}