#ifndef MYHTMLSTYLE_H
#define MYHTMLSTYLE_H

#include "ScintillaEdit.h"
#include <SciLexer.h>

//#include ""
namespace mystyles {

    struct LuaEditorColors {
        inline static int PRE_PROC = 0xDDB26D; // Funções e métodos
        inline static int IDENTIFIER = 0xE7BEB4; // Identificadores
        inline static int KEYWORD = 0x65BD91; // Palavras-chave (preto para destaque)
        inline static int FOLDING_WORDS = 0xB46981; // Funções e métodos
        inline static int COMMENT = 0x79554C; // Comentários
        inline static int DARK_BACKGROUND = 0x2C1E1B; // Cor de fundo do editor
        inline static int BACKGROUND = 0x3B2824; // Cor de fundo do editor
        inline static int LINE_ACIVE = 0x422E29;
        inline static int STRING = 0xCBB129; // Strings
        inline static int KNOWN_FUNCTION = 0x6193E9; // Funções e métodos
        inline static int ERRORS = 0x4B4BDB;
        inline static int NUMBER = 0x68AFE0; // Números
        inline static int OPEN_STRING = 0xE7BEB4; // Strings
        inline static int OPERATOR = 0xE7BEB4; // Operadores
        inline static int CONSTANT = 0xAAB362; // Constantes (nil, true, false)

    };

//    struct Colors {
//        inline static int WHITE = 0xFFFFFF;
//        inline static int GREY = 0x808080;
//        inline static int DARK_GREY = 0x404040;
//        inline static int RED = 0x0000FF;
//        inline static int GREEN = 0x00FF00;
//        inline static int BLUE = 0xFF0000;
//        inline static int YELLOW = 0x00FFFF;
//        inline static int CYAN = 0xFFFF00;
//        inline static int MAGENTA = 0xFF00FF;
//        inline static int ORANGE = 0x00A5FF;
//        inline static int BROWN = 0x2A2AA5;
//        inline static int PINK = 0xCBC0FF;
//        inline static int PURPLE = 0x800080;
//        inline static int LIME = 0x00FF00;
//        inline static int OLIVE = 0x008080;
//        inline static int TEAL = 0x808000;
//        inline static int NAVY = 0x800000;
//        inline static int MAROON = 0x000080;
//        inline static int CORAL = 0x507FFF;
//        inline static int KHAKI = 0x8CE6F0;
//        inline static int VIOLET = 0xEE82EE;
//        inline static int LIGHT_GREY = 0xD3D3D3;
//    };
//
//


