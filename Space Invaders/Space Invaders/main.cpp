//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: main.cpp
// Description	: is main
// Author		: Madeleine Day Jack Mair
// Mail			: jack.mair@mediadesign.school.nz
//

//Library Includes
#include <windows.h>
#include <windowsx.h>

//Local Includes
#include "Game.h"
#include "Clock.h"
#include "utils.h"
#include "mainmenu.h"
#include "highscoremenu.h"
#include "level.h"
#include "player.h"
#include "resource.h"

const int kiWidth = 960;
const int kiHeight = 720;
int g_iLineToWrite = 0;

enum buttonClicked
{
	NOBUTTON = 0,
	START = 1,
	QUIT,
	HIGHSCOREB,
	RETURN
};

CGame& rGame = CGame::GetInstance();

#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

HWND g_hDlgDebug;
HWND g_hDlgHighscore;

LRESULT CALLBACK
WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	static int s_iCurMouseX;
	static int s_iCurMouseY;

	static buttonClicked buttonDown;

	switch (_uiMsg)
	{
	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case 0x1B:
		{
			if (rGame.GetGameState() == GAMESCREEN)
			{
				ShowWindow(g_hDlgDebug, SW_SHOWNORMAL);
			}
			break;
		}
		default:
			break;
		}
		return (0);
	}
		break;
	case WM_LBUTTONDOWN:
	{
		//Checks the state of the game then checks which if a button has been clicked if so, makes it clicked down
		if (rGame.GetGameState() == MAINMENU && rGame.GetMenu()->checkIfStartSelected(s_iCurMouseX, s_iCurMouseY) == true)
		{
			buttonDown = START;
		}
		else if (rGame.GetGameState() == MAINMENU && rGame.GetMenu()->checkIfHighScoreSelected(s_iCurMouseX, s_iCurMouseY) == true)
		{
			buttonDown = HIGHSCOREB;
		}
		else if (rGame.GetGameState() == MAINMENU && rGame.GetMenu()->checkIfQuitSelected(s_iCurMouseX, s_iCurMouseY) == true)
		{
			buttonDown = QUIT;
		}
		else if (rGame.GetGameState() == HIGHSCORE && rGame.GetHSMenu()->checkIfStartSelected(s_iCurMouseX, s_iCurMouseY) == true)
		{
			buttonDown = RETURN;
		}
		return (0);
	}
		break;
	case WM_LBUTTONUP:
	{
		//Checks the state of the game then checks which if a button has been clicked down, if so checks if the mouse is still over the button when clicked released
		if (buttonDown == START && rGame.GetGameState() == MAINMENU && rGame.GetMenu()->checkIfStartSelected(s_iCurMouseX, s_iCurMouseY) == true)
		{
			//set all the radio buttons to their default state
			CheckRadioButton(g_hDlgDebug, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
			CheckRadioButton(g_hDlgDebug, IDC_RADIO13, IDC_RADIO15, IDC_RADIO14);
			CheckRadioButton(g_hDlgDebug, IDC_RADIO4, IDC_RADIO6, IDC_RADIO5);
			CheckRadioButton(g_hDlgDebug, IDC_RADIO10, IDC_RADIO12, IDC_RADIO11);
			rGame.ShowFinalScore(true);
			rGame.ChangeGameState(GAMESCREEN);
		}
		else if (buttonDown == HIGHSCOREB && rGame.GetGameState() == MAINMENU && rGame.GetMenu()->checkIfHighScoreSelected(s_iCurMouseX, s_iCurMouseY) == true)
		{
			rGame.ShowFinalScore(false);
			rGame.ChangeGameState(HIGHSCORE);
		}
		else if (buttonDown == QUIT && rGame.GetGameState() == MAINMENU && rGame.GetMenu()->checkIfQuitSelected(s_iCurMouseX, s_iCurMouseY) == true)
		{
			PostQuitMessage(0);
		}
		else if (buttonDown == RETURN && rGame.GetGameState() == HIGHSCORE && rGame.GetHSMenu()->checkIfStartSelected(s_iCurMouseX, s_iCurMouseY) == true)
		{ 
			rGame.ChangeGameState(MAINMENU);
		}
		buttonDown = NOBUTTON;

		return (0);
	}
		break;
	case WM_MOUSEMOVE:
	{
		s_iCurMouseX = static_cast<int>(LOWORD(_lParam));
		s_iCurMouseY = static_cast<int>(HIWORD(_lParam));
		//int iMouseX = LOWORD(_lParam);
		//CGame::GetInstance().GetLevel()->GetPaddle()->SetX(static_cast<float>(iMouseX));
		return (0);
	}
		break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);

		return(0);
	}
		break;

	default:
	{
		break;
	}

	}

	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

BOOL CALLBACK HighscoreDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{

	switch (_msg)
	{
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
		case IDOK:
		{

			rGame.GetHSMenu()->AddHighScore(ReadFromEditBox(g_hDlgHighscore, IDC_EDIT1), rGame.GetHSMenu()->GetLineToWrite()-1);
			ShowWindow(_hwnd, SW_HIDE);
			g_iLineToWrite = 0;
			break;
		}
		default:break;
		}
	}
	default:
		break;
	}
	return FALSE;
}

