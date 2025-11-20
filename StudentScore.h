#pragma once

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
        int studentKey,
        int examId,
        int kukScore,
        int engScore,
        int mathScore,
        int socialScore,
        int scienceScore
    );

    void setExamId(int examId);

    void setScoreInfo(const StudentScore& score);
    void setScoreInfo(int examId, int kukScore, int engScore, int mathScore, int socialScore, int scienceScore);
    
    int getExamId() const;
    int getTotalScore() const;
    int getKukScore() const;
    int getEngScore() const;
    int getMathScore() const;
    int getSocialScore() const;
    int getScienceScore() const;
    
	bool isSameScore(const StudentScore& compareScore) const;
};