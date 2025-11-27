
// StudentManagementDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "StudentManagement.h"
#include "StudentManagementDlg.h"
#include "Convert.h"
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
	, scoreInfoService(studentService, examService, scoreService)
	, studentScoreInfoController(scoreInfoService)
	, now(CTime::GetCurrentTime())
	, m_name(_T(""))
	, m_grade(_T(""))
	, m_class(_T(""))
	, m_studentNumber(_T(""))
	, m_kukScore(0)
	, m_mathScore(0)
	, m_scienceScore(0)
	, m_socialScore(0)
	, m_totalScore(0)
	, m_rank(0)
	, m_engScore(0)
	, m_year(now.GetYear())
	, m_semester(1)
	, m_exam_type(_T(""))
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
	DDV_MinMaxInt(pDX, m_kukScore, 0, 100);
	DDV_MinMaxInt(pDX, m_engScore, 0, 100);
	DDV_MinMaxInt(pDX, m_mathScore, 0, 100);
	DDV_MinMaxInt(pDX, m_scienceScore, 0, 100);
	DDV_MinMaxInt(pDX, m_socialScore, 0, 100);
	DDX_Text(pDX, IDC_EDIT_YEAR, m_year);
	DDX_Text(pDX, IDC_EDIT_SEMESTER, m_semester);
	DDV_MinMaxInt(pDX, m_semester, 1, 3);
	DDX_CBString(pDX, IDC_COMBO_EXAM_TYPE, m_exam_type);
	DDX_Control(pDX, IDC_COMBO_EXAM_TYPE, m_exam_type_ctl);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_button_save);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_button_delete);
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
	createStudentScoreList(); // 리스트 생성
	reloadStudentScoreList(); // 리스트 초기화
	loadExamTypeComboBox(); // 시험 항목 선택 박스 초기화

	m_button_save.EnableWindow(FALSE); // 수정 버튼 비활성화 
	m_button_delete.EnableWindow(FALSE); // 삭제 버튼 비활성화

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

// ===== 개인 정리 =====
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

// 학생 성적 리스트 뷰 생성 (열)
void CStudentManagementDlg::createStudentScoreList()
{
	// 성적 리스트 제작 (열)
	CRect rt; //리스트 컨트롤 크기를 가져올 변수
	m_studentInfoListCtl.GetWindowRect(&rt);
	m_studentInfoListCtl.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_studentInfoListCtl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); //리스트 컨트롤 선표시 및 item 선택시 한 행 전체 선택

	std::vector<std::string> attributeNames = ::StudentScoreInfoRow::getAttributeNames();
	std::vector<int> attributeSizes = ::StudentScoreInfoRow::getAttributeSizes();

	int totalSize = 0;
	for (int size : attributeSizes)
	{
		totalSize += size;
	}
	int colWidth = rt.Width() / totalSize;

	// 식별을 위해 숨겨진 항목 - 학생 리스트 키
	m_studentInfoListCtl.InsertColumn(0, L"hiddenKey", LVCFMT_LEFT, 0);
	// 식별을 위해 숨겨진 항목 - 성적 ID
	m_studentInfoListCtl.InsertColumn(1, L"hiddenExamId", LVCFMT_LEFT, 0);

	for (int i = 0; i < attributeNames.size(); i++)
	{
		CString attributeName = Convert::StdStringToCString(attributeNames[i]);
		int width = colWidth * attributeSizes[i];

		m_studentInfoListCtl.InsertColumn(i + 2, attributeName, LVCFMT_CENTER, width);
	}
}

// 학생 성적 리스트 뷰 새로고침 (내용)
void CStudentManagementDlg::reloadStudentScoreList()
{
	// 학생 리스트 뷰 비우기
	if (m_studentInfoListCtl.GetItemCount() > 0)
	{
		m_studentInfoListCtl.DeleteAllItems();
	}

	// 리스트 데이터 불러오기
	std::vector<StudentScoreInfoRow> studenScoreRows = studentScoreInfoController.getAllStudentScoreInfoRows();

	// 리스트 재표시
	if (studenScoreRows.empty()) return;
	for (int i = 0; i < studenScoreRows.size(); ++i)
	{
		StudentScoreInfoRow& studentScoreRow =  studenScoreRows[i];
		// 식별 데이터 추출
		std::string listKeyStr = studentScoreRow.getListKey().toString();
		std::string examIdStr = studentScoreRow.getExamId();

		// row 생성
		auto row = studentScoreRow.toVector();
		
		// 빈 item 추가 (행 추가)
		int rowIndex = m_studentInfoListCtl.InsertItem(i, L"");

		// 숨겨진 키 - 학생 (0번 컬럼)
		m_studentInfoListCtl.SetItemText(rowIndex, 0, Convert::StdStringToCString(listKeyStr));
		// 숨겨진 키 - 시험 (1번 컬럼)
		m_studentInfoListCtl.SetItemText(rowIndex, 1, Convert::StdStringToCString(examIdStr));

		// 우측으로 나머지 서브 항목 채우기
		for (int j = 0; j < row.size(); ++j)
		{
			m_studentInfoListCtl.SetItemText(rowIndex, j + 2, Convert::StdStringToCString(row[j]));
		}
	}
}