BOOL CALLBACK DebugDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
	{
		static float _value;
		switch (_msg)
		{
		case WM_COMMAND:
		{
			switch (LOWORD(_wparam))
			{
			case IDC_RADIO1:
			{
				CheckRadioButton(_hwnd, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
				rGame.GetInstance().GetLevel()->SetMotherShipSpeed(0.0f);
				return TRUE;
				break;
			}
			case IDC_RADIO2:
			{
				CheckRadioButton(_hwnd, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
				rGame.GetInstance().GetLevel()->SetMotherShipSpeed(1.0f);

				return TRUE;
				break;
			}
			case IDC_RADIO13:
			{
				CheckRadioButton(_hwnd, IDC_RADIO13, IDC_RADIO15, IDC_RADIO13);
				rGame.GetInstance().GetLevel()->SetEnemySpeed(1000.0f);
				return TRUE;
				break;
			}
			case IDC_RADIO14:
			{
				CheckRadioButton(_hwnd, IDC_RADIO13, IDC_RADIO15, IDC_RADIO14);
				rGame.GetInstance().GetLevel()->SetEnemySpeed(1.0f);

				return TRUE;
				break;
			}
			case IDC_RADIO15:
			{
				CheckRadioButton(_hwnd, IDC_RADIO13, IDC_RADIO15, IDC_RADIO15);
				rGame.GetInstance().GetLevel()->SetEnemySpeed(0.01f);

				return TRUE;
				break;
			}
			case IDC_RADIO4:
			{
				CheckRadioButton(_hwnd, IDC_RADIO4, IDC_RADIO6, IDC_RADIO4);
				rGame.GetInstance().GetLevel()->GetPlayer()->SetBulletSpeed(-52.0);

				return TRUE;
				break;
			}
			case IDC_RADIO5:
			{
				CheckRadioButton(_hwnd, IDC_RADIO4, IDC_RADIO6, IDC_RADIO5);
				rGame.GetInstance().GetLevel()->GetPlayer()->SetBulletSpeed(-520.0);

				return TRUE;
				break;
			}
			case IDC_RADIO6:
			{
				CheckRadioButton(_hwnd, IDC_RADIO4, IDC_RADIO6, IDC_RADIO6);
				rGame.GetInstance().GetLevel()->GetPlayer()->SetBulletSpeed(-2600.0);
				return TRUE;
				break;
			}
			case IDC_RADIO10:
			{
				CheckRadioButton(_hwnd, IDC_RADIO10, IDC_RADIO12, IDC_RADIO10);
				rGame.GetInstance().GetLevel()->SetAlienShootSpeed(-1);
				return TRUE;
				break;
			}
			case IDC_RADIO11:
			{
				CheckRadioButton(_hwnd, IDC_RADIO10, IDC_RADIO12, IDC_RADIO11);
				rGame.GetInstance().GetLevel()->SetAlienShootSpeed(500);
				return TRUE;
				break;
			}
			case IDC_RADIO12:
			{
				CheckRadioButton(_hwnd, IDC_RADIO10, IDC_RADIO12, IDC_RADIO12);
				rGame.GetInstance().GetLevel()->SetAlienShootSpeed(50);
				return TRUE;
				break;
			}
			default:
				break;
			}
		case WM_CLOSE:
		{
			ShowWindow(_hwnd, SW_HIDE);
			return TRUE;
			break;
		}
		}
		default:
			break;
		}
	return FALSE;
}

HWND
CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, const wchar_t* _pcTitle)
{
	WNDCLASSEX winclass;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_ICON1));
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(NULL_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(_hInstance , MAKEINTRESOURCE(IDI_ICON2));

	if (!RegisterClassEx(&winclass))
	{
		// Failed to register.
		return (0);
	}

	HWND hwnd;
	hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		_pcTitle,
		WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		_iWidth, _iHeight,
		NULL,
		NULL,
		_hInstance,
		NULL);

	if (!hwnd)
	{
		// Failed to create.
		return (0);
	}

	return (hwnd);
}

int WINAPI
WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
	MSG msg;
	RECT _rect;
	ZeroMemory(&msg, sizeof(MSG));

	static bool s_bScoreChecked = false;


	HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Space Invaders - Attack of the Goons");
	
	g_hDlgDebug = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DebugDlgProc);
	g_hDlgHighscore = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, HighscoreDlgProc);

	
	GetClientRect(hwnd, &_rect);

	//if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
	if (!rGame.Initialise(_hInstance, hwnd, _rect.right, _rect.bottom))
	{
		// Failed
		return (0);
	}

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			bool bPauseGame;
			if (IsWindowVisible(g_hDlgDebug) || IsWindowVisible(g_hDlgHighscore))
			{
				bPauseGame = true;
			}
			else
			{
				bPauseGame = false;
			}
			rGame.ExecuteOneFrame(bPauseGame);

			if (rGame.GetLevel() != nullptr && rGame.GetLevel()->GetLoseState())
			{
				if (s_bScoreChecked == false && rGame.GetHSMenu()->CheckIfHighScore(rGame.GetLevel()->GetScore()))
				{
					ShowWindow(g_hDlgHighscore, SW_SHOWNORMAL);
					s_bScoreChecked = true;
				}
				else
				{
					rGame.ChangeGameState(HIGHSCORE);
					rGame.GetLevel()->ResetLevel();
					rGame.GetInstance().GetLevel()->GetPlayer()->SetBulletSpeed(-260.0);
					rGame.GetInstance().GetLevel()->SetAlienShootSpeed(500);
					rGame.GetInstance().GetLevel()->SetEnemySpeed(1);
			
					rGame.GetLevel()->SetLoseState(false);
					s_bScoreChecked = true;
				}
			}
			else
			{
				s_bScoreChecked = false;
			}
		}
	}

	CGame::DestroyInstance();

	return (static_cast<int>(msg.wParam));
}
