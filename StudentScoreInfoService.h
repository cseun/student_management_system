#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include "Student.h"
#include "StudentScore.h"
#include "StudentScoreInfo.h"
#include "ExamInfoService.h"
#include "StudentService.h"
#include "StudentScoreService.h"

class StudentScoreInfoService
{
private:
	ExamInfoService& examInfoService;
	StudentService& studentService;
	StudentScoreService& scoreService;

public:
	StudentScoreInfoService(
		StudentService& studentService,
		ExamInfoService& examInfoService,
		StudentScoreService& scoreService)
		: studentService(studentService), examInfoService(examInfoService), scoreService(scoreService) {}

	// StudentScoreRow 를 받아서 -> 컨트롤러에서 필요한걸 꺼내 -> 서비스로 넘겨서 처리
	bool isStudentScoreInfoExist(StudentListKey& listKey, ExamInfo& examInfo);
	std::vector<StudentScoreInfo> getAllStudentScoreInfo();
	std::vector<StudentScoreInfo> searchStudentScoreInfos(StudentListKey& listKey);
	StudentScoreInfo searchStudentScoreInfo(StudentListKey& listKey, ExamInfo& examInfo);
	StudentScoreInfo addStudentScoreInfo(StudentScoreInfo& studentScoreInfo);
	StudentScoreInfo updateStudentScoreInfo(
		Student& originStudent,
		ExamInfo& originExam,
		StudentScoreInfo& updateInfo
	);
	void deleteStudentScoreInfo(Student& student, ExamInfo& examInfo);
	void deleteStudentScoreInfo(StudentListKey& listKey, int examId);
};