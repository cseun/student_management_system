#pragma once
#include "Student.h"
#include "StudentStorage.h"

class StudentService
{
private:
	StudentStorage studentStorage;
public:
	bool isStudentIndexExist(const std::string& listKey) const;
	int searchStudentKey(const std::string& listKey) const;

	Student* searchStudent(const std::string& listKey);
	Student* addStudent(const std::string& listKey, const Student& student);
	Student* updateStudent(const std::string& originListKey, const std::string& newListKey, const Student& updateStudent);
	void deleteStudent(const std::string& listKey);
};