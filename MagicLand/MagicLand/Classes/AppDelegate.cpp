#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "Round\MLRoomCreator.h"
#include "StateMachine\MLStateMachineMgr.h"
#include "Collision\MLCollisionMgr.h"
#include "EntityComponent\MLEntityMgr.h"
#include "StateMachine\MLComCon.h"
#include "StateMachine\MLStartState.h"
#include "StateMachine\MLXJNormalState.h"
#include "StateMachine\MLXJJumpState.h"
#include "StateMachine\MLXJFallState.h"
#include "StateMachine\MLFireBallFlyState.h"
#include "StateMachine\MLFireBallDestroyState.h"
#include "StateMachine\MLOrgeWalkState.h"
#include "StateMachine\MLOrgeWaitState.h"
#include "StateMachine\MLEndState.h"
#include "Framerate\MLFrameRateMgr.h"
#include "Round/MLRound.h"
#include "marco.h"
#include "Support\Script\MLScriptMgr.h"

USING_NS_CC;
using namespace MagicLand;

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

	// set the pScene as the running scene immediately
	pDirector->drawScene();

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

	// Initialize the game
	gameInit();

	CCEGLView* pMainWnd = CCEGLView::sharedOpenGLView();
	pMainWnd->centerWindow();
	ShowWindow(pMainWnd->getHWnd(), SW_SHOW);

	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setFrameSize(MLScriptMgr::SharedInstance()->GetValue("GameScreenWidth"), MLScriptMgr::SharedInstance()->GetValue("GameScreenHeight"));

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
				gameMainLoop(1.0f * nDelta / nFreq.QuadPart);
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
			break;
		}

		// Deal with windows message.
		if (! m_hAccelTable || ! TranslateAccelerator(msg.hwnd, m_hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	gameFinish();

	return (int) msg.wParam;
}

void AppDelegate::gameInit()
{
	// Create the Script manager
	MLScriptMgr::SharedInstance()->LoadScript("Config.script");

	// Create Collision manager here...
	MLCollisionMgr::SharedInstance();

	// Create Entity manager here
	MLEntityMgr::SharedInstance();

	// Create room here...
	MLRound::SharedInstance();

	// Create State machine here...
	CreateXJSM();
	
	CreateFireBallSM();

	CreateOrgeSM();
}

void AppDelegate::gameMainLoop(float delta)
{
	MLFrameRateMgr::SharedInstance()->AddDelta(delta);

	MLRound::SharedInstance()->Update(delta);
}

void AppDelegate::gameFinish()
{
	// Destroy the State Machine manager here...
	MLStateMachineMgr::SharedInstance()->Destroy();

	// Destroy the Entity manager here...
	MLEntityMgr::SharedInstance()->Destroy();

	// Destroy the Round
	MLRound::Destroy();

	// Destroy the Collision manager here...
	MLCollisionMgr::SharedInstance()->Destroy();

	// Destroy the Script manager here...


	// Destroy the cocos2d
	CCDirector::sharedDirector()->end();
}

void AppDelegate::CreateXJSM()
{
	MLStateMachine* pHeroXJSM = new MLStateMachine;
	ML_SAFE_ASSERT(pHeroXJSM != NULL, "Failed to allocate the memory for the state machine");

	// Create the state
	MLXJNormalState* normalState = new MLXJNormalState();
	ML_SAFE_ASSERT(normalState != NULL, "Failed to allocate the memory for the normal state");

	MLXJJumpState* jumpState = new MLXJJumpState();
	ML_SAFE_ASSERT(jumpState != NULL, "Failed to allocate the memory for the jump state");

	MLXJFallState* fallState = new MLXJFallState();
	ML_SAFE_ASSERT(fallState != NULL, "Failed to allocate the memory for fall state");

	MLStartState* startState = MLStartState::SharedInstance();
	ML_SAFE_ASSERT(startState != NULL, "Failed to allocate the memory for start state");

	// Build the state transform table
	pHeroXJSM->AddStateEntry(startState, &MLComCon::StartOK, fallState);
	pHeroXJSM->AddStateEntry(fallState, &MLComCon::TouchGround, normalState);
	pHeroXJSM->AddStateEntry(normalState, &MLComCon::NeedJump, jumpState);
	pHeroXJSM->AddStateEntry(jumpState, &MLComCon::TouchGround, normalState);
	pHeroXJSM->AddStateEntry(normalState, &MLComCon::NeedFall, fallState);
	pHeroXJSM->AddStateEntry(jumpState, &MLComCon::NeedFall, fallState);

	MLStateMachineMgr::SharedInstance()->AddMgrEntry(ML_ETYSUBTYPE_XJ, pHeroXJSM);
	ML_SAFE_DROP(pHeroXJSM);
	ML_SAFE_DROP(fallState);
	ML_SAFE_DROP(jumpState);
	ML_SAFE_DROP(normalState);
	ML_SAFE_DROP(startState);
}

void AppDelegate::CreateFireBallSM()
{
	// Create statemachine for FireBall
	MLStateMachine* fireBallSM = new MLStateMachine();
	ML_SAFE_ASSERT(fireBallSM != NULL, "Allocate the memory failed");

	// Create the state
	MLFireBallFlyState* fireBallFlyState = new MLFireBallFlyState();
	ML_SAFE_ASSERT(fireBallFlyState != NULL, "Allocate the memory failed");

	MLFireBallDestroyState* fireBallDestroyState = new MLFireBallDestroyState();
	ML_SAFE_ASSERT(fireBallDestroyState != NULL, "Allocate the memory failed");

	MLStartState* startState = MLStartState::SharedInstance();
	ML_SAFE_ASSERT(startState != NULL, "Allocate the memory failed");

	MLEndState* endState = MLEndState::SharedInstance();
	ML_SAFE_ASSERT(endState != NULL, "Allocate the memory failed");

	fireBallSM->AddStateEntry(startState, &MLComCon::StartOK, fireBallFlyState);
	fireBallSM->AddStateEntry(fireBallFlyState, &MLComCon::FireBallFlyTimeUp, fireBallDestroyState);
	fireBallSM->AddStateEntry(fireBallFlyState, &MLComCon::FireBallCollidedWithEnemy, fireBallDestroyState);
	fireBallSM->AddStateEntry(fireBallDestroyState, &MLComCon::NeedEnd, endState);

	MLStateMachineMgr::SharedInstance()->AddMgrEntry(ML_ETYSUBTYPE_FIREBALL, fireBallSM);
	ML_SAFE_DROP(fireBallSM);
	ML_SAFE_DROP(fireBallFlyState);
	ML_SAFE_DROP(fireBallDestroyState);
	ML_SAFE_DROP(startState);
	ML_SAFE_DROP(endState);
}

void AppDelegate::CreateOrgeSM()
{
	// Create statemachine for Orge
	MLStateMachine* orgeSM = new MLStateMachine();
	ML_SAFE_ASSERT(orgeSM != NULL, "Allocate the memory failed");

	// Create the state
	MLOrgeWalkState* orgeWalkState = new MLOrgeWalkState();
	MLOrgeWaitState* orgeWaitState = new MLOrgeWaitState();
	MLStartState* startState = MLStartState::SharedInstance();

	// Create State Transform Table
	orgeSM->AddStateEntry(startState, &MLComCon::StartOK, orgeWalkState);
	orgeSM->AddStateEntry(orgeWalkState, &MLComCon::OrgeWalkTimeUp, orgeWaitState);
	orgeSM->AddStateEntry(orgeWaitState, &MLComCon::OrgeWaitTimeUp, orgeWalkState);

	MLStateMachineMgr::SharedInstance()->AddMgrEntry(ML_ETYSUBTYPE_ORGE, orgeSM);
	ML_SAFE_DROP(orgeSM);
	ML_SAFE_DROP(orgeWalkState);
	ML_SAFE_DROP(orgeWaitState);
	ML_SAFE_DROP(startState);
}