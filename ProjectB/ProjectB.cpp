#include "stdafx.h"
#include <crtdbg.h>
#include <tchar.h>
#include <stdio.h>
#include <d2d1.h>	//!	Direct2D に必要
#include "TextureLoader.h"
#include "ProjectB.h"
#include "Selector.h"

#pragma comment(lib,"d2d1.lib")    //!< direct2d に必要

//! 関数 WndProc のプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

ID2D1Factory             *g_pD2DFactory = NULL;      //  D2D1Factoryオブジェクト
ID2D1HwndRenderTarget    *g_pRenderTarget = NULL;    //  描画ターゲット

/**
 *  マクロ宣言
 */
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if (o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)  if (o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY(o) if (o){ delete [] (o); o = NULL; }

CSelector *g_pSelector = NULL;

/**
 *@fn
 *@param in ... （Windows APIの指定通り)
 *\ アプリケーションのエントリーポイント
 */
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	//! デバッグ用フラグのセット
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//! 変数宣言
	WNDCLASSEX wcex;  //  ウィンドウクラス構造体
	HWND hWnd;        //  ウィンドウハンドル
	RECT    bounds, client;  //  RECT 構造体

	/**
	 * (1)初期化部分
	 */

	CoInitialize(NULL);    //!< COM の初期化

	//!  (1)-a ウィンドウクラスの登録
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;  //  ウィンドウプロシージャの登録
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;  //  アプリケーションインスタンス
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _T("BlockBuster");  //  ウィンドウクラス名
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wcex);

	//! (1)-b ウィンドウの生成
	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, wcex.lpszClassName, _T("Block Buster"),
		WS_VISIBLE |WS_POPUP,
		CW_USEDEFAULT, 0, 1920, 1080, NULL, NULL, hInstance, NULL);
	if (!hWnd)
		return FALSE;

	//! ウィンドウサイズの調整
	//! ここは無くても動く
	GetWindowRect(hWnd, &bounds);
	GetClientRect(hWnd, &client);
	MoveWindow(hWnd, bounds.left, bounds.top,
		1920 * 2 - client.right,
		1080 * 2 - client.bottom,
		false);


	//  Direct2D 初期化
	{
		HRESULT hr;
		//  Direct2D Factory の生成
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
		GetClientRect(hWnd, &client);
		D2D1_SIZE_U size = D2D1::SizeU(
			1920,
			1080
		);

		//  Direct2D 描画ターゲットの生成
		hr = g_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&g_pRenderTarget
		);
	}
	double		g_dblDenominator;
	double		g_dblFrame;
	__int64		g_i64OldTimer;

	//	タイマーの初期化
	::QueryPerformanceCounter((LARGE_INTEGER*)&g_i64OldTimer);
	__int64		i64Tmp;
	::QueryPerformanceFrequency((LARGE_INTEGER*)&i64Tmp);
	g_dblDenominator = 1.0 / (double)i64Tmp;
	g_dblFrame = 0.0f;

	g_pSelector = new CSelector(g_pRenderTarget);

	InvalidateRect(hWnd, NULL, false);

	//! ウィンドウの再表示
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);
	//! 再表示の際、WndProc が呼び出される事にも注意！

	/**
	 * (2)メッセージループ
	 */
	MSG        msg;
	while (true) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			double t;
			::QueryPerformanceCounter((LARGE_INTEGER*)&i64Tmp);
			t = (i64Tmp - g_i64OldTimer)*g_dblDenominator;
			g_i64OldTimer = i64Tmp;
			g_dblFrame += t;

			if (g_pSelector)
				g_pSelector->doAnim();

			InvalidateRect(hWnd, NULL, true);	//	画面書き換えを指示
		}
	}

	/**
	 * (3)終了処理
	 */
	_CrtDumpMemoryLeaks();
	CTextureLoader::Destroy();		//	textureLoader の終了


	g_pRenderTarget->Release();  //  RenderTarget の破棄
	g_pRenderTarget = NULL;

	g_pD2DFactory->Release(); //  ファクトリーの解放
	g_pD2DFactory = NULL;

	CoUninitialize();    //!< COM の使用終了

	return (int)msg.wParam;

}


/******************************************************************
 *@fn
 * ウインドウに渡されたイベントのハンドラ
 *@param in hWnd    イベントが発生したウィンドウ
 *@param in message イベントの種類
 *@param in wParam  WORD パラメータ・・イベントによって意味は異なる
 *@param in lParam  LONG パラメータ・・イベントによって意味は異なる
 ******************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:  //  画面再描画イベント
		if (g_pRenderTarget != NULL) {

			g_pRenderTarget->BeginDraw();  //!< 描画開始
			g_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity()); //!< Transform の設定
			g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkBlue));   //!< 画面のクリア

			//! ここに描画コードを書くこと
			if (g_pSelector)
				g_pSelector->doDraw(g_pRenderTarget);


			//! 描画終了
			g_pRenderTarget->EndDraw();
		}
		ValidateRect(hWnd, NULL);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return    0;
}