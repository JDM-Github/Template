#pragma once
#ifndef JDM_KEYCODES_HPP
#define JDM_KEYCODES_HPP
#include "defines.hpp"

JNAMESPACE JDM
{
    JNAMESPACE KeyCode
    {
        JEXTERN JBOOL A; JEXTERN JBOOL B; JEXTERN JBOOL C;
        JEXTERN JBOOL D; JEXTERN JBOOL E; JEXTERN JBOOL F;
        JEXTERN JBOOL G; JEXTERN JBOOL H; JEXTERN JBOOL I;
        JEXTERN JBOOL J; JEXTERN JBOOL K; JEXTERN JBOOL L;
        JEXTERN JBOOL M; JEXTERN JBOOL N; JEXTERN JBOOL O;
        JEXTERN JBOOL P; JEXTERN JBOOL Q; JEXTERN JBOOL R;
        JEXTERN JBOOL S; JEXTERN JBOOL T; JEXTERN JBOOL U;
        JEXTERN JBOOL V; JEXTERN JBOOL W; JEXTERN JBOOL X;
        JEXTERN JBOOL Y; JEXTERN JBOOL Z;

        JEXTERN JBOOL LEFT_SHIFT;
        JEXTERN JBOOL RIGHT_SHIFT;
        JEXTERN JBOOL LEFT_CONTROL;
        JEXTERN JBOOL RIGHT_CONTROL;

        JEXTERN JBOOL CAPSLOCK; JEXTERN JBOOL ENTER;
        JEXTERN JBOOL TAB; JEXTERN JBOOL BACKSPACE;
        JEXTERN JBOOL SPACE; JEXTERN JBOOL KPLUS;
        JEXTERN JBOOL KMINUS;

        JEXTERN JBOOL N0; JEXTERN JBOOL N1;
        JEXTERN JBOOL N2; JEXTERN JBOOL N3;
        JEXTERN JBOOL N4; JEXTERN JBOOL N5;
        JEXTERN JBOOL N6; JEXTERN JBOOL N7;
        JEXTERN JBOOL N8; JEXTERN JBOOL N9;

        JEXTERN JBOOL UP; JEXTERN JBOOL DOWN;
        JEXTERN JBOOL LEFT; JEXTERN JBOOL RIGHT;
        JEXTERN JBOOL PERIOD; JEXTERN JBOOL COMMA;
        JEXTERN JBOOL QUESTION; JEXTERN JBOOL QOUTE;

        JEXTERN JCCHAR *KeyCodeToString(JCBOOL *Key);
    }
}

#endif