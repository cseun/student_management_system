#pragma once
#include "ExamType.h"
class ExamInfo
{
private:
    int examId = -1; // 기본값

    int year;
    int semester;
    ExamType examType;

public:
    static int examIndex; //키 증가 인덱스

    ExamInfo() = default;
    ExamInfo(
        int year,
        int semester,
        ExamType examType
    );

    // Getter
    int getId() const;
    int getYear() const;
    int getSemester() const;
    ExamType getExamType() const;

    // Setter
    void setYear(int year);
    void setSemester(int semester);
    void setExamType(ExamType ExamType);

	bool isSameExamInfo(const ExamInfo& compareExamInfo) const;
};