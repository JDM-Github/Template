#pragma once
#ifndef JDM_COMP_IMAGE_HPP
#define JDM_COMP_IMAGE_HPP

#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMstructs.hpp"
#include "JDM/Header/JDMenum.hpp"
#include "JDM/Header/JDMobjects/JDMobject.hpp"

#include "JDM/Header/JDMbaseComponents/JDMbaseGradient.hpp"
#include "JDM/Header/JDMbaseComponents/JDMbaseImage.hpp"
#include "JDM/Header/JDMcomponents/JDMcomponent.hpp"

JNAMESPACE JDM
{
    JNAMESPACE Comp
    {
        JCLASS Image : JPUBLIC JDM::Comp::Components, JPUBLIC JDM::Base::BaseGradient, JPUBLIC JDM::Base::BaseImage
        {
        JPUBLIC:
            JENUM Properties
            {
                X                     = 0x00,
                Y                     = 0x01,
                WIDTH                 = 0x02,
                HEIGHT                = 0x03,
                DISABLED              = 0x04,
                PICK_ON_BOUNDS        = 0x05,
                WILL_RENDER           = 0x06,
                SOURCE                = 0x14,
                IMAGE_COLOR_R         = 0x15,
                IMAGE_COLOR_G         = 0x16,
                IMAGE_COLOR_B         = 0x17,
                IMAGE_COLOR_A         = 0x18,
                IMAGE_COLOR_STR       = 0x19,
                ARC_STR               = 0x1A,
                LINEWIDTH             = 0x1B
            };

        JPUBLIC:
            JUINT8        *getPointerRImage () JOVERRIDE;
            JUINT8        *getPointerGImage () JOVERRIDE;
            JUINT8        *getPointerBImage () JOVERRIDE;
            JUINT8        *getPointerAImage () JOVERRIDE;

            JCVOID         update           () JOVERRIDE;
            JCVOID         renderComp       () JOVERRIDE;

            JVIRTUAL JCSTR getName          () JCONST;

            Image(
                JCSTR                &source   = DefaultImage,
                JCDOUBLE              xPos     = 0x00,
                JCDOUBLE              yPos     = 0x00,
                JCDOUBLE              width    = 0x64,
                JCDOUBLE              height   = 0x64,
                JCONST JDM::ColorRGBA color    = {0xff, 0xff, 0xff, 0xff},
                JCONST FourArc        arc      = {0x00, 0x00, 0x00, 0x00}
            );

            Image(
                JMAP<Properties, JSP<JDM::Object>> mapComponent
            );
        };
    }
}


#endif