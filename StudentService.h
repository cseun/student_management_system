#pragma once
#include <string>
#include <vector>
#include <map>
#include "StudentListKey.h"
#include "Student.h"
#include "StudentStorage.h"

class StudentService
{
private:
	StudentStorage studentStorage;
public:
	bool isStudentIndexExist(const StudentListKey& listKey) const;
	bool isStudentKeyExist(int studentKey) const;
	int searchStudentKey(const StudentListKey& listKey) const;

	std::vector<std::pair<int, const Student*>> getAllStudents() const;
	const Student* searchStudent(const StudentListKey& listKey) const;
	const Student* searchStudentByKey(int studentKey) const;
	
	Student& addStudent(const Student& student);
	Student& updateStudent(const StudentListKey& originListKey, const Student& newStudent);
	void deleteStudent(const StudentListKey& listKey);
};