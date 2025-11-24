#pragma once
#include <vector>
#include "StudentScoreStorage.h"
#include "Student.h"

class StudentScoreService
{
private:
	StudentScoreStorage studentScoreStorage;

public:
	bool isStudentScoreExist(int studentKey, int examId = -1);
	std::map<int, std::vector<StudentScore>>& getAllStudentScores();
	StudentScore* searchStudentExamScore(int studentKey, int examId);
	std::vector<StudentScore>* searchStudentScores(int studentKey);
	
	StudentScore& addStudentScore(int studentKey, int examId, StudentScore& score); // 추가 전 score의 examId를 세팅
	StudentScore& updateStudentScore(int studentKey, int examId, StudentScore& updateScore); // 추가 전 score의 examId를 세팅
	void deleteStudentScore(int studentKey, int examId);
};