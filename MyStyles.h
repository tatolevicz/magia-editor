#ifndef MYHTMLSTYLE_H
#define MYHTMLSTYLE_H

#include "ScintillaEdit.h"
#include <SciLexer.h>

//#include ""
namespace mystyles {

    struct Colors {
        inline static int WHITE = 0xFFFFFF;
        inline static int GREY = 0x808080;
        inline static int RED = 0x0000FF;
        inline static int GREEN = 0x00FF00;
        inline static int BLUE = 0xFF0000;
        inline static int YELLOW = 0x00FFFF;
        inline static int CYAN = 0xFFFF00;
        inline static int MAGENTA = 0xFF00FF;
        inline static int ORANGE = 0x00A5FF;
        inline static int BROWN = 0x2A2AA5;
        inline static int PINK = 0xCBC0FF;
        inline static int PURPLE = 0x800080;
        inline static int LIME = 0x00FF00;
        inline static int OLIVE = 0x008080;
        inline static int TEAL = 0x808000;
        inline static int NAVY = 0x800000;
        inline static int MAROON = 0x000080;
        inline static int CORAL = 0x507FFF;
        inline static int KHAKI = 0x8CE6F0;
        inline static int VIOLET = 0xEE82EE;
        inline static int LIGHT_GREY = 0xD3D3D3;
    };



   struct editor{
        inline static void setDefaultStyle(ScintillaEdit* editor){
            editor->styleSetBack(STYLE_DEFAULT, 0x212121);
            editor->styleClearAll(); //this copies the defualt style to all the others
            editor->setCaretFore(0xAAAAAA);
        }
   };

   struct lua{
       inline static void setDefaultStyle(ScintillaEdit* editor){

           // Configurações de cores e estilos para o lexer Lua ajustadas para BGR
           editor->styleSetFore(SCE_LUA_DEFAULT, Colors::WHITE); // Cinza claro para texto padrão
           editor->styleSetBold(SCE_LUA_DEFAULT, true);

           editor->styleSetFore(SCE_LUA_COMMENT, Colors::GREY);
           editor->styleSetBold(SCE_LUA_COMMENT, true);

           editor->styleSetFore(SCE_LUA_COMMENTLINE, Colors::RED);
           editor->styleSetBold(SCE_LUA_COMMENTLINE, true);

           editor->styleSetFore(SCE_LUA_COMMENTDOC,Colors::GREEN);
           editor->styleSetBold(SCE_LUA_COMMENTDOC, true);

           editor->styleSetFore(SCE_LUA_NUMBER, Colors::BLUE);
           editor->styleSetBold(SCE_LUA_NUMBER, true);

           editor->styleSetFore(SCE_LUA_WORD, Colors::YELLOW);
           editor->styleSetBold(SCE_LUA_WORD, true);

           editor->styleSetFore(SCE_LUA_STRING, Colors::CYAN);
           editor->styleSetBold(SCE_LUA_STRING, true);

           editor->styleSetFore(SCE_LUA_CHARACTER, Colors::MAGENTA);
           editor->styleSetBold(SCE_LUA_CHARACTER, true);

           editor->styleSetFore(SCE_LUA_LITERALSTRING, Colors::ORANGE);
           editor->styleSetBold(SCE_LUA_LITERALSTRING, true);

           editor->styleSetFore(SCE_LUA_PREPROCESSOR, Colors::BROWN);
           editor->styleSetBold(SCE_LUA_PREPROCESSOR, true);

           editor->styleSetFore(SCE_LUA_OPERATOR,  Colors::PINK);
           editor->styleSetBold(SCE_LUA_OPERATOR, true);

           editor->styleSetFore(SCE_LUA_IDENTIFIER,  Colors::PURPLE);
           editor->styleSetBold(SCE_LUA_IDENTIFIER, true);

           editor->styleSetFore(SCE_LUA_STRINGEOL,Colors::LIME);
           editor->styleSetBold(SCE_LUA_STRINGEOL, true);

           editor->styleSetFore(SCE_LUA_WORD2, Colors::OLIVE);
           editor->styleSetBold(SCE_LUA_WORD2, true);

           editor->styleSetFore(SCE_LUA_WORD3, Colors::TEAL);
           editor->styleSetBold(SCE_LUA_WORD3, true);

           editor->styleSetFore(SCE_LUA_WORD4, Colors::NAVY);
           editor->styleSetBold(SCE_LUA_WORD4, true);

           editor->styleSetFore(SCE_LUA_WORD5, Colors::MAROON);
           editor->styleSetBold(SCE_LUA_WORD5, true);

           editor->styleSetFore(SCE_LUA_WORD6, Colors::CORAL);
           editor->styleSetBold(SCE_LUA_WORD6, true);

           editor->styleSetFore(SCE_LUA_WORD7, Colors::KHAKI);
           editor->styleSetBold(SCE_LUA_WORD7, true);

           editor->styleSetFore(SCE_LUA_WORD8, Colors::VIOLET);
           editor->styleSetBold(SCE_LUA_WORD8, true);

           editor->styleSetFore(SCE_LUA_LABEL, Colors::LIGHT_GREY);
           editor->styleSetBold(SCE_LUA_LABEL, true);

           editor->setKeyWords(1,"local print function");
           editor->setKeyWords(2,"if then end");
       }
   };

}
#endif // MYHTMLSTYLE_H
