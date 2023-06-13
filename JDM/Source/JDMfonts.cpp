#include "JDM/Header/JDMfonts.hpp"

JDM::Font::Consolas::Consolas()
{
    JTHIS->Normal     = "C:/SDL/Template/JDM/DLL/Assets/Font/consolas/consolas_regular.ttf";
    JTHIS->Italic     = "C:/SDL/Template/JDM/DLL/Assets/Font/consolas/consolas_italic.ttf";
    JTHIS->Bold       = "C:/SDL/Template/JDM/DLL/Assets/Font/consolas/consolas_bold.ttf";
    JTHIS->ItalicBold = "C:/SDL/Template/JDM/DLL/Assets/Font/consolas/consolas_italic_bold.ttf";
}

JNAMESPACE JDM
{
    JNAMESPACE Font
    {
        JDM::Font::Font getFont(AvailableFont fontName)
        {
            JSWITCH (fontName)
            {
                JCASE AvailableFont::CONSOLAS:
                    JRETURN JDM::Font::Consolas();
                JDEFAULT:
                    JRETURN JDM::Font::Consolas();
            }
        }

    }
}
