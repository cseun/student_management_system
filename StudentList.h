#pragma once
#include <string>
#include <map>
#include <vector>
#include "Student.h"

// 학생 목록
class StudentList
{
private:
	// 학년,반,번호(studentListKey)로 학생(student)을 찾아갈 수 있도록 한다.
	std::map<std::string, std::string> studentIndexList; // 인덱스 개념 <studentListKey : studentIdx>
	std::map<std::string, Student> studentList; // 실제 리스트 <studentIdx : Student>

public:
	StudentList() = default;

	struct StudentListRow
	{
		std::string studentListKey;
		std::string name;
		std::string grade;
		std::string className;
		std::string studentNumber;

		std::vector<std::string> toVector() const {
			return { studentListKey, name, grade, className, studentNumber };
		}

		std::pair<std::string, StudentListRow> toPair() const {
			return { studentListKey, *this };
		}
	};
	// excel
	std::vector<std::string> getAttributeNames();
	std::map<std::string, StudentListRow> getAttriuteRows();

	std::string StudentList::makeStudentListKey(Student& student);// [학년]-[반]-[번호]
	std::string StudentList::searchStudentListKey(std::string studentKey);

	bool isStudentIndexExist(std::string studentListKey);
	std::string searchStudentKey(std::string studentListKey);

	void addStudentIndex(std::string studentListKey, std::string studentKey);
	void updateStudentIndex(std::string originStudentListKey, std::string studentListKey);
	void deleteStudentIndex(std::string studentListKey);

	Student* searchStudent(Student& student);
	Student* searchStudent(std::string studentListKey);

	Student* addStudent(Student& student);
	Student* updateStudent(Student& originStudent, Student& student);

	bool deleteStudent(Student& student);
	bool deleteStudent(std::string studentListKey);
};