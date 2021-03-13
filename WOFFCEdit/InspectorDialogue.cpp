#include "InspectorDialogue.h"

IMPLEMENT_DYNAMIC(InspectorDialogue, CDialogEx)

BEGIN_MESSAGE_MAP(InspectorDialogue, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE2, &InspectorDialogue::OnTvnSelchangedTree2)
	ON_COMMAND(IDOK, &InspectorDialogue::End)					//ok button
	ON_BN_CLICKED(IDOK, &InspectorDialogue::OnBnClickedOk)
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_STATIC_TEXT, &InspectorDialogue::OnStnClickedStaticText)
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
	treeSet = false;
	previousSelectionID = *m_currentSelection;
	SetSelectionTree();
	HBITMAP image;
}

void InspectorDialogue::SetImage(HBITMAP image)
{
}


void InspectorDialogue::DoDataExchange(CDataExchange * pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE2, m_treeCtrl);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_IDText);
	DDX_Control(pDX, IDC_PICTURE_STATIC, m_InspectorImage);
}

void InspectorDialogue::End()
{
	DestroyWindow();
}

void InspectorDialogue::Select()
{
}


void InspectorDialogue::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	if (*m_currentSelection == -1 || previousSelectionID == -1)
		SetSelectionTree();
	else
		UpdateSectionTree();
}

void InspectorDialogue::SetSelectionTree()
{
	m_treeCtrl.DeleteAllItems();
	HTREEITEM hNodeName, hValueName;
	std::wstring optionString;
	if (*m_currentSelection != -1)
	{
		std::wstring optionString;

		optionString = L"Item ID: " + std::to_wstring(*m_currentSelection);
		m_IDText.SetWindowText(optionString.c_str());

		//Transform options
		hNodeName = m_treeCtrl.InsertItem(L"Transform", TVI_ROOT);
		//Position
		hValueName = m_treeCtrl.InsertItem(L"Position", hNodeName);
		//X Pos
		optionString = L"X: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).posX);
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		//Y Pos
		optionString = L"Y: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).posY);
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		//Z Pos
		optionString = L"Z: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).posZ);
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		//Rotation
		hValueName = m_treeCtrl.InsertItem(L"Rotation", hNodeName);
		//X-Rotation
		optionString = L"X: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).rotX);
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		//Y-Rotation
		optionString = L"Y: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).rotY);
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		//Z-Rotation
		optionString = L"Z: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).rotZ);
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		//Scale
		hValueName = m_treeCtrl.InsertItem(L"Scale", hNodeName);
		//X-Scale
		optionString = L"X: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).scaX);
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		//Y-Scale
		optionString = L"Y: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).scaY);
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		//Z-Scale
		optionString = L"Z: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).scaZ);
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		//Inspection window
		//TODO: Find out how to add an image to the tree and add here
		//
		hNodeName = m_treeCtrl.InsertItem(L"Test", TVI_ROOT);
		hValueName = m_treeCtrl.InsertItem(L"Test More", hNodeName);
		HTREEITEM root = m_treeCtrl.GetRootItem();
		root = m_treeCtrl.GetNextSiblingItem(root);
		m_treeCtrl.SetItemText(root, L"REEE");
	}
	else
	{
		/*optionString = L"Item ID: " + std::to_wstring(0);

		m_IDText.SetWindowText(optionString.c_str());*/
		hNodeName = m_treeCtrl.InsertItem(L"Please select an object", TVI_ROOT);
	}
	previousSelectionID = *m_currentSelection;
}

void InspectorDialogue::UpdateSectionTree()
{
	
	if (*m_currentSelection != -1)
	{
		std::wstring optionString;
		HTREEITEM hNodeName, hValueName;
		HTREEITEM root = m_treeCtrl.GetRootItem();
		HTREEITEM transformItem = m_treeCtrl.GetChildItem(root);
		HTREEITEM nextItem = m_treeCtrl.GetNextSiblingItem(transformItem);
		HTREEITEM currentItem;
		optionString = L"Item ID: " + std::to_wstring(*m_currentSelection);

		m_IDText.SetWindowText(optionString.c_str());
		//X Pos
		currentItem = m_treeCtrl.GetChildItem(transformItem);
		optionString = L"X: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).posX);
		m_treeCtrl.SetItemText(currentItem, optionString.c_str());
		//Y Pos
		currentItem = m_treeCtrl.GetNextSiblingItem(currentItem);
		optionString = L"Y: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).posY);
		m_treeCtrl.SetItemText(currentItem, optionString.c_str());
		//Z Pos
		currentItem = m_treeCtrl.GetNextSiblingItem(currentItem);
		optionString = L"Z: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).posZ);
		m_treeCtrl.SetItemText(currentItem, optionString.c_str());
		////Rotation
		//hValueName = m_treeCtrl.InsertItem(L"Rotation", hNodeName);
		////X-Rotation
		//optionString = L"X: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).rotX);
		//m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		////Y-Rotation
		//optionString = L"Y: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).rotY);
		//m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		////Z-Rotation
		//optionString = L"Z: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).rotZ);
		//m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		////Scale
		//hValueName = m_treeCtrl.InsertItem(L"Scale", hNodeName);
		////X-Scale
		//optionString = L"X: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).scaX);
		//m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		////Y-Scale
		//optionString = L"Y: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).scaY);
		//m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		////Z-Scale
		//optionString = L"Z: " + std::to_wstring(m_sceneGraph->at(*m_currentSelection).scaZ);
		//m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		////Inspection window
		////TODO: Find out how to add an image to the tree and add here
		////
		//hNodeName = m_treeCtrl.InsertItem(L"Test", TVI_ROOT);
		//hValueName = m_treeCtrl.InsertItem(L"Test More", hNodeName);
		//HTREEITEM root = m_treeCtrl.GetRootItem();
		//root = m_treeCtrl.GetNextSiblingItem(root);
		//m_treeCtrl.SetItemText(root, L"REEE");
	}
	previousSelectionID = *m_currentSelection;
}


void InspectorDialogue::OnStnClickedStaticText()
{
	// TODO: Add your control notification handler code here
}
