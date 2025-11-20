#include "pch.h"
#include <stdexcept>
#include "ExamInfoService.h"

bool ExamInfoService::isExamExist(const ExamInfo& examInfo) const
{
    return searchExamInfo(examInfo) != nullptr;
}

const ExamInfo* ExamInfoService::searchExamInfoById(int examId) const
{
    const auto& it = examInfoStorage.examInfoTable.find(examId);
    if (it != examInfoStorage.examInfoTable.end()) {
        return &(it->second);
    }
	return nullptr;
}
const ExamInfo* ExamInfoService::searchExamInfo(const ExamInfo& examInfo) const
{
    for (const auto& pair : examInfoStorage.examInfoTable) {
        if (pair.second.isSameExamInfo(examInfo))
        {
            return &pair.second;
        }
    }
    return nullptr;
}
const ExamInfo* ExamInfoService::searchExamInfo(int year, int semester, ExamType examType) const {
    for (const auto& pair : examInfoStorage.examInfoTable) {
        if (pair.second.getYear() == year &&
            pair.second.getSemester() == semester &&
            pair.second.getExamType() == examType)
        {
			return &(pair.second);
        }
    }
    return nullptr;
}

ExamInfo& ExamInfoService::updateExamInfo(int originExamId, const ExamInfo& updateExam)
{
	auto it = examInfoStorage.examInfoTable.find(originExamId);
    if (it == examInfoStorage.examInfoTable.end())
    {
		throw std::runtime_error("업데이트할 시험 ID에 해당하는 시험정보를 찾아오지 못하였습니다.");
    }

    ExamInfo& originExamInfo = it->second;
	originExamInfo.setYear(updateExam.getYear());   
	originExamInfo.setSemester(updateExam.getSemester());
	originExamInfo.setExamType(updateExam.getExamType());

	return originExamInfo;
}
ExamInfo& ExamInfoService::addExamInfo(const ExamInfo& examInfo)
{
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