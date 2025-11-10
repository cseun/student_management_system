#pragma once
#include <string>
#include <chrono>
#include <sstream>
#include <vector>
#include "StudentList.h"

// 학생 목록
// - 지속 관리하는게 아니라 당시 학생 정보를 확인하기 위한 프로그램으로 생각

std::vector<std::string> StudentList::getAttributeNames()
{
	return { "이름", "학년", "반", "번호" };
}
std::map<std::string, StudentList::StudentListRow> StudentList::getAttriuteRows()
{
	std::map<std::string, StudentListRow> rows;
	for (auto it = studentList.begin(); it != studentList.end(); ++it) {
		std::string studentKey = it->first;
		Student& student = it->second;
		
		StudentListRow row;
		row.studentListKey = searchStudentListKey(studentKey);
		row.name = student.name;
		row.grade = student.grade;
		row.className = student.className;
		row.studentNumber = student.studentNumber;
		
		rows.insert(row.toPair());
	}
	return rows;
}

std::string StudentList::makeStudentListKey(Student& student)
{
	std::ostringstream oss;
	oss << student.grade << "-" << student.className << "-" << student.studentNumber;

	return oss.str();
}
std::string StudentList::searchStudentListKey(std::string studentKey)
{
	for (const auto& pair : studentIndexList)
	{
		if (pair.second == studentKey)
		{
			return pair.first; // studentListKey 반환
		}
	}
	return "";
}
bool StudentList::isStudentIndexExist(std::string studentListKey)
{
	return studentIndexList.find(studentListKey) != studentIndexList.end();
}
std::string StudentList::searchStudentKey(std::string studentListKey)
{
	auto it = studentIndexList.find(studentListKey);
	if (it != studentIndexList.end())
	{
		return it->second;
	}
	return "";
}
// TODO 오류검사 추가
void StudentList::addStudentIndex(std::string studentListKey, std::string studentKey)
{
	if (isStudentIndexExist(studentListKey)) {
		return;
	}
	studentIndexList[studentListKey] = studentKey;
}
void StudentList::updateStudentIndex(std::string originStudentListKey, std::string newStudentListKey)
{
	if (originStudentListKey == newStudentListKey) return;

	auto it = studentIndexList.find(originStudentListKey);
	auto newIt = studentIndexList.find(newStudentListKey);
	if (newIt != studentIndexList.end()) {
		return;
	}
	// 기존 인덱스가 존재하고, 새로운 인덱스가 존재하지 않으면 업데이트
	if (it != studentIndexList.end() && newIt == studentIndexList.end()) {
		deleteStudentIndex(it->first); // 기존 인덱스 삭제
		addStudentIndex(newStudentListKey, it->second); // 새로운 인덱스 추가
	}
}
void StudentList::deleteStudentIndex(std::string studentListKey)
{
	studentIndexList.erase(studentListKey);
}

// 학생 조회 (최종적으로는 studentKey 로 조회)
// - 인덱스에 없거나, 리스트에 없으면 nullptr 반환
// (1) studentIndexList 에서 studentListKey 로 studentKey 를 찾아온다.
// (2) studentKey 로 studentList 에서 student를 찾아온다.
Student* StudentList::searchStudent(Student& student)
{
	std::string studentListKey = searchStudentListKey(student.getKey());
	return searchStudent(studentListKey);
};
Student* StudentList::searchStudent(std::string studentListKey)
{
	std::string studentKey = searchStudentKey(studentListKey);
	if (studentKey.empty()) {
		return nullptr;
	}

	auto it = studentList.find(studentKey);
	if (it != studentList.end())
	{
		return &(it->second);
	}
	return nullptr;
}

// 학생 추가
// (1) 학생이 존재하는지 확인한다.
// (2) 학생이 존재하지 않는다면 학생을 리스트에 추가한다.
// (3) 학생 인덱스를 추가한다.
Student* StudentList::addStudent(Student& student)
{
	if (searchStudent(student)) {
		return nullptr;
	};

	std::string studentKey = student.getKey();
	// 학생 리스트 추가
	studentList[studentKey] = student;
	// 인덱스 추가
	std::string studentListKey = makeStudentListKey(student);
	addStudentIndex(studentListKey, studentKey);

	return &studentList[studentKey];
}

// 학생 업데이트
// (1) 학생이 존재하는지 확인한다.
// (2) 학생이 존재한다면 학생을 업데이트한다.
// (3) 학생 인덱스를 업데이트한다.
Student* StudentList::updateStudent(Student& originStudent, Student& student)
{
	// TODO: student 를 꼭 찾아와야할까? 인덱스만 찾아와도 되지 않을까?
	Student* searchedStudent = searchStudent(originStudent);
	if (searchedStudent != nullptr)
	{
		// 학생 정보 업데이트
		searchedStudent->updateInfo(student);
		// 학생 인덱스 업데이트
		std::string originListKey = searchStudentListKey(originStudent.getKey());
		std::string newListKey = searchStudentListKey(student.getKey());
		updateStudentIndex(originListKey, newListKey);
		
		return searchedStudent;
	}
	return nullptr;
}

// 학생 삭제
// (1) 학생이 존재하는지 확인한다.
// (2) 학생이 존재하면 학생 인덱스를 삭제한다.
// (3) 학생을 리스트에서 삭제한다.
bool StudentList::deleteStudent(Student& student) {
	std::string studentListKey = searchStudentListKey(student.getKey());
	return deleteStudent(studentListKey);
};
bool StudentList::deleteStudent(std::string studentListKey) {
	std::string studentKey = searchStudentKey(studentListKey);
	if (studentKey.empty()) {
		return false;
	}
	
	// TODO: 이후 transaction 구현 (like orm rollback)
	deleteStudentIndex(studentListKey);
	return studentList.erase(studentKey) > 0; // key가 있으면 1, 없으면 0
	
};