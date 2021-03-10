#include "InspectorDialogue.h"

IMPLEMENT_DYNAMIC(InspectorDialogue, CDialogEx)

BEGIN_MESSAGE_MAP(InspectorDialogue, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE2, &InspectorDialogue::OnTvnSelchangedTree2)
	ON_COMMAND(IDOK, &InspectorDialogue::End)					//ok button
	ON_BN_CLICKED(IDOK, &InspectorDialogue::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL InspectorDialogue::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog. The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);            // Set big icon
	SetIcon(m_hIcon, FALSE);            // Set small icon
	
	

	return TRUE;
}

void InspectorDialogue::PostNcDestroy()
{
	
}

void InspectorDialogue::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void InspectorDialogue::OnLBnSelectChange()
{
}

void InspectorDialogue::OnTvnSelchangedTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

InspectorDialogue::InspectorDialogue(CWnd* pParent, std::vector<SceneObject>* sceneGraph) : CDialogEx(IDD_DIALOG2, pParent)
{
	m_hIcon = LoadIcon(NULL, MAKEINTRESOURCE(460));
	m_sceneGraph = sceneGraph;
}

InspectorDialogue::InspectorDialogue(CWnd * pParent)
{
}

InspectorDialogue::~InspectorDialogue()
{
}

void InspectorDialogue::SetObjectData(std::vector<SceneObject>* sceneGraph, int* selection)
{

	m_sceneGraph = sceneGraph;
	m_currentSelection = selection;
	HTREEITEM hNodeName, hValueName;
	std::wstring optionString;
	if (*m_currentSelection != -1)
	{
		//Transform options
		hNodeName = m_treeCtrl.InsertItem(L"Transform", TVI_ROOT);
		hValueName = m_treeCtrl.InsertItem(L"Position", hNodeName);
		//X
		optionString = L"X" + std::to_wstring(m_sceneGraph->at(0).posX);
		//Y
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		optionString = L"Y" + std::to_wstring(m_sceneGraph->at(0).posY);
		//Z
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		optionString = L"Z" + std::to_wstring(m_sceneGraph->at(0).posZ);
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		hValueName = m_treeCtrl.InsertItem(L"Rotation", hNodeName);
		m_treeCtrl.InsertItem(L"X", hValueName);
		m_treeCtrl.InsertItem(L"Y", hValueName);
		m_treeCtrl.InsertItem(L"Z", hValueName);
		hValueName = m_treeCtrl.InsertItem(L"Scale", hNodeName);
		m_treeCtrl.InsertItem(L"X", hValueName);
		m_treeCtrl.InsertItem(L"Y", hValueName);
		m_treeCtrl.InsertItem(L"Z", hValueName);
		//Inspection window
		//TODO: Find out how to add an image to the tree and add here
		//
		hNodeName = m_treeCtrl.InsertItem(L"Test", TVI_ROOT);
		hValueName = m_treeCtrl.InsertItem(L"Test More", hNodeName);
	}
	else
	{
		hNodeName = m_treeCtrl.InsertItem(L"Please select an object", TVI_ROOT);
	}
	
}


void InspectorDialogue::DoDataExchange(CDataExchange * pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE2, m_treeCtrl);
}

void InspectorDialogue::End()
{
	DestroyWindow();
}

void InspectorDialogue::Select()
{
}
