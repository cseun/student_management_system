
// StudentManagementDlg.h: 헤더 파일
//

#pragma once
#include "student.h"
#include "StudentList.h"


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
	StudentList studentList;
	CString m_name;
	CString m_grade;
	CString m_class;
	CString m_kukScore;
	CString m_mathScore;
	CString m_scienceScore;
	CString m_socialScore;
	CString m_totalScore;
	CString m_studentNumber;
	CString m_rank;
	CListCtrl m_studentInfoListCtl;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonDelete();
	student getStudentInfo();
	void setStudentInfo(StudentList::StudentRow row);
	void resetStudentInfo();
	void createStudentInfoList();
	void resetStudentList();
	afx_msg void OnClickedButtonLoadFile();
	afx_msg void OnClickedButtonSaveFile();
	CString m_engScore;
	afx_msg void OnClickListStudent(NMHDR* pNMHDR, LRESULT* pResult);
};
