#include <stdexcept>
#include "Student.h"
#include "StudentService.h"

// 학생 인덱스 존재여부
bool StudentService::isStudentIndexExist(const std::string& listKey) const
{
	return studentStorage.studentIndexList.find(listKey) != studentStorage.studentIndexList.end();
}
// 학생 키 조회
int StudentService::searchStudentKey(const std::string& listKey) const
{
	auto it = studentStorage.studentIndexList.find(listKey);
	if (it == studentStorage.studentIndexList.end()) {
		throw std::runtime_error("존재하지 않는 학생키입니다.");
	}
	return it->second;
}
// 학생 조회
Student* StudentService::searchStudent(const std::string& listKey)
{
	int studentKey = searchStudentKey(listKey);
	// 학생 조회
	auto it = studentStorage.studentTable.find(studentKey);
	if (it != studentStorage.studentTable.end())
	{
		// 학생 객체 주소 반환
		return &(it->second);
	}
	return nullptr;
}
// 학생 추가
Student* StudentService::addStudent(const std::string& listKey, const Student& student)
{
	int id = student.getKey();
	// 학생 리스트 추가
	studentStorage.studentTable[id] = student;
	// 인덱스 추가
	studentStorage.studentIndexList[listKey] = id;
	// 저장된 학생 객체 주소 반환
	return &studentStorage.studentTable[id];
}
// 학생 업데이트
Student* StudentService::updateStudent(const std::string& originListKey, const std::string& newListKey, const Student& updateStudent)
{
	// 학생 조회
	Student* student = searchStudent(originListKey);
	// 실제 학생의 정보를 업데이트할 학생 정보로 변경한다.
	student->setStudent(updateStudent);
	// 인덱스 업데이트
	studentStorage.studentIndexList.erase(originListKey);
	studentStorage.studentIndexList[newListKey] = student->getKey();
	// 실제 학생의 주소를 반환
	return student;
}
// 학생 삭제
void StudentService::deleteStudent(const std::string& listKey)
{
	if (!studentStorage.studentIndexList.erase(listKey) > 0)
	{
		throw std::runtime_error("삭제할 학생 인덱스가 없습니다.");
	}

	int studentKey = searchStudentKey(listKey);
	if (!studentStorage.studentTable.erase(studentKey) > 0)
	{
		throw std::runtime_error("삭제할 학생이 없습니다.");
	}
}