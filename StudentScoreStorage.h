#pragma once
#include <map>
#include <vector>
#include "StudentScore.h"
// 학생 성적 목록 저장소
class StudentScoreStorage
{
private:
	
public:
	StudentScoreStorage() = default;

	// 학생 성적은 학생을 기반으로 생성된다.
	// 한 학생에게는 여러 성적 정보가 있다.
	// 학생 키 studentKey : 학생 성적 객체 배열 StudentScore
	std::map<int, std::vector<StudentScore>> studentScoreTable;
	std::map<int, std::vector<StudentScore>>& getAllScores();
};