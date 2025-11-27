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
	StudentScoreInfoService& studentScoreInfoService;
public:
	StudentScoreInfoController(StudentScoreInfoService& service);

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
	StudentScoreInfoRow updateStudentScoreInfo(std::string& listKey, int examId, StudentScoreInfoRow& updateRow);
	void deleteStudentScoreInfo(std::string& listKey, int examId);

	// 학생 성적 csv 불러오기 버튼
	// 학생 성적 csv 저장하기 버튼

	// 처음에 프로그램을 시작할 때, 먼저 조회해서 리스트를 받아온다.
	// 뷰에서는 데이터 CUD 작업이 발생할 때를 제외하고는 불러온 리스트를 사용하여 처리한다.

};
