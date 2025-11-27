#pragma once
#include <string>
#include <vector>
#include <map>
#include "StudentListKey.h"

struct StudentScoreInfoRow
{
	std::string grade;
	std::string classNumber;
	std::string studentNumber;
	std::string name;

	std::string examId;
	std::string year;
	std::string semester;
	std::string examType;
	std::string examTypeName;

	std::string kukScore;
	std::string engScore;
	std::string mathScore;
	std::string socialScore;
	std::string scienceScore;
	std::string totalScore;

	std::string rank;

	static std::vector<std::string> getAttributeNames()
	{
		return { "학년", "반", "번호", "이름", "년도", "학기", "시험종류", "국어", "영어", "수학", "사회", "과학", "총점", "등수" };
	}
	static std::vector<int> getAttributeSizes()
	{
		return { 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1 };
	}
	std::vector<std::string> toVector() {
		return {
			grade, 
			classNumber, 
			studentNumber, 
			name,
			year,
			semester,
			examTypeName,
			kukScore, 
			engScore, 
			mathScore,
			socialScore,
			scienceScore,
			totalScore, 
			rank
		};
	}
	StudentListKey getListKey()
	{
		return StudentListKey{
			std::stoi(grade),
			std::stoi(classNumber),
			std::stoi(studentNumber)
		};
	}

	std::string getExamId()
	{
		return examId;
	}
};