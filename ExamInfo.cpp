#pragma once
#include "pch.h"
#include "StudentScoreInfoRow.h"
#include "ExamType.h"
#include "ExamInfo.h"


int ExamInfo::examIndex = 0;  // 정적 멤버 정의 및 초기화

ExamInfo::ExamInfo(
    int year,
    int semester,
    ExamType examType
):year(year), semester(semester), examType(examType) {}

ExamInfo::ExamInfo(StudentScoreInfoRow& studentScoreInfoRow)
    : year(std::stoi(studentScoreInfoRow.year)),
    semester(std::stoi(studentScoreInfoRow.semester)),
    examType(static_cast<ExamType>(std::stoi(studentScoreInfoRow.examType)))
{
}

// Getter
int ExamInfo::getId() { return examId; }
int ExamInfo::getYear() { return year; }
int ExamInfo::getSemester() { return semester; }
ExamType ExamInfo::getExamType() { return examType; }

// Setter
void ExamInfo::setId() {
    this->examId = this->examId = ++examIndex;
}
void ExamInfo::setYear(int year) { this->year = year; }
void ExamInfo::setSemester(int semester) { this->semester = semester; }
void ExamInfo::setExamType(ExamType examType) { this->examType = examType; }

bool ExamInfo::isSameExamInfo(ExamInfo& other)
{
    return (year == other.year) &&
        (semester == other.semester) && 
        (examType == other.examType);   
}

bool ExamInfo::operator<(const ExamInfo& other) const
{
    if (year != other.year)
        return year < other.year;
    if (semester != other.semester)
        return semester < other.semester;
    return examType < other.examType;
}