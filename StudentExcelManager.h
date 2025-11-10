#pragma once
#pragma once
#include <map>
#include <fstream>
#include <vector>
#include <locale>
#include "studentList.h"
#include "student.h"
#include "studentScoreList.h"

class StudentExcelManager
{
public:
	struct StudentScoreInfoRow
	{
		// 학생 정보 + 학생 mergedRows
		// - 엑셀 값과, 리스트 값, 실제 값이 모두 다를 수 있으므로.
		std::string name;
		std::string grade;
		std::string className;
		std::string studentNumber;
		std::string kukScore;
		std::string engScore;
		std::string mathScore;
		std::string scienceScore;
		std::string socialScore;
		std::string totalScore;
		std::string rank;

		std::vector<std::string> toVector() const {
			return {
				name, grade, className, studentNumber, kukScore, engScore, mathScore, scienceScore, socialScore, totalScore, rank
			};
		}
	};

	std::vector<StudentScoreInfoRow> mapStudentScoreRows(
		std::map<std::string, StudentList::StudentListRow>& studentRows,
		std::map<std::string, StudentScoreList::StudentScoreListRow>& studentScoreRows
	);
};

// csv 파일로 불러온 정보들을 맵핑해서 내부에서 다룰 수 있는 객체로 만들어준다.

//// 리스트에서 다루는 학생 정보 - 내용
//StudentList::StudentRow StudentList::getAttributeRow(const student& student)
//{
//	StudentRow row;
//
//	row.name = student.name.c_str();
//	row.grade.Format(L"%d", student.grade);
//	row.className = student.className.c_str();
//	row.studentNumber = student.studentNumber.c_str();
//	row.kukScore.Format(L"%d", student.kukScore);
//	row.engScore.Format(L"%d", student.engScore);
//	row.mathScore.Format(L"%d", student.mathScore);
//	row.scienceScore.Format(L"%d", student.scienceScore);
//	row.socialScore.Format(L"%d", student.socialScore);
//	row.totalScore.Format(L"%d", student.totalScore);
//	row.rank.Format(L"%d", student.rank);
//
//	return row;
//}