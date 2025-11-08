
// StudentManagementDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "StudentManagement.h"
#include "StudentManagementDlg.h"
#include "afxdialogex.h"
#include "student.h"
#include "studentList.h"
#include <atlconv.h>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStudentManagementDlg 대화 상자



CStudentManagementDlg::CStudentManagementDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDENTMANAGEMENT_DIALOG, pParent)
	, m_name(_T(""))
	, m_grade(_T(""))
	, m_class(_T(""))
	, m_kukScore(_T(""))
	, m_mathScore(_T(""))
	, m_scienceScore(_T(""))
	, m_socialScore(_T(""))
	, m_totalScore(_T(""))
	, m_studentNumber(_T(""))
	, m_rank(_T(""))
	, m_engScore(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudentManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_GRADE, m_grade);
	DDX_Text(pDX, IDC_EDIT_CLASS, m_class);
	DDX_Text(pDX, IDC_EDIT_KUK, m_kukScore);
	DDX_Text(pDX, IDC_EDIT_ENG, m_engScore);
	DDX_Text(pDX, IDC_EDIT_MATH, m_mathScore);
	DDX_Text(pDX, IDC_EDIT_SCIENCE, m_scienceScore);
	DDX_Text(pDX, IDC_EDIT_SOCIAL, m_socialScore);
	DDX_Text(pDX, IDC_EDIT_SCORE, m_totalScore);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_studentNumber);
	DDX_Text(pDX, IDC_EDIT_RANK, m_rank);
	DDX_Control(pDX, IDC_LIST_STUDENT, m_studentInfoListCtl);
}

BEGIN_MESSAGE_MAP(CStudentManagementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CStudentManagementDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CStudentManagementDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CStudentManagementDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_FILE, &CStudentManagementDlg::OnClickedButtonLoadFile)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_FILE, &CStudentManagementDlg::OnClickedButtonSaveFile)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STUDENT, &CStudentManagementDlg::OnClickListStudent)
END_MESSAGE_MAP()


// CStudentManagementDlg 메시지 처리기

BOOL CStudentManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	createStudentInfoList();
	resetStudentList(); // 학생 리스트 초기화

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CStudentManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CStudentManagementDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CStudentManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// ===== 개인 주석 =====
// [오류 확인에 대해서]
//	1) 화면단에서 확인할 수 있는 오류는 확인하고 넘겨주기
//	2) 내부에서도 안전하게 재확인하기
// [구조에 대하여]
//	1) 뷰에서 사용자가 하는 모든 행동이 이벤트.
//		- 사용자가 하는 행동은 이벤트 함수로 추가
//	2) 이벤트 내에서 뷰단에 일어나는 일은 이벤트 내 정의 혹은 헬퍼 함수 분리
//		- 뷰단에서 일어나는 일(리스트 내용, 버튼 내용 변경 등)은 이벤트 내 정의
//		- 만약 반복적으로 일어나는 행동이면 헬퍼 함수로 분리
//	3) 내부적으로 일어나는 일은 클래스를 따로 정의
//		- 성적 총합 계산, 등수 재계산 등의 로직은 내부적으로 일어난 일
//		- 내부적인 일은 클래스로 분리하여 정의
// [작성 순서에 대하여]
//	1) 이벤트 먼저 등록하기
//		- 사용자가 사용하는 이벤트를 먼저 추가
//		- 이벤트 내에 어떤 동작이 일어나는지 메모
//	2) 이벤트 내 뷰단 동작 코딩하기
//		- 뷰단 외의 동작은 되었다는 가정하여 코딩
//	3) 클래스에 내부 동작 코딩하기
//		- 뷰단에서 가정한 부분을 클래스에서 함수를 불러와 대체

// 학생 추가
// 1) 컨트롤 학생 정보 읽고 학생 추가.
// 2) 추가가 되면 컨트롤 리셋
// 3) 추가가 안되면 추가 안된 이유 안내 (return {true/false, errorContext})
//		- 학생이 이미 존재하는가?
//		- 입력 값이 잘못되었는가?
//		- 학생 추가 중 문제가 발생하였는가?
// 4) 리스트 리셋
void CStudentManagementDlg::OnBnClickedButtonAdd()
{
	student student = getStudentInfo();

	if (studentList.addStudent(student)) {
		resetStudentInfo();
		resetStudentList();
	}
}

