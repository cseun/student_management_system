#include "pch.h"
#include <string>
#include "StudentScore.h"

StudentScore::StudentScore(
    int examId,
    int kukScore = 0,
    int engScore = 0,
    int mathScore = 0,
    int socialScore = 0,
    int scienceScore = 0
): 
    examId(examId),
    kukScore(kukScore), 
    engScore(engScore), 
    mathScore(mathScore), 
    socialScore(socialScore),
    scienceScore(scienceScore)
{
    updateTotalScore();
};

void StudentScore::setExamId(const int examId)
{
	this->examId = examId;
}
void StudentScore::setKukScore(const int kukScore)
{
	this->kukScore = kukScore;
}
void StudentScore::setEngScore(const int engScore)
{
	this->engScore = engScore;
}
void StudentScore::setMathScore(const int mathScore)
{
	this->mathScore = mathScore;
}
void StudentScore::setSocialScore(const int socialScore)
{
	this->socialScore = socialScore;
}
void StudentScore::setScienceScore(const int scienceScore)
{
	this->scienceScore = scienceScore;
}

void StudentScore::setScoreInfo(const StudentScore& updateScore)
{
    setScoreInfo(
        updateScore.examId,
        updateScore.kukScore,
        updateScore.engScore,
        updateScore.mathScore,
        updateScore.socialScore,
        updateScore.scienceScore
	);

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
    setExamId(examId);
    setKukScore(kukScore);
    setEngScore(engScore);
    setMathScore(mathScore);
    setSocialScore(socialScore);
    setScienceScore(scienceScore);

    updateTotalScore();
}
void StudentScore::updateTotalScore()
{
    this->totalScore = this->kukScore + this->engScore + this->mathScore + this->socialScore + this->scienceScore;
}
int StudentScore::getTotalScore()
{
    return this->totalScore;
}