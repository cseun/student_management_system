#pragma once
#include <string>
#include "Student.h"
#include "StudentScore.h"

StudentScore::StudentScore(
    std::string studentListKey,
    int kukScore = 0,
    int engScore = 0,
    int mathScore = 0,
    int scienceScore = 0,
    int socialScore = 0
) : kukScore(kukScore), engScore(engScore), mathScore(mathScore), scienceScore(scienceScore), socialScore(socialScore), studentListKey(studentListKey), rank(0)
{
    updateTotalScore();
};

std::string& StudentScore::getStudentListKey()
{
    return studentListKey;
}

void StudentScore::updateScoreInfo(StudentScore& score)
{
    this->kukScore = score.kukScore;
    this->engScore = score.engScore;
    this->mathScore = score.mathScore;
    this->scienceScore = score.scienceScore;
    this->socialScore = score.socialScore;

    updateTotalScore();
}

void StudentScore::updateTotalScore()
{
    totalScore = kukScore + engScore + mathScore + scienceScore + socialScore;
}