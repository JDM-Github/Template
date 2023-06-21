#pragma once
#ifndef JDM_FUNCTIONS_HPP
#define JDM_FUNCTIONS_HPP
#include "defines.hpp"
#include "JDMstructs.hpp"
#include "JDMobjects/JDMobjInc.hpp"

JNAMESPACE JDM
{
    JEXTERN JCVOID subtractCharAtIndex    (JSTR &str, JCINT index           );
    JEXTERN JCVOID addCharAtIndex         (JSTR &str, JCINT index, JCSTR &ch);
    JEXTERN JCSTR  retSubtractCharAtIndex (JSTR str, JCINT index            );
    JEXTERN JCSTR  retAddCharAtIndex      (JSTR str, JCINT index, JCSTR &ch );
    JEXTERN JCBOOL isFileExist            (JSTRVIEW file                    );

    JTEMPLATE <JCLASS _Base, JCLASS _Derived>
    JINLINE JCBOOL isInstanceOf()
    {
        JRETURN std::is_base_of<_Base, _Derived>();
    }

    JTEMPLATE <JCLASS _Base, JCLASS _Derived>
    JINLINE JCBOOL isInstanceOf(_Derived object)
    {
        JRETURN std::is_base_of<_Base, JGETTYPE(object)>();
    }

    // THIS IS FREAKING DANGEROUS, BUT I WILL LEAVE IT AS IT IS
    // WHY?? JUST BECAUSE
    JTEMPLATE <JCLASS _Class, JCLASS _ReturnVal>
    JINLINE _ReturnVal getObjectValue(JSP<JDM::Object> object)
    {
        _Class *isValue = JDYNAMICC<_Class *>(object.get());
        JIF (isValue)
        {
            JRETURN JSTATICC<_ReturnVal>(isValue->getValue());
        }
        JRETURN JNULLPTR;
    }
    JEXTERN JBOOL   getIfBoolean          (JSP<JDM::Object> object                                );
    JEXTERN JLLONG  getIfInteger          (JSP<JDM::Object> object                                );
    JEXTERN JDOUBLE getIfDouble           (JSP<JDM::Object> object                                );
    JEXTERN JSTR    getIfString           (JSP<JDM::Object> object                                );

    JEXTERN JDOUBLE getObjectArithmetic   (JSP<JDM::Object> object                                );
    JEXTERN JUINT8  getUint8Limit         (JSP<JDM::Object> object                                );
    JEXTERN JLLONG  getNumberLimit        (JSP<JDM::Object> object, JLLONG minimum, JLLONG maximum);

    JEXTERN JCBOOL IsTextureInWindow(
        JCDOUBLE x,
        JCDOUBLE y,
        JCDOUBLE width,
        JCDOUBLE height
    );
    JEXTERN SDL_Texture *loadRoundedTexture(
        JCONST  JDM::Size size,
        JCCHARP path,
        JCONST  JDM::FourArc arc,
        JCUINT8 lineWidth
    );
    JEXTERN SDL_Texture *loadTextTexture(
        JCCHARP path,
        JCCHARP text,
        JCONST  ColorRGBA color
    );

    JEXTERN JCONST JDM::ColorRGB  getColorFromHex  (JSTRVIEW hexColor);
    JEXTERN JCONST JDM::ColorRGBA getColorFromHexA (JSTRVIEW hexColor);
};

#endif