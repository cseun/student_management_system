#include "pch.h"
#include "Student.h"
#include "StudentScore.h"
#include "ExamInfo.h"
#include "StudentScoreInfo.h"

StudentScoreInfo::StudentScoreInfo(
	Student student,
	StudentScore score,
	ExamInfo exam
) : 
	student(student), 
	score(score), 
	exam(exam), 
	studentListKey(student.getListKey()), 
	examId(exam.getId()), 
	totalScore(score.getTotalScore()), 
	rank(0)
{}

// Getter
StudentListKey& StudentScoreInfo::getStudentListKey()
{
	return studentListKey;
}

Student& StudentScoreInfo::getStudent()
{
	return student;
}
StudentScore& StudentScoreInfo::getScore()
{
	return score;
}
ExamInfo& StudentScoreInfo::getExam()
{
	return exam;
}
int StudentScoreInfo::getExamId()
{
	return examId;
}
int StudentScoreInfo::getTotalScore()
{
	return totalScore;
}
int StudentScoreInfo::getRank()
{
	return rank;
}

void StudentScoreInfo::setRank(int rank)
{
	this->rank = rank;
}