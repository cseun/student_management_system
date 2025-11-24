#include "pch.h"
#include <stdexcept>
#include <vector>
#include "StudentListKey.h"
#include "StudentStorage.h"
#include "Student.h"
#include "StudentService.h"

// ListKey -> StudentKey 매핑 조회 -> Student 객체 조회

// 학생 인덱스 존재여부
bool StudentService::isStudentIndexExist(StudentListKey& listKey)
{
	return searchStudentKey(listKey) != -1;
}
// 학생 키 존재여부
bool StudentService::isStudentKeyExist(int studentKey)
{
	return studentStorage.studentTable.find(studentKey) != studentStorage.studentTable.end();
}

// 학생 키 조회
int StudentService::searchStudentKey(StudentListKey& listKey)
{
	auto it = studentStorage.studentIndexList.find(listKey);
	if (it == studentStorage.studentIndexList.end()) {
		return -1;
	}
	return it->second;
}
// 학생 조회 (index 순서 정렬 목록)
std::vector<std::pair<int, Student*>> StudentService::getAllStudents()
{
	return studentStorage.getAllStudentsIndexOrder();
}
Student* StudentService::searchStudent(StudentListKey& listKey)
{
	int studentKey = searchStudentKey(listKey);
	auto it = studentStorage.studentTable.find(studentKey);
	if (it != studentStorage.studentTable.end())
	{
		return &(it->second);
	}
	return nullptr;
}
Student* StudentService::searchStudentByKey(int studentKey)
{
	auto it = studentStorage.studentTable.find(studentKey);
	if (it != studentStorage.studentTable.end())
	{
		// 학생 객체 주소 반환
		return &(it->second);
	}
	return nullptr;
}
// 학생 추가
Student& StudentService::addStudent(Student& student)
{
	Student newStudent = student;
	StudentListKey listKey = newStudent.getListKey();
	if(isStudentIndexExist(listKey))
		throw std::runtime_error("이미 존재하는 학생 키입니다.");

	if (newStudent.getKey() == -1)
		newStudent.setKey(); // 학생 키 설정

	int studentKey = newStudent.getKey();
	// 학생 리스트 추가
	studentStorage.studentTable[studentKey] = newStudent;
	// 인덱스 추가
	studentStorage.studentIndexList[newStudent.getListKey()] = studentKey;
	// 저장된 학생 객체 반환
	return studentStorage.studentTable[studentKey];
}
// 학생 업데이트
Student& StudentService::updateStudent(Student& targetStudent, Student& newStudent)
{
	// 동일한 학생 정보인지 확인
	if(targetStudent.isSameStudentInfo(newStudent))
	{
		return targetStudent;
	}

	// 새로운 학생의 리스트 키 생성
	StudentListKey originListKey = targetStudent.getListKey();
	StudentListKey newListKey = newStudent.getListKey();
	if(isStudentIndexExist(newListKey) && originListKey != newListKey)
	{
		throw std::runtime_error("업데이트할 학년, 반, 번호에 대한 학생이 이미 존재합니다.");
	}

	auto it = studentStorage.studentTable.find(targetStudent.getKey());
	if (it == studentStorage.studentTable.end())
	{
		throw std::runtime_error("학생 키에 해당하는 학생정보를 찾아오지 못하였습니다.");
	}
	Student& student = it->second;
	student.setStudent(newStudent);
	
	// 인덱스 업데이트
	studentStorage.studentIndexList.erase(originListKey);
	studentStorage.studentIndexList[newListKey] = student.getKey();
	// 실제 학생을 반환
	return student;
}
// 학생 삭제
void StudentService::deleteStudent(StudentListKey& listKey)
{
	// studentKey 조회
	int studentKey = searchStudentKey(listKey);
	if (studentKey == -1)
	{
		throw std::runtime_error("삭제할 학생의 키를 찾을 수 없습니다.");
	}
	// 인덱스 listKey 삭제
	if (studentStorage.studentIndexList.erase(listKey) == 0)
	{
		throw std::runtime_error("삭제할 학생 인덱스가 없습니다.");
	}

	// 학생 테이블 삭제
	if (studentStorage.studentTable.erase(studentKey) == 0)
	{
		throw std::runtime_error("삭제할 학생이 없습니다.");
	}
}