#include "pch.h"
#include <stdexcept>
#include <vector>
#include "StudentScoreStorage.h"
#include "StudentScore.h"
#include "StudentScoreService.h"
bool StudentScoreService::isStudentScoreExist(int studentKey, int examId)
{
	auto it = studentScoreStorage.studentScoreTable.find(studentKey);
	if (it == studentScoreStorage.studentScoreTable.end()) {
		return false;
	}
	std::vector<StudentScore>& studentScores = it->second;
	if (studentScores.empty()) {
		return false;
	}
	if (examId == -1) {
		return true;
	}
	for (auto& score : studentScores) {
		if (score.getExamId() == examId) {
			return true;
		}
	}
	return false;
}
std::map<int, std::vector<StudentScore>>& StudentScoreService::getAllStudentScores()
{
	return studentScoreStorage.getAllScores();
}
StudentScore* StudentScoreService::searchStudentExamScore(int studentKey, int examId)
{
	std::vector<StudentScore>* studentScores = searchStudentScores(studentKey);
	if (studentScores == nullptr)
	{
		throw std::runtime_error("해당 학생의 성적 정보가 존재하지 않습니다.");
	}

	for (auto it = studentScores->begin(); it != studentScores->end(); ++it)
	{
		if (it->getExamId() == examId)
		{
			return &(*it); //실제 객체의 주소 반환
		}
	}
	return nullptr;
}
std::vector<StudentScore>* StudentScoreService::searchStudentScores(int studentKey) 
{
	auto it = studentScoreStorage.studentScoreTable.find(studentKey);
	if (it == studentScoreStorage.studentScoreTable.end())
	{
		return nullptr;
	}

	return &(it->second);
}

StudentScore& StudentScoreService::addStudentScore(int studentKey, int examId, StudentScore& score)
{
	StudentScore* searchedScore = searchStudentExamScore(studentKey, examId);
	if (searchedScore != nullptr)
	{
		throw std::runtime_error("이미 해당 학생과 시험에 대한 성적이 존재합니다.");
	}
	studentScoreStorage.studentScoreTable[studentKey].push_back(score);

	//가장 마지막 요소를 반환
	return studentScoreStorage.studentScoreTable[studentKey].back();
}
StudentScore& StudentScoreService::updateStudentScore(int studentKey, int originExamId, StudentScore& updateScore) //이미 성적을 생성하고 들어옴
{
	StudentScore* searchedScore = searchStudentExamScore(studentKey, originExamId);
	if (searchedScore == nullptr)
	{
		throw std::runtime_error("기준 학생과 시험에 대한 성적이 존재하지 않습니다.");
	}

	int updateExamId = updateScore.getExamId();
	
	for (auto& score : studentScoreStorage.studentScoreTable[studentKey])
	{
		if (score.getExamId() == originExamId) // 바꿔야할 스코어를 찾는다.
		{
			int updateExamId = updateScore.getExamId();
			// 시험 ID가 다르면 기존에 존재하는지 확인
			if (originExamId != updateExamId)
			{ 
				// 존재하면 오류 발생
				if (searchStudentExamScore(studentKey, updateExamId) != nullptr)
				{
					throw std::runtime_error("이미 수정할 시험에 대한 성적이 존재합니다. 해당 시험을 선택하여 수정해주세요.");
				}
			}

			// 기존에 존재하지 않거나 같은 시험이면 성적과 시험id를 업데이트
			score.setScoreInfo(updateScore);

			return score;
		}
	}
	
	throw std::runtime_error("수정할 학생과 시험에 대한 성적을 찾을 수 없습니다.");
}
void StudentScoreService::deleteStudentScore(int studentKey, int examId)
{
	std::map<int, std::vector<StudentScore>>& allScores = studentScoreStorage.getAllScores();
	
	auto it = allScores.find(studentKey);
	if (it == allScores.end())
	{
		throw std::runtime_error("해당 학생의 성적 정보가 존재하지 않습니다.");
	}
	
	// 학생 성적 정보들을 순회하면서 해당 examId를 찾아 지우기
	std::vector<StudentScore>& scores = it->second;

	// 시험 성적 삭제
	for (auto scoreIt = scores.begin(); scoreIt != scores.end(); ++scoreIt)
	{
		if (scoreIt->getExamId() == examId)
		{
			scores.erase(scoreIt);
			return;
		}
	}

	throw std::runtime_error("해당 시험의 성적이 존재하지 않습니다.");

}