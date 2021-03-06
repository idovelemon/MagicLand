#ifndef ML_MAROC_H_
#define ML_MAROC_H_

#include <assert.h>
#include <math.h>
#include <stdio.h>

#define ML_SAFE_ASSERT(_expression_, _msg_) \
    do\
    {\
      bool bRet = _expression_;\
      assert(bRet && _msg_); \
    }while(false)

#define ML_SAFE_DELETE(_pointer_) \
    if(_pointer_ != NULL)\
    {\
        delete _pointer_;\
        _pointer_ = NULL;\
    }

#define ML_SAFE_DELETE_ARRAY(_pointer_) \
    if(_pointer_ != NULL)\
    {\
        delete[] _pointer_;\
        _pointer_ = NULL;\
    }

#define ML_SAFE_GRAB(_pointer_) \
    ML_SAFE_ASSERT(_pointer_ != NULL, "Please pass a valid pointer"); \
    _pointer_->Grab();

#define ML_SAFE_DROP(_pointer_) \
    if(_pointer_ != NULL)\
    {\
        _pointer_->Drop();\
        _pointer_ = NULL;\
    }

#define ML_SAFE_RELEASE_ENTITY(_entity_) \
	if(_entity_ != NULL) \
	{\
		_entity_->RemoveAllComponents();\
		_entity_->Drop();\
		_entity_ = NULL;\
	}

#define ML_DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&); \
	void operator=(const TypeName&)

#define ML_FLOAT_EQUAL(_value1_, _value2_) (abs(_value1_ - _value2_) <= 0.0001f)

#endif // ML_MAROC_H_