#pragma once
#include "ExamInfoStorage.h"
class ExamInfoService
{
private:
	ExamInfoStorage examInfoStorage;
public:
	bool isExamExist(const ExamInfo& examInfo) const;
	// nullptr 반환 가능
	const ExamInfo* searchExamInfoById(int examId) const;
	const ExamInfo* searchExamInfo(const ExamInfo& examInfo) const;
	const ExamInfo* searchExamInfo(int year,int semester, ExamType examType) const;
	
	ExamInfo& updateExamInfo(int originExamId, const ExamInfo& updateExam);
	ExamInfo& addExamInfo(const ExamInfo& examInfo);
	void deleteExamInfo(int examId);
};