#include "ExamInfoService.h"

bool ExamInfoService::isExamExist(const ExamInfo& examInfo)
{
    for (const auto& pair : examInfoStorage.examInfoTable) {
        if (pair.second.isSameExamInfo(examInfo))
        {
            return true;
        }
    }
    return false;
}
ExamInfo* ExamInfoService::searchExamInfo(const ExamInfo& examInfo)
{
    for (auto& pair : examInfoStorage.examInfoTable) {
        if (pair.second.isSameExamInfo(examInfo))
        {
            return &pair.second;
        }
    }
    return nullptr;
}
ExamInfo* ExamInfoService::addExamInfo(const ExamInfo& examInfo)
{
    examInfoStorage.examInfoTable.insert(std::make_pair(
        examInfo.getId(),
        examInfo
	));
}
bool ExamInfoService::deleteExamInfo(const int examId)
{
    return examInfoStorage.examInfoTable.erase(examId) > 0;
}