#pragma once
#include "pch.h"
#include <string>
#include <sstream>
#include <chrono>
#include "student.h"

Student::Student(
    std::string name,          
    int grade,                     
    std::string className,     
    std::string studentNumber
) : name(name), grade(grade), className(className), studentNumber(studentNumber)
{
    setKey();
}

void Student::setKey()
{
    // 키: [현재시간]-[학년]-[반]-[번호]
    auto now = std::chrono::system_clock::now();
    auto millis = 
        std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()).count();

    std::ostringstream oss;
    oss << millis << "-" << grade << "-" << className << "-" << studentNumber;
    studentKey = oss.str();
}

std::string Student::getKey() const
{
    return studentKey;
}

// studentKey는 유지, 나머지만 업데이트
bool Student::updateInfo(Student& student)
{
    this->name = student.name;
    this->grade = student.grade;
    this->className = student.className;
    this->studentNumber = student.studentNumber;
}