   struct editor{
       inline static void setupFolding(ScintillaEdit* editor) {
           // Configurar a margin para dobradura (número da margin, geralmente 2 para dobradura)
           int marginId = 2;
           int marginWidth = 16; // Largura da margin em pixels

           editor->send(SCI_SETMARGINWIDTHN, marginId, marginWidth);
           editor->send(SCI_SETMARGINMASKN, marginId, SC_MASK_FOLDERS);
           editor->send(SCI_SETMARGINTYPEN, marginId, SC_MARGIN_SYMBOL);
           editor->send(SCI_SETMARGINSENSITIVEN, marginId, true);


           editor->send(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN, SC_MARK_BOXMINUS);
           editor->send(SCI_MARKERDEFINE, SC_MARKNUM_FOLDER, SC_MARK_BOXPLUS);
           editor->send(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_VLINE);
           editor->send(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_LCORNER);
           editor->send(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND, SC_MARK_BOXPLUSCONNECTED);
           editor->send(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID, SC_MARK_BOXMINUSCONNECTED);
           editor->send(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_TCORNER);



           editor->send(SCI_MARKERSETBACK, SC_MARKNUM_FOLDER, LuaEditorColors::LINE_ACIVE);
           editor->send(SCI_MARKERSETBACK, SC_MARKNUM_FOLDEROPEN, LuaEditorColors::LINE_ACIVE);
           editor->send(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERSUB, LuaEditorColors::LINE_ACIVE);
           editor->send(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERTAIL, LuaEditorColors::LINE_ACIVE);
           editor->send(SCI_MARKERSETBACK, SC_MARKNUM_FOLDEREND, LuaEditorColors::LINE_ACIVE);
           editor->send(SCI_MARKERSETBACK, SC_MARKNUM_FOLDEROPENMID, LuaEditorColors::LINE_ACIVE);
           editor->send(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERMIDTAIL, LuaEditorColors::LINE_ACIVE);

           // Definir a cor de frente (foreground) do marcador de dobradura
           editor->send(SCI_MARKERSETFORE, SC_MARKNUM_FOLDER, LuaEditorColors::COMMENT);
           editor->send(SCI_MARKERSETFORE, SC_MARKNUM_FOLDEROPEN, LuaEditorColors::COMMENT);
           editor->send(SCI_MARKERSETFORE, SC_MARKNUM_FOLDERSUB, LuaEditorColors::COMMENT);
           editor->send(SCI_MARKERSETFORE, SC_MARKNUM_FOLDERTAIL, LuaEditorColors::COMMENT);
           editor->send(SCI_MARKERSETFORE, SC_MARKNUM_FOLDEREND, LuaEditorColors::COMMENT);
           editor->send(SCI_MARKERSETFORE, SC_MARKNUM_FOLDEROPENMID, LuaEditorColors::COMMENT);
           editor->send(SCI_MARKERSETFORE, SC_MARKNUM_FOLDERMIDTAIL, LuaEditorColors::COMMENT);

           editor->setFoldMarginColour(true, LuaEditorColors::DARK_BACKGROUND);
           editor->setFoldMarginHiColour(true, LuaEditorColors::DARK_BACKGROUND);

           // Habilitar dobradura
           editor->send(SCI_SETPROPERTY, (uptr_t)"fold", (sptr_t)"1");
           editor->send(SCI_SETPROPERTY, (uptr_t)"fold.compact", (sptr_t)"1");

       }

        inline static void setDefaultStyle(ScintillaEdit* editor){
            editor->styleSetBack(STYLE_DEFAULT, LuaEditorColors::DARK_BACKGROUND);
            editor->styleSetFont(STYLE_DEFAULT, "Courier New");
            editor->styleSetSize(STYLE_DEFAULT, 16);
            editor->styleClearAll(); //this copies the defualt style to all the others

            editor->setCaretFore(LuaEditorColors::IDENTIFIER);
            editor->setCaretLineBack(LuaEditorColors::LINE_ACIVE);  // Define a cor de fundo para o destaque
            editor->setCaretLineFrame(1.0);

            editor->styleSetBack(STYLE_LINENUMBER, LuaEditorColors::BACKGROUND); // Cinza para fundo
            editor->styleSetFore(STYLE_LINENUMBER, LuaEditorColors::COMMENT); // Branco para texto
//            editor->styleSetFont(STYLE_LINENUMBER, "Courier New");
//            editor->styleSetFont(STYLE_LINENUMBER, "Poppins");
            editor->styleSetSize(STYLE_LINENUMBER, 12);

            editor->setMarginTypeN(1, SC_MARGIN_NUMBER);
            editor->setMarginWidthN(1,25);
            editor->setMarginMaskN(1, 0); // nao permite a renderizacao de marcadores na margem 1

            editor->setMarginWidthN(0,30);
            editor->setMarginTypeN(0, SC_MARGIN_COLOUR);
            editor->setMarginMaskN(0, 1 << 1); // Permite o marcador 1 na margem 0

            setupFolding(editor);
//
            int markerBreakpoint = 1; // Escolha um número de índice para o marcador de breakpoint
            editor->markerDefine(markerBreakpoint, SC_MARK_CIRCLE);
            editor->markerSetFore(markerBreakpoint, LuaEditorColors::ERRORS); // Cor azul para o símbolo
            editor->markerSetBack(markerBreakpoint, LuaEditorColors::ERRORS); //

            editor->setMarginBackN(0, LuaEditorColors::BACKGROUND);
        }
   };



