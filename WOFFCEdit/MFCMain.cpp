#include "MFCMain.h"
#include "resource.h"


BEGIN_MESSAGE_MAP(MFCMain, CWinApp)
	ON_COMMAND(ID_FILE_QUIT,	&MFCMain::MenuFileQuit)
	ON_COMMAND(ID_FILE_SAVETERRAIN, &MFCMain::MenuFileSaveTerrain)
	ON_COMMAND(ID_EDIT_SELECT, &MFCMain::MenuEditSelect)
	ON_COMMAND(ID_VIEW_INSPECTOR, &MFCMain::MenuViewInspector)
	ON_COMMAND(ID_BUTTON40001,	&MFCMain::ToolBarButton1)
	ON_COMMAND(ID_BUTTON40006, &MFCMain::ToolBarFreeCamButton)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TOOL, &CMyFrame::OnUpdatePage)
END_MESSAGE_MAP()

BOOL MFCMain::InitInstance()
{
	//instanciate the mfc frame
	m_frame = new CMyFrame();
	m_pMainWnd = m_frame;

	m_frame->Create(	NULL,
					_T("World Of Flim-Flam Craft Editor"),
					WS_OVERLAPPEDWINDOW,
					CRect(100, 100, 1024, 768),
					NULL,
					NULL,
					0,
					NULL
				);
	//show and set the window to run and update. 
	m_frame->ShowWindow(SW_SHOW);
	m_frame->UpdateWindow();

	//get the rect from the MFC window so we can get its dimensions
	m_toolHandle = m_frame->m_DirXView.GetSafeHwnd();				//handle of directX child window
	m_frame->m_DirXView.GetClientRect(&WindowRECT);
	m_width		= WindowRECT.Width();
	m_height	= WindowRECT.Height();

	m_ToolSystem.onActionInitialise(m_toolHandle, m_pMainWnd->GetSafeHwnd(), m_width, m_height);

	return TRUE;
}

int MFCMain::Run()
{
	MSG msg;
	BOOL bGotMsg;

	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		if (true)
		{
			bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);
		}
		else
		{
			bGotMsg = (GetMessage(&msg, NULL, 0U, 0U) != 0);
		}

		if (bGotMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			m_ToolSystem.UpdateInput(&msg);
		}
		else
		{	
			int ID = m_ToolSystem.getCurrentSelectionID();
			std::wstring statusString;
			if(ID == -1)
				statusString = L"Selected Object: None";
			else
				statusString = L"Selected Object: " + std::to_wstring(ID);

			m_ToolSystem.Tick(&msg);


			//send current object ID to status bar in The main frame
			m_frame->m_wndStatusBar.SetPaneText(1, statusString.c_str(), 1);
			if (m_ToolInspectorDialogue)
			{
				if(m_ToolInspectorDialogue.GetSelectedID() != ID)
					m_ToolInspectorDialogue.RedrawWindow();
			}
			
		}
	}

	

	return (int)msg.wParam;
}

void MFCMain::MenuFileQuit()
{
	//will post message to the message thread that will exit the application normally
	PostQuitMessage(0);
}

void MFCMain::MenuFileSaveTerrain()
{
	m_ToolSystem.onActionSaveTerrain();
}

void MFCMain::MenuEditSelect()
{
	//SelectDialogue m_ToolSelectDialogue(NULL, &m_ToolSystem.m_sceneGraph);		//create our dialoguebox //modal constructor
	//m_ToolSelectDialogue.DoModal();	// start it up modal

	//modeless dialogue must be declared in the class.   If we do local it will go out of scope instantly and destroy itself
	if (!m_ToolSelectDialogue)
	{
		m_ToolSelectDialogue.Create(IDD_DIALOG1);	//Start up modeless
		m_ToolSelectDialogue.ShowWindow(SW_SHOW);	//show modeless
		m_ToolSelectDialogue.SetObjectData(&m_ToolSystem.m_sceneGraph, &m_ToolSystem.m_selectedObject);
	}
	else
	{
		m_ToolSelectDialogue.SetForegroundWindow();
	}
	
}

void MFCMain::ToolBarButton1()
{
	
	m_ToolSystem.onActionSave();
}

void MFCMain::ToolBarFreeCamButton()
{
	m_ToolSystem.onFreeCamToggle();
}

void MFCMain::MenuViewInspector()
{
	if (!m_ToolInspectorDialogue)
	{
		m_ToolInspectorDialogue.Create(IDD_DIALOG2);	//Start up modeless
		m_ToolInspectorDialogue.ShowWindow(SW_SHOW);	//show modeless
		m_ToolInspectorDialogue.SetObjectData(&m_ToolSystem.GetDisplayList(), &m_ToolSystem.m_selectedObject);
	}
	else
	{
		m_ToolInspectorDialogue.SetForegroundWindow();
	}
	
}


MFCMain::MFCMain()
{
}


MFCMain::~MFCMain()
{

}
