#pragma once
#ifndef JDM_BASE_IMAGE_HPP
#define JDM_BASE_IMAGE_HPP

#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMstructs.hpp"
#include "JDM/Header/JDMenum.hpp"
#include "JDM/Header/JDMobjects/JDMobject.hpp"

JNAMESPACE JDM
{
    JNAMESPACE Base
    {
        JCLASS BaseImage
        {
        JPUBLIC:
            JENUM ImageProperties
            {
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
            JINLINE ~BaseImage()
            {
                SDL_DestroyTexture(JTHIS->_imageTexture);
            }

        JPUBLIC:
            JCVOID         setImageSource            (JCSTR &source              );
            JCVOID         setImageAndOpacityColor   (JCONST JDM::ColorRGBA color);
            JCVOID         setImageColor             (JCONST JDM::ColorRGB color );
            JCVOID         setImageOpacity           (JCONST JUINT8 opacity      );
            JCVOID         setImageColorR            (JUINT8 rColor              );
            JCVOID         setImageColorG            (JUINT8 gColor              );
            JCVOID         setImageColorB            (JUINT8 bColor              );
            JCVOID         setImageFourArc           (JCONST JDM::FourArc arc    );
            JCVOID         setImageTwoLRArc          (JCONST JDM::TwoLRArc arcLR );
            JCVOID         setImageTwoTBArc          (JCONST JDM::TwoTBArc arcTB );
            JCVOID         setImageLineWidth         (JUINT8 lineWidth           );
            JCVOID         setImageRegion            (JCONST JDM::Region region  );
            JCVOID         setWillUpdateImageColor   (JCBOOL imageUpdate         );
            JCVOID         setWillUpdateImageOpacity (JCBOOL imageUpdate         );

            // JCVOID         setAnimationStep          (JINT    delay              );
            // JCVOID         setAnimationLoop          (JINT    loop               );
            // JCVOID         setAnimationDelay         (JDOUBLE delay              );

            JDM::ColorRGBA getImageAndOpacityColor () JCONST;
            JDM::ColorRGB  getImageColor           () JCONST;
            JUINT8         getImageOpacity         () JCONST;
            JUINT8         getImageColorR          () JCONST;
            JUINT8         getImageColorG          () JCONST;
            JUINT8         getImageColorB          () JCONST;
            Region         getImageRegion          () JCONST;
            RegionF        getImageDestination     () JCONST;

            // JDOUBLE         getAnimationDelay      () JCONST;
            // JINT            getAnimationLoop       () JCONST;
            // JINT            getAnimationStep       () JCONST;

            JDM::FourArc   getImageFourArc         () JCONST;
            JUINT8         getImageLineWidth       () JCONST;
            SDL_Texture   *getImageTexture         ();
            JCSTR          getImageSource          ();

        JPROTECTED:
            JINLINE BaseImage() {}

        JPROTECTED:
            JBOOL        _willUpdateImageTexture = JFALSE;
            JBOOL        _willUpdateImageColor   = JFALSE;
            JBOOL        _willUpdateImageOpacity = JFALSE;

            JSTR         _sourceFiles            = JEMPTYSTRING;
            SDL_Texture *_imageTexture           = JNULLPTR;

            SDL_FRect    _imageDestination       = {0x00, 0x00, 0x00, 0x00};
            SDL_Rect     _imageSource            = {0x00, 0x00, 0x00, 0x00};
            ColorRGBA    _imageColor             = {0xff, 0xff, 0xff, 0xff};

            JDM::FourArc _arc                    = {0x00, 0x00, 0x00, 0x00};
            JINT         _lineWidth              = JNONE;

            JINT         _currentStep            = 0;
            JINT         _currentLoop            = 0;
            JDOUBLE      _currentDelay           = 0;

            JINT         _animationStep          = 3;
            JINT         _animationLoop          = 0;
            JDOUBLE      _animationDelay         = JDM::AnimationSpeed::ANIMATION_NORMAL;

        JPROTECTED:
            JCVOID _setImageRectDestination (JCONST JDM::PositionSize posSize                      );
            JCVOID _setImageTexture         (JCONST JDM::Size size                                 );
            JCVOID _updateImage             (JCONST JDM::PositionSize posSize                      );
            JCVOID _updateImageColor        (                                                      );
            JCVOID _updateImageOpacity      (                                                      );
            JCVOID _renderImage             (                                                      );
            JCBOOL _setObjectProperties     (ImageProperties propertyName, JSP<JDM::Object> &object);
        };
    }
}

#endif