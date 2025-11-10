#pragma once
#include <map>
#include <fstream>
#include <vector>
#include <locale>
#include "studentList.h"
#include "student.h"
#include "studentScoreList.h"
#include "StudentExcelManager.h"

// map Rows ? 
// 
// 학생 성적 엑셀에 표시될 항목 맵핑(학생정보 + 성적정보)
std::vector<StudentExcelManager::StudentScoreInfoRow> StudentExcelManager::mapStudentScoreRows(
	std::map<std::string, StudentList::StudentListRow>& studentRows,
	std::map<std::string, StudentScoreList::StudentScoreListRow>& studentScoreRows
)
{
	std::vector<StudentExcelManager::StudentScoreInfoRow> rows;

	// 학생 - 성적
	for (auto& it : studentRows)
	{
		std::string studentListKey = it.first;
		StudentList::StudentListRow studentListRow = it.second;

		StudentScoreInfoRow row;
		row.name = studentListRow.name;
		row.grade = studentListRow.grade;
		row.className = studentListRow.className;
		row.studentNumber = studentListRow.studentNumber;

		// 성적이 존재할 경우 매칭
		auto scoreIt = studentScoreRows.find(studentListKey);
		if (scoreIt != studentScoreRows.end()) {
			StudentScoreList::StudentScoreListRow scoreRow = scoreIt->second;
			row.kukScore = scoreRow.kukScore;
			row.engScore = scoreRow.engScore;
			row.mathScore = scoreRow.mathScore;
			row.scienceScore = scoreRow.scienceScore;
			row.socialScore = scoreRow.socialScore;
			row.totalScore = scoreRow.totalScore;
			row.rank = scoreRow.rank;
		}
		else {
			row.kukScore = "";
			row.engScore = "";
			row.mathScore = "";
			row.scienceScore = "";
			row.socialScore = "";
			row.totalScore = "";
			row.rank = "";
		}
		rows.push_back(row);
	}
	return rows;
}

std::vector<StudentExcelManager::StudentScoreInfoRow> getStudentScoreInfosFromFile(std::string filetype, std::string filepath)
{
	if (filetype != "csv")
	{
		// 지원되지 않는 파일 형식입니다.
		return;
	}
}