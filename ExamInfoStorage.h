#pragma once
#include <map>
#include "ExamInfo.h"
// 학생 성적 목록 저장소
class ExamInfoStorage
{
private:

public:
	ExamInfoStorage() = default;

	// 시험 id : 시험 정보 객체 examInfoTable
	std::map<int, ExamInfo> examInfoTable;
};