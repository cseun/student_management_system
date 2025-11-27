#include "pch.h"
#include "StudentScoreInfoService.h"
#include "StudentScoreInfoController.h"


StudentScoreInfoController::StudentScoreInfoController(StudentScoreInfoService& service)
	: studentScoreInfoService(service)
{
}

void StudentScoreInfoController::validateStudentInfo(Student& student)
{
	// 학생 이름은 비어있을 수 없다.
	if (student.getName().empty()) {
		throw std::runtime_error("이름은 비어있을 수 없습니다.");
	}
	// 반, 번호, 학년은 1 이상이어야 한다.
	if (student.getGrade() < 1 || student.getClassNumber() < 1 || student.getStudentNumber() < 1) {
		throw std::runtime_error("학년, 반, 번호는 1 이상이어야 합니다.");
	}
}
void StudentScoreInfoController::validateExamInfo(ExamInfo& exam)
{
	// 시험은 2000년 이후부터 등록이 가능하다.
	if (exam.getYear() < 2000) {
		throw std::runtime_error("시험 년도는 2000년 이후여야 합니다.");
	}
	// 학기는 1 이하일 수 없다.
	if (exam.getSemester() < 1) {
		throw std::runtime_error("학기는 1 이상이어야 합니다.");
	}
}
void StudentScoreInfoController::validateStudentScore(StudentScore& score)
{
	// 성적은 0 이상이어야 한다.
	if (score.getKukScore() < 0 || score.getEngScore() < 0 || score.getMathScore() < 0 || score.getSocialScore() < 0 || score.getScienceScore() < 0) {
		throw std::runtime_error("성적은 0 이상이어야 합니다.");
	}
}
void StudentScoreInfoController::validateStudentScoreInfo(StudentScoreInfo& info)
{
	validateStudentInfo(info.getStudent());
	validateExamInfo(info.getExam());
	validateStudentScore(info.getScore());
}

std::vector<StudentScoreInfoRow> StudentScoreInfoController::getAllStudentScoreInfoRows()
{
	// 캐시가 비어있으면 갱신
	if (cachedStudentScoreInfos.empty()) resetCachedInfos();

	std::vector<StudentScoreInfoRow> infoRows;
	for (StudentScoreInfo& info : cachedStudentScoreInfos)
	{
		infoRows.push_back(studentScoreInfoToRow(info));
	}
	return infoRows;
}
void StudentScoreInfoController::resetCachedInfos()
{
	cachedStudentScoreInfos.clear();
	cachedStudentScoreInfos = studentScoreInfoService.getAllStudentScoreInfo();
	setRanks(cachedStudentScoreInfos);
}
void StudentScoreInfoController::setRanks(std::vector<StudentScoreInfo>& cachedInfos)
{
	// 시험 별로 등수가 매겨진다.

	// 임시 포인터 벡터
	std::map<int, std::vector<StudentScoreInfo*>> sortedPtrs;

	// cachedStudentScoreInfos를 포인터로 모아 정렬
	for (StudentScoreInfo& studentScoreInfo : cachedInfos)
	{
		int examId = studentScoreInfo.getExamId();
		sortedPtrs[examId].push_back(&studentScoreInfo);
	}

	// 그룹별로 rank 계산
	for (auto& group : sortedPtrs)
	{
		std::vector<StudentScoreInfo*>& list = group.second;

		// 점수 내림차순 정렬
		std::sort(list.begin(), list.end(), [](StudentScoreInfo* a, StudentScoreInfo* b) {
			return a->getTotalScore() > b->getTotalScore();
			}
		);

		int rank = 1;
		int prevScore = list[0]->getTotalScore();

		for (StudentScoreInfo*& infoPtr : list)
		{
			int currentScore = infoPtr->getTotalScore();
			if (prevScore != currentScore)
				rank++;

			infoPtr->setRank(rank);
			prevScore = currentScore;
		}
	}
}
//void filterAndsortBy();

