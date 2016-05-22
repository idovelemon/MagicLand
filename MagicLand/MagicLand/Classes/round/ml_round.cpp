#include "ml_round.h"

#include "marco.h"
#include "ml_entitymgr.h"
#include "ml_roundconfig.h"

namespace magicland {
//-----------------------------------------------------------------------------
// Locals/Constant
//-----------------------------------------------------------------------------
const int32_t kRoundStateUnkown = 0;
const int32_t kRoundStateRun = 1;
const int32_t kRoundStatePause = 2;

//-----------------------------------------------------------------------------
// Class/Typedef
//-----------------------------------------------------------------------------
class MLRoundMgrImp {
public:
  static MLRoundMgrImp* SharedInstance();
  static void DestroyInstance();

public:
  virtual int32_t Init();
  virtual void Update(float delta);
  virtual void Destroy();

  virtual void StartRound(int32_t round);
  virtual void ReStartRound();
  virtual void PauseRound();
  virtual void ResumeRound();
  virtual void StopRound();

protected:
  MLRoundMgrImp();
  virtual ~MLRoundMgrImp();

private:
  int32_t       m_CurRound;
  int32_t       m_RoundState;

  static MLRoundMgrImp* s_Instance;
  ML_DISALLOW_COPY_AND_ASSIGN(MLRoundMgrImp);
};

//----------------------------------------------------------------------------
// Implement
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Implement MLRoundMgrImp
//----------------------------------------------------------------------------
MLRoundMgrImp* MLRoundMgrImp::s_Instance = NULL;

MLRoundMgrImp::MLRoundMgrImp()
  :m_CurRound(-1)
  ,m_RoundState(kRoundStateUnkown) {
}

MLRoundMgrImp::~MLRoundMgrImp() {
  Destroy();
}

MLRoundMgrImp* MLRoundMgrImp::SharedInstance() {
  if(s_Instance == NULL) {
    s_Instance = new MLRoundMgrImp();
    ML_SAFE_ASSERT(s_Instance != NULL, "Memory error");
  }

  return s_Instance;
}

void MLRoundMgrImp::DestroyInstance() {
  if(s_Instance != NULL) {
    delete s_Instance;
  }

  s_Instance = NULL;
}

int32_t MLRoundMgrImp::Init() {
  int32_t result = -1;

  // Init round config
  if(MLRoundConfig::Init() != 0) {
    result = -1;
    return result;
  }


  return 0;
}

void MLRoundMgrImp::Update(float delta) {

  switch(m_RoundState) {
  case kRoundStateUnkown:
    break;

  case kRoundStateRun:
    MLEntityMgr::Update(delta);
    break;

  case kRoundStatePause:
    break;
  }
}

void MLRoundMgrImp::Destroy() {

  // Destroy round config
  MLRoundConfig::Destroy();

  // Destroy entity mgr
  MLEntityMgr::Destroy();
}

void MLRoundMgrImp::StartRound(int32_t round) {

  ML_SAFE_ASSERT(1 <= round && round <= MLRoundMgr::kMaxRound, "Round Error");
  m_CurRound = round;
  m_RoundState = kRoundStateRun;
  MLRoundConfig::ConfigRound(round);
}

void MLRoundMgrImp::ReStartRound() {
  MLEntityMgr::ClearAllEntity();
  MLRoundConfig::ConfigRound(m_CurRound);
}

void MLRoundMgrImp::PauseRound() {
  m_RoundState = kRoundStatePause;
}

void MLRoundMgrImp::ResumeRound() {
  m_RoundState = kRoundStateRun;
}

void MLRoundMgrImp::StopRound() {
  MLEntityMgr::ClearAllEntity();
}

//---------------------------------------------------------------------------
// Implement MLRoundMgr
//---------------------------------------------------------------------------
int32_t MLRoundMgr::Init() {
  int32_t result = -1;

  MLRoundMgrImp* instance = MLRoundMgrImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Error");
  if(instance != NULL) {
    result = instance->Init();
  }

  return result;
}

void MLRoundMgr::Update(float delta) {

  MLRoundMgrImp* instance = MLRoundMgrImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Error");
  if(instance != NULL) {
    instance->Update(delta);
  }
}

void MLRoundMgr::Destroy() {

  MLRoundMgrImp* instance = MLRoundMgrImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Error");
  if(instance != NULL) {
    instance->Destroy();
  }
  MLRoundMgrImp::DestroyInstance();
}

void MLRoundMgr::StartRound(int32_t round) {

  MLRoundMgrImp* instance = MLRoundMgrImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Error");
  if(instance != NULL) {
    instance->StartRound(round);
  }
}

void MLRoundMgr::ReStartRound() {

  MLRoundMgrImp* instance = MLRoundMgrImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Error");
  if(instance != NULL) {
    instance->ReStartRound();
  }
}

void MLRoundMgr::PauseRound() {

  MLRoundMgrImp* instance = MLRoundMgrImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Error");
  if(instance != NULL) {
    instance->PauseRound();
  }
}

void MLRoundMgr::ResumeRound() {

  MLRoundMgrImp* instance = MLRoundMgrImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Error");
  if(instance != NULL) {
    instance->ResumeRound();
  }
}

void MLRoundMgr::StopRound() {

  MLRoundMgrImp* instance = MLRoundMgrImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Error");
  if(instance != NULL) {
    instance->StopRound();
  }
}
} // namespace magicland