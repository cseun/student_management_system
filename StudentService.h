#pragma once
#include <string>
#include <vector>
#include <map>
#include "Student.h"
#include "StudentStorage.h"

class StudentService
{
private:
	StudentStorage studentStorage;
public:
	bool isStudentIndexExist(const std::string& listKey) const;
	bool isStudentKeyExist(int studentKey) const;
	int searchStudentKey(const std::string& listKey) const;

	const std::map<int, Student>& getAllStudents() const;
	const Student* searchStudent(const std::string& listKey) const;
	const Student* searchStudentByKey(int studentKey) const;
	
	Student& addStudent(const Student& student);
	Student& updateStudent(const std::string& originListKey, const Student& newStudent);
	void deleteStudent(const std::string& listKey);
};