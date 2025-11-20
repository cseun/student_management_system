#pragma once
#include <string>
#include "StudentListKey.h"

class Student
{
private:
    int studentKey = -1; // 기본값
    std::string name;
    int grade;
    int classNumber;
    int studentNumber;

public:
    static int studentIndex; // 학생 키 인덱스

    Student() = default;
    Student(
        std::string& name,
        int grade,
        int classNumber,
        int studentNumber
    );

    int getKey() const;

    // Getter
    const std::string& getName() const;
    const int getGrade() const;
    const int getClassNumber() const;
    const int getStudentNumber() const;
	
    // Setter
    void setName(const std::string& name);
    void setGrade(const int grade);
    void setClassNumber(const int classNumber);
    void setStudentNumber(const int studentNumber);

    void setStudent(const Student& updateStudent);
    StudentListKey Student::getListKey() const;
    bool isSameStudentInfo(const Student& compareStudent) const;
};