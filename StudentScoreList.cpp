#pragma once
#include "pch.h"
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include <codecvt>
#include <locale>
#include "StudentScoreList.h"

std::map<std::string, StudentScoreList::StudentScoreListRow> StudentScoreList::getAttriuteRows()
{
	std::map<std::string, StudentScoreListRow> rows;
	for (auto it = studentScoreList.begin(); it != studentScoreList.end(); ++it) {
		std::string studentListKey = it->first;
		StudentScore& studentScore = it->second;
		
		StudentScoreListRow row;
		rows.insert(row.assignFrom(studentScore).toPair(studentListKey));
	}
	return rows;
}

// 리스트에서 학생 추가, 수정, 삭제
bool StudentScoreList::isStudentScoreExist(std::string studentListKey) {
	return studentScoreList.find(studentListKey) != studentScoreList.end();
}
StudentScore* StudentScoreList::searchStudentScore(std::string studentListKey)
{
	if (!isStudentIndexExist(studentListKey)) {
		return nullptr;
	}

	auto it = studentScoreList.find(studentListKey);
	if (it != studentScoreList.end())
	{
		return &(it->second);
	}
	return nullptr;
}
StudentScore* StudentScoreList::addStudentScore(Student& student, StudentScore& studentScore)
{
	Student* searchedStudent = StudentList::searchStudent(student);
	std::string studentListKey = StudentList::searchStudentListKey(searchedStudent->getKey());

	return addStudentScore(studentListKey, studentScore);
}
StudentScore* StudentScoreList::addStudentScore(std::string studentListKey, StudentScore& studentScore)
{
	// 학생 인덱스가 존재하고, 학생 성적 정보가 존재하지 않으면 학생 성적정보 추가.
	if (!isStudentIndexExist(studentListKey))
	{
		return nullptr;
	}
	studentScoreList[studentListKey] = studentScore;
	updateRank();
	return &studentScore;
}
StudentScore* StudentScoreList::updateStudentScore(StudentScore& originStudentScore, StudentScore& studentScore)
{
	StudentScore* SearchedStudentScore = searchStudentScore(originStudentScore.getStudentListKey());
	SearchedStudentScore->updateScoreInfo(studentScore);
	updateRank();
}
bool StudentScoreList::deleteStudentScore(StudentScore& studentScore)
{
	std::string studentListKey = studentScore.getStudentListKey();
	deleteStudentScore(studentListKey);
}
bool StudentScoreList::deleteStudentScore(std::string studentListKey)
{
	// 학생 성적이 삭제되더라도 학생 정보는 남아있다.
	if (studentScoreList.erase(studentListKey) == 0) {
		return false;
	};
	updateRank();
	return true;
}

// 리스트 학생들 등수 업데이트
void StudentScoreList::updateRank()
{
	for (auto& a : studentScoreList) {
		int rank = 1;
		for (auto& b : studentScoreList) {
			if (a.second.totalScore < b.second.totalScore) {
				rank++;
			}
		}
		a.second.rank = rank;
	}
};