// 시험 콤보 박스 로드
void CStudentManagementDlg::loadExamTypeComboBox()
{
	for (ExamType type : getExamTypes())
	{
		std::string examTypeStr = getExamName(type);
		CString examTypeCStr = Convert::StdStringToCString(examTypeStr);
		// 콤보박스에 문자열 추가
		int index = m_exam_type_ctl.AddString(examTypeCStr);
		// 항목에 enum 값 저장
		m_exam_type_ctl.SetItemData(index, (DWORD_PTR)type);
	}

	m_exam_type_ctl.SetCurSel(0);
}

/*
 학생 정보 컨트롤에서 가져오기
 1) 뷰에서 학생과 성적 정보를 가져온다.
 2) 입력값을 확인한다.
	- DDV로 뷰 데이터 제한
	- 내부에서 데이터 재확인
		- 성적이 숫자로 변환하는데 문제가 생기면 오류 반환
		- 점수가 0에서 100점 사이가 아니면 오류 반환
 3) 학생 객체에 담아서 반환
 4) 업데이트가 안되면 업데이트 안된 이유 안내 (return {result, errorStruct<errorCode, errorContext>})
		- 학생이 존재하지 않는가?
		- 입력 값이 잘못되었는가?
		- 학생 업데이트 중 문제가 발생하였는가?
 5) 리스트 리셋
 6) 에러 객체 추가, 에러 dialog 출력 함수 추가
 7) TODO 이후에 학생 성적 정보가 여러개가 될 수 있으니, 학생으로 조회하고 여러개면 성적정보로 조회해야되나
 */

 // 뷰 학생 정보 -> DTO 객체
StudentScoreInfoRow CStudentManagementDlg::getRowData()
{
	UpdateData(TRUE); // 컨트롤 데이터를 멤버 변수에 저장
	if (m_name == "" || m_grade == "" || m_class == "" || m_studentNumber == "")
	{
		throw std::runtime_error("학생 이름, 학년, 반, 번호 값 입력은 필수입니다.");
	}
	StudentScoreInfoRow row;
	row.name = Convert::CStringToStdString(m_name);
	row.grade = Convert::CStringToStdString(m_grade);
	row.classNumber = Convert::CStringToStdString(m_class);
	row.studentNumber = Convert::CStringToStdString(m_studentNumber);

	row.year = std::to_string(m_year);
	row.semester = std::to_string(m_semester);

	//CString examTypeText;
	int examIndex = m_exam_type_ctl.GetCurSel();
	if (examIndex == CB_ERR)
	{
		throw std::runtime_error("시험 종류를 선택은 필수입니다.");
	}
	//m_exam_type_ctl.GetLBText(examIndex, examTypeText);
	//row.examType = Convert::CStringToStdString(examTypeText);
	row.examType = std::to_string((int)m_exam_type_ctl.GetItemData(examIndex));

	row.kukScore = std::to_string(m_kukScore);
	row.engScore = std::to_string(m_engScore);
	row.mathScore = std::to_string(m_mathScore);
	row.socialScore = std::to_string(m_socialScore);
	row.scienceScore = std::to_string(m_scienceScore);

	return row;
}

// DTO 객체 -> 뷰 학생 정보 표시
void CStudentManagementDlg::setStudentData(StudentScoreInfoRow& row)
{
	try {
		m_name = Convert::StdStringToCString(row.name);
		m_class = Convert::StdStringToCString(row.classNumber);
		m_grade = Convert::StdStringToCString(row.grade);
		m_studentNumber = Convert::StdStringToCString(row.studentNumber);
		m_year = stoi(row.year);
		m_semester = stoi(row.semester);

		ExamType examType = (ExamType)(std::stoi(row.examType));
		selectExamType(examType);

		m_kukScore = stoi(row.kukScore);
		m_engScore = stoi(row.engScore);
		m_mathScore = stoi(row.mathScore);
		m_scienceScore = stoi(row.scienceScore);
		m_socialScore = stoi(row.socialScore);
		m_totalScore = stoi(row.totalScore);
		m_rank = stoi(row.rank);

		UpdateData(FALSE);
	} 
	catch (const std::exception e)
	{
		std::string msg = "[학생 정보를 표시 중 오류 발생] \n";
		AfxMessageBox(Convert::StdStringToCString(msg + e.what()));
	}
}

