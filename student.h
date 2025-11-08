#pragma once
#include <string>

class student
{
public:
    std::string studentNumber;
    std::string name;
    int grade;
    std::string className;
    int kukScore;
    int engScore;
    int mathScore;
    int scienceScore;
    int socialScore;
    int totalScore;
    int rank;

    student();
    student(
        std::string studentNumber,
        std::string name,
        int grade,
        std::string className,
        int kukScore,
        int engScore,
        int mathScore,
        int scienceScore,
        int socialScore
    );

    int getTotalScore();
    void updateTotalScore();
};