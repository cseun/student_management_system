#pragma once
#include "StudentListKey.h"
#include "Student.h"
#include "StudentScore.h"
#include "ExamInfo.h"

class StudentScoreInfo
{
private:
	Student student;
	StudentScore score;
	ExamInfo exam;
	StudentListKey studentListKey;
	int examId;
	int totalScore;
	int rank;
public:
	StudentScoreInfo() = default;
	StudentScoreInfo(
		Student student,
		StudentScore score,
		ExamInfo exam
	);

	// Getter
	Student& getStudent();
	StudentScore& getScore();
	ExamInfo& getExam();
	StudentListKey& getStudentListKey();
	int getExamId();
	int getTotalScore();
	int getRank();

	// Setter
	void setRank(int rank); // 캐시 갱신시 자동 계산
};