#pragma once
#include <map>
#include <fstream>
#include <vector>
#include "student.h"
#include "fileService.h"

extern std::map<std::string, student> studentInfos;

// 학생 정보 리스트를 다루는 클래스
class StudentList
{
public:
	StudentList();
	
	struct StudentRow
	{
		CString name;
		CString grade;
		CString className;
		CString studentNumber;
		CString kukScore;
		CString engScore;
		CString mathScore;
		CString scienceScore;
		CString socialScore;
		CString totalScore;
		CString rank;

		// 벡터 변환
		std::vector<CString> toVector() const {
			return { name, grade, className, studentNumber, kukScore, engScore, mathScore, scienceScore, socialScore, totalScore, rank };
		}
	};

	// 리스트에서 다루는 학생 정보 - 목록
	std::vector<CString> getAttributeNames();
	// 리스트에서 다루는 학생 정보 - 내용
	StudentRow getAttributeRow(const student& student);
	std::vector<std::vector<CString>> getAttributeRows();

	// 리스트에서 학생 찾기, 추가, 수정, 삭제
	student* searchStudent(std::string studentNumber);
	bool addStudent(student student);
	bool updateStudent(student studentInfo);
	bool deleteStudent(std::string studentNumber);
	// 리스트 학생들 등수 업데이트
	void updateRank();

	// 엑셀 구현
	bool loadFromCSV(const std::string& filePath); 
	bool saveToCSV(std::string& filePath);

	// 에러 구현
	//void CStudentManagementDlg::showErrorDialog(errorStruct error);
};