StudentScoreInfoRow StudentScoreInfoController::studentScoreInfoToRow(StudentScoreInfo& info)
{
	try {
		Student& student = info.getStudent();
		ExamInfo& exam = info.getExam();
		StudentScore& score = info.getScore();

		StudentScoreInfoRow row;
		row.grade = std::to_string(student.getGrade());
		row.classNumber = std::to_string(student.getClassNumber());
		row.studentNumber = std::to_string(student.getStudentNumber());
		row.name = student.getName();
		row.examId = std::to_string(exam.getId());
		row.year = std::to_string(exam.getYear());
		row.semester = std::to_string(exam.getSemester());
		row.examType = std::to_string((int)exam.getExamType()); //ExamType : 1
		row.examTypeName = getExamName((ExamType)exam.getExamType());
		row.kukScore = std::to_string(score.getKukScore());
		row.engScore = std::to_string(score.getEngScore());
		row.mathScore = std::to_string(score.getMathScore());
		row.socialScore = std::to_string(score.getSocialScore());
		row.scienceScore = std::to_string(score.getScienceScore());
		row.totalScore = std::to_string(info.getTotalScore());
		row.rank = std::to_string(info.getRank());

		return row;
	} 
	catch (const std::exception e)
	{
		throw std::runtime_error(
			std::string("[학생 성적 정보 객체를 DTO 데이터로 변환 중 오류 발생]\n") + e.what()
		);
	}
}
StudentScoreInfo* StudentScoreInfoController::searchStudentScoreInfoInCache(StudentListKey& listKey, int examId) //수정가능
{
	for (StudentScoreInfo& info : cachedStudentScoreInfos)
	{
		if (info.getStudentListKey() == listKey && info.getExamId() == examId)
		{
			return &info;
		}
	}
	return nullptr;
}
StudentScoreInfoRow StudentScoreInfoController::addStudentScoreInfo(StudentScoreInfoRow& row)
{
	try {
		// 객체	변환
		Student student = Student(row);
		ExamInfo exam = ExamInfo(row);
		StudentScore score = StudentScore(row);
		StudentScoreInfo studentScoreInfo(student, score, exam);

		// 유효성 검사
		validateStudentScoreInfo(studentScoreInfo);

		// 서비스 호출
		StudentScoreInfo savedInfo = studentScoreInfoService.addStudentScoreInfo(studentScoreInfo);

		// 캐시 갱신
		resetCachedInfos();
		// 캐시에서 해당 학생 성적 정보 조회
		StudentScoreInfo* newInfo = searchStudentScoreInfoInCache(savedInfo.getStudentListKey(), savedInfo.getExamId());

		if (newInfo == nullptr)
			throw std::runtime_error("성적 정보 검색 실패");

		// row로 변환 후 반환
		return studentScoreInfoToRow(*newInfo);
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error(
			std::string("[학생 시험 성적 정보 추가 중 오류 발생]\n") + e.what()
		);
	}
}
StudentScoreInfoRow StudentScoreInfoController::updateStudentScoreInfo(std::string& listKey, int examId, StudentScoreInfoRow& updateRow)
{
	try {

		// 기존 학생 성적 정보
		StudentScoreInfo* originStudentScoreInfo = searchStudentScoreInfoInCache(StudentListKey::fromString(listKey), examId);
		Student originStudent = originStudentScoreInfo->getStudent();
		ExamInfo originExam = originStudentScoreInfo->getExam();

		// 업데이트할 학생 성적 정보
		Student updatedStudent(updateRow);
		ExamInfo updatedExam(updateRow);
		StudentScore updatedScore(updateRow);
		StudentScoreInfo updateInfo(updatedStudent, updatedScore, updatedExam);

		// 유효성 검사
		validateStudentScoreInfo(updateInfo);

		// 서비스 호출
		StudentScoreInfo savedInfo =
			studentScoreInfoService.updateStudentScoreInfo(originStudent, originExam, updateInfo);

		// 캐시 갱신
		resetCachedInfos();

		// 캐시에서 다시 검색
		StudentScoreInfo* newInfo = searchStudentScoreInfoInCache(savedInfo.getStudentListKey(), savedInfo.getExamId());

		if (newInfo == nullptr)
			throw std::runtime_error("수정된 학생 성적 정보를 찾을 수 없습니다.");

		return studentScoreInfoToRow(*newInfo);
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error(
			std::string("[학생 시험 성적 정보 업데이트 중 오류 발생]\n") + e.what()
		);
	}
}

void StudentScoreInfoController::deleteStudentScoreInfo(std::string& listKey, int examId)
{
	try {
		// Service 호출
		studentScoreInfoService.deleteStudentScoreInfo(StudentListKey::fromString(listKey), examId);

		// 캐시 갱신
		resetCachedInfos();
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error(
			std::string("[학생 시험 성적 정보 삭제 중 오류 발생]\n") + e.what()
		);
	}
}
