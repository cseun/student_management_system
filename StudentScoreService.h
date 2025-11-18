#pragma once
#include <vector>
#include <stdexcept>
#include "StudentScoreStorage.h"
#include "Student.h"

class StudentScoreService
{
private:
	StudentScoreStorage studentScoreStorage;

public:
	bool isStudentScoreExist(const int studentKey, const int examId = -1) const;
	StudentScore* searchStudentExamScore(const int studentKey, const int examId);
	std::vector<StudentScore*> searchStudentScores(const int studentKey);
	StudentScore* addStudentScore(const int studentKey, const int examId, const StudentScore& score);
	StudentScore* updateStudentScore(const int studentKey, const int examId, const StudentScore& updateScore);
	void deleteStudentScore(const int studentKey, const int examId);
};

bool StudentScoreService::isStudentScoreExist(const int studentKey, const int examId) const
{
	auto it = studentScoreStorage.studentScoreTable.find(studentKey);
	if (it == studentScoreStorage.studentScoreTable.end()) {
		return false;
	}
	const std::vector<StudentScore>& studentScores = it->second;
	if (studentScores.empty()) {
		return false;
	}
	if (examId == -1) {
		return true;
	}
	for (const auto& score : studentScores) {
		if (score.examId == examId) {
			return true;
		}
	}
	return false;
}
StudentScore* StudentScoreService::searchStudentExamScore(const int studentKey, const int examId)
{
	auto it = studentScoreStorage.studentScoreTable.find(studentKey);
	if (it == studentScoreStorage.studentScoreTable.end()) {
		return nullptr;
	}
	std::vector<StudentScore>& studentScores = it->second;

	for (auto& score : studentScores) 
	{
		if (score.examId == examId) {
			return &score;
		}
	}
	return nullptr;
}
std::vector<StudentScore*> StudentScoreService::searchStudentScores(const int studentKey)
{
	std::vector<StudentScore*> studentScores;

	auto it = studentScoreStorage.studentScoreTable.find(studentKey);
	if (it == studentScoreStorage.studentScoreTable.end())
	{
		return studentScores;   // 빈 리스트 반환
	}

	auto& scores = it->second; // std::vector<StudentScore*>

	for (auto& score : scores)
	{
		studentScores.push_back(&score);
	}

	return studentScores;
}
StudentScore* StudentScoreService::addStudentScore(const int studentKey, const int examId, const StudentScore& score)
{
	StudentScore* searchedScore = searchStudentExamScore(studentKey, examId);
	if(searchedScore != nullptr)
	{
		throw std::runtime_error("이미 존재하는 학생 성적입니다.");
	}
	studentScoreStorage.studentScoreTable[studentKey].push_back(score);

	return searchStudentExamScore(studentKey, examId);
}
StudentScore* StudentScoreService::updateStudentScore(const int studentKey, const int examId, const StudentScore& updateScore)
{
	StudentScore* searchedScore = searchStudentExamScore(studentKey, examId);
	if (searchedScore == nullptr)
	{
		throw std::runtime_error("학생 성적이 존재하지 않습니다.");
	}
	searchedScore->setScoreInfo(updateScore);

	return searchedScore;
}
void StudentScoreService::deleteStudentScore(const int studentKey, const int examId)
{
	auto it = studentScoreStorage.studentScoreTable.find(studentKey);
	if (it == studentScoreStorage.studentScoreTable.end())
	{
		throw std::runtime_error("학생 성적이 존재하지 않습니다.");
	}

	auto& scores = it->second;
	for (auto scoreIt = scores.begin(); scoreIt != scores.end(); ++scoreIt)
	{
		if (scoreIt->examId == examId)
		{
			scores.erase(scoreIt);
			return;
		}
	}

	throw std::runtime_error("학생 성적이 존재하지 않습니다.");
	
}