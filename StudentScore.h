#pragma once
#include <string>
#include "ExamType.h"
#include "Student.h"

class StudentScore
{
private:
    int studentKey = 0;
    int totalScore = 0;
public:
    int examId;
    int kukScore;
    int engScore;
    int mathScore;
    int socialScore;
    int scienceScore;

    StudentScore() = default;
    StudentScore(
        int studentKey,
        int examId,
        int kukScore,
        int engScore,
        int mathScore,
        int socialScore,
        int scienceScore
    );

    int getStudentKey() const;
    void setExamId(const int examId);
    void setKukScore(const int kukScore);
    void setEngScore(const int engScore);
    void setMathScore(const int mathScore);
    void setSocialScore(const int socialScore);
    void setScienceScore(const int scienceScore);

    void setScoreInfo(const StudentScore& score);
    void setScoreInfo(int, int, int, int, int, int);
    void updateTotalScore();
    int getTotalScore();
};