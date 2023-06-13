#include "JDM/Header/JDMinclude.hpp"

JNAMESPACE JDM
{
    SDL_Renderer *renderer       = JNULLPTR;
    JDOUBLE       TimeFrame      = 0x00;
    JDOUBLE       FPS            = 0x3c;
    JDOUBLE       ElapseTime     = 0x00;
    JINT          WindowX        = 0x00;
    JINT          WindowY        = 0x00;
    JINT          WindowWidth    = 0x00;
    JINT          WindowHeight   = 0x00;
    JBOOL         alreadyTouched = JFALSE;

    JNAMESPACE Mouse
    {
        JBOOL LeftMouseDown  = JFALSE;
        JBOOL RightMouseDown = JFALSE;
        JINT MouseX          = -1;
        JINT MouseY          = -1;
        JINT GlobalMouseX    = -1;
        JINT GlobalMouseY    = -1;
    }
}