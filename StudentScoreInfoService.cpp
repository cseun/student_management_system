#include "pch.h"
#include "StudentScoreInfoService.h"

bool StudentScoreInfoService::isStudentScoreInfoExist(
	StudentListKey& listKey,
	ExamInfo& examInfo
)
{
	int studentKey = studentService.searchStudentKey(listKey);
	if (studentKey == -1) return false;
	int examId = examInfo.getId();
	if (examId == -1) return false;

	return scoreService.isStudentScoreExist(studentKey, examId);
}

// 모든 학생 성적 정보 가져오기 (Eager Loading)
std::vector<StudentScoreInfo> StudentScoreInfoService::getAllStudentScoreInfo()
{
	std::vector<StudentScoreInfo> studentScoreInfos;

	// 모든 학생 정보(학년-반-번호 순서)
	std::vector<std::pair<int, Student*>>& allStudents = studentService.getAllStudents();
	// 모든 성적 정보
	std::map<int, std::vector<StudentScore>>& allScores = scoreService.getAllStudentScores();
	// 학생 번호 기준으로 합치기
	for (auto& pair : allStudents)
	{
		int studentKey = pair.first;
		Student* student = pair.second;

		auto scoreIt = allScores.find(studentKey);
		if (scoreIt != allScores.end())
		{
			std::vector<StudentScore>& scores = scoreIt->second;
			for (StudentScore& score : scores)
			{
				int examId = score.getExamId();
				ExamInfo* exam = examInfoService.searchExamInfoById(examId);
				if (exam == nullptr)
				{
					throw std::runtime_error("성적 정보를 불러올 수 없습니다.");
				}
				StudentScoreInfo info(*student, score, *exam);
				studentScoreInfos.push_back(info);
			}
		}
	}
	return studentScoreInfos;
}
// 특정 학생 성적 정보 가져오기
std::vector<StudentScoreInfo> StudentScoreInfoService::searchStudentScoreInfos(StudentListKey& listKey)
{
	std::vector<StudentScoreInfo> studentScoreInfos;

	// 학생 정보
	int studentKey = studentService.searchStudentKey(listKey);
	Student* searchedStudent = nullptr;
	if (studentKey == -1)
		searchedStudent = studentService.searchStudentByKey(studentKey);
	if (searchedStudent == nullptr)
		throw std::runtime_error("저장된 학생 정보에 문제가 있습니다. -1");

	// 성적 정보
	std::vector<StudentScore>* scores = scoreService.searchStudentScores(studentKey);
	if (scores->empty()) {
		return studentScoreInfos;
	}

	for (StudentScore& score : *scores)
	{
		int totalScore = score.getTotalScore();
		int examId = score.getExamId();
		ExamInfo* examInfo = examInfoService.searchExamInfoById(examId);

		studentScoreInfos.push_back(StudentScoreInfo(*searchedStudent, score, *examInfo));
	}


	return studentScoreInfos;
}
StudentScoreInfo StudentScoreInfoService::searchStudentScoreInfo(StudentListKey& listKey, ExamInfo& examInfo)
{
	// 학생 정보
	int studentKey = studentService.searchStudentKey(listKey);
	Student* searchedStudent = studentService.searchStudentByKey(studentKey);
	if (searchedStudent == nullptr)
		throw std::runtime_error("저장된 학생 정보에 문제가 있습니다. -1");

	// 성적 정보
	int totalScore = 0;
	StudentScore* score = scoreService.searchStudentExamScore(studentKey, examInfo.getId());
	if (score == nullptr)
		throw std::runtime_error("저장된 학생 성적 정보가 없습니다.");

	StudentScoreInfo studentScoreInfo(*searchedStudent, *score, examInfo);
	return studentScoreInfo;
}
StudentScoreInfo StudentScoreInfoService::addStudentScoreInfo(StudentScoreInfo& studentScoreInfo)
{
	// 학생 시험 정보가 이미 존재하는지 확인
	Student student = studentScoreInfo.getStudent();
	ExamInfo examInfo = studentScoreInfo.getExam();
	StudentScore score = studentScoreInfo.getScore();

	StudentListKey listKey = studentScoreInfo.getStudentListKey();
	if (isStudentScoreInfoExist(listKey, examInfo))
	{
		throw std::runtime_error("이미 존재하는 학생과 시험 정보입니다.");
	}

	// 시험 정보가 존재하지 않으면 시험 정보 생성
	ExamInfo* searchedExam = examInfoService.searchExamInfo(examInfo);
	if (searchedExam == nullptr)
	{
		examInfo = examInfoService.addExamInfo(examInfo);
	}
	else
	{
		examInfo = *searchedExam;
	}

	// 학생이 존재하지 않으면 학생 생성
	Student* searchedStudent = studentService.searchStudent(listKey);
	if (searchedStudent == nullptr)
	{
		student = studentService.addStudent(student);
	}
	else
	{
		student = *searchedStudent;
	}

	score.setExamId(examInfo.getId());
	score.setStudentKey(student.getKey());
	// 성적 정보 추가
	score = scoreService.addStudentScore(score);

	return StudentScoreInfo(student, score, examInfo);
}

