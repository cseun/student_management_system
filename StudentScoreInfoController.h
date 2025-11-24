#pragma once
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <algorithm>
#include "StudentScoreInfoRow.h"
#include "ExamInfo.h"
#include "Student.h"
#include "StudentScore.h"
#include "StudentScoreInfo.h"
#include "StudentScoreInfoService.h"

// 컨트롤러가 하는 일:
//	- 데이터 필터링
//	- 이벤트 별 처리 및 서비스 호출
//	- 뷰에 맞는 데이터 변환
// 컨트롤러의 주요 작업 흐름:
// 1. 뷰에서 row 를 전달받는다.
// 2. row 의 값을 필터링한다.
// 3. 값을 객체로 변환한다.
// 4. 해당하는 service(매개변수: 객체 혹은 객체의 값)를 실행한다.
// 5. 결과를 row로 변환하고 뷰로 반환한다.
class StudentScoreInfoController
{
private:
	std::vector<StudentScoreInfo> cachedStudentScoreInfos; //캐시는 조회 성능을 위해 메모리에 원본 데이터 형태로 보관 -> domain 저장
	StudentScoreInfoService studentScoreInfoService;
public:
	StudentScoreInfoController() = default;

	// 유효성 검사
	void validateStudentInfo(Student& student);
	void validateExamInfo(ExamInfo& exam);
	void validateStudentScore(StudentScore& score);
	void validateStudentScoreInfo(StudentScoreInfo& info);
	
	// 전체 조회 (listKey 순서 정렬, 캐싱)
	std::vector<StudentScoreInfoRow> getAllStudentScoreInfoRows();
	
	// 리스트 캐싱
	void resetCachedInfos();
	// 캐싱된 리스트 rank 재계산 (시험별)
	void setRanks(std::vector<StudentScoreInfo>& cachedInfos);
	// domain -> DTO 변환
	StudentScoreInfoRow studentScoreInfoToRow(StudentScoreInfo& info);
	// 캐싱된 리스트에서 학생 성적 조회
	StudentScoreInfo* StudentScoreInfoController::searchStudentScoreInfoInCache(
		StudentListKey& listKey,
		int examId
	);

	// CUD 작업
	StudentScoreInfoRow addStudentScoreInfo(StudentScoreInfoRow& row);
	StudentScoreInfoRow updateStudentScoreInfo(StudentScoreInfoRow& originRow, StudentScoreInfoRow& updateRow);
	void deleteStudentScoreInfo(StudentScoreInfoRow& row);

	// 학생 성적 csv 불러오기 버튼
	// 학생 성적 csv 저장하기 버튼

	// 처음에 프로그램을 시작할 때, 먼저 조회해서 리스트를 받아온다.
	// 뷰에서는 데이터 CUD 작업이 발생할 때를 제외하고는 불러온 리스트를 사용하여 처리한다.

};

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
	// 1. 학년-반-번호 순서대로 담겨져있다.
	// 2. 같은 시험 안에 순서대로 담는다.
	// 3. 시험은 year-semester-type 순서대로 담긴다.

	// 임시 포인터 벡터
	std::map<int, std::vector<StudentScoreInfo*>> sortedPtrs;

	// cachedStudentScoreInfos를 포인터로 모아 정렬
	for (StudentScoreInfo& studentScoreInfo : cachedInfos)
	{
		int examId = studentScoreInfo.getExamId();
		sortedPtrs[examId].push_back(& studentScoreInfo);
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
	Student& student = info.getStudent();
	ExamInfo& exam = info.getExam();
	StudentScore& score = info.getScore();

	StudentScoreInfoRow row;
	row.grade = std::to_string(student.getGrade());
	row.classNumber = std::to_string(student.getClassNumber());
	row.studentNumber = std::to_string(student.getStudentNumber());
	row.name = student.getName();
	row.year = std::to_string(exam.getYear());
	row.semester = std::to_string(exam.getSemester());
	row.examType = getExamName(exam.getExamType());
	row.kukScore = std::to_string(score.getKukScore());
	row.engScore = std::to_string(score.getEngScore());
	row.mathScore = std::to_string(score.getMathScore());
	row.socialScore = std::to_string(score.getSocialScore());
	row.scienceScore = std::to_string(score.getScienceScore());
	row.totalScore = std::to_string(info.getTotalScore());
	row.rank = std::to_string(info.getRank());
	return row;
}
StudentScoreInfo* StudentScoreInfoController::searchStudentScoreInfoInCache(StudentListKey& listKey,int examId) //수정가능
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
StudentScoreInfoRow StudentScoreInfoController::updateStudentScoreInfo(StudentScoreInfoRow& originRow, StudentScoreInfoRow& updateRow)
{
	// 기존 학생 성적 정보
	Student originStudent(originRow);
	ExamInfo originExam(originRow);

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
void StudentScoreInfoController::deleteStudentScoreInfo(StudentScoreInfoRow& row)
{
	Student student(row);
	ExamInfo examInfo(row);

	// Service 호출
	studentScoreInfoService.deleteStudentScoreInfo(student, examInfo);

	// 캐시 갱신
	resetCachedInfos();
}

