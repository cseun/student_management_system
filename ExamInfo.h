#pragma once
#include "ExamType.h"
class ExamInfo
{
private:
    int examId = 0;

public:
    static int examIndex;

    int year;
    int semester;
    ExamType examType;

    ExamInfo() = default;
    ExamInfo(
        int year,
        int semester,
        ExamType examType
    );

    int getId() const;
    void setYear(const int year);
    void setSemester(const int semester);
    void setExamType(const ExamType ExamType);

    void setExamInfo(
        const int year,
        const int semester,
        const ExamType examType
    );
    void setExamInfo(const ExamInfo& updateExamInfo);
	bool isSameExamInfo(const ExamInfo& compareExamInfo) const;
};