// 해당하는 시험을 콤보박스에서 선택
void CStudentManagementDlg::selectExamType(ExamType examType)
{
	int count = m_exam_type_ctl.GetCount();
	for (int i = 0; i < count; i++)
	{
		ExamType ctlExamType = (ExamType)m_exam_type_ctl.GetItemData(i);

		if (examType == ctlExamType)
		{
			m_exam_type_ctl.SetCurSel(i);
			return;
		}
	}
}

// 입력란 리셋
void CStudentManagementDlg::resetStudentEditCtl()
{
	m_name = _T("");
	m_grade = _T("");
	m_class = _T("");
	m_studentNumber = _T("");

	m_year = now.GetYear();
	m_semester = 1;
	m_exam_type = _T("");

	m_kukScore = 0;
	m_mathScore = 0;
	m_scienceScore = 0;
	m_socialScore = 0;
	m_totalScore = 0;
	m_rank = 0;
	m_engScore = 0;

	UpdateData(FALSE);
}

// 학생 추가 버튼 클릭
void CStudentManagementDlg::OnBnClickedButtonAdd()
{
	try {
		// 뷰에서 학생, 성적 정보를 가져옴
		StudentScoreInfoRow originRow = getRowData();

		// 학생 성적 정보 생성
		StudentScoreInfoRow newRow = studentScoreInfoController.addStudentScoreInfo(originRow);
	}
	catch (const std::exception& e)
	{
		CString msg = Convert::StdStringToCString(e.what());
		AfxMessageBox(msg);
		return;
	}

	reloadStudentScoreList();

	m_button_save.EnableWindow(FALSE); // 수정 버튼 비활성화 
	m_button_delete.EnableWindow(FALSE); // 삭제 버튼 비활성화
}

// 학생 수정 버튼 클릭
void CStudentManagementDlg::OnBnClickedButtonSave()
{
	try {
		std::string studentListKey;
		int examId;
		getSelectedHiddenValues(studentListKey, examId);

		// 뷰에서 업데이트할 학생, 성적 정보를 가져옴
		StudentScoreInfoRow updateRow = getRowData();

		// 학생 성적 정보 생성
		StudentScoreInfoRow newRow = studentScoreInfoController.updateStudentScoreInfo(studentListKey, examId, updateRow);
		CString successMsg = _T("학생 성적 정보가 업데이트 되었습니다.");
		AfxMessageBox(successMsg);
	}
	catch (const std::exception& e)
	{
		CString msg = Convert::StdStringToCString(e.what());
		AfxMessageBox(msg);
	}

	m_button_save.EnableWindow(FALSE); // 수정 버튼 비활성화
	m_button_delete.EnableWindow(FALSE); // 삭제 버튼 비활성화

	reloadStudentScoreList();
}

// 선택된 학생의 숨겨진 값 가져오기
void CStudentManagementDlg::getSelectedHiddenValues(std::string& listKeyStr, int& examId)
{
	// 현재 선택된 row index 가져오기
	int selected = m_studentInfoListCtl.GetNextItem(-1, LVNI_SELECTED);
	if (selected == -1)
	{
		throw std::runtime_error("선택된 항목이 없습니다.");
	}
	// 학생 리스트 키
	CString listKeyCStr = m_studentInfoListCtl.GetItemText(selected, 0);
	listKeyStr = Convert::CStringToStdString(listKeyCStr);

	// 시험 ID
	CString examIdCStr = m_studentInfoListCtl.GetItemText(selected, 1);
	examId = std::stoi(Convert::CStringToStdString(examIdCStr));
}

