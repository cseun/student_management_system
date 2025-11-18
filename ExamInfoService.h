#pragma once
#include "ExamInfoStorage.h"
class ExamInfoService
{
private:
	ExamInfoStorage examInfoStorage;
public:
	bool isExamExist(const ExamInfo& examInfo);
	ExamInfo* searchExamInfo(const ExamInfo& examInfo);
	ExamInfo* addExamInfo(const ExamInfo& examInfo);
	bool deleteExamInfo(const int examId);
};