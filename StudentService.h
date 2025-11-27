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
	bool isStudentIndexExist(StudentListKey& listKey);
	bool isStudentKeyExist(int studentKey);
	int searchStudentKey(StudentListKey& listKey);

	std::vector<std::pair<int, Student*>> getAllStudents();
	Student* searchStudent(StudentListKey& listKey);
	Student* searchStudentByKey(int studentKey);
	
	Student& addStudent(Student& student);
	Student& updateStudent(Student& targetStudent, Student& newStudent);
	void deleteStudent(StudentListKey& listKey);
	void deleteAllStudents();
};