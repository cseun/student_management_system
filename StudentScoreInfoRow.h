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

	std::string year;
	std::string semester;
	std::string examType;

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
	const std::vector<std::string> toVector() const {
		return {
			grade, 
			classNumber, 
			studentNumber, 
			name,
			year,
			semester,
			examType,
			kukScore, 
			engScore, 
			mathScore,
			socialScore,
			scienceScore,
			totalScore, 
			rank
		};
	}
	const StudentListKey getListKey() const
	{
		return StudentListKey{
			std::stoi(grade),
			std::stoi(classNumber),
			std::stoi(studentNumber)
		};
	}
};