#include "pch.h"
#include <string>
#include <sstream>
#include "StudentScoreInfoRow.h"
#include "StudentListKey.h"
#include "Student.h"

int Student::studentIndex = 0;  // 정적 멤버 정의 및 초기화

Student::Student(
    std::string name,
    int grade,
    int classNumber,
    int studentNumber
) : name(name), grade(grade), classNumber(classNumber), studentNumber(studentNumber)
{
}

Student::Student(StudentScoreInfoRow& studentScoreInfoRow) :
    name(studentScoreInfoRow.name),
    grade(std::stoi(studentScoreInfoRow.grade)),
    classNumber(std::stoi(studentScoreInfoRow.classNumber)),
    studentNumber(std::stoi(studentScoreInfoRow.studentNumber))
{
}

int Student::getKey() { return studentKey; }

std::string& Student::getName() { return name; }
int Student::getGrade() { return grade; }
int Student::getClassNumber() { return classNumber; }
int Student::getStudentNumber() { return studentNumber; }

void Student::setKey()
{
	this->studentKey = ++studentIndex; // 학생 키 자동 증가
}
void Student::setName(std::string& name) { this->name = name; }
void Student::setGrade(int grade) { this->grade = grade; }
void Student::setClassNumber(int classNumber) { this->classNumber = classNumber; }
void Student::setStudentNumber(int studentNumber) { this->studentNumber = studentNumber; }

void Student::setStudent(Student& updateStudent) {
    name = updateStudent.name;
    grade = updateStudent.grade;
    classNumber = updateStudent.classNumber;
    studentNumber = updateStudent.studentNumber;
}

StudentListKey Student::getListKey() {
    return StudentListKey{
        grade,
        classNumber,
        studentNumber
	};
}

bool Student::isSameStudentInfo(Student& compareStudent)
{
    return (this->grade == compareStudent.grade) &&
        (this->classNumber == compareStudent.classNumber) &&
		(this->studentNumber == compareStudent.studentNumber);
}