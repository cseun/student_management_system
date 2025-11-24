#pragma once
#include <string>
#include "StudentScoreInfoRow.h"
#include "StudentListKey.h"

class Student
{
private:
    int studentKey = -1; // 기본값

    std::string name = "";
    int grade = 0;
    int classNumber = 0;
    int studentNumber = 0;

public:
    static int studentIndex; // 학생 키 인덱스

    Student() = default;
    Student(
        std::string name,
        int grade,
        int classNumber,
        int studentNumber
	);

    Student(StudentScoreInfoRow& studentScoreInfoRow);

    int getKey();

    // Getter
    std::string& getName();
    int getGrade();
    int getClassNumber();
    int getStudentNumber();
	
    // Setter
	void setKey();
    void setName(std::string& name);
    void setGrade(int grade);
    void setClassNumber(int classNumber);
    void setStudentNumber(int studentNumber);

    void setStudent(Student& updateStudent);
    StudentListKey getListKey();
    bool isSameStudentInfo(Student& compareStudent);
};