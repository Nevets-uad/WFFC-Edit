#include "InspectorDialogue.h"

IMPLEMENT_DYNAMIC(InspectorDialogue, CDialogEx)

BEGIN_MESSAGE_MAP(InspectorDialogue, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE2, &InspectorDialogue::OnTvnSelchangedTree2)
	ON_COMMAND(IDOK, &InspectorDialogue::End)					//ok button
	ON_BN_CLICKED(IDOK, &InspectorDialogue::OnBnClickedOk)
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_STATIC_TEXT, &InspectorDialogue::OnStnClickedStaticText)
	ON_STN_CLICKED(IDC_PICTURE_STATIC, &InspectorDialogue::OnStnClickedPictureStatic)
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

InspectorDialogue::InspectorDialogue(CWnd* pParent, std::vector<DisplayObject>* sceneGraph) : CDialogEx(IDD_DIALOG2, pParent)
{
	m_hIcon = LoadIcon(NULL, MAKEINTRESOURCE(460));
	m_displayList = sceneGraph;
}

InspectorDialogue::InspectorDialogue(CWnd * pParent)
{
}

InspectorDialogue::~InspectorDialogue()
{
}

void InspectorDialogue::SetObjectData(std::vector<DisplayObject>* sceneGraph, int* selection)
{

	m_displayList = sceneGraph;
	m_currentSelection = selection;
	treeSet = false;
	previousSelectionID = *m_currentSelection;
	SetSelectionTree();
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
		DeleteObject(m_inspectorBitmap);
		DisplayObject selectedObject = m_displayList->at(*m_currentSelection);
		std::wstring optionString;

		optionString = L"Item ID: " + std::to_wstring(*m_currentSelection);
		m_IDText.SetWindowText(optionString.c_str());

		//Transform options
		hNodeName = m_treeCtrl.InsertItem(L"Transform", TVI_ROOT);
		//Position
		hValueName = m_treeCtrl.InsertItem(L"Position", hNodeName);
		optionString = L"X: " + std::to_wstring(selectedObject.m_position.x) + L" Y: " + std::to_wstring(selectedObject.m_position.y) + L" Z: " + std::to_wstring(selectedObject.m_position.z);
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		//Rotation
		hValueName = m_treeCtrl.InsertItem(L"Rotation", hNodeName);
		optionString = L"X: " + std::to_wstring(selectedObject.m_orientation.x) + L" Y: " + std::to_wstring(selectedObject.m_orientation.y) + L" Z: " + std::to_wstring(selectedObject.m_orientation.z);
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		//Scale
		hValueName = m_treeCtrl.InsertItem(L"Scale", hNodeName);
		optionString = L"X: " + std::to_wstring(selectedObject.m_scale.x) + L" Y: " + std::to_wstring(selectedObject.m_scale.y) + L" Z: " + std::to_wstring(selectedObject.m_scale.z);
		m_treeCtrl.InsertItem(optionString.c_str(), hValueName);
		//Inspection window
		//TODO: Find out how to add an image to the tree and add here
		//
		hNodeName = m_treeCtrl.InsertItem(L"Test", TVI_ROOT);
		hValueName = m_treeCtrl.InsertItem(L"Test More", hNodeName);
		HTREEITEM root = m_treeCtrl.GetRootItem();
		root = m_treeCtrl.GetNextSiblingItem(root);
		m_treeCtrl.SetItemText(root, L"REEE");
	/*	HBITMAP pic = CreateBitmap(100, 100, 1, 255, m_displayList->at(*m_currentSelection).m_texture_diffuse);
		m_InspectorImage.SetBitmap(pic);
		CBitmap pic2;
		pic2.LoadBitmapW(1);*/

		m_inspectorBitmap = CreateBitmap(100, 125, 1, 32, m_displayList->at(*m_currentSelection).m_texture_diffuse);
		m_InspectorImage.SetBitmap(m_inspectorBitmap);
		
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
		DeleteObject(m_inspectorBitmap);
		std::wstring optionString;
		HTREEITEM hNodeName, hValueName;
		HTREEITEM root = m_treeCtrl.GetRootItem();
		HTREEITEM transformItem = m_treeCtrl.GetChildItem(root);
		HTREEITEM nextItem = m_treeCtrl.GetNextSiblingItem(transformItem);
		HTREEITEM currentItem;
		optionString = L"Item ID: " + std::to_wstring(*m_currentSelection);
		DisplayObject selectedObject = m_displayList->at(*m_currentSelection);
		m_IDText.SetWindowText(optionString.c_str());
		//Position
		currentItem = m_treeCtrl.GetChildItem(transformItem);
		optionString = L"X: " + std::to_wstring(selectedObject.m_position.x) + L" Y: " + std::to_wstring(selectedObject.m_position.y) + L" Z: " + std::to_wstring(selectedObject.m_position.z);
		m_treeCtrl.SetItemText(currentItem, optionString.c_str());
		//Scale
		currentItem = m_treeCtrl.GetChildItem(nextItem);
		optionString = L"X: " + std::to_wstring(selectedObject.m_orientation.x) + L" Y: " + std::to_wstring(selectedObject.m_orientation.y) + L" Z: " + std::to_wstring(selectedObject.m_orientation.z);
		m_treeCtrl.SetItemText(currentItem, optionString.c_str());

		//Update nextItem to rotation
		nextItem = m_treeCtrl.GetNextSiblingItem(nextItem);

		//Rotation
		currentItem = m_treeCtrl.GetChildItem(nextItem);
		optionString = L"X: " + std::to_wstring(selectedObject.m_scale.x) + L" Y: " + std::to_wstring(selectedObject.m_scale.y) + L" Z: " + std::to_wstring(selectedObject.m_scale.z);
		m_treeCtrl.SetItemText(currentItem, optionString.c_str());

		m_inspectorBitmap = CreateBitmap(100, 125, 1, 32, m_displayList->at(*m_currentSelection).m_texture_diffuse);
		
		m_InspectorImage.SetBitmap(m_inspectorBitmap);

	}
	previousSelectionID = *m_currentSelection;
}


void InspectorDialogue::OnStnClickedStaticText()
{
	// TODO: Add your control notification handler code here
}


void InspectorDialogue::OnStnClickedPictureStatic()
{
	// TODO: Add your control notification handler code here
}
