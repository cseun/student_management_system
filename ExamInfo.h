#pragma once
#include "ExamType.h"
#include "StudentScoreInfoRow.h"

class ExamInfo
{
private:
    int examId = -1; // 기본값

    int year = 0;
    int semester = 0;
    ExamType examType = ExamType::Unknown;

public:
    static int examIndex; //키 증가 인덱스

    ExamInfo() = default;
    ExamInfo(
        int year,
        int semester,
        ExamType examType
    );
    ExamInfo(StudentScoreInfoRow& studentScoreInfoRow);

    // Getter
    int getId();
    int getYear();
    int getSemester();
    ExamType getExamType();

    // Setter
    void setId();
    void setYear(int year);
    void setSemester(int semester);
    void setExamType(ExamType ExamType);

	bool isSameExamInfo(ExamInfo& other);
    bool operator<(const ExamInfo& other) const;
};