   struct lua{
       inline static void setDefaultStyle(ScintillaEdit* editor){

           editor->styleSetFore(SCE_LUA_DEFAULT, LuaEditorColors::IDENTIFIER);
           editor->styleSetBold(SCE_LUA_DEFAULT, true);

           editor->styleSetFore(SCE_LUA_COMMENT, LuaEditorColors::COMMENT);
           editor->styleSetBold(SCE_LUA_COMMENT, true);

           editor->styleSetFore(SCE_LUA_COMMENTLINE, LuaEditorColors::COMMENT);
           editor->styleSetBold(SCE_LUA_COMMENTLINE, true);

           editor->styleSetFore(SCE_LUA_NUMBER, LuaEditorColors::NUMBER);
           editor->styleSetBold(SCE_LUA_NUMBER, true);

           editor->styleSetFore(SCE_LUA_WORD, LuaEditorColors::KEYWORD);
           editor->styleSetBold(SCE_LUA_WORD, true);

           editor->styleSetFore(SCE_LUA_STRING, LuaEditorColors::STRING);
           editor->styleSetBold(SCE_LUA_STRING, true);

           editor->styleSetFore(SCE_LUA_CHARACTER, LuaEditorColors::STRING);
           editor->styleSetBold(SCE_LUA_CHARACTER, true);

           editor->styleSetFore(SCE_LUA_LITERALSTRING, LuaEditorColors::STRING);
           editor->styleSetBold(SCE_LUA_LITERALSTRING, true);

           editor->styleSetFore(SCE_LUA_PREPROCESSOR, LuaEditorColors::PRE_PROC);
           editor->styleSetBold(SCE_LUA_PREPROCESSOR, true);

           editor->styleSetFore(SCE_LUA_OPERATOR,  LuaEditorColors::OPERATOR);
           editor->styleSetBold(SCE_LUA_OPERATOR, true);

           editor->styleSetFore(SCE_LUA_IDENTIFIER, LuaEditorColors::IDENTIFIER);
           editor->styleSetBold(SCE_LUA_IDENTIFIER, false);

           editor->styleSetFore(SCE_LUA_STRINGEOL,LuaEditorColors::OPEN_STRING);
           editor->styleSetBold(SCE_LUA_STRINGEOL, true);

           editor->styleSetFore(SCE_LUA_WORD2, LuaEditorColors::KNOWN_FUNCTION);
           editor->styleSetBold(SCE_LUA_WORD2, true);

           editor->styleSetFore(SCE_LUA_WORD3, LuaEditorColors::CONSTANT);
           editor->styleSetBold(SCE_LUA_WORD3, true);

//           editor->styleSetFore(SCE_LUA_WORD4, Colors::NAVY);
//           editor->styleSetBold(SCE_LUA_WORD4, true);
//
//           editor->styleSetFore(SCE_LUA_WORD5, Colors::MAROON);
//           editor->styleSetBold(SCE_LUA_WORD5, true);
//
//           editor->styleSetFore(SCE_LUA_WORD6, Colors::CORAL);
//           editor->styleSetBold(SCE_LUA_WORD6, true);
//
//           editor->styleSetFore(SCE_LUA_WORD7, Colors::KHAKI);
//           editor->styleSetBold(SCE_LUA_WORD7, true);

//           editor->styleSetFore(SCE_LUA_WORD8, Colors::VIOLET);
//           editor->styleSetBold(SCE_LUA_WORD8, true);
//
//           editor->styleSetFore(SCE_LUA_LABEL, Colors::LIGHT_GREY);
//           editor->styleSetBold(SCE_LUA_LABEL, true);

           editor->setKeyWords(1,"print");//todo load here know functions
           editor->setKeyWords(2,"and break false for in local nil not or repeat return true");
       }
   };

}
#endif // MYHTMLSTYLE_H
