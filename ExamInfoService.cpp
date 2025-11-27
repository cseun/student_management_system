#include "pch.h"
#include <stdexcept>
#include "ExamInfoService.h"

bool ExamInfoService::isExamInfoExist(ExamInfo& examInfo)
{
    return searchExamInfo(examInfo) != nullptr;
}

ExamInfo* ExamInfoService::searchExamInfoById(int examId)
{
    auto it = examInfoStorage.examInfoTable.find(examId);
    if (it != examInfoStorage.examInfoTable.end()) {
        return &(it->second);
    }
	return nullptr;
}
ExamInfo* ExamInfoService::searchExamInfo(ExamInfo& examInfo)
{
    for (auto& pair : examInfoStorage.examInfoTable) {
        if (pair.second.isSameExamInfo(examInfo))
        {
            return &(pair.second);
        }
    }
    return nullptr;
}
ExamInfo* ExamInfoService::searchExamInfo(int year, int semester, ExamType examType)
{
    for (auto& pair : examInfoStorage.examInfoTable) 
    {
        if (pair.second.getYear() == year &&
            pair.second.getSemester() == semester &&
            pair.second.getExamType() == examType)
        {
			return &(pair.second);
        }
    }
    return nullptr;
}

ExamInfo& ExamInfoService::updateExamInfo(int originExamId, ExamInfo& updateExam)
{
    // 업데이트할 시험 정보가 기존과 같으면 그대로 반환
    ExamInfo* targetExam = searchExamInfoById(originExamId);
    if (targetExam->isSameExamInfo(updateExam))
    {
        return *targetExam;
    }
    
    // 업데이트할 시험이 이미 존재하면 해당 시험으로 변경
    ExamInfo* searchedUpdateExam = searchExamInfo(updateExam);
    if (searchedUpdateExam != nullptr)
    {
        return *searchedUpdateExam;
    }

    // 업데이트할 시험이 존재하지 않으면 새로 생성
    return addExamInfo(updateExam);
}
ExamInfo& ExamInfoService::addExamInfo(ExamInfo& examInfo)
{
    examInfo.setId();
    examInfoStorage.examInfoTable[examInfo.getId()] = examInfo;
    return examInfoStorage.examInfoTable[examInfo.getId()];
}
void ExamInfoService::deleteExamInfo(int examId)
{
    if (examInfoStorage.examInfoTable.erase(examId) == 0)
    {
        throw std::runtime_error("시험 ID에 해당하는 시험정보를 삭제하기 못하였습니다.");
	}
}

void ExamInfoService::deleteAllExams()
{
    examInfoStorage.examInfoTable.clear();
}