#pragma once
#include <afx.h>

class fileService {
	//public:
	//fileService();
	//void loadCsvFile();
	//void saveCsvFile();

	//void loadCsvFile()
	//{
	//	CStdioFile file;
	//	CString line;

	//	if (!file.Open(_T("students.csv"), CFile::modeRead | CFile::typeText)) {
	//		AfxMessageBox(_T("파일을 열 수 없습니다."));
	//		return;
	//	}

	//	while (file.ReadString(line)) {
	//		AfxMessageBox(line); // 예시: 한 줄씩 읽기
	//	}

	//	file.Close();

	//};

	//void saveCsvFile(열, 리스트) {
	//	CStdioFile file;
	//	if (!file.Open(_T("students.csv"), CFile::modeCreate | CFile::modeWrite | CFile::typeText)) {
	//		AfxMessageBox(_T("CSV 파일을 저장할 수 없습니다."));
	//		return;
	//	}

	//	file.WriteString(_T("학번,이름,점수\n"));
	//	file.WriteString(_T("2024001,홍길동,95\n"));
	//	file.Close();
	//}
};
