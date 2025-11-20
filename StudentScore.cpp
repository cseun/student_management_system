#include "pch.h"
#include <string>
#include "StudentScore.h"

void StudentScore::updateTotalScore()
{
    totalScore = kukScore + engScore + mathScore + socialScore + scienceScore;
}

StudentScore::StudentScore(
    int studentKey,
    int examId,
    int kukScore,
    int engScore,
    int mathScore,
    int socialScore,
    int scienceScore
) :
    studentKey(studentKey),
    examId(examId),
    kukScore(kukScore),
    engScore(engScore),
    mathScore(mathScore),
    socialScore(socialScore),
    scienceScore(scienceScore)
{
    updateTotalScore();
}

void StudentScore::setExamId(int examId)
{
	this->examId = examId;
}

void StudentScore::setScoreInfo(const StudentScore& updateScore)
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

int StudentScore::getExamId() const { return examId; }
int StudentScore::getTotalScore() const { return totalScore; }
int StudentScore::getKukScore() const { return kukScore; }
int StudentScore::getEngScore() const { return engScore; }
int StudentScore::getMathScore() const { return mathScore; }
int StudentScore::getSocialScore() const { return socialScore; }
int StudentScore::getScienceScore() const { return scienceScore; }

bool StudentScore::isSameScore(const StudentScore& compareScore) const
{
    return (this->examId == compareScore.examId) &&
        (this->kukScore == compareScore.kukScore) &&
        (this->engScore == compareScore.engScore) &&
        (this->mathScore == compareScore.mathScore) &&
        (this->socialScore == compareScore.socialScore) &&
        (this->scienceScore == compareScore.scienceScore);
}