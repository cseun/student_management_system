#pragma once
#include "pch.h"
#include "ExamType.h"
#include "ExamInfo.h"

int ExamInfo::examIndex = 0;  // 정적 멤버 정의 및 초기화

ExamInfo::ExamInfo(
    int year,
    int semester,
    ExamType examType
):year(year), semester(semester), examType(examType) {
	this->examId = ++examIndex;
}

// Getter
int ExamInfo::getId() const { return examId; }
int ExamInfo::getYear() const { return year; }
int ExamInfo::getSemester() const { return semester; }
ExamType ExamInfo::getExamType() const { return examType; }

// Setter
void ExamInfo::setYear(int year) { this->year = year; }
void ExamInfo::setSemester(int semester) { this->semester = semester; }
void ExamInfo::setExamType(ExamType examType) { this->examType = examType; }

bool ExamInfo::isSameExamInfo(const ExamInfo& compareExamInfo) const
{
    return (year == compareExamInfo.year) &&
        (semester == compareExamInfo.semester) && 
        (examType == compareExamInfo.examType);   
}