#pragma once
#include "pch.h"
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include <codecvt>
#include <locale>
#include "student.h"
#include "StudentList.h"
#include "fileService.h"

std::map<std::string, student> studentInfos;

// 학생 정보 리스트를 다루는 클래스
StudentList::StudentList() {
	if (!studentInfos.empty()) {
		updateRank();
	}
};

// 리스트에서 다루는 학생 정보 - 목록
std::vector<CString> StudentList::getAttributeNames()
{
	return {
		_T("이름"), _T("학년"), _T("반"), _T("번호"),
		_T("국어"), _T("영어"), _T("수학"),
		_T("과학"), _T("사회"), _T("총점"), _T("등수")
	};
}
// 리스트에서 다루는 학생 정보 - 내용
StudentList::StudentRow StudentList::getAttributeRow(const student& student)
{
	StudentRow row;

	row.name = student.name.c_str();
	row.grade.Format(L"%d", student.grade);
	row.className = student.className.c_str();
	row.studentNumber = student.studentNumber.c_str();
	row.kukScore.Format(L"%d", student.kukScore);
	row.engScore.Format(L"%d", student.engScore);
	row.mathScore.Format(L"%d", student.mathScore);
	row.scienceScore.Format(L"%d", student.scienceScore);
	row.socialScore.Format(L"%d", student.socialScore);
	row.totalScore.Format(L"%d", student.totalScore);
	row.rank.Format(L"%d", student.rank);

	return row;
}
std::vector<std::vector<CString>> StudentList::getAttributeRows()
{
	std::vector<std::vector<CString>> rows;

	for (const auto& studentInfo : studentInfos)
	{
		const student& student = studentInfo.second;

		StudentRow row = getAttributeRow(student);
		rows.push_back(row.toVector());
	}

	return rows;
}

// 리스트에서 학생 추가, 수정, 삭제
student* StudentList::searchStudent(std::string studentNumber)
{
	if (studentInfos.empty()) {
		return nullptr;
	}

	auto it = studentInfos.find(studentNumber);
	if (it == studentInfos.end()) {
		return nullptr;
	}

	return &it->second;
};
bool StudentList::addStudent(student student)
{
	if (searchStudent(student.studentNumber)) {
		return FALSE; // 이미 존재하는 학생
	}

	studentInfos.insert({ student.studentNumber, student });
	updateRank();
	return TRUE;
};
bool StudentList::updateStudent(student studentInfo)
{
	student* student = searchStudent(studentInfo.studentNumber);

	if (student == nullptr) {
		return FALSE; // 존재하지 않는 학생
	}

	*student = studentInfo;
	updateRank();
	return TRUE;
};
bool StudentList::deleteStudent(std::string studentNumber)
{
	student* student = searchStudent(studentNumber);

	if (student == nullptr) {
		return FALSE; // 존재하지 않는 학생
	}

	studentInfos.erase(studentNumber);
	updateRank();
	return TRUE;
};
// 리스트 학생들 등수 업데이트
void StudentList::updateRank()
{
	for (auto& student1 : studentInfos) {
		int rank = 1;
		for (auto& student2 : studentInfos) {
			if (student1.second.getTotalScore() < student2.second.getTotalScore()) {
				rank++;
			}
		}
		student1.second.rank = rank;
	}
};

// csv 파일로부터 정보 불러오기
bool StudentList::loadFromCSV(const std::string& filePath)
{
	std::wifstream in(filePath);
	if (!in.is_open())
		return false;

	// UTF-8로 읽기 설정
	in.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

	studentInfos.clear();

	std::wstring line;
	bool isHeader = true;

	while (std::getline(in, line))
	{
		if (isHeader) { isHeader = false; continue; } // 첫 줄은 컬럼 헤더라서 스킵

		std::wstringstream ss(line);
		std::wstring cell;
		std::vector<std::wstring> cells;

		while (std::getline(ss, cell, L','))  // CSV 구분자
		{
			// 따옴표 제거
			if (cell.size() > 1 && cell.front() == L'"' && cell.back() == L'"')
				cell = cell.substr(1, cell.size() - 2);
			cells.push_back(cell);
		}

		if (cells.size() < 10)
			continue;

		student s;
		s.name = CW2A(cells[0].c_str());
		s.grade = std::stoi(cells[1]);
		s.className = CW2A(cells[2].c_str());
		s.studentNumber = CW2A(cells[3].c_str());
		s.kukScore = std::stoi(cells[4]);
		s.engScore = std::stoi(cells[5]);
		s.mathScore = std::stoi(cells[6]);
		s.scienceScore = std::stoi(cells[7]);
		s.socialScore = std::stoi(cells[8]);
		s.totalScore = std::stoi(cells[9]);
		s.rank = std::stoi(cells[10]);

		studentInfos[s.studentNumber] = s;
	}

	in.close();
	return true;
}
// csv 파일로 저장
bool StudentList::saveToCSV(std::string& filePath)
{
	std::ofstream out(filePath);
	if (!out.is_open())
		return false;

	out << "\xEF\xBB\xBF";

	// 컬럼 헤더 출력
	auto columns = getAttributeNames();
	for (int i = 0; i < columns.size(); ++i)
	{
		CT2CA colStr(columns[i]);
		out << colStr;
		if (i < columns.size() - 1)
			out << ",";
	}
	out << "\n";

	// 학생 정보 출력
	auto rows = getAttributeRows();
	for (const auto& row : rows)
	{
		for (int i = 0; i < row.size(); ++i)
		{
			CT2CA cellStr(row[i]);

			// CSV 안전하게: 쉼표나 따옴표 있을 경우 감싸기
			std::string cell(cellStr);
			if (cell.find(',') != std::string::npos || cell.find('"') != std::string::npos)
			{
				std::string escaped;
				for (char c : cell)
				{
					if (c == '"') escaped += "\"\"";
					else escaped += c;
				}
				cell = "\"" + escaped + "\"";
			}

			out << cell;
			if (i < row.size() - 1)
				out << ",";
		}
		out << "\n";
	}

	out.close();
	return true;
}