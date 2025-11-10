#pragma once
#include <string>
#include "Student.h"

class StudentScore
{
private:
    std::string studentListKey;
public:
    int kukScore;
    int engScore;
    int mathScore;
    int scienceScore;
    int socialScore;
    int totalScore;
    int rank;

    StudentScore(
        std::string studentListKey,
        int kukScore,
        int engScore,
        int mathScore,
        int scienceScore,
        int socialScore
    );

    std::string& getStudentListKey();
    void updateScoreInfo(StudentScore& score);
    void updateTotalScore();
};