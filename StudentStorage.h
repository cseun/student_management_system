#pragma once
#include <string>
#include <map>
#include "Student.h"
#include "StudentListKey.h"

// 학생 목록 저장소
class StudentStorage
{
// TODO: public -> private 변경 필요
public:
	StudentStorage() = default;
	// 학생목록 인덱스 studentIndexList
	// DB의 세컨더리 인덱스 개념을 추가하여 효율적으로 학생(student)을 찾아가도록 한다.
	// 인덱스 키(studentListKey) 구성: 학년-반-번호
	// 인덱스 키 - 인덱스 값 : studentListKey - studentIdx
	std::map<StudentListKey, int> studentIndexList; // 학생 리스트 키 순서대로 정렬 -> map
	std::map<int, Student> studentTable; // 학생 키 순서대로 정렬 -> map

	std::map<int, Student>& getAllStudents(); //학생 키 순서대로 정렬된 학생 목록
	std::vector<std::pair<int, Student*>> getAllStudentsIndexOrder(); // 리스트 키 순서대로 정렬된 학생 목록
};