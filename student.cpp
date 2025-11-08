#pragma once
#include "pch.h"
#include <string>
#include "student.h"

student::student() : grade(0), kukScore(0), engScore(0), mathScore(0), scienceScore(0), socialScore(0), totalScore(0), rank(0) {};

student::student(
    std::string studentNumber,
    std::string name,
    int grade,
    std::string className,
    int kukScore,
    int engScore,
    int mathScore,
    int scienceScore,
    int socialScore
) : studentNumber(studentNumber),
name(name),
grade(grade),
className(className),
kukScore(kukScore),
engScore(engScore),
mathScore(mathScore),
scienceScore(scienceScore),
socialScore(socialScore),
rank(0)
{
    updateTotalScore();
}

int student::getTotalScore()
{
    return totalScore;
}

void student::updateTotalScore()
{
    totalScore = kukScore + engScore + mathScore + scienceScore + socialScore;
}
