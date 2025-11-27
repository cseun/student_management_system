#pragma once
#include "StudentScoreInfoRow.h"

class StudentScore
{
private:
	int studentKey = -1;
    int examId = -1;

    int kukScore = 0;
    int engScore = 0;
    int mathScore = 0;
    int socialScore = 0;
    int scienceScore = 0;

    int totalScore = 0;

    void updateTotalScore();
   
public:
    StudentScore() = default;

    StudentScore(
        int kukScore,
        int engScore,
        int mathScore,
        int socialScore,
        int scienceScore,
        int studentKey = -1,
        int examId = -1
    );

    StudentScore(StudentScoreInfoRow& studentScoreInfoRow);

    void setExamId(int examId);
    void setStudentKey(int studentKey);

    void setScoreInfo(StudentScore& score);
    void setScoreInfo(int examId, int kukScore, int engScore, int mathScore, int socialScore, int scienceScore);
    
    int getStudentKey();
    int getExamId();
    int getTotalScore();
    int getKukScore();
    int getEngScore();
    int getMathScore();
    int getSocialScore();
    int getScienceScore();
    
	bool isSameScore(StudentScore& compareScore);
};