StudentScoreInfo StudentScoreInfoService::updateStudentScoreInfo(
	Student& originStudent,
	ExamInfo& originExam,
	StudentScoreInfo& updateInfo
)
{
	// 기존 학생 정보
	Student* targetStudent = studentService.searchStudent(originStudent.getListKey());
	if (targetStudent == nullptr)
	{
		throw std::runtime_error("업데이트할 학생이 존재하지 않습니다.");
	}
	// 기존 시험 정보
	ExamInfo* targetExam = examInfoService.searchExamInfo(originExam);
	if (targetExam == nullptr)
	{
		throw std::runtime_error("존재하지 않는 시험 정보입니다.");
	}

	// 학생 정보 업데이트
	Student updatedStudent = studentService.updateStudent(*targetStudent, updateInfo.getStudent());
	// 시험 정보 업데이트
	ExamInfo updatedExam = examInfoService.updateExamInfo(targetExam->getId(), updateInfo.getExam());

	updateInfo.getScore().setStudentKey(updatedStudent.getKey());
	updateInfo.getScore().setExamId(updatedExam.getId());
	// 성적 정보 업데이트
	StudentScore updatedScore = scoreService.updateStudentScore(targetStudent->getKey(), targetExam->getId(), updateInfo.getScore());

	return StudentScoreInfo(updatedStudent, updatedScore, updatedExam);
}

void StudentScoreInfoService::deleteStudentScoreInfo(Student& student, ExamInfo& examInfo)
{
	// 학생 조회
	Student* searchedStudent = studentService.searchStudent(student.getListKey());
	if (searchedStudent == nullptr)
		throw std::runtime_error("존재하지 않는 학생입니다.");
	ExamInfo* searchedExamInfo = examInfoService.searchExamInfo(examInfo);
	if (searchedExamInfo == nullptr)
		throw std::runtime_error("존재하지 않는 시험 정보입니다.");
	// 학생 성적 삭제
	scoreService.deleteStudentScore(searchedStudent->getKey(), examInfo.getId());
}

void StudentScoreInfoService::deleteStudentScoreInfo(StudentListKey& listKey, int examId)
{
	// 학생 조회
	Student* searchedStudent = studentService.searchStudent(listKey);
	if (searchedStudent == nullptr)
		throw std::runtime_error("존재하지 않는 학생입니다.");
	ExamInfo* searchedExamInfo = examInfoService.searchExamInfoById(examId);
	if (searchedExamInfo == nullptr)
		throw std::runtime_error("존재하지 않는 시험 정보입니다.");

	int studentKey = searchedStudent->getKey();
	// 학생 성적 삭제
	scoreService.deleteStudentScore(studentKey, examId);

	// 학생 성적이 존재하지 않는다면 학생 삭제
	if (scoreService.searchStudentScores(studentKey) == nullptr)
	{
		studentService.deleteStudent(studentKey);
	}
}

void StudentScoreInfoService::deleteAllStudentScoreInfos()
{
	// 데이터 전체 삭제
	scoreService.deleteAllScores();
	examInfoService.deleteAllExams();
	studentService.deleteAllStudents();
}