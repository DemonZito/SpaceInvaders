//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

//Library Includes
#include <windows.h>
#include <windowsx.h>
//#include <vld.h>

//Local Includes
#include "Game.h"
#include "Clock.h"
#include "utils.h"
#include "level.h"
#include "player.h"
#include "resource.h"

const int kiWidth = 960;
const int kiHeight = 720;

CGame& rGame = CGame::GetInstance();

HWND g_hDlgDebug;

#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

LRESULT CALLBACK
WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uiMsg)
	{
	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case 0x1B:
		{
			ShowWindow(g_hDlgDebug, SW_SHOWNORMAL);
			break;
		}
		default:
			break;
		}
		return (0);
	}
		break;
	case WM_MOUSEMOVE:
	{
		int iMouseX = LOWORD(_lParam);
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
			case IDC_RADIO13:
			{
				CheckRadioButton(_hwnd, IDC_RADIO13, IDC_RADIO15, IDC_RADIO13);
				return TRUE;
				break;
			}
			case IDC_RADIO14:
			{
				CheckRadioButton(_hwnd, IDC_RADIO13, IDC_RADIO15, IDC_RADIO14);

				return TRUE;
				break;
			}
			case IDC_RADIO15:
			{
				CheckRadioButton(_hwnd, IDC_RADIO13, IDC_RADIO15, IDC_RADIO15);

				return TRUE;
				break;
			}
			case IDC_RADIO4:
			{
				CheckRadioButton(_hwnd, IDC_RADIO4, IDC_RADIO6, IDC_RADIO4);
				rGame.GetInstance().GetLevel()->GetPlayer()->SetBulletSpeed(-26.0);

				return TRUE;
				break;
			}
			case IDC_RADIO5:
			{
				CheckRadioButton(_hwnd, IDC_RADIO4, IDC_RADIO6, IDC_RADIO5);
				rGame.GetInstance().GetLevel()->GetPlayer()->SetBulletSpeed(-260.0);

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
			case IDC_RADIO7:
			{
				CheckRadioButton(_hwnd, IDC_RADIO7, IDC_RADIO9, IDC_RADIO7);
				return TRUE;
				break;
			}
			case IDC_RADIO8:
			{
				CheckRadioButton(_hwnd, IDC_RADIO7, IDC_RADIO9, IDC_RADIO8);
				return TRUE;
				break;
			}
			case IDC_RADIO9:
			{
				CheckRadioButton(_hwnd, IDC_RADIO7, IDC_RADIO9, IDC_RADIO9);
				return TRUE;
				break;
			}
			case IDC_RADIO10:
			{
				CheckRadioButton(_hwnd, IDC_RADIO10, IDC_RADIO12, IDC_RADIO10);
				rGame.GetInstance().GetLevel()->SetAlienShootSpeed(50000);
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
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(NULL_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

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

	g_hDlgDebug = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DebugDlgProc);

	CheckRadioButton(g_hDlgDebug, IDC_RADIO13, IDC_RADIO15, IDC_RADIO14);
	CheckRadioButton(g_hDlgDebug, IDC_RADIO4, IDC_RADIO6, IDC_RADIO5);
	CheckRadioButton(g_hDlgDebug, IDC_RADIO10, IDC_RADIO12, IDC_RADIO11);
	CheckRadioButton(g_hDlgDebug, IDC_RADIO7, IDC_RADIO9, IDC_RADIO8);

	return (hwnd);
}

int WINAPI
WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
	MSG msg;
	RECT _rect;
	ZeroMemory(&msg, sizeof(MSG));


	HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Breakout");
	
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
			rGame.ExecuteOneFrame(IsWindowVisible(g_hDlgDebug));
		}
	}

	CGame::DestroyInstance();

	return (static_cast<int>(msg.wParam));
}
