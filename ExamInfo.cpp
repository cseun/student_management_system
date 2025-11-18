#pragma once
#include "pch.h"
#include "ExamType.h"
#include "ExamInfo.h"

int ExamInfo::examIndex = 0;  // 정적 멤버 정의 및 초기화

ExamInfo::ExamInfo(
    int year,
    int semester,
    ExamType examType
):year(0), semester(0), examType(ExamType::Unknown) {
	this->examId = ++examIndex;
}

int ExamInfo::getId() const
{
    return this->examId;
}
void ExamInfo::setYear(const int year)
{
	this->year = year;
}
void ExamInfo::setSemester(const int semester)
{
	this->semester = semester;
}
void ExamInfo::setExamType(const ExamType examType)
{
    this->examType = examType;
}

void ExamInfo::setExamInfo(
    const int year,
    const int semester,
    const ExamType examType
) {
    setYear(year);
    setSemester(semester);
    setExamType(examType);
}
void ExamInfo::setExamInfo(const ExamInfo& updateExamInfo)
{
    setExamInfo(
        updateExamInfo.year,
        updateExamInfo.semester,
        updateExamInfo.examType
    );
}
bool ExamInfo::isSameExamInfo(const ExamInfo& compareExamInfo) const
{
    return (this->year == compareExamInfo.year) &&
           (this->semester == compareExamInfo.semester) &&
		(this->examType == compareExamInfo.examType);   
}