#pragma once
#include <vector>
#include "StudentScoreStorage.h"
#include "Student.h"

class StudentScoreService
{
private:
	StudentScoreStorage studentScoreStorage;

public:
	bool isStudentScoreExist(int studentKey, int examId = -1) const;
	const std::map<int, std::vector<StudentScore>>& getAllStudentScores() const;
	const StudentScore* searchStudentExamScore(int studentKey, int examId) const;
	const std::vector<StudentScore>* searchStudentScores(const int studentKey) const;
	
	StudentScore& addStudentScore(int studentKey, const StudentScore& addScore); // 추가 전 score의 examId를 세팅
	StudentScore& updateStudentScore(int studentKey, int examId, const StudentScore& updateScore); // 추가 전 score의 examId를 세팅
	void deleteStudentScore(int studentKey, int examId);
};