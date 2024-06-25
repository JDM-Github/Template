#pragma once
#ifndef JDM_ANIMATION_HPP
#define JDM_ANIMATION_HPP
#include "defines.hpp"
#include "JDMinclude.hpp"
#include "JDMenum.hpp"

JNAMESPACE JDM
{
    JCLASS AnimationBase
    {
    JPUBLIC:
        JVIRTUAL JCVOID   setDuration       (JCUINT64 duration  ) = 0;
        JVIRTUAL JCVOID   setAutoRemove     (JCBOOL   autoRemove) = 0;
        JVIRTUAL JCVOID   stopAnimation     (                   ) = 0;
        JVIRTUAL JCVOID   continueAnimation (                   ) = 0;
        JVIRTUAL JCVOID   cancelAnimation   (                   ) = 0;
        JVIRTUAL JCVOID   start             (                   ) = 0;
        JVIRTUAL JCBOOL   getAutoRemove     (                   ) = 0;
        JVIRTUAL JCBOOL   update            (                   ) = 0;
        JVIRTUAL JCUINT64 getDuration       (                   ) = 0;    
    };

    JTEMPLATE <JCLASS T>
    JCLASS Animation : JPUBLIC AnimationBase
    {
    JPUBLIC:
        JINLINE Animation(
            T * ref        = JNULLPTR,
            T   target     = JNULLPTR,
            JCUINT64   duration   = AnimationSpeed::ANIMATION_NORMAL,
            JCBOOL     autoRemove = JTRUE,
            JFUNCCALL  onProgress = [](){}
        ) :
            _duration           (duration / 1000.0),
            _targetAnimating    (ref              ),
            _target             (target           ),
            _autoRemove         (autoRemove       ),
            _onProgressFunction (onProgress       )
        {}

        JINLINE JCVOID setReference(JCONST T * ref)
        {
            JIF (!JTHIS->_started)
            {
                JTHIS->_targetAnimating = ref;
                JTHIS->_setVariables();
            }
        }

        JINLINE JCVOID setDuration(JCUINT64 duration)
        {
            JIF (!JTHIS->_started)
            {
                JTHIS->_duration = duration / 1000.0;
                JTHIS->_setVariables();
            }
        }

        JINLINE JCVOID setAutoRemove(JCBOOL autoRemove)
        {
            JIF (!JTHIS->_started)
                JTHIS->_autoRemove = autoRemove;
        }

        JINLINE JCVOID setTarget(T target)
        {
            JIF (!JTHIS->_started)
            {
                JTHIS->_target = target;
                JTHIS->setVariables();
            }
        }

        JINLINE JCVOID stopAnimation()
        {
            JIF (JTHIS->_started)
            {
                JTHIS->_stopped = JTRUE;
                JTHIS->_onStopFunction();
            }
        }

        JINLINE JCVOID continueAnimation()
        {
            JIF (JTHIS->_started)
            {
                JTHIS->_stopped = JFALSE;
                JTHIS->_onContinueFunction();
            }
        }

        JINLINE JCVOID cancelAnimation()
        {
            JTHIS->_started = JFALSE;
            JTHIS->_onCancelFunction();
        }

        JINLINE JCVOID start()
        {
            JIF (!JTHIS->_started)
            {
                JTHIS->_setVariables();
                JTHIS->_started = JTRUE;
                JTHIS->_onStartFunction();
            }
        }

        JCONSTEXPR JCUINT64 getDuration() JNOEXCEPT
        {
            JRETURN JSTATICC<JUINT64>(JTHIS->_duration * 1000);
        }

        JCONSTEXPR JCBOOL getAutoRemove() JNOEXCEPT
        {
            JRETURN JTHIS->_autoRemove;
        }

        JINLINE JCBOOL update()
        {    
            JIF (JTHIS->_started && !JTHIS->_stopped)
            {
                JIF ((JTHIS->_target <= *JTHIS->_targetAnimating && JTHIS->_adder >= 0)
                  || (JTHIS->_target >= *JTHIS->_targetAnimating && JTHIS->_adder <= 0))
                {
                    JTHIS->_onComplete();
                    JRETURN JTRUE;
                }
                JELSE
                {
                    JTHIS->_progressTracker = JTHIS->_progressTracker + JTHIS->_adder;
                    JTHIS->_onProgressFunction();

                    JIF ((JTHIS->_target <= JTHIS->_progressTracker && JTHIS->_adder >= 0)
                      || (JTHIS->_target >= JTHIS->_progressTracker && JTHIS->_adder <= 0))
                    {
                        JTHIS->_onComplete();
                        JRETURN JTRUE;
                    }
                    *JTHIS->_targetAnimating = JSTATICC<T>(JTHIS->_progressTracker);
                }
            }
            JRETURN JFALSE;
        }

    JPRIVATE:
        JBOOL     _started            = JFALSE;
        JBOOL     _stopped            = JFALSE;
        JBOOL     _autoRemove         = JFALSE;

        JDOUBLE   _duration           = JNONE;
        JDOUBLE   _progressTracker    = JNONE;
        JDOUBLE   _distance           = JNONE;
        JDOUBLE   _adder              = JNONE;

        T         _target             = JNONE;
        T        *_targetAnimating    = JNULLPTR;

        JFUNCCALL _onProgressFunction = []() {};
        JFUNCCALL _onStartFunction    = []() {};
        JFUNCCALL _onCompleteFunction = []() {};
        JFUNCCALL _onStopFunction     = []() {};
        JFUNCCALL _onContinueFunction = []() {};
        JFUNCCALL _onCancelFunction   = []() {};

    JPRIVATE:
        JINLINE JCVOID _setVariables() 
        {
            JTHIS->_distance        = JTHIS->_target - *JTHIS->_targetAnimating;
            JTHIS->_progressTracker = JSTATICC<JDOUBLE>(*JTHIS->_targetAnimating);
            JTHIS->_adder           = JTHIS->_distance * (1.0 / (JTHIS->_duration * JDM::FPS));
        }

        JINLINE JCVOID _onComplete()
        {
            *JTHIS->_targetAnimating = JTHIS->_target;
            JTHIS ->_started         = JFALSE;
            JTHIS ->_onCompleteFunction();
        }
    };

    JCLASS Clock
    {
    JPUBLIC:
        Clock(
            JCUINT64  duration   = AnimationSpeed::ANIMATION_NORMAL,
            JCBOOL    autoRemove = JTRUE,
            JFUNCCALL onComplete = [](){}
        );
        JCVOID setAutoRemove (JCBOOL autoRemove);
        JCVOID start         (                 );
        JCVOID reset         (                 );
        JCBOOL update        (                 );

        JCONSTEXPR JCUINT64 getDuration() JCONST JNOEXCEPT
        {
            JRETURN JSTATICC<JUINT64>(JTHIS->_duration * 1000);
        }

        JCONSTEXPR JCBOOL getAutoRemove() JCONST JNOEXCEPT
        {
            JRETURN JTHIS->_autoRemove;
        }
    
    JPRIVATE:   
        JBOOL     _started            = JFALSE;
        JBOOL     _autoRemove         = JFALSE;

        JDOUBLE   _duration           = JNONE;
        JDOUBLE   _currentDuration    = JNONE;

        JFUNCCALL _onProgressFunction = []() {};
        JFUNCCALL _onStartFunction    = []() {};
        JFUNCCALL _onCompleteFunction = []() {};
        JFUNCCALL _onResetFunction    = []() {};
    };
};

#endif
