#pragma once
#include <map>
#include <fstream>
#include <vector>
#include "studentScore.h"
#include "StudentList.h"

// 학생 성적 목록
// - 학생 성적은 학생을 추가한 이후에 추가된다.
// - 학생의 등수 정보를 가진다.

class StudentScoreList
{
private:
	StudentList studentList;
	std::map<std::string, StudentScore> studentScoreList;

public:
	StudentScoreList() = default;

	struct StudentScoreListRow
	{
		std::string kukScore;
		std::string engScore;
		std::string mathScore;
		std::string scienceScore;
		std::string socialScore;
		std::string totalScore;
		std::string rank;

		std::vector<std::string> getAttributeNames()
		{
			return { "국어", "영어", "수학", "과학", "사회", "총점", "등수" };
		}

		std::vector<std::string> toVector() const {
			return { kukScore, engScore, mathScore, scienceScore, socialScore, totalScore, rank };
		}

		std::pair<std::string, StudentScoreListRow> toPair(std::string& studentListKey) const {
			return { studentListKey, *this };
		}

		StudentScoreListRow& assignFrom(StudentScore& studentScore)
		{
			kukScore = studentScore.kukScore;
			engScore = studentScore.engScore;
			mathScore = studentScore.mathScore;
			scienceScore = studentScore.scienceScore;
			socialScore = studentScore.socialScore;
			totalScore = studentScore.totalScore;
			rank = studentScore.rank;

			return *this;
		}
	};
	// excel
	std::vector<std::string> getAttributeNames();
	std::map<std::string, StudentScoreListRow> getAttriuteRows();

	bool isStudentScoreExist(std::string studentListKey);
	StudentScore* searchStudentScore(std::string studentListKey);
	StudentScore* addStudentScore(Student& student, StudentScore& studentScore);
	StudentScore* addStudentScore(std::string studentListKey, StudentScore& studentScore);
	StudentScore* updateStudentScore(StudentScore& originStudentScore, StudentScore& studentScore);
	bool deleteStudentScore(StudentScore& studentScore);
	bool deleteStudentScore(std::string studentListKey);

	// 리스트 학생들 등수 업데이트
	void updateRank();
};


