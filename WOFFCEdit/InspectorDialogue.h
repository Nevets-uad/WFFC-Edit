#pragma once
#include <afxdialogex.h>
#include "resource.h"
#include <afxwin.h>
#include "SceneObject.h"
#include <vector>
class InspectorDialogue :	public CDialogEx
{
	DECLARE_DYNAMIC(InspectorDialogue)

public:
	InspectorDialogue(CWnd* pParent, std::vector<SceneObject>* sceneGraph);
	InspectorDialogue(CWnd* pParent = NULL);
	virtual ~InspectorDialogue();
	void SetObjectData(std::vector<SceneObject>* sceneGraph, int* selection);
	//Dialog Data
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG2};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void End(); //Kill the dialogue
	afx_msg void Select(); //Item has been selected

	std::vector<SceneObject>* m_sceneGraph;
	int* m_currentSelection;
	HICON m_hIcon;
public:
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLBnSelectChange();
	afx_msg void OnTvnSelchangedTree2(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
	CTreeCtrl m_treeCtrl;
};

