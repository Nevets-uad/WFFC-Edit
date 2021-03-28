#pragma once
#include <afxdialogex.h>
#include "resource.h"
#include <afxwin.h>
#include "DisplayObject.h"
#include <vector>
class InspectorDialogue :	public CDialogEx
{
	DECLARE_DYNAMIC(InspectorDialogue)

public:
	InspectorDialogue(CWnd* pParent, std::vector<DisplayObject>* sceneGraph);
	InspectorDialogue(CWnd* pParent = NULL);
	virtual ~InspectorDialogue();
	void SetObjectData(std::vector<DisplayObject>* sceneGraph, int* selection);
	void SetImage(HBITMAP image);
	int GetSelectedID() { return *m_currentSelection; }
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLBnSelectChange();
	afx_msg void OnTvnSelchangedTree2(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	//Dialog Data
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG2};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void End(); //Kill the dialogue
	afx_msg void Select(); //Item has been selected

	std::vector<DisplayObject>* m_displayList;
	int* m_currentSelection;
	HICON m_hIcon;

private:
	CTreeCtrl m_treeCtrl;
	CStatic m_IDText;
	CStatic m_InspectorImage;
	CBitmap bmp1;
	HBITMAP m_inspectorBitmap;
	void SetSelectionTree();
	void UpdateSectionTree();
	bool treeSet;
	int previousSelectionID;
	afx_msg void OnStnClickedStaticText();
public:
	afx_msg void OnStnClickedPictureStatic();
};

