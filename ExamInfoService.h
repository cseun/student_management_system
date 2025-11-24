#pragma once
#include "ExamInfoStorage.h"
class ExamInfoService
{
private:
	ExamInfoStorage examInfoStorage;
public:
	bool isExamInfoExist(ExamInfo& examInfo);
	// nullptr 반환 가능
	ExamInfo* searchExamInfoById(int examId);
	ExamInfo* searchExamInfo(ExamInfo& examInfo);
	ExamInfo* searchExamInfo(int year,int semester, ExamType examType);
	
	ExamInfo& updateExamInfo(int originExamId, ExamInfo& updateExam);
	ExamInfo& addExamInfo(ExamInfo& examInfo);
	void deleteExamInfo(int examId);
};