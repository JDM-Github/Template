#include "JDM/Header/JDManimation.hpp"
#include "JDM/Header/JDMinclude.hpp"

JDM::Clock::Clock (
    JCUINT64  duration,
    JCBOOL    autoRemove,
    JFUNCCALL onComplete
) :
    _duration           (duration / 1000.0),
    _autoRemove         (autoRemove       ),
    _onCompleteFunction (onComplete       )
{}

JCVOID JDM::Clock::setAutoRemove(JCBOOL autoRemove)
{
    JIF (!JTHIS->_started)
        JTHIS->_autoRemove = autoRemove;
}

JCVOID JDM::Clock::start()
{
    JIF(!JTHIS->_started)
    {
        JTHIS->_currentDuration = JTHIS->_duration;
        JTHIS->_started         = JTRUE;
        JTHIS->_onStartFunction();
    }
}

JCVOID JDM::Clock::reset()
{
    JTHIS->_started = JFALSE;
    JTHIS->_onResetFunction();
}

JCBOOL JDM::Clock::update()
{
    JIF(!JTHIS->_started)
        JRETURN JFALSE;

    JTHIS->_currentDuration -= (1.0 / JDM::FPS);
    JTHIS->_onProgressFunction();

    JIF (JTHIS->_currentDuration <= 0)
    {
        JTHIS->_started         = JFALSE;
        JTHIS->_currentDuration = JTHIS->_duration;
        JTHIS->_onCompleteFunction();
        JRETURN JTRUE;
    }
    JRETURN JFALSE;
}