// 학생 정보 저장
// 1) 컨트롤 학생 정보 읽고 학생 업데이트
// 2) 업데이트가 되면 컨트롤 리셋
// 3) 업데이트가 안되면 업데이트 안된 이유 안내 (return {true/false, errorContext})
//		- 학생이 존재하지 않는가?
//		- 입력 값이 잘못되었는가?
//		- 학생 업데이트 중 문제가 발생하였는가?
// 4) 리스트 리셋
void CStudentManagementDlg::OnBnClickedButtonSave()
{
	student student = getStudentInfo();

	if (studentList.updateStudent(student)) {
		resetStudentInfo();
		resetStudentList();
	}
}

// 학생 정보 삭제
// 1) 컨트롤 학생 정보 읽고 학생 삭제
// 2) 삭제가 되면 컨트롤 리셋
// 3) 삭제가 안되면 삭제 안된 이유 안내 (return {true/false, errorContext})
//		- 학생이 존재하지 않는가?
//		- 학생 삭제 중 문제가 발생하였는가?
// 4) 리스트 리셋
void CStudentManagementDlg::OnBnClickedButtonDelete()
{
	student student = getStudentInfo();

	if (studentList.deleteStudent(student.studentNumber)) {
		resetStudentInfo();
		resetStudentList();
	}
}

// 학생 정보 컨트롤에서 가져오기
// 1) 컨트롤 학생 정보 가져오기
// 2) 입력값 확인하고 이상하면 이유 안내 (DDV추가), 에러 객체 추가, 에러 dialog 출력 함수 추가
//		- 학년, 성적 등이 숫자값인가?
//		- 점수가 0에서 100점 사이인가?
// 3) 학생 객체에 담아서 반환
// 3) 업데이트가 안되면 업데이트 안된 이유 안내 (return {result, errorStruct<errorCode, errorContext>})
//		- 학생이 존재하지 않는가?
//		- 입력 값이 잘못되었는가?
//		- 학생 업데이트 중 문제가 발생하였는가?
// 4) 리스트 리셋
student CStudentManagementDlg::getStudentInfo()
{
	UpdateData(TRUE); // 컨트롤 데이터를 멤버 변수에 저장

	std::string studentNumber = (CT2A)m_studentNumber;
	std::string name = (CT2A)m_name;
	std::string className = (CT2A)m_class;

	student student(
		studentNumber,
		name,
		_ttoi(m_grade),
		className,
		_ttoi(m_kukScore),
		_ttoi(m_engScore),
		_ttoi(m_mathScore),
		_ttoi(m_scienceScore),
		_ttoi(m_socialScore)
	);

	return student;
}

void CStudentManagementDlg::setStudentInfo(StudentList::StudentRow row)
{	
	m_studentNumber = row.studentNumber;
	m_name = row.name;
	m_class = row.className;
	m_grade = row.grade;
	m_class = row.className;
	m_kukScore = row.kukScore;
	m_engScore = row.engScore;
	m_mathScore = row.mathScore;
	m_scienceScore = row.scienceScore;
	m_socialScore = row.socialScore;

	m_totalScore = row.totalScore;
	m_rank = row.rank;

	TRACE(m_studentNumber);
	UpdateData(FALSE); // 멤버 변수를 컨트롤에 저장?
}


// 에러 정보 출력
// 1) 에러 객체(errorStruct<errorCode, errorContext>) 받아오기
// 2) 에러 dialog 출력
//void CStudentManagementDlg::showErrorDialog(errorStruct error) {};

// 학생 정보 컨트롤 리셋
// 1) 저장된 학생 정보값 지우기
// 2) 사용자 노출되는 정보값 지우기
void CStudentManagementDlg::resetStudentInfo()
{
	m_studentNumber = _T("");
	m_name = _T("");
	m_grade = _T("0");
	m_class = _T("");
	m_kukScore = _T("0");
	m_engScore = _T("0");
	m_mathScore = _T("0");
	m_scienceScore = _T("0");
	m_socialScore = _T("0");

	UpdateData(FALSE);
}

