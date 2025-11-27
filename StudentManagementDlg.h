
// StudentManagementDlg.h: 헤더 파일
#pragma once
#include "Convert.h"
#include "studentScoreInfoController.h"


// CStudentManagementDlg 대화 상자
class CStudentManagementDlg : public CDialogEx
{
// 생성입니다.
public:
	CStudentManagementDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENTMANAGEMENT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTime now;

	CListCtrl m_studentInfoListCtl;
	CString m_name;
	CString m_grade;
	CString m_class;
	CString m_studentNumber;
	
	int m_year;
	int m_semester;
	CString m_exam_type;

	int m_kukScore;
	int m_engScore;
	int m_mathScore;
	int m_scienceScore;
	int m_socialScore;
	int m_totalScore;
	int m_rank;
	CComboBox m_exam_type_ctl;

	StudentService studentService;
	ExamInfoService examService;
	StudentScoreService scoreService;
	StudentScoreInfoService scoreInfoService;
	StudentScoreInfoController studentScoreInfoController; 

	void resetStudentEditCtl(); // 학생 정보 입력란 리셋

	StudentScoreInfoRow getRowData(); // 뷰 학생 정보 -> DTO 객체
	void setStudentData(StudentScoreInfoRow& row); // DTO 객체 -> 뷰 학생 정보 표시
	void createStudentScoreList(); // 학생 성적 리스트 생성
	void reloadStudentScoreList(); // 학생 성적 리스트 새로고침
	void loadExamTypeComboBox(); // 시험 선택 박스 로드
	void selectExamType(ExamType examType);
	void getSelectedHiddenValues(std::string& listKeyStr, int& examId); // 리스트에서 선택된 항목의 숨겨진 키값 가져오기

	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSave();
	

	afx_msg void OnBnClickedButtonDelete();


	afx_msg void OnClickedButtonLoadFile();
	afx_msg void OnClickedButtonSaveFile();
	
	afx_msg void OnClickListStudent(NMHDR* pNMHDR, LRESULT* pResult);


	
	CButton m_button_save;
	CButton m_button_delete;
};
