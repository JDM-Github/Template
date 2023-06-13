#pragma once
#ifndef JDM_COMPONENTS_HPP
#define JDM_COMPONENTS_HPP
#include "JDMinclude.hpp"
#include "JDMfonts.hpp"
#include "logger.hpp"
#include "JDMstructs.hpp"
#include "JDMenum.hpp"
#include "JDMfunctions.hpp"
#include "JDMobjects/JDMobjInc.hpp"

JNAMESPACE JDM
{
    JNAMESPACE Comp
    {
        JCLASS BaseGradient
        {
        JPUBLIC:
            JCVOID setGradientAlignment (JCONST JDM::Gradient gradientAlignment         );
            JCVOID setGradientColor     (JCONST ColorRGBA first, JCONST ColorRGBA second);

        JPROTECTED:
            JINLINE BaseGradient() {}

        JPROTECTED:
            JDM::Gradient _gradientAlignment  = JDM::GRADIENT_NONE;
            ColorRGBA     _gradientStartColor = {0x00, 0x00, 0x00, 0x00};
            ColorRGBA     _gradientEndColor   = {0x00, 0x00, 0x00, 0x00}; 

        JPROTECTED:
            JCONST JUINT8 _interpolateColorComponent (JUINT8 startComponent, JUINT8 endComponent, JINT position, JINT length) JCONST;
            JCVOID        _renderGradient            (JCONST JDM::PositionSize posSize                                      );
        };

        JCLASS BaseImage
        {
        JPUBLIC:
            JINLINE ~BaseImage()
            {
                SDL_DestroyTexture(JTHIS->_imageTexture);
            }

        JPUBLIC:
            JCVOID         setImageSource          (JCSTR &source              );
            JCVOID         setImageAndOpacityColor (JCONST JDM::ColorRGBA color);
            JCVOID         setImageColor           (JCONST JDM::ColorRGB color );
            JCVOID         setImageOpacity         (JCONST JUINT8 opacity      );
            JCVOID         setImageColorR          (JUINT8 rColor              );
            JCVOID         setImageColorG          (JUINT8 gColor              );
            JCVOID         setImageColorB          (JUINT8 bColor              );
            JCVOID         setImageFourArc         (JCONST JDM::FourArc arc    );
            JCVOID         setImageTwoLRArc        (JCONST JDM::TwoLRArc arcLR );
            JCVOID         setImageTwoTBArc        (JCONST JDM::TwoTBArc arcTB );
            JCVOID         setImageLineWidth       (JUINT8 lineWidth           );
            JCVOID         setImageRegion          (JCONST JDM::Region region  );
            JCVOID         setWillUpdateImageColor (JCBOOL imageUpdate         );

            JDM::ColorRGBA getImageAndOpacityColor () JCONST;
            JDM::ColorRGB  getImageColor           () JCONST;
            JUINT8         getImageOpacity         () JCONST;
            JUINT8         getImageColorR          () JCONST;
            JUINT8         getImageColorG          () JCONST;
            JUINT8         getImageColorB          () JCONST;
            Region         getImageRegion          () JCONST;
            RegionF        getImageDestination     () JCONST;

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

        JPROTECTED:
            JCVOID _setImageRectDestination (JCONST JDM::PositionSize posSize);
            JCVOID _setImageTexture         (JCONST JDM::Size size           );
            JCVOID _updateImage             (JCONST JDM::PositionSize posSize);
            JCVOID _updateImageColor        (                                );
            JCVOID _updateImageOpacity      (                                );
            JCVOID _renderImage             (                                );
        };

        JCLASS BaseText
        {
        JPUBLIC:
            JINLINE ~BaseText()
            {
                SDL_DestroyTexture(JTHIS->_textTexture);
            }

        JPUBLIC:
            JCVOID            setTextMessage         (JCSTR &text                );
            JCVOID            setTextAndOpacityColor (JCONST JDM::ColorRGBA color);
            JCVOID            setTextColor           (JCONST JDM::ColorRGB color );
            JCVOID            setTextOpacity         (JCONST JUINT8 opacity      );
            JCVOID            setTextColorR          (JUINT8 rColor              );
            JCVOID            setTextColorG          (JUINT8 gColor              );
            JCVOID            setTextColorB          (JUINT8 bColor              );
            JCVOID            setTextRegion          (JCONST JDM::Region region  );
            JCVOID            setFontSize            (JCUINT size                );
            JCVOID            setBold                (JCBOOL bold                );
            JCVOID            setItalic              (JCBOOL italic              );
            JCVOID            setFont                (JCONST JDM::Font::Font font);
            JCVOID            setFontRegular         (JCSTR &str                 );
            JCVOID            setFontBold            (JCSTR &str                 );
            JCVOID            setFontItalic          (JCSTR &str                 );
            JCVOID            setFontBoldItalic      (JCSTR &str                 );
            JCVOID            setValign              (JDM::Font::Valign valign   );
            JCVOID            setHalign              (JDM::Font::Halign halign   );
            JCVOID            setPaddingWidth        (JCDOUBLE padWidth          );
            JCVOID            setPaddingHeight       (JCDOUBLE padHeight         );

            JCUINT            getFontSize            () JCONST;
            JCDOUBLE          getCopyFontSize        () JCONST;
            JCBOOL            getBold                () JCONST;
            JCBOOL            getItalic              () JCONST;
            JDM::Font::Valign getValign              () JCONST;
            JDM::Font::Halign getHalign              () JCONST;
            JCDOUBLE          getPaddingWidth        () JCONST;
            JCDOUBLE          getPaddingHeight       () JCONST;
            JDM::ColorRGBA    getTextAndOpacityColor () JCONST;
            JDM::ColorRGB     getTextColor           () JCONST;
            JUINT8            getTextOpacity         () JCONST;
            JUINT8            getTextColorR          () JCONST;
            JUINT8            getTextColorG          () JCONST;
            JUINT8            getTextColorB          () JCONST;
            Region            getTextRegion          () JCONST;
            RegionF           getTextDestination     () JCONST;
            SDL_Texture      *getTextTexture         ();
            JCSTR             getText                ();
        
        JPROTECTED:
            JINLINE BaseText() {}

        JPROTECTED:
            JBOOL             _willUpdateTextTexture = JFALSE;   
            JBOOL             _willUpdateTextColor   = JFALSE;     
            JBOOL             _willUpdateTextOpacity = JFALSE;

            JBOOL             _isBold                = JFALSE;
            JBOOL             _isItalic              = JFALSE;

            JSTR              _textMessage           = JEMPTYSTRING;
            ColorRGBA         _textColor             = {0xff, 0xff, 0xff, 0xff};
            SDL_Rect          _textSource            = {0x00, 0x00, 0x00, 0x00}; 
            SDL_FRect         _textDestination       = {0x00, 0x00, 0x00, 0x00};
            SDL_Texture      *_textTexture           = JNULLPTR;

            JUINT             _fontSize              = 0x0f;
            JDOUBLE           _copyFontSize          = 0x0f;

            JDM::Font::Valign _valign                = JDM::Font::Valign::VCENTER;
            JDM::Font::Halign _halign                = JDM::Font::Halign::HCENTER;
            JDM::Font::Font   _font                  = JDM::Font::Consolas(); 

            JDOUBLE           _paddingWidth          = JNONE;
            JDOUBLE           _paddingHeight         = JNONE;

        JPROTECTED:
            JCVOID _setTextRectDestination (JCONST JDM::PositionSize posSize);
            JCVOID _updateText             (JCONST JDM::PositionSize posSize);
            JCVOID _setTextTexture         (                                );
            JCVOID _updateTextColor        (                                );
            JCVOID _updateTextOpacity      (                                );
            JCVOID _renderText             (                                );
        };

        JCLASS Components
        {
        JPUBLIC:
            JENUM Properties
            {
                X,
                Y,
                WIDTH,
                HEIGHT,
                DISABLED,
                PICK_ON_BOUNDS,
                WILL_RENDER
            };

        JPUBLIC:
            JCBOOL              contains               (JCDOUBLE xPos, JCDOUBLE yPos                                  ) JCONST;
            JCVOID              setSizePos             (JCONST PositionSize sPos                                      );
            JCVOID              setPos                 (JCONST Position pos                                           );
            JCVOID              setSize                (JCONST Size size                                              );
            JCVOID              setX                   (JCDOUBLE xPos                                                 );
            JCVOID              setY                   (JCDOUBLE yPos                                                 );
            JCVOID              setWidth               (JCDOUBLE Width                                                );
            JCVOID              setHeight              (JCDOUBLE Height                                               );
            JCVOID              setDisabled            (JCBOOL disabled                                               );
            JCVOID              setPickOnBounds        (JCBOOL bounds                                                 );
            JCVOID              setPickOnTop           (JCBOOL top                                                    );
            JCVOID              setRendering           (JCBOOL isRendering                                            );
            JCVOID              setUpdateFunction      (JCONST JFUNCCALL function                                     );
            JCVOID              setmouseDownFunction   (JCONST JFUNCTION<JCVOID(SDL_MouseButtonEvent &mouse)> function);
            JCVOID              setmouseMotionFunction (JCONST JFUNCTION<JCVOID(SDL_MouseMotionEvent &mouse)> function);
            JCVOID              setmouseUpFunction     (JCONST JFUNCTION<JCVOID(SDL_MouseButtonEvent &mouse)> function);

            JCONST PositionSize getSizePos             () JCONST;
            JCONST Position     getPos                 () JCONST;
            JCONST Size         getSize                () JCONST;
            JCDOUBLE            getX                   () JCONST;
            JCDOUBLE            getY                   () JCONST;
            JCDOUBLE            getWidth               () JCONST;
            JCDOUBLE            getHeight              () JCONST;
            JCBOOL              getDisabled            () JCONST;
            JCBOOL              getRendering           () JCONST;
            JCBOOL              getPickOnBounds        () JCONST;
            JCBOOL              getPickOnTop           () JCONST;
            JCBOOL              getMouseClick          () JCONST;
            JDOUBLE            *getPointerX            ();
            JDOUBLE            *getPointerY            ();
            JDOUBLE            *getPointerWidth        ();
            JDOUBLE            *getPointerHeight       ();

            JVIRTUAL JUINT8    *getPointerRImage       ();
            JVIRTUAL JUINT8    *getPointerGImage       ();
            JVIRTUAL JUINT8    *getPointerBImage       ();
            JVIRTUAL JUINT8    *getPointerAImage       ();
            JVIRTUAL JUINT8    *getPointerRText        ();
            JVIRTUAL JUINT8    *getPointerGText        ();
            JVIRTUAL JUINT8    *getPointerBText        ();
            JVIRTUAL JUINT8    *getPointerAText        ();
            JVIRTUAL JCSTR      getName                () JCONST;

            JCONST JFUNCCALL                                     getUpdateFunction      () JCONST;
            JCONST JFUNCTION<JVOID(SDL_MouseButtonEvent &mouse)> getmouseDownFunction   () JCONST;
            JCONST JFUNCTION<JVOID(SDL_MouseMotionEvent &mouse)> getmouseMotionFunction () JCONST;
            JCONST JFUNCTION<JVOID(SDL_MouseButtonEvent &mouse)> getmouseUpFunction     () JCONST;

            JVIRTUAL JCBOOL         mouseDownComp   (SDL_MouseButtonEvent &mouse);
            JVIRTUAL JCVOID         mouseMotionComp (SDL_MouseMotionEvent &mouse);
            JVIRTUAL JCVOID         mouseUpComp     (SDL_MouseButtonEvent &mouse);
            JCVOID                  updateComp      (                           );
            JINLINE JVIRTUAL JCVOID renderComp      (                           ) {}            

            Components(
                JCDOUBLE xPos   = 0x00,
                JCDOUBLE yPos   = 0x00,
                JCDOUBLE width  = 0x64,
                JCDOUBLE height = 0x64
            );
            Components(
                JMAP<Properties, JSP<JDM::Object>> mapComponent
            );

        JPROTECTED:
            JCVOID                  setMouseClick (JCBOOL set);
            JINLINE JVIRTUAL JCVOID update        (          ) {}

        JPRIVATE:
            JFUNCCALL                                      _updateFunction      = [](                           ) {}; 
            JFUNCTION<JCVOID(SDL_MouseButtonEvent& mouse)> _mouseDownFunction   = [](SDL_MouseButtonEvent &mouse) {};
            JFUNCTION<JCVOID(SDL_MouseMotionEvent& mouse)> _mouseMotionFunction = [](SDL_MouseMotionEvent &mouse) {};
            JFUNCTION<JCVOID(SDL_MouseButtonEvent& mouse)> _mouseUpFunction     = [](SDL_MouseButtonEvent &mouse) {};

            JBOOL        _mouseClicked   = JFALSE;
            JBOOL        _pickOnTop      = JFALSE;
            JBOOL        _pickOnBounds   = JTRUE;
            JBOOL        _stopRendering  = JFALSE;
            JBOOL        _disabled       = JFALSE;
            PositionSize _sizePos        = {0x00, 0x00, 0x64, 0x64};
        };

        JCLASS Text : JPUBLIC Components, JPUBLIC BaseText
        {
        JPUBLIC:
            JENUM Properties
            {
                X,
                Y,
                WIDTH,
                HEIGHT,
                DISABLED,
                PICK_ON_BOUNDS,
                WILL_RENDER,
                BOLD,
                ITALIC,
                TEXT,
                TEXT_COLOR_R,
                TEXT_COLOR_G,
                TEXT_COLOR_B,
                TEXT_COLOR_A,
                TEXT_COLOR_STR,
                FONT_SIZE,
                VERTICAL_ALIGNMENT,
                HORIZONTAL_ALIGNMENT,
                PADDING_WIDTH,
                PADDING_HEIGHT
            };

        JPUBLIC:
            JUINT8        *getPointerRText () JOVERRIDE;
            JUINT8        *getPointerGText () JOVERRIDE;
            JUINT8        *getPointerBText () JOVERRIDE;
            JUINT8        *getPointerAText () JOVERRIDE;

            JCVOID         update          () JOVERRIDE;
            JCVOID         renderComp      () JOVERRIDE;

            JVIRTUAL JCSTR getName         () JCONST;

            Text(
                JCSTR                   &text     = JEMPTYSTRING,
                JCDOUBLE                 xPos     = 0x00,
                JCDOUBLE                 yPos     = 0x00,
                JCDOUBLE                 width    = 0x64,
                JCDOUBLE                 height   = 0x64,
                JCONST JDM::ColorRGBA    color    = {0xff, 0xff, 0xff, 0xff},
                JCINT                    fontSize = 0x0f,
                JCONST JDM::Font::Halign hAlign   = JDM::Font::HCENTER,
                JCONST JDM::Font::Valign vAlign   = JDM::Font::VCENTER
            );
            Text(
                JMAP<Properties, JSP<JDM::Object>> mapComponent
            );
        };

        JCLASS Image : JPUBLIC Components, JPUBLIC BaseGradient, JPUBLIC BaseImage
        {
        JPUBLIC:
            JENUM Properties
            {
                X,
                Y,
                WIDTH,
                HEIGHT,
                DISABLED,
                PICK_ON_BOUNDS,
                WILL_RENDER,
                SOURCE,
                IMAGE_COLOR_R,
                IMAGE_COLOR_G,
                IMAGE_COLOR_B,
                IMAGE_COLOR_A,
                IMAGE_COLOR_STR,
                ARC_STR,
                LINEWIDTH
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

        JCLASS Label : JPUBLIC Components, JPUBLIC BaseImage, JPUBLIC BaseText, JPUBLIC BaseGradient
        {
        JPUBLIC:
            JUINT8        *getPointerRText  () JOVERRIDE;
            JUINT8        *getPointerGText  () JOVERRIDE;
            JUINT8        *getPointerBText  () JOVERRIDE;
            JUINT8        *getPointerAText  () JOVERRIDE;
            JUINT8        *getPointerRImage () JOVERRIDE;
            JUINT8        *getPointerGImage () JOVERRIDE;
            JUINT8        *getPointerBImage () JOVERRIDE;
            JUINT8        *getPointerAImage () JOVERRIDE;

            JCVOID         update           () JOVERRIDE;
            JCVOID         renderComp       () JOVERRIDE;

            JVIRTUAL JCSTR getName          () JCONST;

            Label(
                JCSTR                   &text       = JEMPTYSTRING,
                JCSTR                   &source     = DefaultImage,
                JCDOUBLE                 xPos       = 0x00,
                JCDOUBLE                 yPos       = 0x00,
                JCDOUBLE                 width      = 0x64,
                JCDOUBLE                 height     = 0x64,
                JCONST JDM::ColorRGBA    color      = {0x00, 0x00, 0x00, 0xff},
                JCONST JDM::ColorRGBA    colorImage = {0xff, 0xff, 0xff, 0xff},
                JCONST FourArc           arc        = {0x00, 0x00, 0x00, 0x00},
                JCINT                    fontSize   = 0x0f,
                JCONST JDM::Font::Halign hAlign     = JDM::Font::HCENTER,
                JCONST JDM::Font::Valign vAlign     = JDM::Font::VCENTER
            );
        };

        JCLASS Button : JPUBLIC Label
        {
        JPUBLIC:
            JCVOID setOriginalColor (JCONST ColorRGBA &color    );
            JCVOID setClickedColor  (JCONST ColorRGBA &color    );
            JCVOID setHoverColor    (JCONST ColorRGBA &color    );
            JCVOID setIsHoverable   (JCBOOL isHoverable         );
            JCVOID mouseUpComp      (SDL_MouseButtonEvent &mouse) JOVERRIDE;
            JCVOID update           (                           ) JOVERRIDE;
            JCBOOL mouseDownComp    (SDL_MouseButtonEvent &mouse) JOVERRIDE;
            JCBOOL getIsHoverable   (                           ) JCONST;

            Button(
                JCSTR                   &text       = JEMPTYSTRING,
                JCSTR                   &source     = DefaultImage,
                JCDOUBLE                 xPos       = 0x00,
                JCDOUBLE                 yPos       = 0x00,
                JCDOUBLE                 width      = 0x64,
                JCDOUBLE                 height     = 0x64,
                JCONST JDM::ColorRGBA    color      = {0x00, 0x00, 0x00, 0x00},
                JCONST JDM::ColorRGBA    colorImage = {0xff, 0xff, 0xff, 0xff},
                JCONST FourArc           arc        = {0x00, 0x00, 0x00, 0x00},
                JCINT                    fontSize   = 0x0f,
                JCONST JDM::Font::Halign hAlign     = JDM::Font::HCENTER,
                JCONST JDM::Font::Valign vAlign     = JDM::Font::VCENTER,
                JCONST ColorRGBA         colorClick = {0x32, 0x32, 0x32, 0xff},
                JCONST ColorRGBA         colorHover = {0xff, 0xff, 0xff, 0xff}
            );

        JPRIVATE:
            ColorRGBA _originalColor = {0x64, 0x64, 0x64, 0xff};
            ColorRGBA _clickedColor  = {0x32, 0x32, 0x32, 0xff};
            ColorRGBA _hoverColor    = {0xff, 0xff, 0xff, 0xff};

            JBOOL     _clicked       = JFALSE;
            JBOOL     _isHoverable   = JFALSE;
        };

        JCLASS FocusedTextComponent : JPUBLIC Label
        {
        JPUBLIC:
            JBOOL     isFocused     = JFALSE;
            JINT      index         = -1;
            JFUNCCALL functionEnter = []() {};
        
        JPUBLIC:
            JCSTR getName() JCONST JOVERRIDE;

        JPROTECTED:
            FocusedTextComponent(
                JCSTR                   &text       = JEMPTYSTRING,
                JCSTR                   &source     = DefaultImage,
                JCDOUBLE                 xPos       = 0x00,
                JCDOUBLE                 yPos       = 0x00,
                JCDOUBLE                 width      = 0x64,
                JCDOUBLE                 height     = 0x64,
                JCONST JDM::ColorRGBA    color      = {0x11, 0x11, 0x11, 0x11},
                JCONST JDM::ColorRGBA    colorImage = {0xcc, 0xcc, 0xcc, 0xcc},
                JCONST FourArc           arc        = {0x1e, 0x1e, 0x1e, 0x1e},
                JCINT                    fontSize   = 0x0f,
                JCONST JDM::Font::Halign hAlign     = JDM::Font::LEFT,
                JCONST JDM::Font::Valign vAlign     = JDM::Font::VCENTER
            );
        
        };

        JCLASS TextInput : JPUBLIC FocusedTextComponent
        {
        JPUBLIC:
            JCVOID setCursorColor(JCONST ColorRGBA color);
            JCVOID renderComp    (                      ) JOVERRIDE;

            TextInput(
                JCSTR                   &text       = JEMPTYSTRING,
                JCSTR                   &source     = DefaultImage,
                JCDOUBLE                 xPos       = 0x00,
                JCDOUBLE                 yPos       = 0x00,
                JCDOUBLE                 width      = 0x64,
                JCDOUBLE                 height     = 0x64,
                JCONST JDM::ColorRGBA    color      = {0x11, 0x11, 0x11, 0x11},
                JCONST JDM::ColorRGBA    colorImage = {0xcc, 0xcc, 0xcc, 0xcc},
                JCONST FourArc           arc        = {0x1e, 0x1e, 0x1e, 0x1e},
                JCINT                    fontSize   = 0x0f,
                JCONST JDM::Font::Halign hAlign     = JDM::Font::LEFT,
                JCONST JDM::Font::Valign vAlign     = JDM::Font::VCENTER
            );            

        JPRIVATE:
            JBOOL     _blinked       = JFALSE;
            JDOUBLE   _blinkDuration = 0.3;
            JDOUBLE   _currentBlink  = _blinkDuration;
            ColorRGBA _colorCursor   = {0xb4, 0xb4, 0xb4, 0xff};
        };
    }
}

#endif