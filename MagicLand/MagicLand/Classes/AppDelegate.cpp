#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "round\ml_roomcreator.h"
#include "stateMachine\ml_statemachinemgr.h"
#include "collision\ml_collisionmgr.h"
#include "entitycomponent\ml_entitymgr.h"
#include "statemachine\ml_com_con.h"
#include "statemachine\ml_startstate.h"
#include "statemachine\ml_XJNormalState.h"
#include "statemachine\ml_XJJumpState.h"
#include "statemachine\ml_XJFallState.h"
#include "statemachine\ml_FireBallFlyState.h"
#include "statemachine\ml_FireBallDestroyState.h"
#include "statemachine\ml_OrgeWalkState.h"
#include "statemachine\ml_OrgeWaitState.h"
#include "statemachine\ml_EndState.h"
#include "statemachine\ml_JumpOrgeSleepState.h"
#include "statemachine\ml_JumpOrgeJumpState.h"
#include "statemachine\ml_JumpOrgeBackState.h"
#include "statemachine\ml_MovePlatformMoveState.h"
#include "statemachine\ml_ThrowOrgeThrowState.h"
#include "statemachine\ml_BoomBallFlyState.h"
#include "statemachine\ml_BrokenStoneFlyState.h"
#include "framerate\ml_FrameRateMgr.h"
#include "round/ml_Round.h"
#include "marco.h"
#include "support\Script\ml_ScriptMgr.h"

USING_NS_CC;
using namespace magicland;

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
	MLScriptMgr::SharedInstance()->LoadScript("Script/Config.script");

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

	CreateJumpOrgeSM();

	CreateMovePlatformSM();

	CreateThrowOrgeSM();

	CreateBoomBallSM();

	CreateBrokenStoneSM();

	CreateGearCoreSM();
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
	MLScriptMgr::SharedInstance()->Destory();

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

void AppDelegate::CreateJumpOrgeSM()
{
	// Create statemachine for Jump Orge
	MLStateMachine* jumpOrgeSM = new MLStateMachine();
	ML_SAFE_ASSERT(jumpOrgeSM != NULL, "Allocate the memory failed");

	// Create the state
	MLStartState* startState = MLStartState::SharedInstance();
	MLJumpOrgeSleepState* sleepState = new MLJumpOrgeSleepState();
	MLJumpOrgeJumpState* jumpState = new MLJumpOrgeJumpState();
	MLJumpOrgeBackState* backState = new MLJumpOrgeBackState();

	// Create State Transform Table
	jumpOrgeSM->AddStateEntry(startState, &MLComCon::StartOK, sleepState);
	jumpOrgeSM->AddStateEntry(sleepState, &MLComCon::JumpOrgeSeePlayer, jumpState);
	jumpOrgeSM->AddStateEntry(jumpState, &MLComCon::TouchGround, backState);
	jumpOrgeSM->AddStateEntry(backState, &MLComCon::JumpOrgeIsBack, sleepState);

	MLStateMachineMgr::SharedInstance()->AddMgrEntry(ML_ETYSUBTYPE_JUMPORGE, jumpOrgeSM);
	ML_SAFE_DROP(jumpOrgeSM);
	ML_SAFE_DROP(startState);
	ML_SAFE_DROP(sleepState);
	ML_SAFE_DROP(jumpState);
	ML_SAFE_DROP(backState);
}

void AppDelegate::CreateMovePlatformSM()
{
	// Create statemachine for MovePlatform
	MLStateMachine* movePlatformSM = new MLStateMachine();
	ML_SAFE_ASSERT(movePlatformSM != NULL, "Failed to create State machine");

	// Create the State
	MLStartState* startState = MLStartState::SharedInstance();
	MLMovePlatformMoveState* moveState = new MLMovePlatformMoveState();

	// Create the State Transform Table
	movePlatformSM->AddStateEntry(startState, &MLComCon::StartOK, moveState);

	MLStateMachineMgr::SharedInstance()->AddMgrEntry(ML_ETYSUBTYPE_MOVEPLATFORM, movePlatformSM);
	ML_SAFE_DROP(movePlatformSM);
	ML_SAFE_DROP(startState);
	ML_SAFE_DROP(moveState);
}

void AppDelegate::CreateThrowOrgeSM()
{
	// Create State machine for ThrowOrge
	MLStateMachine* throwOrgeSM = new MLStateMachine();
	ML_SAFE_ASSERT(throwOrgeSM != NULL, "Failed to create State machine");

	// Create State
	MLStartState* startState = MLStartState::SharedInstance();
	MLThrowOrgeThrowState* throwState = new MLThrowOrgeThrowState();

	// Create the State Transform Table
	throwOrgeSM->AddStateEntry(startState, &MLComCon::StartOK, throwState);

	MLStateMachineMgr::SharedInstance()->AddMgrEntry(ML_ETYSUBTYPE_THROWORGE, throwOrgeSM);
	ML_SAFE_DROP(throwOrgeSM);
	ML_SAFE_DROP(startState);
	ML_SAFE_DROP(throwState);
}

void AppDelegate::CreateBoomBallSM()
{
	MLStateMachine* boomBallSM = new MLStateMachine();

	// Create State
	MLStartState* startState = MLStartState::SharedInstance();
	MLBoomBallFlyState* flyState = new MLBoomBallFlyState();
	MLEndState* endState = MLEndState::SharedInstance();

	// Create State Transform Table
	boomBallSM->AddStateEntry(startState, &MLComCon::StartOK, flyState);
	boomBallSM->AddStateEntry(flyState, &MLComCon::TouchGround, endState);

	MLStateMachineMgr::SharedInstance()->AddMgrEntry(ML_ETYSUBTYPE_BOOMBALL, boomBallSM);
	ML_SAFE_DROP(boomBallSM);
	ML_SAFE_DROP(startState);
	ML_SAFE_DROP(flyState);
	ML_SAFE_DROP(endState);
}

void AppDelegate::CreateBrokenStoneSM()
{
	MLStateMachine* brokenStoneSM = new MLStateMachine;
	ML_SAFE_ASSERT(brokenStoneSM != NULL, "Failed to create State Machine");

	MLStartState* startState = MLStartState::SharedInstance();
	MLBrokenStoneFlyState* flyState = new MLBrokenStoneFlyState();
	MLEndState* endState = MLEndState::SharedInstance();

	brokenStoneSM->AddStateEntry(startState, &MLComCon::StartOK, flyState);
	brokenStoneSM->AddStateEntry(flyState, &MLComCon::TouchGround, endState);

	MLStateMachineMgr::SharedInstance()->AddMgrEntry(ML_ETYSUBTYPE_BROKENSTONE, brokenStoneSM);

	ML_SAFE_DROP(brokenStoneSM);
	ML_SAFE_DROP(startState);
	ML_SAFE_DROP(flyState);
	ML_SAFE_DROP(endState);
}

void AppDelegate::CreateGearCoreSM()
{
	MLStateMachine* gearCoreSM = new MLStateMachine;
	ML_SAFE_ASSERT(gearCoreSM != NULL, "Failed to create State Machine");
	if(gearCoreSM != NULL)
	{
		MLStateMachineMgr::SharedInstance()->AddMgrEntry(ML_ETYSUBTYPE_GEARCORE, gearCoreSM);

		//MLStartState* startState = MLStartState::SharedInstance();
		//MLEndState* endState = MLEndState::SharedInstance();

		ML_SAFE_DROP(gearCoreSM);
		//ML_SAFE_DROP(startState);
		//ML_SAFE_DROP(endState);
	}
}