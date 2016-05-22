#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"

#include "round\ml_round.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
}

// override the run method
int AppDelegate::run()
{
	// Main message loop:
	MSG msg;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nLast);

	// Initialize instance and cocos2d.
	if (!applicationDidFinishLaunching())
	{
		return 0;
	}

	CCEGLView* pMainWnd = CCEGLView::sharedOpenGLView();
	pMainWnd->centerWindow();
	ShowWindow(pMainWnd->getHWnd(), SW_SHOW);

	while (1)
	{
		if (! PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Get current time tick.
			QueryPerformanceCounter(&nNow);

			// If it's the time to draw next frame, draw it, else sleep a while.
			LONGLONG nDelta = nNow.QuadPart - nLast.QuadPart;
			if (nDelta > m_nAnimationInterval.QuadPart)
			{
				nLast.QuadPart = nNow.QuadPart;
				CCDirector::sharedDirector()->mainLoop();
			}
			else
			{
				Sleep(0);
			}
			continue;
		}

		if (WM_QUIT == msg.message)
		{
			// Quit message loop.
      magicland::MLRoundMgr::Destroy();
			break;
		}

		// Deal with windows message.
		if (! m_hAccelTable || ! TranslateAccelerator(msg.hwnd, m_hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}