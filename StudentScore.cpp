#include "pch.h"
#include <string>
#include "StudentScoreInfoRow.h"
#include "StudentScore.h"

void StudentScore::updateTotalScore()
{
    totalScore = kukScore + engScore + mathScore + socialScore + scienceScore;
}

StudentScore::StudentScore(
    int kukScore,
    int engScore,
    int mathScore,
    int socialScore,
    int scienceScore,
    int studentKey,
    int examId
) :
    kukScore(kukScore),
    engScore(engScore),
    mathScore(mathScore),
    socialScore(socialScore),
    scienceScore(scienceScore),
    studentKey(studentKey),
    examId(examId)
{
    updateTotalScore();
}

StudentScore::StudentScore(StudentScoreInfoRow& studentScoreInfoRow)
    : kukScore(std::stoi(studentScoreInfoRow.kukScore)),
    engScore(std::stoi(studentScoreInfoRow.engScore)),
    mathScore(std::stoi(studentScoreInfoRow.mathScore)),
    socialScore(std::stoi(studentScoreInfoRow.socialScore)),
    scienceScore(std::stoi(studentScoreInfoRow.scienceScore)),
    studentKey(-1),
    examId(-1)
{
}

void StudentScore::setExamId(int examId)
{
	this->examId = examId;
}

void StudentScore::setStudentKey(int studentKey)
{
    this->studentKey = studentKey;
}

void StudentScore::setScoreInfo(StudentScore& updateScore)
{
    this->examId = updateScore.examId;
    this->kukScore = updateScore.kukScore;
    this->engScore = updateScore.engScore;
    this->mathScore = updateScore.mathScore;
    this->socialScore = updateScore.socialScore;
    this->scienceScore = updateScore.scienceScore;

    updateTotalScore();
}

void StudentScore::setScoreInfo(
    int examId,
    int kukScore,
    int engScore,
    int mathScore,
    int socialScore,
    int scienceScore
){
    this->examId = examId;
    this->kukScore = kukScore;
    this->engScore = engScore;
    this->mathScore = mathScore;
    this->socialScore = socialScore;
    this->scienceScore = scienceScore;

    updateTotalScore();
}

int StudentScore::getExamId() { return examId; }
int StudentScore::getTotalScore() { return totalScore; }
int StudentScore::getKukScore() { return kukScore; }
int StudentScore::getEngScore() { return engScore; }
int StudentScore::getMathScore() { return mathScore; }
int StudentScore::getSocialScore() { return socialScore; }
int StudentScore::getScienceScore() { return scienceScore; }

bool StudentScore::isSameScore(StudentScore& compareScore)
{
    return (this->examId == compareScore.examId) &&
        (this->kukScore == compareScore.kukScore) &&
        (this->engScore == compareScore.engScore) &&
        (this->mathScore == compareScore.mathScore) &&
        (this->socialScore == compareScore.socialScore) &&
        (this->scienceScore == compareScore.scienceScore);
}