// 학생 성적 리스트 만들기
// 1) 성적 리스트 제작 (열)
//		- 학생 정보 수 만큼 열 제작
//		- 열의 길이는 균등 (이후 이름, 번호 등은 2배 처리)
// 2) DB 사용시 리스트 제작 후 학생 정보 불러와서 표시
void CStudentManagementDlg::createStudentInfoList()
{
	CRect rt; //리스트 컨트롤 크기를 가져올 변수
	m_studentInfoListCtl.GetWindowRect(&rt);
	m_studentInfoListCtl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); //리스트 컨트롤 선표시 및 item 선택시 한 행 전체 선택

	std::vector<CString> columns = studentList.getAttributeNames();
	int colCount = (int)columns.size();
	int colWidth = rt.Width() / colCount;

	for (int i = colCount - 1; i >= 0; --i)
	{
		m_studentInfoListCtl.InsertColumn(0, columns[i], LVCFMT_CENTER, colWidth);
	}

	//resetStudentList();
}

// 학생 리스트 선택 시 컨트롤에 데이터 표시
// 1) 선택된 항목에 대한 정보 불러오기
// 2) 불러온 정보를 컨트롤에 표시
void CStudentManagementDlg::OnClickListStudent(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 클릭된 위치 정보 가져오기
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int selectIdx = pNMItemActivate->iItem; // 클릭된 행 인덱스

	if (selectIdx >= 0) {
		CString studentNumber = m_studentInfoListCtl.GetItemText(selectIdx, 3);

		CT2A ascii(studentNumber);                // CString → const char*
		std::string studentNumStr(ascii);          // const char* → std::string

		// searchStudent()는 student* 반환
		student* pStudent = studentList.searchStudent(studentNumStr);
		
		if (pStudent != nullptr) {
			setStudentInfo(studentList.getAttributeRow(*pStudent));
		}
		else {
			AfxMessageBox(_T("학생 정보를 찾을 수 없습니다."));
		}
	}

	*pResult = 0;
}

// 학생 성적 리스트 새로고침
// 1) 학생들 등수 재계산
// 2) 학생들 정렬 (등록 순서대로)
// 3) 리스트 재표시
void CStudentManagementDlg::resetStudentList()
{
	if (studentInfos.empty()) {
		return;
	}

	m_studentInfoListCtl.DeleteAllItems();

	auto rows = studentList.getAttributeRows();

	for (int i = 0; i < rows.size(); ++i)
	{
		auto& row = rows[i];

		// 첫 번째 컬럼에 대한 항목 추가
		int index = m_studentInfoListCtl.InsertItem(i, row[0]);

		// 우측으로 나머지 서브 항목 채우기
		for (int j = 1; j < row.size(); ++j)
		{
			m_studentInfoListCtl.SetItemText(index, j, row[j]);
		}
	}
}

// 파일(학생 리스트) 불러오기
// 1) 기본적으로 제공하는 파일 라이브러리 사용
// 2) csv 파일만 불러오도록 제한
// 3) 파일 양식은 다운된 파일을 기준으로 한다.
//		- 가장 상단 행 제외 (목록)
//		- 정의된 열 순서대로 데이터 배치되어있을 것
// 4) 파일 불러오는 중 오류 발생시 오류 안내
void CStudentManagementDlg::OnClickedButtonLoadFile()
{
	CFileDialog dlg(TRUE, _T("csv"), nullptr,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||"),
		this);

	if (dlg.DoModal() != IDOK)
		return;

	CString filePath = dlg.GetPathName();
	CT2CA converted(filePath, CP_UTF8);
	std::string path(converted);

	if (studentList.loadFromCSV(path))
	{
		AfxMessageBox(_T("CSV 파일을 성공적으로 불러왔습니다."));
		resetStudentList(); // 리스트 초기화
	}
	else
	{
		AfxMessageBox(_T("CSV 파일을 불러오는 중 오류가 발생했습니다."));
	}
}

// 파일(학생 리스트) 저장하기
// 1) 기본적으로 제공하는 파일 라이브러리 사용
// 2) csv 파일로 저장
// 3) 파일 양식
//		- 가장 상단 행은 목록
//		- 정의된 열 순서대로 데이터 배치
// 4) 파일 저장 중 오류 발생시 오류 안내
void CStudentManagementDlg::OnClickedButtonSaveFile()
{
	CFileDialog dlg(FALSE, _T("csv"), _T("학생정보.csv"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||"),
		this);

	if (dlg.DoModal() != IDOK)
		return;

	CString filePath = dlg.GetPathName();

	CT2CA pszConvertedAnsiString(filePath);
	std::string path(pszConvertedAnsiString);

	if (studentList.saveToCSV(path))
		AfxMessageBox(_T("CSV 파일로 저장되었습니다."));
	else
		AfxMessageBox(_T("CSV 저장 중 오류가 발생했습니다."));
}