// 학생 성적 정보 삭제
void CStudentManagementDlg::OnBnClickedButtonDelete()
{
	try {
		// 현재 선택된 row index 가져오기
		int selected = m_studentInfoListCtl.GetNextItem(-1, LVNI_SELECTED);
		if (selected == -1)
		{
			throw std::runtime_error("선택된 항목이 없습니다.");
		}
		// 학생 리스트 키
		CString listKeyCStr = m_studentInfoListCtl.GetItemText(selected, 0);
		std::string listKeyStr = Convert::CStringToStdString(listKeyCStr);

		CString examIdCStr = m_studentInfoListCtl.GetItemText(selected, 1);
		int examId = std::stoi(Convert::CStringToStdString(examIdCStr));

		// 학생 성적 정보 삭제
		studentScoreInfoController.deleteStudentScoreInfo(listKeyStr, examId);

		m_button_save.EnableWindow(FALSE); // 수정 버튼 비활성화 
		m_button_delete.EnableWindow(FALSE); // 삭제 버튼 비활성화
	}
	catch (const std::exception& e)
	{
		CString msg = Convert::StdStringToCString(e.what());
		AfxMessageBox(msg);
	}

	reloadStudentScoreList();
	
}

// 학생 리스트 선택 시 컨트롤에 데이터 표시
void CStudentManagementDlg::OnClickListStudent(NMHDR* pNMHDR, LRESULT* pResult)
{
	try {
		// 클릭된 위치 정보 가져오기
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		int selectIdx = pNMItemActivate->iItem; // 클릭된 행 인덱스

		if (selectIdx >= 0) {
			m_button_save.EnableWindow(TRUE); // 수정 버튼 활성화 
			m_button_delete.EnableWindow(TRUE); // 삭제 버튼 활성화

			CString listKeyCstr = m_studentInfoListCtl.GetItemText(selectIdx, 0); // 행에 저장한 listKey값 가져오기
			CString examIdCstr = m_studentInfoListCtl.GetItemText(selectIdx, 1); // 행에 저장한 examId값 가져오기
			std::string listKeyStr = Convert::CStringToStdString(listKeyCstr);
			int examId = stoi(Convert::CStringToStdString(examIdCstr));

			StudentScoreInfo* info = studentScoreInfoController.searchStudentScoreInfoInCache(StudentListKey::fromString(listKeyStr), examId);

			// 뷰 입력란에 표시
			if (info != nullptr) {
				StudentScoreInfoRow row = studentScoreInfoController.studentScoreInfoToRow(*info);
				setStudentData(row);
			} else {
				AfxMessageBox(_T("학생 성적 정보를 찾을 수 없습니다."));
				m_button_save.EnableWindow(FALSE); // 수정 버튼 비활성화 
				m_button_delete.EnableWindow(FALSE); // 삭제 버튼 비활성화
			}
		}
	}
	catch (const std::exception e)
	{
		CString msg = Convert::StdStringToCString(e.what());
		AfxMessageBox(msg);
	}

	*pResult = 0;
}

// 파일(학생 리스트) 불러오기
void CStudentManagementDlg::OnClickedButtonLoadFile()
{
	try {
		// 리스트에 데이터가 있을 경우, 데이터 삭제해도되는지 확인
		if (m_studentInfoListCtl.GetItemCount() > 0)
		{
			int result = AfxMessageBox(_T("파일을 불러오면 기존에 등록된 데이터는 전부 삭제됩니다. \n정말 삭제하시겠습니까?"), MB_YESNO | MB_ICONQUESTION);
			if (result == IDNO)
				return;
		}

		CFileDialog dlg(TRUE, _T("csv"), nullptr,
			OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
			_T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||"),
			this);

		if (dlg.DoModal() != IDOK)
			return;

		CString filePathCstr = dlg.GetPathName();
		std::string pathStr = Convert::CStringToStdString(filePathCstr);

		// 파일 불러오기 실행
		studentScoreInfoController.loadFromFile(pathStr);
	}
	catch (const std::exception& e)
	{
		CString msg = Convert::StdStringToCString(e.what());
		AfxMessageBox(msg);
	}

	AfxMessageBox(_T("파일을 불러왔습니다."));
	reloadStudentScoreList(); // 리스트 초기화
}

// 파일(학생 리스트) 저장하기
void CStudentManagementDlg::OnClickedButtonSaveFile()
{
	try {
		CFileDialog dlg(FALSE, _T("csv"), _T("학생정보.csv"),
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			_T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||"),
			this);

		if (dlg.DoModal() != IDOK)
			return;

		CString filePathCstr = dlg.GetPathName();
		std::string pathStr = Convert::CStringToStdString(filePathCstr);

		studentScoreInfoController.saveToFile(pathStr);
	}
	catch (const std::exception& e)
	{
		CString msg = Convert::StdStringToCString(e.what());
		AfxMessageBox(msg);
	}

	AfxMessageBox(_T("파일을 저장했습니다."));
	
}